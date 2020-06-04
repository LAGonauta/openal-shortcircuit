#include <cstdlib>

#include "ShortCircuit.hpp"

namespace Short
{
    Circuit::Circuit()
    {
        Init(std::getenv("SC_OAL_LIBRARY_BINARY_PATH"));
    }

    Circuit::~Circuit()
    {
        if (library_handle)
        {
            FreeLibrary(library_handle);
        }
    }

    void Circuit::Init(const char* path)
    {
        if (path)
        {
            library_handle = LoadLibrary(path);
        }
        else
        {
            library_handle = LoadLibrary("openal32.dll");
        }

        if (!library_handle)
        {
            return;
        }
        functions = OpenALFunctions{};

        functions.alEnable = (LPALENABLE)GetProcAddress(library_handle, "alEnable");
        functions.alDisable = (LPALDISABLE)GetProcAddress(library_handle, "alDisable");
        functions.alIsEnabled = (LPALISENABLED)GetProcAddress(library_handle, "alIsEnabled");
        functions.alGetBoolean = (LPALGETBOOLEAN)GetProcAddress(library_handle, "alGetBoolean");
        functions.alGetInteger = (LPALGETINTEGER)GetProcAddress(library_handle, "alGetInteger");
        functions.alGetFloat = (LPALGETFLOAT)GetProcAddress(library_handle, "alGetFloat");
        functions.alGetDouble = (LPALGETDOUBLE)GetProcAddress(library_handle, "alGetDouble");
        functions.alGetBooleanv = (LPALGETBOOLEANV)GetProcAddress(library_handle, "alGetBooleanv");
        functions.alGetIntegerv = (LPALGETINTEGERV)GetProcAddress(library_handle, "alGetIntegerv");
        functions.alGetFloatv = (LPALGETFLOATV)GetProcAddress(library_handle, "alGetFloatv");
        functions.alGetDoublev = (LPALGETDOUBLEV)GetProcAddress(library_handle, "alGetDoublev");
        functions.alGetString = (LPALGETSTRING)GetProcAddress(library_handle, "alGetString");
        functions.alGetError = (LPALGETERROR)GetProcAddress(library_handle, "alGetError");
        functions.alIsExtensionPresent = (LPALISEXTENSIONPRESENT)GetProcAddress(library_handle, "alIsExtensionPresent");
        functions.alGetProcAddress = (LPALGETPROCADDRESS)GetProcAddress(library_handle, "alGetProcAddress");
        functions.alGetEnumValue = (LPALGETENUMVALUE)GetProcAddress(library_handle, "alGetEnumValue");
        functions.alListeneri = (LPALLISTENERI)GetProcAddress(library_handle, "alListeneri");
        functions.alListenerf = (LPALLISTENERF)GetProcAddress(library_handle, "alListenerf");
        functions.alListener3f = (LPALLISTENER3F)GetProcAddress(library_handle, "alListener3f");
        functions.alListenerfv = (LPALLISTENERFV)GetProcAddress(library_handle, "alListenerfv");
        functions.alGetListeneri = (LPALGETLISTENERI)GetProcAddress(library_handle, "alGetListeneri");
        functions.alGetListenerf =(LPALGETLISTENERF)GetProcAddress(library_handle, "alGetListenerf");
        functions.alGetListener3f = (LPALGETLISTENER3F)GetProcAddress(library_handle, "alGetListener3f");
        functions.alGetListenerfv = (LPALGETLISTENERFV)GetProcAddress(library_handle, "alGetListenerfv");
        functions.alGenSources = (LPALGENSOURCES)GetProcAddress(library_handle, "alGenSources");
        functions.alDeleteSources = (LPALDELETESOURCES)GetProcAddress(library_handle, "alDeleteSources");
        functions.alIsSource = (LPALISSOURCE)GetProcAddress(library_handle, "alIsSource");
        functions.alSourcei = (LPALSOURCEI)GetProcAddress(library_handle, "alSourcei");
        functions.alSourceiv = (LPALSOURCEIV)GetProcAddress(library_handle, "alSourceiv");
        functions.alSourcef = (LPALSOURCEF)GetProcAddress(library_handle, "alSourcef");
        functions.alSource3f = (LPALSOURCE3F)GetProcAddress(library_handle, "alSource3f");
        functions.alSourcefv = (LPALSOURCEFV)GetProcAddress(library_handle, "alSourcefv");
        functions.alGetSourcei = (LPALGETSOURCEI)GetProcAddress(library_handle, "alGetSourcei");
        functions.alGetSourcef = (LPALGETSOURCEF)GetProcAddress(library_handle, "alGetSourcef");
        functions.alGetSourcefv = (LPALGETSOURCEFV)GetProcAddress(library_handle, "alGetSourcefv");
        functions.alSourcePlayv = (LPALSOURCEPLAYV)GetProcAddress(library_handle, "alSourcePlayv");
        functions.alSourceStopv = (LPALSOURCESTOPV)GetProcAddress(library_handle, "alSourceStopv");
        functions.alSourcePlay = (LPALSOURCEPLAY)GetProcAddress(library_handle, "alSourcePlay");
        functions.alSourcePause = (LPALSOURCEPAUSE)GetProcAddress(library_handle, "alSourcePause");
        functions.alSourceStop = (LPALSOURCESTOP)GetProcAddress(library_handle, "alSourceStop");
        functions.alGenBuffers = (LPALGENBUFFERS)GetProcAddress(library_handle, "alGenBuffers");
        functions.alDeleteBuffers = (LPALDELETEBUFFERS)GetProcAddress(library_handle, "alDeleteBuffers");
        functions.alIsBuffer = (LPALISBUFFER)GetProcAddress(library_handle, "alIsBuffer");
        functions.alBufferData = (LPALBUFFERDATA)GetProcAddress(library_handle, "alBufferData");
        functions.alGetBufferi = (LPALGETBUFFERI)GetProcAddress(library_handle, "alGetBufferi");
        functions.alGetBufferf = (LPALGETBUFFERF)GetProcAddress(library_handle, "alGetBufferf");
        functions.alSourceQueueBuffers = (LPALSOURCEQUEUEBUFFERS)GetProcAddress(library_handle, "alSourceQueueBuffers");
        functions.alSourceUnqueueBuffers = (LPALSOURCEUNQUEUEBUFFERS)GetProcAddress(library_handle, "alSourceUnqueueBuffers");
        functions.alDistanceModel = (LPALDISTANCEMODEL)GetProcAddress(library_handle, "alDistanceModel");
        functions.alDopplerFactor = (LPALDOPPLERFACTOR)GetProcAddress(library_handle, "alDopplerFactor");
        functions.alDopplerVelocity = (LPALDOPPLERVELOCITY)GetProcAddress(library_handle, "alDopplerVelocity");
        functions.alcGetString = (LPALCGETSTRING)GetProcAddress(library_handle, "alcGetString");
        functions.alcGetIntegerv = (LPALCGETINTEGERV)GetProcAddress(library_handle, "alcGetIntegerv");
        functions.alcOpenDevice = (LPALCOPENDEVICE)GetProcAddress(library_handle, "alcOpenDevice");
        functions.alcCloseDevice = (LPALCCLOSEDEVICE)GetProcAddress(library_handle, "alcCloseDevice");
        functions.alcCreateContext = (LPALCCREATECONTEXT)GetProcAddress(library_handle, "alcCreateContext");
        functions.alcMakeContextCurrent = (LPALCMAKECONTEXTCURRENT)GetProcAddress(library_handle, "alcMakeContextCurrent");
        functions.alcProcessContext = (LPALCPROCESSCONTEXT)GetProcAddress(library_handle, "alcProcessContext");
        functions.alcGetCurrentContext = (LPALCGETCURRENTCONTEXT)GetProcAddress(library_handle, "alcGetCurrentContext");
        functions.alcGetContextsDevice = (LPALCGETCONTEXTSDEVICE)GetProcAddress(library_handle, "alcGetContextsDevice");
        functions.alcSuspendContext = (LPALCSUSPENDCONTEXT)GetProcAddress(library_handle, "alcSuspendContext");
        functions.alcDestroyContext = (LPALCDESTROYCONTEXT)GetProcAddress(library_handle, "alcDestroyContext");
        functions.alcGetError = (LPALCGETERROR)GetProcAddress(library_handle, "alcGetError");
        functions.alcIsExtensionPresent = (LPALCISEXTENSIONPRESENT)GetProcAddress(library_handle, "alcIsExtensionPresent");
        functions.alcGetProcAddress = (LPALCGETPROCADDRESS)GetProcAddress(library_handle, "alcGetProcAddress");
        functions.alcGetEnumValue = (LPALCGETENUMVALUE)GetProcAddress(library_handle, "alcGetEnumValue");
    }
}