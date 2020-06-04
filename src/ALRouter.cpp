#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <cstring>

#include "ShortCircuit.hpp"
#include "Router.hpp"
#include "OpenALEnum.h"
#include "Utils.hpp"

extern Short::Circuit short_;
extern bool is_xfi;
struct distModelConfig
{
    ALenum type = OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED;
    float custom_gain = 1.0f;
    float max_distance;
    float ref_distance;
    bool source_relative = false;
};
struct
{
    std::unordered_map<ALuint, distModelConfig> source_map;
    bool emulate_source_distance_model = false;
} x_fi_workaround;


// DLL_PUBLIC void DLL_ENTRY alDistanceModel(ALenum distanceModel) { short_.functions.alDistanceModel(distanceModel) };
DLL_PUBLIC void DLL_ENTRY alEnable(ALenum capability)
{
    if (is_xfi)
    {
        switch (capability)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
                x_fi_workaround.emulate_source_distance_model = true;
                // enable manual distance/gain control
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
                x_fi_workaround.emulate_source_distance_model = false;
                // disable manual distance/gain control
                return;
        }
    }
    
    return short_.functions.alDisable(capability);
}

DLL_PUBLIC ALboolean DLL_ENTRY alIsEnabled(ALenum capability)
{
    if (is_xfi)
    {
        switch (capability)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
                return x_fi_workaround.emulate_source_distance_model;
        }
    }
    
    return short_.functions.alIsEnabled(capability);
}

DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint* sources)
{
    if (is_xfi) for (size_t i = 0; i < n; ++i) x_fi_workaround.source_map.erase(sources[i]);
    return short_.functions.alDeleteSources(n, sources);
}

std::string alGetStringExtension;
DLL_PUBLIC const ALchar* DLL_ENTRY alGetString(ALenum param)
{
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

// DLL_PUBLIC ALenum DLL_ENTRY alGetError(void)
// {
//     return 0;
//     //return short_.functions.alGetError();
// }

DLL_PUBLIC ALenum DLL_ENTRY alGetEnumValue(const ALchar *ename)
{
    if (is_xfi)
    {
        if (strncmp(ename, "AL_EXT_source_distance_model", 25) == 0) return true;
    }
    return short_.functions.alGetEnumValue(ename);
};

DLL_PUBLIC ALboolean DLL_ENTRY alIsExtensionPresent(const ALchar *extname)
{
    if (is_xfi)
    {
        if (strncmp(extname, "AL_EXT_source_distance_model", 25) == 0) return true;
    }
    return short_.functions.alIsExtensionPresent(extname);
}

// DLL_PUBLIC void DLL_ENTRY alListener3f(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3) { short_.functions.alListener3f(value) };
// DLL_PUBLIC void DLL_ENTRY alSource3f(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3) { short_.functions.alDopplerFactor(value) };
DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value)
{
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_SOURCE_DISTANCE_MODEL:
            case OpenALEnum::AL_DISTANCE_MODEL:
                break;
            case OpenALEnum::AL_SOURCE_RELATIVE:
                {
                    auto src = x_fi_workaround.source_map.find(source);
                    if (src != source_map.end())
                    {
                        src->second.source_relative = value;
                    }
                    // this will be hard. TODO: Update manual source gain.
                    break;
                }
        }
    }
    
    return short_.functions.alSourcei(source, param, value);
}

DLL_PUBLIC void DLL_ENTRY alSourceiv(ALuint source, ALenum param, const ALint *values)
{
    if (is_xfi)
    {
        if (param == OpenALEnum::AL_SOURCE_DISTANCE_MODEL || param == OpenALEnum::AL_DISTANCE_MODEL)
        {
            return;
        } 
    }
    return short_.functions.alSourceiv(source, param, values);
}

// Hook for: AL_GAIN, AL_MIN_GAIN, AL_MAX_GAIN, AL_MAX_DISTANCE, AL_ROLLOFF_FACTOR, AL_REFERENCE_DISTANCE when emulating
// DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value) { short_.functions.alDopplerFactor(value) };

// Hook for: ALPOSITION when emulating
// DLL_PUBLIC void DLL_ENTRY alSourcefv(ALuint source, ALenum param, const ALfloat *values) { short_.functions.alDopplerFactor(value) };

DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname)
{
    if (strncmp(fname, "alGetString", 12) == 0) return reinterpret_cast<void*>(&alGetString);
    if (strncmp(fname, "alIsExtensionPresent", 21) == 0) return reinterpret_cast<void*>(&alIsExtensionPresent);
    if (strncmp(fname, "alSourcei", 10) == 0) return reinterpret_cast<void*>(&alSourcei);
    if (strncmp(fname, "alSourceiv", 11) == 0) return reinterpret_cast<void*>(&alSourceiv);
    // if (strncmp(fname, "alGetError", 21) == 0) return reinterpret_cast<void*>(&alGetError);
    return short_.functions.alGetProcAddress(fname);
}