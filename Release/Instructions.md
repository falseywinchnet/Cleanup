Copyright Joshuah Rainstar 2023 
Licensed under the Free as in Free Toothpaste license


Instructions for how to use the DLL:
The dll allocates a bunch of stack, very little heap.
All statically allocated std::arrays- no vectors!
<complex><numeric><algorithm><cmath><array>
Does not rely on any external libraries or runtimes.


```cpp
//example implementation shim
#include <windows.h>
#include <array>

using dfloat = double;

extern "C" {
    __declspec(dllimport) void setConstant(double* value); #ensure range is between 0.045 and 0.085, defaults to 0.057
    __declspec(dllimport) void set_MULT(double* value); #ensure range is between 0 and 1, defaults to 1
    __declspec(dllimport) void set_NBINS(int* value); #ensure range is between 5 and 257, defaults to 37
    __declspec(dllimport) void process(std::array<dfloat, 8192>* input); #ensure sampling rate is 48k
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

    FreeLibrary(hGetProcIDDLL);
    return 0;
}
```
