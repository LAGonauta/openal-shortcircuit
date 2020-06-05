#pragma once

#include <unordered_map>

#include "OpenALAPI.h"
#include "OpenALEnum.h"
#include "Vector3.hpp"

struct SourceSettings
{
    bool source_relative = false;
    bool use_workaround = true; // change to default false later;
    ALenum type = OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED;
    ALfloat additional_gain = 1.0f;
    ALfloat max_distance = std::numeric_limits<float>::max();
    ALfloat ref_distance = 1.0f;
    ALfloat rolloff_factor = 1.0f;
    Vector3 position{};
};

class SourceDistanceModelManager final
{
private:
    std::unordered_map<ALuint, SourceSettings> source_map;
    Vector3 listener_position{};
    bool emulate_source_distance_model = false;

public:
    void Enable();
    void Disable();

    bool IsEnabled();
    
    float CalculateFinalGain(const SourceSettings& source);

    void AttachSource(ALuint source);
    void DettachSource(ALuint source);

    template<class Functor>
    void ForEachSource(Functor lambda)
    {
      for (auto& tuple : source_map)
      {
          lambda(tuple);
      }
    }

    template<class Functor>
    void ForSource(ALuint source, Functor lambda)
    {
        auto src = source_map.find(source);
        if (src != source_map.end()) lambda(src->second);
    }

    void SetListenerPosition(const Vector3& position);
};