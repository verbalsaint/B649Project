#ifndef MEXTEST_H
#define MEXTEST_H
#include "headers.h"

VERBALSAINTNS(MEX)
using namespace std;

struct MexPackage{
    static void MEXPrintf(string msg){
        mexPrintf(msg.c_str());
    }
    static mxClassID MEXGetClassID(const mxArray *array_ptr){
        mxClassID  category;
        return category = mxGetClassID(array_ptr);
    }
    static string MEXGetClassName(const mxArray *pm){
        return string(mxGetClassName(pm));
    }
};

VERBALSAINTNSEND
#endif // MEXTEST_H
