#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>

#include "ShortCircuit.hpp"
#include "Router.hpp"
#include "OpenALEnum.h"

#include "Utils.hpp"

extern Short::Circuit short_;
extern bool is_xfi;

DLL_PUBLIC ALCdevice* DLL_ENTRY alcOpenDevice(const ALCchar *devicename)
{
    const char* device_name = std::getenv("SC_OAL_LIBRARY_DEVICE_NAME");
    if (device_name == nullptr)
    {
        device_name = devicename;
    }
    return short_.functions.alcOpenDevice(device_name);
}

DLL_PUBLIC ALCboolean DLL_ENTRY alcMakeContextCurrent(ALCcontext *context)
{
    auto result = short_.functions.alcMakeContextCurrent(context);
    if (context && result)
    {
        auto renderer = short_.functions.alGetString(OpenALEnum::AL_RENDERER);
        is_xfi = strstr(renderer, "X-Fi") != nullptr;
    }
    return result;
}

std::string alcGetStringExtension;
DLL_PUBLIC const ALCchar* DLL_ENTRY alcGetString(ALCdevice *device, ALCenum param)
{
    if (is_xfi)
    {
        switch (param)
        {
        case OpenALEnum::ALC_EXTENSIONS:
            std::array<std::string, 4> custom {"ALC_EXT_EFX", "ALC_ENUMERATE_ALL_EXT", "ALC_ENUMERATION_EXT", "ALC_EXT_CAPTURE"};
            auto all_extensions = string_unwrap(short_.functions.alcGetString(device, param), "\n");
            std::copy_if(
                custom.begin(),
                custom.end(),
                std::back_inserter(all_extensions),
                [=](const std::string& value) { return std::find(all_extensions.begin(), all_extensions.end(), value) == all_extensions.end(); }
                );
            alcGetStringExtension = string_join(all_extensions, ' ');
            return alcGetStringExtension.c_str();
            break;
        }
    }
     
    return short_.functions.alcGetString(device, param);
}

DLL_PUBLIC ALCvoid* DLL_ENTRY alcGetProcAddress(ALCdevice *device, const ALCchar *funcname)
{
    if (strncmp(funcname, "alcGetString", 13) == 0) return reinterpret_cast<void*>(&alcGetString);
    if (strncmp(funcname, "alcMakeContextCurrent", 22) == 0) return reinterpret_cast<void*>(&alcMakeContextCurrent);
    if (strncmp(funcname, "alcOpenDevice", 14) == 0) return reinterpret_cast<void*>(&alcOpenDevice);
    return short_.functions.alcGetProcAddress(device, funcname);
}