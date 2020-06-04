#include <iostream>

#include "OpenALAPI.h"
#include "OpenALEnum.h"
#include "Router.hpp"

int main (int argc, char **argv)
{
    auto device = alcOpenDevice(nullptr);
    auto context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
    auto ext = alcGetString(device, OpenALEnum::ALC_EXTENSIONS);
    std::cout << std::string(ext) << std::endl;
    ext = alGetString(OpenALEnum::AL_EXTENSIONS);
    std::cout << std::string(ext) << std::endl;

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}