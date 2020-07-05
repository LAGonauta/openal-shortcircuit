#include <algorithm>

#include "ALManager.hpp"

#include "Utils.hpp"

ALManager::ALManager(Short::Circuit* short_, bool is_xfi)
{
    this->is_xfi = is_xfi;
    this->short_ = short_;
    xram_manager = std::make_unique<XRamManager>(short_);
}

void ALManager::alDistanceModel(ALenum distanceModel)
{
    source_distance_model = distanceModel;
    short_->functions.alDistanceModel(distanceModel);
}

void ALManager::alEnable(ALenum capability)
{
    if (is_xfi)
    {
        switch (capability)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
                source_distance_model = true;
                return;
        }
    }
    
    return short_->functions.alEnable(capability);
}

void ALManager::alDisable(ALenum capability)
{
    if (is_xfi)
    {
        switch (capability)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
                source_distance_model = false;
                return;
        }
    }
    
    return short_->functions.alDisable(capability);
}

ALboolean ALManager::alIsEnabled(ALenum capability)
{
    //std::cout << "Using alIsEnabled: " << capability << std::endl;
    if (is_xfi)
    {
        switch (capability)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
                return source_distance_model;
        }
    }
    
    return short_->functions.alIsEnabled(capability);
}

const ALchar* ALManager::alGetString(ALenum param)
{
    //std::cout << "Using alGetString: " << param << std::endl;
    if (is_xfi)
    {
        switch (param)
        {
        case OpenALEnum::AL_VERSION:
            return "1.1";
        
        case OpenALEnum::AL_EXTENSIONS:
            std::array<std::string, 5> custom {"AL_EXT_EXPONENT_DISTANCE", "AL_EXT_LINEAR_DISTANCE", "AL_EXT_MCFORMATS", "AL_EXT_OFFSET", "AL_EXT_source_distance_model"};
            auto all_extensions = string_unwrap(short_->functions.alGetString(param), "\n");
            std::copy_if(
                custom.begin(),
                custom.end(),
                std::back_inserter(all_extensions),
                [=](const std::string& value) { return std::find(all_extensions.begin(), all_extensions.end(), value) == all_extensions.end(); }
                );
            alGetStringExtension = string_join(all_extensions, ' ');
            return alGetStringExtension.c_str();
            break;
        }
    }
    return short_->functions.alGetString(param);
}

ALboolean ALManager::alIsExtensionPresent(const ALchar* extname)
{
    if (is_xfi)
    {
        if (strncmp(extname, "AL_EXT_source_distance_model", 25) == 0) return true;
    }
    return short_->functions.alIsExtensionPresent(extname);
}


void ALManager::alDeleteSources(ALsizei n, const ALuint* sources)
{
    for (size_t i = 0; i < n; ++i) sources_no_attenuation.erase(sources[i]);
    short_->functions.alDeleteSources(n, sources);
}

void ALManager::alSourcef(ALuint source, ALenum param, ALfloat value)
{
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_ROLLOFF_FACTOR:
                auto s = sources_no_attenuation.find(source);
                if (s != sources_no_attenuation.end())
                {
                    s->second = value; // save AL_ROLLOFF_FACTOR if source is to be reutilized after having distance model AL_NONE
                    return; // force AL_ROLLOFF_FACTOR to be zero if the source should not be attenuated
                }
                break;
        }
    }

    short_->functions.alSourcef(source, param, value);
}

void ALManager::alSourcei(ALuint source, ALenum param, ALint value)
{
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_DISTANCE_MODEL:
                if (value != OpenALEnum::AL_NONE && value != last_global_model)
                {
                    last_global_model = value;
                    alDistanceModel(value); // set globally
                }

                if (value == OpenALEnum::AL_NONE)
                {
                    sources_no_attenuation.insert(std::make_pair(source, 0.0f));
                    short_->functions.alSourcef(source, OpenALEnum::AL_ROLLOFF_FACTOR, 0.0f); // force no attenuation
                }
                else
                {
                    // Re-add attenuation if source is reutilized
                    auto vl = sources_no_attenuation.find(source);
                    if (vl != sources_no_attenuation.end())
                    {
                        short_->functions.alSourcef(source, OpenALEnum::AL_ROLLOFF_FACTOR, vl->second);
                        sources_no_attenuation.erase(source);
                    }
                }
                
                return;
        }
    }
    
    return short_->functions.alSourcei(source, param, value);
}

void ALManager::alGenBuffers(ALsizei n, ALuint *buffers)
{
    short_->functions.alGenBuffers(n, buffers);
    if (is_xfi) xram_manager->SetXRamMode(n, buffers);
}

Short::Circuit* ALManager::GetShort()
{
    return short_;
}

bool ALManager::IsXFi()
{
    return is_xfi;
}
