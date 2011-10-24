#ifndef MEXARGCHECK_H
#define MEXARGCHECK_H
#include "headers.h"
#include "mexpackage.h"

VERBALSAINTNS(MEX)

class MexArgChecker{
private:
    int _nlhs;
    int _nrhs;
private:
    MexArgChecker(const MexArgChecker&);
    void operator=(const MexArgChecker&);
public:
    MexArgChecker(int nlhs,int nrhs):_nlhs(nlhs),_nrhs(nrhs){

    }

    //Mex:
    int checkRhsArgNo(int nrhs){
        return _nrhs == nrhs ? 0 : -1;
    }
    int checkLhsArgNo(int nlhs){
        return _nlhs == nlhs ? 0 : -1;
    }
    void checkMxArrayType(const mxArray *array_ptr){
        MexPackage::MEXPrintf(MexPackage::MEXGetClassName(array_ptr));
    }

};

VERBALSAINTNSEND
#endif // MEXARGCHECK_H
