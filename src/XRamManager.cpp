#include <cstdlib>
#include <cstring>

#include "XRamManager.hpp"

XRamManager::XRamManager(Short::Circuit* short_)
{
    this->short_ = short_;
}

void XRamManager::SetXRamMode(ALsizei n, ALuint* buffers)
{
    if (!initialized)
    {
        if (short_->functions.alIsExtensionPresent("EAX-RAM"))
        {
            can_use_xram = true;
            xram_acessible = short_->functions.alGetEnumValue("AL_STORAGE_ACCESSIBLE");
            if (xram_acessible)
            {
                eaxSetBufferMode = (EAXSetBufferMode)short_->functions.alGetProcAddress("EAXSetBufferMode");
                if (eaxSetBufferMode)
                {
                    auto e = std::getenv("SC_FORCE_XRAM");
                    use_xram = e && strnicmp(e, "true", 5) == 0;
                }
            }
        }
        initialized = true;
    }
    
    if (can_use_xram && !use_xram && eaxSetBufferMode)
    {
        eaxSetBufferMode(n, buffers, xram_acessible);
    }
}