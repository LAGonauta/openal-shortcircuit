#include <algorithm>    

#include "SourceDistanceModelManager.hpp"

float SourceDistanceModelManager::CalculateFinalGain(const SourceSettings& value)
{
    float ret = 1.0f;
    if (!emulate_source_distance_model) return ret;

    auto distance = value.source_relative ? value.position.Length() : listener_position.CalculateDistance(value.position);
    switch (value.type)
    {
        case OpenALEnum::AL_INVERSE_DISTANCE_CLAMPED:
            distance = std::clamp(distance, value.ref_distance, value.max_distance);
        case OpenALEnum::AL_INVERSE_DISTANCE:
            ret = value.ref_distance / (value.ref_distance + value.rolloff_factor * (distance - value.ref_distance));
            break;

        case OpenALEnum::AL_LINEAR_DISTANCE:
            distance = std::min(distance, value.max_distance);
            ret = (1 - value.rolloff_factor * (distance - value.ref_distance) / (value.max_distance - value.ref_distance));
            break;

        case OpenALEnum::AL_LINEAR_DISTANCE_CLAMPED:
            distance = std::clamp(distance, value.ref_distance, value.max_distance);
            ret = (1 - value.rolloff_factor * (distance - value.ref_distance) / (value.max_distance - value.ref_distance));
            break;

        case OpenALEnum::AL_EXPONENT_DISTANCE_CLAMPED:
            distance = std::clamp(distance, value.ref_distance, value.max_distance);
        case OpenALEnum::AL_EXPONENT_DISTANCE:
            ret = std::pow(distance / value.ref_distance, - value.rolloff_factor);
            break;

        case OpenALEnum::AL_NONE:
            break;
    }

    return std::clamp(ret * value.additional_gain, 0.0f, 1.0f);
}

void SourceDistanceModelManager::AttachSource(ALuint source)
{
    source_map.try_emplace(source, SourceSettings{});
}
void SourceDistanceModelManager::DettachSource(ALuint source)
{
    source_map.erase(source);
}

void SourceDistanceModelManager::Enable()
{
    emulate_source_distance_model = true;
}
void SourceDistanceModelManager::Disable()
{
    emulate_source_distance_model = false;
}

bool SourceDistanceModelManager::IsEnabled()
{
    return emulate_source_distance_model;
}

void SourceDistanceModelManager::SetListenerPosition(const Vector3& position)
{
    listener_position = position;
}