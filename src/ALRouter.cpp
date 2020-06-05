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

#include "SourceDistanceModelManager.hpp"

extern Short::Circuit short_;
extern bool is_xfi;

SourceDistanceModelManager x_fi_workaround;

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
                x_fi_workaround.Enable();
                x_fi_workaround.ForEachSource([](auto& source)
                {
                    if (source.second.type != global_distance_model)
                    {
                        // disable OpenAL's native attenuation for this source
                        short_.functions.alSourcef(source.first, OpenALEnum::AL_REFERENCE_DISTANCE, 1.0f);
                        short_.functions.alSourcef(source.first, OpenALEnum::AL_MAX_DISTANCE, std::numeric_limits<float>::max());
                    }
                });
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
                x_fi_workaround.Disable();
                x_fi_workaround.ForEachSource([](auto& source)
                {
                    if (source.second.type != global_distance_model)
                    {
                        // enable OpenAL's native attenuation for this source
                        short_.functions.alSourcef(source.first, OpenALEnum::AL_REFERENCE_DISTANCE, source.second.ref_distance);
                        short_.functions.alSourcef(source.first, OpenALEnum::AL_MAX_DISTANCE, source.second.max_distance);
                    }
                });
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
                return x_fi_workaround.IsEnabled();
        }
    }
    
    return short_.functions.alIsEnabled(capability);
}

DLL_PUBLIC void DLL_ENTRY alGenSources(ALsizei n, ALuint *sources)
{
    short_.functions.alGenSources(n, sources);
    if (is_xfi) for (size_t i = 0; i < n; ++i) x_fi_workaround.AttachSource(sources[i]);
}

DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint* sources)
{
    if (is_xfi) for (size_t i = 0; i < n; ++i) x_fi_workaround.DettachSource(sources[i]);
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

DLL_PUBLIC void DLL_ENTRY alListener3f(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3)
{
    if (is_xfi && param == OpenALEnum::AL_POSITION)
    {
        x_fi_workaround.SetListenerPosition(Vector3 { value1, value2, value3 });
        x_fi_workaround.ForEachSource([&](auto& source_pair)
        {
            if (source_pair.second.use_workaround)
            {
                short_.functions.alSourcef(source_pair.first, OpenALEnum::AL_GAIN, x_fi_workaround.CalculateFinalGain(source_pair.second));
            }
        });
    }
        
    short_.functions.alListener3f(param, value1, value2, value3);
}

DLL_PUBLIC void DLL_ENTRY alSource3f(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3)
{
    if (is_xfi && param == OpenALEnum::AL_POSITION)
    {
        x_fi_workaround.ForSource(source, [&](SourceSettings& settings)
        {
            settings.position = Vector3 { value1, value2, value3 };
            if (settings.use_workaround) short_.functions.alSourcef(source, OpenALEnum::AL_GAIN, x_fi_workaround.CalculateFinalGain(settings));
        });
    }
        
    short_.functions.alSource3f(source, param, value1, value2, value3);
}

DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value)
{
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_DISTANCE_MODEL:
                x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                {
                    settings.use_workaround = global_distance_model != value;
                    settings.type = value;
                    if (settings.type != global_distance_model && x_fi_workaround.IsEnabled())
                    {
                        // disable OpenAL's native attenuation for this source
                        short_.functions.alSourcef(source, OpenALEnum::AL_REFERENCE_DISTANCE, 1.0f);
                        short_.functions.alSourcef(source, OpenALEnum::AL_MAX_DISTANCE, std::numeric_limits<float>::max());
                    }
                });
                break;
            case OpenALEnum::AL_SOURCE_RELATIVE:
                {
                    x_fi_workaround.ForSource(source, [=] (SourceSettings& settings) { settings.source_relative = value; });
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
DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value)
{
    bool using_workaround = false;
    if (is_xfi)
    {
        switch (param)
        {
            case OpenALEnum::AL_GAIN:
                    x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    {
                        settings.additional_gain = value;
                        using_workaround = settings.use_workaround;
                    });
                    break;
            case OpenALEnum::AL_MIN_GAIN:
                    // x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    // {
                    //     settings.additional_gain = value;
                    //     using_workaround = settings.use_workaround;
                    // });
                    break;
            case OpenALEnum::AL_MAX_GAIN:
                    // x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    // {
                    //     settings.additional_gain = value;
                    //     using_workaround = settings.use_workaround;
                    // });
                    break;
            case OpenALEnum::AL_MAX_DISTANCE:
                    x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    {
                        settings.max_distance = value;
                        using_workaround = settings.use_workaround;
                    });
                    break;
            case OpenALEnum::AL_REFERENCE_DISTANCE:
                    x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    {
                        settings.ref_distance = value;
                        using_workaround = settings.use_workaround;
                    });
                    break;
            case OpenALEnum::AL_ROLLOFF_FACTOR:
                    x_fi_workaround.ForSource(source, [&] (SourceSettings& settings)
                    {
                        settings.rolloff_factor = value;
                        using_workaround = settings.use_workaround;
                    });
                    break;
        }
    }

    if (!using_workaround)
    {
        short_.functions.alSourcef(source, param, value);
    }
}

// Hook for: AL_POSITION when emulating
DLL_PUBLIC void DLL_ENTRY alSourcefv(ALuint source, ALenum param, const ALfloat *values)
{
    if (is_xfi && param == OpenALEnum::AL_POSITION) x_fi_workaround.ForSource(source, [=](SourceSettings& settings) { settings.position = Vector3 { values[0], values[1], values[2] }; });
    short_.functions.alSourcefv(source, param, values);
}

DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname)
{
    if (is_xfi)
    {
        if (strncmp(fname, "alGetString", 12) == 0) return reinterpret_cast<void*>(&alGetString);
        if (strncmp(fname, "alIsExtensionPresent", 21) == 0) return reinterpret_cast<void*>(&alIsExtensionPresent);
        if (strncmp(fname, "alSourcei", 10) == 0) return reinterpret_cast<void*>(&alSourcei);
        if (strncmp(fname, "alSourcef", 10) == 0) return reinterpret_cast<void*>(&alSourcef);
        if (strncmp(fname, "alSourceiv", 11) == 0) return reinterpret_cast<void*>(&alSourceiv);
        // if (strncmp(fname, "alGetError", 21) == 0) return reinterpret_cast<void*>(&alGetError);
    }

    return short_.functions.alGetProcAddress(fname);
}