# Cleanup DLL Instructions
Copyright Joshuah Rainstar 2023 \
Licensed under the Free as in Free Toothpaste license


- The dll allocates a bunch of stack, very little heap.
- it links to complex, numeric, algorithm, cmath, and array headers only. 
- no dynamic memory- all static. 16mb of stack reserved per instance. At most- 5mb used.
- absolutely no memset or recursion anywhere- all standard arrays and clean behavior.
- you should probably apply ephraim-malah and spectral shaping in advance of this filter.
    - such is not included in cleanup, to ensure its behavior is predictable. cleanup = remove noise. Not improve signal.
    - As such, such methods should proceed cleanup, with the caveat that intelligent squelching will not work the same, perhaps at all.
    - Additionally, you should usually if not always run a notch filter before cleanup.
- all settings are optional- the program will work without initializing them.

```cpp
//example implementation shim
#include <windows.h>
#include <array>

using dfloat = float; //for fast
using dfloat = double; //for correct

extern "C" {
    struct Version {
        const char* version;
    };

    __declspec(dllimport) void setConstant(double* value); //good range is between 0.045 and 0.085, defaults to 0.057, valid is 0.001 to 1
    __declspec(dllimport) void set_MULT(double* value); DEPRECATED
    __declspec(dllimport) void set_NBINS(int* value); //ensure range is between 5 and 257, defaults to 37
    __declspec(dllimport) void set_NBINSHZ(int* value); //set to your bandwidth in hz of what you're sending us
    //note: you only need to either set the HZ or the bins. Interally, bins is set based on Hz.
    __declspec(dllimport) void set_Silent(bool* value); //enable for auto-squelch, defaults to true
    __declspec(dllimport) void set_Renorm(bool* value);DEPRECATED
    __declspec(dllimport) void set_PCS(bool* value);DEPRECATED
    __declspec(dllimport) void getResult(int* value);//2 = there was good signal, 1 = first 384 samples were from previous frame overlap, 0 = nothing
    __declspec(dllimport) void process(std::array<dfloat, 8192>* input); //ensure sampling rate is 48k
    __declspec(dllimport) void getEntropy(std::array<dfloat, 64>* input); //get the current entropy samples
    __declspec(dllimport) Version version();
    }
}

int main() {
    HINSTANCE hGetProcIDDLL = LoadLibrary("path to cleanup.dll");

    if (!hGetProcIDDLL) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    // resolve function setConstant from the DLL
    auto funcSetConstant = (void (*)(double*)) GetProcAddress(hGetProcIDDLL, "setConstant");
    
    // resolve function set_MULT from the DLL
    auto funcSetMult = (void (*)(double*)) GetProcAddress(hGetProcIDDLL, "set_MULT");

    // resolve function set_NBINS from the DLL
    auto funcSetNBins = (void (*)(int*)) GetProcAddress(hGetProcIDDLL, "set_NBINS");
    
    // resolve function process from the DLL
    auto funcProcess = (void (*)(std::array<dfloat, 8192>*)) GetProcAddress(hGetProcIDDLL, "process");

    auto funcEntropy = (void (*)(std::array<dfloat, 64>*)) GetProcAddress(hGetProcIDDLL, "getEntropy");

    if (!funcSetConstant || !funcSetMult || !funcSetNBins || !funcProcess) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    // Now you can call the functions
    double constant = 0.057;
    funcSetConstant(&constant);

    double mult = 1.0;
    funcSetMult(&mult);

    int nBins = 37;
    funcSetNBins(&nBins);

    std::array<dfloat, 8192> inputArray;
    funcProcess(&inputArray); //will impose a fixed 170.66ms delay

    std::array<dfloat, 64> entArray;
    funcEntropy(&entArray); //will return the entropy values

    FreeLibrary(hGetProcIDDLL);
    return 0;
}
```


