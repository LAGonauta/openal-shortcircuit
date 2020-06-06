#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <cstring>
#include <unordered_map>

#include "ShortCircuit.hpp"
#include "Router.hpp"
#include "OpenALEnum.h"
#include "Utils.hpp"
#include "XRamManager.hpp"

extern Short::Circuit short_;
extern bool is_xfi;

bool source_distance_model = false;
std::unordered_map<ALuint, ALfloat> sources_no_attenuation;

XRamManager xram_manager;

DLL_LOCAL std::string DistanceModelToName(ALenum model)
{
    switch (model)
    {
        case OpenALEnum::AL_EXPONENT_DISTANCE:
            return "ExponentDistance";
        case OpenALEnum::AL_EXPONENT_DISTANCE_CLAMPED:
            return "ExponentDistanceClamped";
        case OpenALEnum::AL_INVERSE_DISTANCE:
            return "InverseDistance";
        case OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED:
            return "InverseDistanceClamped";
        case OpenALEnum::AL_LINEAR_DISTANCE:
            return "LinearDistance";
        case OpenALEnum::AL_LINEAR_DISTANCE_CLAMPED:
            return "LinearDistanceClamped";
        case OpenALEnum::AL_NONE:
            return "None";
    }

    return std::to_string(model);
}

auto global_distance_model = OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED;
DLL_PUBLIC void DLL_ENTRY alDistanceModel(ALenum distanceModel)
{
    global_distance_model = distanceModel;
    short_.functions.alDistanceModel(distanceModel);
};

DLL_PUBLIC void DLL_ENTRY alEnable(ALenum capability)
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
    
    return short_.functions.alEnable(capability);
}

DLL_PUBLIC void DLL_ENTRY alDisable(ALenum capability)
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
    
    return short_.functions.alDisable(capability);
}

DLL_PUBLIC ALboolean DLL_ENTRY alIsEnabled(ALenum capability)
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
    
    return short_.functions.alIsEnabled(capability);
}

std::string alGetStringExtension;
DLL_PUBLIC const ALchar* DLL_ENTRY alGetString(ALenum param)
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
            auto all_extensions = string_unwrap(short_.functions.alGetString(param), "\n");
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
    return short_.functions.alGetString(param);
}

DLL_PUBLIC ALboolean DLL_ENTRY alIsExtensionPresent(const ALchar *extname)
{
    if (is_xfi)
    {
        if (strncmp(extname, "AL_EXT_source_distance_model", 25) == 0) return true;
    }
    return short_.functions.alIsExtensionPresent(extname);
}

DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint* sources)
{
    for (size_t i = 0; i < n; ++i) sources_no_attenuation.erase(sources[i]);
    short_.functions.alDeleteSources(n, sources);
}

DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value)
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

    short_.functions.alSourcef(source, param, value);
}

ALenum last_model = OpenALEnum::AL_NONE;
DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value)
{
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_DISTANCE_MODEL:
                if (value != OpenALEnum::AL_NONE && value != last_model)
                {
                    last_model = value;
                    alDistanceModel(value); // set globally
                }

                if (value == OpenALEnum::AL_NONE)
                {
                    sources_no_attenuation.insert(std::make_pair(source, 0.0f));
                    short_.functions.alSourcef(source, OpenALEnum::AL_ROLLOFF_FACTOR, 0.0f); // force no attenuation
                }
                else
                {
                    // Re-add attenuation if source is reutilized
                    auto vl = sources_no_attenuation.find(source);
                    if (vl != sources_no_attenuation.end())
                    {
                        short_.functions.alSourcef(source, OpenALEnum::AL_ROLLOFF_FACTOR, vl->second);
                        sources_no_attenuation.erase(source);
                    }
                }
                
                return;
        }
    }
    
    return short_.functions.alSourcei(source, param, value);
}

DLL_PUBLIC void DLL_ENTRY alGenBuffers(ALsizei n, ALuint *buffers)
{
    short_.functions.alGenBuffers(n, buffers);
    if (is_xfi) xram_manager.SetXRamMode(n, buffers);
}

DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname)
{
    if (is_xfi)
    {
        if (strncmp(fname, "alDistanceModel", 16) == 0) return reinterpret_cast<void*>(&alDistanceModel);
        else if (strncmp(fname, "alGetString", 12) == 0) return reinterpret_cast<void*>(&alGetString);
        else if (strncmp(fname, "alIsExtensionPresent", 21) == 0) return reinterpret_cast<void*>(&alIsExtensionPresent);
        else if (strncmp(fname, "alEnable", 9) == 0) return reinterpret_cast<void*>(&alEnable);
        else if (strncmp(fname, "alDisable", 10) == 0) return reinterpret_cast<void*>(&alDisable);
        else if (strncmp(fname, "alIsEnabled", 12) == 0) return reinterpret_cast<void*>(&alIsEnabled);
        else if (strncmp(fname, "alSourcei", 10) == 0) return reinterpret_cast<void*>(&alSourcei);
        else if (strncmp(fname, "alSourcef", 10) == 0) return reinterpret_cast<void*>(&alSourcef);
        else if (strncmp(fname, "alGenBuffers", 13) == 0) return reinterpret_cast<void*>(&alGenBuffers);
    }

    return short_.functions.alGetProcAddress(fname);
}