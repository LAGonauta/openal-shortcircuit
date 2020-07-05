#include "Router.hpp"
#include "ALManager.hpp"

ALManager* al_manager;

DLL_LOCAL void AlSetManager(ALManager* manager)
{
    al_manager = manager;
}

DLL_PUBLIC void DLL_ENTRY alDistanceModel(ALenum distanceModel)
{
    al_manager->alDistanceModel(distanceModel);
}

DLL_PUBLIC void DLL_ENTRY alEnable(ALenum capability)
{
    al_manager->alEnable(capability);
}

DLL_PUBLIC void DLL_ENTRY alDisable(ALenum capability)
{
    al_manager->alDisable(capability);
}

DLL_PUBLIC ALboolean DLL_ENTRY alIsEnabled(ALenum capability)
{
    return al_manager->alIsEnabled(capability);
}

DLL_PUBLIC const ALchar* DLL_ENTRY alGetString(ALenum param)
{
    return al_manager->alGetString(param);
}

DLL_PUBLIC ALboolean DLL_ENTRY alIsExtensionPresent(const ALchar *extname)
{
    return al_manager->alIsExtensionPresent(extname);
}

DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint* sources)
{
    al_manager->alDeleteSources(n, sources);
}

DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value)
{
    al_manager->alSourcef(source, param, value);
}

DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value)
{
    al_manager->alSourcei(source, param, value);
}

DLL_PUBLIC void DLL_ENTRY alGenBuffers(ALsizei n, ALuint *buffers)
{
    al_manager->alGenBuffers(n, buffers);
}

DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname)
{
    if (al_manager->IsXFi())
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

    return al_manager->GetShort()->functions.alGetProcAddress(fname);
}