#ifndef VSTBBMATRIX_H
#define VSTBBMATRIX_H
#include "headers.h"
#include <strings.h>




VERBALSAINTNS(TBB)
using namespace tbb;
using namespace std;

struct TBBMatrix{
private:
    double* lhsMatrix;
    size_t _lhsrow;
    size_t _lhscol;
    double* rhsMatrix;
    size_t _rhsrow;
    size_t _rhscol;
    double* resultMatrix;


private:
    void calculate(size_t r) const{
        size_t lhs_row = r / _rhscol;
        size_t rhs_col = r % _rhscol;
        for(size_t i=0;i<_lhscol;++i){
            resultMatrix[r] += lhsMatrix[i+lhs_row*_lhscol] * rhsMatrix[i*_rhscol + rhs_col];
        }
    }


    void calculateC(int r) const{
        size_t lhs_row = r%_lhsrow; //Left start row
        size_t rhs_col = r/_lhsrow; //right start col

        for(size_t i=0;i<_lhscol;++i){
            resultMatrix[r] += lhsMatrix[lhs_row + _lhsrow * i] * rhsMatrix[i + rhs_col*_rhsrow];
        }


    }
public:
    TBBMatrix(double* lMatrix,size_t lrow,size_t lcol,double* rMatrix,size_t rrow,size_t rcol,double* ResultMatrix):
    lhsMatrix(lMatrix),_lhsrow(lrow),_lhscol(lcol),rhsMatrix(rMatrix),_rhsrow(rrow),_rhscol(rcol),resultMatrix(ResultMatrix){}


    void operator()(const blocked_range<size_t> range) const{
        for(size_t i=range.begin(); i!=range.end();++i){
            calculateC(i);
        }
    }

};



VERBALSAINTNSEND
#endif // VSTBBMATRIX_H

