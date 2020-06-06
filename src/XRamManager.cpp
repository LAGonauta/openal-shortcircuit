#include <cstdlib>
#include <cstring>

#include "XRamManager.hpp"
#include "ShortCircuit.hpp"

extern Short::Circuit short_;

typedef ALboolean (__cdecl *EAXSetBufferMode)(ALsizei n, ALuint *buffers, ALint value);
typedef ALenum (__cdecl *EAXGetBufferMode)(ALuint buffer, ALint *value);

static EAXSetBufferMode eaxSetBufferMode;

void XRamManager::SetXRamMode(ALsizei n, ALuint* buffers)
{
    if (!initialized)
    {
        if (short_.functions.alIsExtensionPresent("EAX-RAM"))
        {
            can_use_xram = true;
            xram_acessible = short_.functions.alGetEnumValue("AL_STORAGE_ACCESSIBLE");
            if (xram_acessible)
            {
                eaxSetBufferMode = (EAXSetBufferMode)short_.functions.alGetProcAddress("EAXSetBufferMode");
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