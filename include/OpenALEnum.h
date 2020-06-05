#pragma once

namespace OpenALEnum
{
    constexpr int AL_NONE = 0;
    constexpr int AL_SOURCE_RELATIVE = 0x202;
    constexpr int AL_CONE_INNER_ANGLE = 0x1001;
    constexpr int AL_CONE_OUTER_ANGLE = 0x1002;
    constexpr int AL_PITCH = 0x1003;
    constexpr int AL_POSITION = 0x1004;
    constexpr int AL_DIRECTION = 0x1005;
    constexpr int AL_VELOCITY = 0x1006;
    constexpr int AL_LOOPING = 0x1007;
    constexpr int AL_BUFFER = 0x1009;
    constexpr int AL_GAIN = 0x100A;
    constexpr int AL_MIN_GAIN = 0x100D;
    constexpr int AL_MAX_GAIN = 0x100E;
    constexpr int AL_ORIENTATION = 0x100F;
    constexpr int AL_SOURCE_STATE = 0x1010;
    constexpr int AL_INITIAL = 0x1011;
    constexpr int AL_PLAYING = 0x1012;
    constexpr int AL_PAUSED = 0x1013;
    constexpr int AL_STOPPED = 0x1014;
    constexpr int AL_BUFFERS_QUEUED = 0x1015;
    constexpr int AL_BUFFERS_PROCESSED = 0x1016;
    constexpr int AL_REFERENCE_DISTANCE = 0x1020;
    constexpr int AL_ROLLOFF_FACTOR = 0x1021;
    constexpr int AL_CONE_OUTER_GAIN = 0x1022;
    constexpr int AL_MAX_DISTANCE = 0x1023;
    constexpr int AL_SEC_OFFSET = 0x1024;
    constexpr int AL_SAMPLE_OFFSET = 0x1025;
    constexpr int AL_BYTE_OFFSET = 0x1026;
    constexpr int AL_SOURCE_TYPE = 0x1027;
    constexpr int AL_STATIC = 0x1028;
    constexpr int AL_STREAMING = 0x1029;
    constexpr int AL_UNDETERMINED = 0x1030;
    constexpr int AL_FORMAT_MONO8 = 0x1100;
    constexpr int AL_FORMAT_MONO16 = 0x1101;
    constexpr int AL_FORMAT_STEREO8 = 0x1102;
    constexpr int AL_FORMAT_STEREO16 = 0x1103;
    constexpr int AL_FREQUENCY = 0x2001;
    constexpr int AL_BITS = 0x2002;
    constexpr int AL_CHANNELS = 0x2003;
    constexpr int AL_SIZE = 0x2004;
    constexpr int AL_UNUSED = 0x2010;
    constexpr int AL_PENDING = 0x2011;
    constexpr int AL_PROCESSED = 0x2012;
    constexpr int AL_NO_ERROR = 0;
    constexpr int AL_INVALID_NAME = 0xA001;
    constexpr int AL_INVALID_ENUM = 0xA002;
    constexpr int AL_INVALID_VALUE = 0xA003;
    constexpr int AL_INVALID_OPERATION = 0xA004;
    constexpr int AL_OUT_OF_MEMORY = 0xA005;
    constexpr int AL_VENDOR = 0xB001;
    constexpr int AL_VERSION = 0xB002;
    constexpr int AL_RENDERER = 0xB003;
    constexpr int AL_EXTENSIONS = 0xB004;
    constexpr int AL_DOPPLER_FACTOR = 0xC000;
    constexpr int AL_DOPPLER_VELOCITY = 0xC001;
    constexpr int AL_SPEED_OF_SOUND = 0xC003;
    constexpr int AL_DISTANCE_MODEL = 0xD000;
    constexpr int AL_INVERSE_DISTANCE = 0xD001;
    constexpr int AL_INVERSE_DISTANCE_CLAMPED = 0xD002;
    constexpr int AL_LINEAR_DISTANCE = 0xD003;
    constexpr int AL_LINEAR_DISTANCE_CLAMPED = 0xD004;
    constexpr int AL_EXPONENT_DISTANCE = 0xD005;
    constexpr int AL_EXPONENT_DISTANCE_CLAMPED = 0xD006;

    // EXT

    constexpr int AL_SOURCE_DISTANCE_MODEL = 0x200;

    // ALC

    constexpr int ALC_EXTENSIONS = 0x1006;
}