#pragma once

#include "OpenALAPI.h"

class XRamManager {
private:
    bool use_xram = false;
    bool can_use_xram = false;
    bool initialized = false;
    ALenum xram_acessible = 0;
    
public:
    void SetXRamMode(ALsizei n, ALuint* buffers);
};