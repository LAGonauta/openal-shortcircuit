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

    ALuint buffers[2];
    alGenBuffers(2, buffers);

    alSourcef(1, OpenALEnum::AL_ROLLOFF_FACTOR, 1.0f);
    alSourcei(1, OpenALEnum::AL_DISTANCE_MODEL, OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED);
    alSourcei(1, OpenALEnum::AL_DISTANCE_MODEL, OpenALEnum::AL_NONE);
    alSourcei(1, OpenALEnum::AL_DISTANCE_MODEL, OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED);
    alSourcei(1, OpenALEnum::AL_DISTANCE_MODEL, OpenALEnum::AL_NONE);
    alSourcef(1, OpenALEnum::AL_ROLLOFF_FACTOR, 1.0f);

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}