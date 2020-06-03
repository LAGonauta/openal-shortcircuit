#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef AL_API
 #if defined(AL_LIBTYPE_STATIC)
  #define AL_API
 #elif defined(_WIN32)
  #define AL_API __declspec(dllimport)
 #else
  #define AL_API extern
 #endif
#endif

#if defined(_WIN32)
 #define AL_APIENTRY __cdecl
#else
 #define AL_APIENTRY
#endif

typedef char ALboolean;
typedef char ALchar;
typedef signed char ALbyte;
typedef unsigned char ALubyte;
typedef short ALshort;
typedef unsigned short ALushort;
typedef int ALint;
typedef unsigned int ALuint;
typedef int ALsizei;
typedef int ALenum;
typedef float ALfloat;
typedef double ALdouble;
typedef void ALvoid;

typedef struct ALCdevice ALCdevice;
typedef struct ALCcontext ALCcontext;
typedef char ALCboolean;
typedef char ALCchar;
typedef signed char ALCbyte;
typedef unsigned char ALCubyte;
typedef short ALCshort;
typedef unsigned short ALCushort;
typedef int ALCint;
typedef unsigned int ALCuint;
typedef int ALCsizei;
typedef int ALCenum;
typedef float ALCfloat;
typedef double ALCdouble;
typedef void ALCvoid;

typedef void (AL_APIENTRY *LPALENABLE)( ALenum capability );
typedef void (AL_APIENTRY *LPALDISABLE)( ALenum capability ); 
typedef ALboolean (AL_APIENTRY *LPALISENABLED)( ALenum capability ); 
typedef const ALchar* (AL_APIENTRY *LPALGETSTRING)( ALenum param );
typedef void (AL_APIENTRY *LPALGETBOOLEANV)( ALenum param, ALboolean* data );
typedef void (AL_APIENTRY *LPALGETINTEGERV)( ALenum param, ALint* data );
typedef void (AL_APIENTRY *LPALGETFLOATV)( ALenum param, ALfloat* data );
typedef void (AL_APIENTRY *LPALGETDOUBLEV)( ALenum param, ALdouble* data );
typedef ALboolean (AL_APIENTRY *LPALGETBOOLEAN)( ALenum param );
typedef ALint (AL_APIENTRY *LPALGETINTEGER)( ALenum param );
typedef ALfloat (AL_APIENTRY *LPALGETFLOAT)( ALenum param );
typedef ALdouble (AL_APIENTRY *LPALGETDOUBLE)( ALenum param );
typedef ALenum (AL_APIENTRY *LPALGETERROR)( void );
typedef ALboolean (AL_APIENTRY *LPALISEXTENSIONPRESENT)(const ALchar* extname );
typedef void* (AL_APIENTRY *LPALGETPROCADDRESS)( const ALchar* fname );
typedef ALenum (AL_APIENTRY *LPALGETENUMVALUE)( const ALchar* ename );
typedef void (AL_APIENTRY *LPALLISTENERF)( ALenum param, ALfloat value );
typedef void (AL_APIENTRY *LPALLISTENER3F)( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void (AL_APIENTRY *LPALLISTENERFV)( ALenum param, const ALfloat* values );
typedef void (AL_APIENTRY *LPALLISTENERI)( ALenum param, ALint value );
typedef void (AL_APIENTRY *LPALGETLISTENERF)( ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETLISTENER3F)( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );
typedef void (AL_APIENTRY *LPALGETLISTENERFV)( ALenum param, ALfloat* values );
typedef void (AL_APIENTRY *LPALGETLISTENERI)( ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALGENSOURCES)( ALsizei n, ALuint* sources ); 
typedef void (AL_APIENTRY *LPALDELETESOURCES)( ALsizei n, const ALuint* sources );
typedef ALboolean (AL_APIENTRY *LPALISSOURCE)( ALuint sid ); 
typedef void (AL_APIENTRY *LPALSOURCEF)( ALuint sid, ALenum param, ALfloat value); 
typedef void (AL_APIENTRY *LPALSOURCE3F)( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void (AL_APIENTRY *LPALSOURCEFV)( ALuint sid, ALenum param, const ALfloat* values );
typedef void (AL_APIENTRY *LPALSOURCEI)( ALuint sid, ALenum param, ALint value);
typedef void (AL_APIENTRY *LPALSOURCEIV)(ALuint source, ALenum param, const ALint *values);
typedef void (AL_APIENTRY *LPALGETSOURCEF)( ALuint sid, ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void (AL_APIENTRY *LPALGETSOURCEFV)( ALuint sid, ALenum param, ALfloat* values );
typedef void (AL_APIENTRY *LPALGETSOURCEI)( ALuint sid, ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALSOURCEPLAYV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCESTOPV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEPLAY)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCESTOP)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEREWIND)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEPAUSE)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
typedef void (AL_APIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
typedef void (AL_APIENTRY *LPALGENBUFFERS)( ALsizei n, ALuint* buffers );
typedef void (AL_APIENTRY *LPALDELETEBUFFERS)( ALsizei n, const ALuint* buffers );
typedef ALboolean (AL_APIENTRY *LPALISBUFFER)( ALuint bid );
typedef void (AL_APIENTRY *LPALBUFFERDATA)( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );
typedef void (AL_APIENTRY *LPALGETBUFFERF)( ALuint bid, ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETBUFFERI)( ALuint bid, ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALDOPPLERFACTOR)( ALfloat value );
typedef void (AL_APIENTRY *LPALDOPPLERVELOCITY)( ALfloat value );
typedef void (AL_APIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );


typedef ALCcontext* (AL_APIENTRY *LPALCCREATECONTEXT) (ALCdevice *device, const ALCint *attrlist);
typedef ALCboolean (AL_APIENTRY *LPALCMAKECONTEXTCURRENT)( ALCcontext *context );
typedef void (AL_APIENTRY *LPALCPROCESSCONTEXT)( ALCcontext *context );
typedef void (AL_APIENTRY *LPALCSUSPENDCONTEXT)( ALCcontext *context );
typedef void (AL_APIENTRY *LPALCDESTROYCONTEXT)( ALCcontext *context );
typedef ALCcontext* (AL_APIENTRY *LPALCGETCURRENTCONTEXT)( ALCvoid );
typedef ALCdevice* (AL_APIENTRY *LPALCGETCONTEXTSDEVICE)( ALCcontext *context );
typedef ALCdevice* (AL_APIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
typedef ALCboolean (AL_APIENTRY *LPALCCLOSEDEVICE)( ALCdevice *device );
typedef ALCenum (AL_APIENTRY *LPALCGETERROR)( ALCdevice *device );
typedef ALCboolean (AL_APIENTRY *LPALCISEXTENSIONPRESENT)( ALCdevice *device, const ALCchar *extname );
typedef void* (AL_APIENTRY *LPALCGETPROCADDRESS)(ALCdevice *device, const ALCchar *funcname );
typedef ALCenum (AL_APIENTRY *LPALCGETENUMVALUE)(ALCdevice *device, const ALCchar *enumname );
typedef const ALCchar* (AL_APIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
typedef void (AL_APIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );
typedef ALCdevice* (AL_APIENTRY *LPALCCAPTUREOPENDEVICE)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
typedef ALCboolean (AL_APIENTRY *LPALCCAPTURECLOSEDEVICE)(ALCdevice *device);
typedef void (AL_APIENTRY *LPALCCAPTURESTART)(ALCdevice *device);
typedef void (AL_APIENTRY *LPALCCAPTURESTOP)(ALCdevice *device);
typedef void (AL_APIENTRY *LPALCCAPTURESAMPLES)(ALCdevice *device, ALCvoid *buffer, ALCsizei samples);

typedef struct
{
	LPALENABLE				    alEnable;
	LPALDISABLE				    alDisable;
	LPALISENABLED			    alIsEnabled;
	LPALGETBOOLEAN			    alGetBoolean;
	LPALGETINTEGER			    alGetInteger;
	LPALGETFLOAT			    alGetFloat;
	LPALGETDOUBLE			    alGetDouble;
	LPALGETBOOLEANV			    alGetBooleanv;
	LPALGETINTEGERV			    alGetIntegerv;
	LPALGETFLOATV			    alGetFloatv;
	LPALGETDOUBLEV			    alGetDoublev;
	LPALGETSTRING			    alGetString;
	LPALGETERROR			    alGetError;
	LPALISEXTENSIONPRESENT	    alIsExtensionPresent;
	LPALGETPROCADDRESS		    alGetProcAddress;
	LPALGETENUMVALUE		    alGetEnumValue;
	LPALLISTENERI			    alListeneri;
	LPALLISTENERF			    alListenerf;
	LPALLISTENER3F			    alListener3f;
	LPALLISTENERFV			    alListenerfv;
	LPALGETLISTENERI		    alGetListeneri;
	LPALGETLISTENERF		    alGetListenerf;
	LPALGETLISTENER3F		    alGetListener3f;
	LPALGETLISTENERFV		    alGetListenerfv;
	LPALGENSOURCES			    alGenSources;
	LPALDELETESOURCES		    alDeleteSources;
	LPALISSOURCE			    alIsSource;
	LPALSOURCEI				    alSourcei;
	LPALSOURCEIV                alSourceiv;
	LPALSOURCEF				    alSourcef;
	LPALSOURCE3F			    alSource3f;
	LPALSOURCEFV			    alSourcefv;
	LPALGETSOURCEI			    alGetSourcei;
	LPALGETSOURCEF			    alGetSourcef;
	LPALGETSOURCEFV			    alGetSourcefv;
	LPALSOURCEPLAYV			    alSourcePlayv;
	LPALSOURCESTOPV			    alSourceStopv;
	LPALSOURCEPLAY			    alSourcePlay;
	LPALSOURCEPAUSE			    alSourcePause;
	LPALSOURCESTOP			    alSourceStop;
	LPALGENBUFFERS			    alGenBuffers;
	LPALDELETEBUFFERS		    alDeleteBuffers;
	LPALISBUFFER			    alIsBuffer;
	LPALBUFFERDATA			    alBufferData;
	LPALGETBUFFERI			    alGetBufferi;
	LPALGETBUFFERF			    alGetBufferf;
	LPALSOURCEQUEUEBUFFERS	    alSourceQueueBuffers;
	LPALSOURCEUNQUEUEBUFFERS    alSourceUnqueueBuffers;
	LPALDISTANCEMODEL		    alDistanceModel;
	LPALDOPPLERFACTOR		    alDopplerFactor;
	LPALDOPPLERVELOCITY		    alDopplerVelocity;
	LPALCGETSTRING			    alcGetString;
	LPALCGETINTEGERV		    alcGetIntegerv;
	LPALCOPENDEVICE			    alcOpenDevice;
	LPALCCLOSEDEVICE		    alcCloseDevice;
	LPALCCREATECONTEXT		    alcCreateContext;
	LPALCMAKECONTEXTCURRENT	    alcMakeContextCurrent;
	LPALCPROCESSCONTEXT		    alcProcessContext;
	LPALCGETCURRENTCONTEXT	    alcGetCurrentContext;
	LPALCGETCONTEXTSDEVICE	    alcGetContextsDevice;
	LPALCSUSPENDCONTEXT		    alcSuspendContext;
	LPALCDESTROYCONTEXT		    alcDestroyContext;
	LPALCGETERROR			    alcGetError;
	LPALCISEXTENSIONPRESENT	    alcIsExtensionPresent;
	LPALCGETPROCADDRESS		    alcGetProcAddress;
	LPALCGETENUMVALUE		    alcGetEnumValue;
	LPALCCAPTUREOPENDEVICE	    alcCaptureOpenDevice;
	LPALCCAPTURECLOSEDEVICE	    alcCaptureCloseDevice;
	LPALCCAPTURESTART		    alcCaptureStart;
	LPALCCAPTURESTOP		    alcCaptureStop;
	LPALCCAPTURESAMPLES		    alcCaptureSamples;
} OpenALFunctions;

#if defined(__cplusplus)
}
#endif