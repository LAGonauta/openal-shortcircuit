#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "ShortCircuit.hpp"
#include "XRamManager.hpp"
#include "OpenALAPI.h"
#include "OpenALEnum.h"

class ALManager
{
private:
    std::unique_ptr<XRamManager> xram_manager;
    bool is_xfi = false;
    Short::Circuit* short_ = nullptr;

    std::unordered_map<ALuint, ALfloat> sources_no_attenuation;

    bool source_distance_model = false;
    ALint distance_model = OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED;
    ALenum last_global_model = OpenALEnum::AL_NONE;

    std::string alGetStringExtension;

public:
    ALManager(Short::Circuit* short_, bool is_xfi);

    void alDistanceModel(ALenum distanceModel);
    void alEnable(ALenum capability);
    void alDisable(ALenum capability);

    ALboolean alIsEnabled(ALenum capability);
    const ALchar* alGetString(ALenum param);
    ALboolean alIsExtensionPresent(const ALchar* extname);

    void alDeleteSources(ALsizei n, const ALuint* sources);
    void alSourcef(ALuint source, ALenum param, ALfloat value);
    void alSourcei(ALuint source, ALenum param, ALint value);
    void alGenBuffers(ALsizei n, ALuint *buffers);

    Short::Circuit* GetShort();
    bool IsXFi();
};