#pragma once

#include "Visibility.h"

#if defined(__cplusplus)
extern "C" {
#endif

// AL

DLL_PUBLIC void DLL_ENTRY alDopplerFactor(ALfloat value);
DLL_PUBLIC void DLL_ENTRY alDopplerVelocity(ALfloat value);
DLL_PUBLIC void DLL_ENTRY alSpeedOfSound(ALfloat value);
DLL_PUBLIC void DLL_ENTRY alDistanceModel(ALenum distanceModel);
DLL_PUBLIC void DLL_ENTRY alEnable(ALenum capability);
DLL_PUBLIC void DLL_ENTRY alDisable(ALenum capability);
DLL_PUBLIC ALboolean DLL_ENTRY alIsEnabled(ALenum capability);
DLL_PUBLIC const ALchar* DLL_ENTRY alGetString(ALenum param);
DLL_PUBLIC void DLL_ENTRY alGetBooleanv(ALenum param, ALboolean *values);
DLL_PUBLIC void DLL_ENTRY alGetIntegerv(ALenum param, ALint *values);
DLL_PUBLIC void DLL_ENTRY alGetFloatv(ALenum param, ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alGetDoublev(ALenum param, ALdouble *values);
DLL_PUBLIC ALboolean DLL_ENTRY alGetBoolean(ALenum param);
DLL_PUBLIC ALint DLL_ENTRY alGetInteger(ALenum param);
DLL_PUBLIC ALfloat DLL_ENTRY alGetFloat(ALenum param);
DLL_PUBLIC ALdouble DLL_ENTRY alGetDouble(ALenum param);
DLL_PUBLIC ALenum DLL_ENTRY alGetError(void);
DLL_PUBLIC ALboolean DLL_ENTRY alIsExtensionPresent(const ALchar *extname);
DLL_PUBLIC void* DLL_ENTRY alGetProcAddress(const ALchar *fname);
DLL_PUBLIC ALenum DLL_ENTRY alGetEnumValue(const ALchar *ename);
DLL_PUBLIC void DLL_ENTRY alListenerf(ALenum param, ALfloat value);
DLL_PUBLIC void DLL_ENTRY alListener3f(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
DLL_PUBLIC void DLL_ENTRY alListenerfv(ALenum param, const ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alListeneri(ALenum param, ALint value);
DLL_PUBLIC void DLL_ENTRY alListener3i(ALenum param, ALint value1, ALint value2, ALint value3);
DLL_PUBLIC void DLL_ENTRY alListeneriv(ALenum param, const ALint *values);
DLL_PUBLIC void DLL_ENTRY alGetListenerf(ALenum param, ALfloat *value);
DLL_PUBLIC void DLL_ENTRY alGetListener3f(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
DLL_PUBLIC void DLL_ENTRY alGetListenerfv(ALenum param, ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alGetListeneri(ALenum param, ALint *value);
DLL_PUBLIC void DLL_ENTRY alGetListener3i(ALenum param, ALint *value1, ALint *value2, ALint *value3);
DLL_PUBLIC void DLL_ENTRY alGetListeneriv(ALenum param, ALint *values);
DLL_PUBLIC void DLL_ENTRY alGenSources(ALsizei n, ALuint *sources);
DLL_PUBLIC void DLL_ENTRY alDeleteSources(ALsizei n, const ALuint *sources);
DLL_PUBLIC ALboolean DLL_ENTRY alIsSource(ALuint source);
DLL_PUBLIC void DLL_ENTRY alSourcef(ALuint source, ALenum param, ALfloat value);
DLL_PUBLIC void DLL_ENTRY alSource3f(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
DLL_PUBLIC void DLL_ENTRY alSourcefv(ALuint source, ALenum param, const ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alSourcei(ALuint source, ALenum param, ALint value);
DLL_PUBLIC void DLL_ENTRY alSource3i(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
DLL_PUBLIC void DLL_ENTRY alSourceiv(ALuint source, ALenum param, const ALint *values);
DLL_PUBLIC void DLL_ENTRY alGetSourcef(ALuint source, ALenum param, ALfloat *value);
DLL_PUBLIC void DLL_ENTRY alGetSource3f(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
DLL_PUBLIC void DLL_ENTRY alGetSourcefv(ALuint source, ALenum param, ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alGetSourcei(ALuint source,  ALenum param, ALint *value);
DLL_PUBLIC void DLL_ENTRY alGetSource3i(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
DLL_PUBLIC void DLL_ENTRY alGetSourceiv(ALuint source,  ALenum param, ALint *values);
DLL_PUBLIC void DLL_ENTRY alSourcePlayv(ALsizei n, const ALuint *sources);
DLL_PUBLIC void DLL_ENTRY alSourceStopv(ALsizei n, const ALuint *sources);
DLL_PUBLIC void DLL_ENTRY alSourceRewindv(ALsizei n, const ALuint *sources);
DLL_PUBLIC void DLL_ENTRY alSourcePausev(ALsizei n, const ALuint *sources);
DLL_PUBLIC void DLL_ENTRY alSourcePlay(ALuint source);
DLL_PUBLIC void DLL_ENTRY alSourceStop(ALuint source);
DLL_PUBLIC void DLL_ENTRY alSourceRewind(ALuint source);
DLL_PUBLIC void DLL_ENTRY alSourcePause(ALuint source);
DLL_PUBLIC void DLL_ENTRY alSourceQueueBuffers(ALuint source, ALsizei nb, const ALuint *buffers);
DLL_PUBLIC void DLL_ENTRY alSourceUnqueueBuffers(ALuint source, ALsizei nb, ALuint *buffers);
DLL_PUBLIC void DLL_ENTRY alGenBuffers(ALsizei n, ALuint *buffers);
DLL_PUBLIC void DLL_ENTRY alDeleteBuffers(ALsizei n, const ALuint *buffers);
DLL_PUBLIC ALboolean DLL_ENTRY alIsBuffer(ALuint buffer);
DLL_PUBLIC void DLL_ENTRY alBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
DLL_PUBLIC void DLL_ENTRY alBufferf(ALuint buffer, ALenum param, ALfloat value);
DLL_PUBLIC void DLL_ENTRY alBuffer3f(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
DLL_PUBLIC void DLL_ENTRY alBufferfv(ALuint buffer, ALenum param, const ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alBufferi(ALuint buffer, ALenum param, ALint value);
DLL_PUBLIC void DLL_ENTRY alBuffer3i(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
DLL_PUBLIC void DLL_ENTRY alBufferiv(ALuint buffer, ALenum param, const ALint *values);
DLL_PUBLIC void DLL_ENTRY alGetBufferf(ALuint buffer, ALenum param, ALfloat *value);
DLL_PUBLIC void DLL_ENTRY alGetBuffer3f(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
DLL_PUBLIC void DLL_ENTRY alGetBufferfv(ALuint buffer, ALenum param, ALfloat *values);
DLL_PUBLIC void DLL_ENTRY alGetBufferi(ALuint buffer, ALenum param, ALint *value);
DLL_PUBLIC void DLL_ENTRY alGetBuffer3i(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
DLL_PUBLIC void DLL_ENTRY alGetBufferiv(ALuint buffer, ALenum param, ALint *values);

// ALC

DLL_PUBLIC ALCcontext* DLL_ENTRY alcCreateContext(ALCdevice *device, const ALCint *attrlist);
DLL_PUBLIC ALCboolean  DLL_ENTRY alcMakeContextCurrent(ALCcontext *context);
DLL_PUBLIC void DLL_ENTRY alcProcessContext(ALCcontext *context);
DLL_PUBLIC void DLL_ENTRY alcSuspendContext(ALCcontext *context);
DLL_PUBLIC void DLL_ENTRY alcDestroyContext(ALCcontext *context);
DLL_PUBLIC ALCcontext* DLL_ENTRY alcGetCurrentContext(void);
DLL_PUBLIC ALCdevice*  DLL_ENTRY alcGetContextsDevice(ALCcontext *context);
DLL_PUBLIC ALCdevice* DLL_ENTRY alcOpenDevice(const ALCchar *devicename);
DLL_PUBLIC ALCboolean DLL_ENTRY alcCloseDevice(ALCdevice *device);
DLL_PUBLIC ALCenum DLL_ENTRY alcGetError(ALCdevice *device);
DLL_PUBLIC ALCboolean DLL_ENTRY alcIsExtensionPresent(ALCdevice *device, const ALCchar *extname);
DLL_PUBLIC ALCvoid* DLL_ENTRY alcGetProcAddress(ALCdevice *device, const ALCchar *funcname);
DLL_PUBLIC ALCenum DLL_ENTRY alcGetEnumValue(ALCdevice *device, const ALCchar *enumname);
DLL_PUBLIC const ALCchar* DLL_ENTRY alcGetString(ALCdevice *device, ALCenum param);
DLL_PUBLIC void DLL_ENTRY alcGetIntegerv(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values);
DLL_PUBLIC ALCdevice* DLL_ENTRY alcCaptureOpenDevice(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
DLL_PUBLIC ALCboolean DLL_ENTRY alcCaptureCloseDevice(ALCdevice *device);
DLL_PUBLIC void DLL_ENTRY alcCaptureStart(ALCdevice *device);
DLL_PUBLIC void DLL_ENTRY alcCaptureStop(ALCdevice *device);
DLL_PUBLIC void DLL_ENTRY alcCaptureSamples(ALCdevice *device, ALCvoid *buffer, ALCsizei samples);

#if defined(__cplusplus)
}
#endif