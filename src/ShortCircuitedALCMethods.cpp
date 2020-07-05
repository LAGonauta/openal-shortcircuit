#include "ShortCircuit.hpp"
#include "Router.hpp"

extern Short::Circuit short_; // From ALCRouter.cpp

DLL_PUBLIC ALCcontext* DLL_ENTRY alcCreateContext(ALCdevice *device, const ALCint *attrlist)
{
    return short_.functions.alcCreateContext(device, attrlist);
}
DLL_PUBLIC void DLL_ENTRY alcProcessContext(ALCcontext *context)
{
    return short_.functions.alcProcessContext(context);
}
DLL_PUBLIC void DLL_ENTRY alcSuspendContext(ALCcontext *context)
{
    return short_.functions.alcSuspendContext(context);
}
DLL_PUBLIC ALCcontext* DLL_ENTRY alcGetCurrentContext(void)
{
    return short_.functions.alcGetCurrentContext();
}
DLL_PUBLIC ALCdevice*  DLL_ENTRY alcGetContextsDevice(ALCcontext *context)
{
    return short_.functions.alcGetContextsDevice(context);
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
DLL_PUBLIC ALCenum DLL_ENTRY alcGetEnumValue(ALCdevice *device, const ALCchar *enumname)
{
    return short_.functions.alcGetEnumValue(device, enumname);
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