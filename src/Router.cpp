#include <cstring>

#include "ShortCircuit.hpp"
#include "Router.hpp"

Short::Circuit short_;

//void alDopplerFactor(ALfloat value) { short_.functions.alDopplerFactor(value); };
//void alDopplerVelocity(ALfloat value) { short_.functions.alDopplerVelocity(value); };
//void alSpeedOfSound(ALfloat value) { short_.functions.alSpeedOfSound(value); };
// DLL_PUBLIC void DLL_ENTRY alDistanceModel(ALenum distanceModel) { short_.functions.alDistanceModel(distanceModel) };
// DLL_PUBLIC void DLL_ENTRY alEnable(ALenum capability) { short_.functions.alEnable(value) };
// DLL_PUBLIC void DLL_ENTRY alDisable(ALenum capability) { short_.functions.alDisable(value) };
// DLL_PUBLIC ALboolean DLL_ENTRY alIsEnabled(ALenum capability) { short_.functions.alIsEnabled(value) };
DLL_PUBLIC const ALchar* DLL_ENTRY alGetString(ALenum param)
{
    if (param == 0xB002) return "1.1"; // AL_VERSION
    else if (param == 0xB004) return "AL_EXT_EXPONENT_DISTANCE AL_EXT_LINEAR_DISTANCE AL_EXT_MCFORMATS AL_EXT_OFFSET AL_EXT_source_distance_model"; // AL_EXTENSIONS
    return short_.functions.alGetString(param); // TODO: append the real output
}
// DLL_PUBLIC void DLL_ENTRY alGetBooleanv(ALenum param, ALboolean *values) { short_.functions.alGetBooleanv(value) };
// DLL_PUBLIC void DLL_ENTRY alGetIntegerv(ALenum param, ALint *values) { short_.functions.alGetIntegerv(value) };
// DLL_PUBLIC void DLL_ENTRY alGetFloatv(ALenum param, ALfloat *values) { short_.functions.alGetFloatv(value) };
// DLL_PUBLIC void DLL_ENTRY alGetDoublev(ALenum param, ALdouble *values) { short_.functions.alGetDoublev(value) };
// DLL_PUBLIC ALboolean DLL_ENTRY alGetBoolean(ALenum param) { short_.functions.alGetBoolean(value) };
// DLL_PUBLIC ALint DLL_ENTRY alGetInteger(ALenum param) { short_.functions.alGetInteger(value) };
// DLL_PUBLIC ALfloat DLL_ENTRY alGetFloat(ALenum param) { short_.functions.alGetFloat(value) };
// DLL_PUBLIC ALdouble DLL_ENTRY alGetDouble(ALenum param) { short_.functions.alGetDouble(value) };
DLL_PUBLIC ALenum DLL_ENTRY alGetError(void)
{
    return 0;
    //return short_.functions.alGetError();
}
DLL_PUBLIC ALboolean DLL_ENTRY alIsExtensionPresent(const ALchar *extname)
{
    if (strncmp(extname, "AL_EXT_source_distance_model", 25) == 0) return true;
    return short_.functions.alIsExtensionPresent(extname);
}
DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname)
{
    if (strncmp(fname, "alGetString", 12) == 0) return reinterpret_cast<void*>(&alGetString);
    if (strncmp(fname, "alIsExtensionPresent", 21) == 0) return reinterpret_cast<void*>(&alIsExtensionPresent);
    // if (strncmp(fname, "alGenBuffers", 13) == 0) return reinterpret_cast<void*>(&alGenBuffers);
    // if (strncmp(fname, "alSourcei", 10) == 0) return reinterpret_cast<void*>(&alSourcei);
    // if (strncmp(fname, "alSourceiv", 11) == 0) return reinterpret_cast<void*>(&alSourceiv);
    if (strncmp(fname, "alGetError", 21) == 0) return reinterpret_cast<void*>(&alGetError);
    return short_.functions.alGetProcAddress(fname);
}
// DLL_PUBLIC ALenum DLL_ENTRY alGetEnumValue(const ALchar *ename) { short_.functions.alGetEnumValue(value) };
// DLL_PUBLIC void DLL_ENTRY alListenerf(ALenum param, ALfloat value) { short_.functions.alListenerf(value) };
// DLL_PUBLIC void DLL_ENTRY alListener3f(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3) { short_.functions.alListener3f(value) };
// DLL_PUBLIC void DLL_ENTRY alListenerfv(ALenum param, const ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alListeneri(ALenum param, ALint value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alListener3i(ALenum param, ALint value1, ALint value2, ALint value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alListeneriv(ALenum param, const ALint *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListenerf(ALenum param, ALfloat *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListener3f(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListenerfv(ALenum param, ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListeneri(ALenum param, ALint *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListener3i(ALenum param, ALint *value1, ALint *value2, ALint *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetListeneriv(ALenum param, ALint *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGenSources(ALsizei n, ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC ALboolean DLL_ENTRY alIsSource(ALuint source) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSource3f(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcefv(ALuint source, ALenum param, const ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value)
// {
//     if (param == 0x200) return; // AL_SOURCE_DISTANCE_MODEL
//     return short_.functions.alSourcei(source, param, value);
// };
// DLL_PUBLIC void DLL_ENTRY alSource3i(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceiv(ALuint source, ALenum param, const ALint *values)
// {
//     if (param == 0x200) return; // AL_SOURCE_DISTANCE_MODEL
//     return short_.functions.alSourceiv(source, param, values);
// };
// DLL_PUBLIC void DLL_ENTRY alGetSourcef(ALuint source, ALenum param, ALfloat *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetSource3f(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetSourcefv(ALuint source, ALenum param, ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetSourcei(ALuint source,  ALenum param, ALint *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetSource3i(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetSourceiv(ALuint source,  ALenum param, ALint *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcePlayv(ALsizei n, const ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceStopv(ALsizei n, const ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceRewindv(ALsizei n, const ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcePausev(ALsizei n, const ALuint *sources) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcePlay(ALuint source) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceStop(ALuint source) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceRewind(ALuint source) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourcePause(ALuint source) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceQueueBuffers(ALuint source, ALsizei nb, const ALuint *buffers) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alSourceUnqueueBuffers(ALuint source, ALsizei nb, ALuint *buffers) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGenBuffers(ALsizei n, ALuint *buffers)
// {
//     std::cout << "Router: GenBuffers -> " << n << ": " << buffers << std::endl;
//     return short_.functions.alGenBuffers(n, buffers);
// }
// DLL_PUBLIC void DLL_ENTRY alDeleteBuffers(ALsizei n, const ALuint *buffers) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC ALboolean DLL_ENTRY alIsBuffer(ALuint buffer) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBufferf(ALuint buffer, ALenum param, ALfloat value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBuffer3f(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBufferfv(ALuint buffer, ALenum param, const ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBufferi(ALuint buffer, ALenum param, ALint value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBuffer3i(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alBufferiv(ALuint buffer, ALenum param, const ALint *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBufferf(ALuint buffer, ALenum param, ALfloat *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBuffer3f(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBufferfv(ALuint buffer, ALenum param, ALfloat *values) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBufferi(ALuint buffer, ALenum param, ALint *value) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBuffer3i(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3) { short_.functions.alDopplerFactor(value) };
// DLL_PUBLIC void DLL_ENTRY alGetBufferiv(ALuint buffer, ALenum param, ALint *values) { short_.functions.alDopplerFactor(value) };

DLL_PUBLIC ALCcontext* DLL_ENTRY alcCreateContext(ALCdevice *device, const ALCint *attrlist)
{
    return short_.functions.alcCreateContext(device, attrlist);
}
DLL_PUBLIC ALCboolean  DLL_ENTRY alcMakeContextCurrent(ALCcontext *context)
{
    return short_.functions.alcMakeContextCurrent(context);
}
DLL_PUBLIC void DLL_ENTRY alcProcessContext(ALCcontext *context)
{
    return short_.functions.alcProcessContext(context);
}
DLL_PUBLIC void DLL_ENTRY alcSuspendContext(ALCcontext *context)
{
    return short_.functions.alcSuspendContext(context);
}
DLL_PUBLIC void DLL_ENTRY alcDestroyContext(ALCcontext *context)
{
    return short_.functions.alcDestroyContext(context);
}
DLL_PUBLIC ALCcontext* DLL_ENTRY alcGetCurrentContext(void)
{
    return short_.functions.alcGetCurrentContext();
}
DLL_PUBLIC ALCdevice*  DLL_ENTRY alcGetContextsDevice(ALCcontext *context)
{
    return short_.functions.alcGetContextsDevice(context);
}
DLL_PUBLIC ALCdevice* DLL_ENTRY alcOpenDevice(const ALCchar *devicename)
{
    return short_.functions.alcOpenDevice(devicename);
}
DLL_PUBLIC ALCboolean DLL_ENTRY alcCloseDevice(ALCdevice *device)
{
    return short_.functions.alcCloseDevice(device);
}
DLL_PUBLIC ALCenum DLL_ENTRY alcGetError(ALCdevice *device)
{
    return short_.functions.alcGetError(device);
}
DLL_PUBLIC ALCboolean DLL_ENTRY alcIsExtensionPresent(ALCdevice *device, const ALCchar *extname)
{
    return short_.functions.alcIsExtensionPresent(device, extname);
}
DLL_PUBLIC ALCvoid* DLL_ENTRY alcGetProcAddress(ALCdevice *device, const ALCchar *funcname)
{
    return short_.functions.alcGetProcAddress(device, funcname);
}
DLL_PUBLIC ALCenum DLL_ENTRY alcGetEnumValue(ALCdevice *device, const ALCchar *enumname)
{
    return short_.functions.alcGetEnumValue(device, enumname);
}
DLL_PUBLIC const ALCchar* DLL_ENTRY alcGetString(ALCdevice *device, ALCenum param)
{
    if (param == 0x1006) return "ALC_EXT_EFX ALC_ENUMERATE_ALL_EXT ALC_ENUMERATION_EXT ALC_EXT_CAPTURE"; // ALC_EXTENSIONS
    return short_.functions.alcGetString(device, param); // TODO: Append the real output
}
DLL_PUBLIC void DLL_ENTRY alcGetIntegerv(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values)
{
    return short_.functions.alcGetIntegerv(device, param, size, values);
}
DLL_PUBLIC ALCdevice* DLL_ENTRY alcCaptureOpenDevice(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize)
{
    return short_.functions.alcCaptureOpenDevice(devicename, frequency, format, buffersize);
}
DLL_PUBLIC ALCboolean DLL_ENTRY alcCaptureCloseDevice(ALCdevice *device)
{
    return short_.functions.alcCaptureCloseDevice(device);
}
DLL_PUBLIC void DLL_ENTRY alcCaptureStart(ALCdevice *device)
{
    return short_.functions.alcCaptureStart(device);
}
DLL_PUBLIC void DLL_ENTRY alcCaptureStop(ALCdevice *device)
{
    return short_.functions.alcCaptureStop(device);
}
DLL_PUBLIC void DLL_ENTRY alcCaptureSamples(ALCdevice *device, ALCvoid *buffer, ALCsizei samples)
{
    return short_.functions.alcCaptureSamples(device, buffer, samples);
}