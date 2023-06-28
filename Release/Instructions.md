Copyright Joshuah Rainstar 2023 
Licensed under the Free as in Free Toothpaste license


Instructions for how to use the DLL:
The dll allocates a bunch of stack, very little heap.
All statically allocated std::arrays- no vectors!
<complex><numeric><algorithm><cmath><array>
Does not rely on any external libraries or runtimes.


```cpp
extern "C" {
    using dfloat = double;
    __declspec(dllexport) void setConstant(double* value) {
        filter.setConstant(*value); #between 0.045 and 0.085
    }

    __declspec(dllexport) void set_MULT(double* value) {
        filter.set_MULT(*value);#between 0 and 1
    }

    __declspec(dllexport) void set_NBINS(int* value) {
        filter.set_NBINS(*value); #between 1 and 255
    }

    __declspec(dllexport) void process(std::array<dfloat, 8192>* input) {
            filter.process(*input);  //only use with 48khz inputs
        }
}
```
