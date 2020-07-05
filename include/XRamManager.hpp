#pragma once

#include "OpenALAPI.h"
#include "ShortCircuit.hpp"

class XRamManager {
private:
    typedef ALboolean (__cdecl *EAXSetBufferMode)(ALsizei n, ALuint *buffers, ALint value);
    typedef ALenum (__cdecl *EAXGetBufferMode)(ALuint buffer, ALint *value);

    EAXSetBufferMode eaxSetBufferMode;

    bool use_xram = false;
    bool can_use_xram = false;
    bool initialized = false;
    ALenum xram_acessible = 0;

    Short::Circuit* short_;
    
public:
    XRamManager(Short::Circuit* short_);

    void SetXRamMode(ALsizei n, ALuint* buffers);
};