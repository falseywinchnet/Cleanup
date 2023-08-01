// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN		// exclude some windows headers

#include "pch.h"
#include "cleanup.h"
static Filter filter;

extern "C" {
    struct Version {
        const char* version;
    };

    using dfloat = DF;
    __declspec(dllexport) void setConstant(double* value) {
        filter.setConstant(*value);
    }

    __declspec(dllexport) void set_MULT(double* value) {
        filter.set_Mult(*value);
    }
    __declspec(dllexport) void set_Renorm(bool* value) {
        return;
    }
    __declspec(dllexport) void set_PCS(bool* value) {
        return;
    }

    __declspec(dllexport) void set_Silent(bool* value) {
        filter.set_Silent(*value);
    }


    __declspec(dllexport) void set_NBINSHZ(int* value) {
        filter.set_NBINSHZ(*value);
    }

    __declspec(dllexport) void set_NBINS(int* value) {
        filter.set_NBINS(*value);
    }
    __declspec(dllexport) void getResult(int* value) {
        filter.getResult(*value);
    }
    __declspec(dllexport) void process(std::array<dfloat, 8192>* input) {
        filter.process(*input);  // dereference the pointer to get the array
    }

    __declspec(dllexport) void getEntropy(std::array<dfloat, 64>* input) {
        filter.getEntropy(*input);  // dereference the pointer to get the array
    }
    __declspec(dllexport) Version version() {
        Version v;
        v.version = "1.7.21 Build date 2023-07-21";
        return v;
    }

}


    BOOL APIENTRY DllMain(HMODULE hModule,
        DWORD  ul_reason_for_call,
        LPVOID lpReserved
    )
    {

        switch (ul_reason_for_call)
        {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
        }
        return TRUE;
}

