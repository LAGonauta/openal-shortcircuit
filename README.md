# OpenAL ShortCircuit

Library to allow one to use any OpenAL library in Minecraft.
It also has some workarounds for the missing `AL_EXT_source_distance_model` extension on Creative's OpenAL when using hardware OpenAL on a X-Fi.

# Configuring

One can configure the library through environment variables.
- `SC_OAL_LIBRARY_DEVICE_NAME`, sets the device to be used, such as `OpenAL Soft` or `SB X-Fi Audio [0001]`. Also supports full enumerated names if supported by the driver.
- `SC_OAL_LIBRARY_BINARY_PATH`, sets the OpenAL binary/driver to use, such as `C:\Windows\System32\OpenAL32.dll` or `C:\Windows\System32\soft_oal.dll`.

# How to compile on Windows

- Install MSYS2 and build packages such as `cmake` and `g++`
- git clone
- mkdir build && cd build && cmake -G "MSYS Makefiles" .. && make