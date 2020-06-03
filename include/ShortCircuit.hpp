#pragma once

#include "windows.h"
#include "OpenALAPI.h"

namespace Short
{
    class Circuit final
    {
private:
        HINSTANCE library_handle = nullptr;

        void Init(char* path = nullptr);

public:
        Circuit();
        ~Circuit();

        OpenALFunctions functions{};
    };
}