#ifndef VSMATRIX_H
#define VSMATRIX_H


#include "verbalsaint.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <ctime>
#include <cstring>
#include <tbb/blocked_range.h>



VERBALSAINTNS(VSMATRIX)

namespace{
    boost::mt19937 genno(std::time(0));
    boost::uniform_int<> rdvalue(0,1000);
}

template<class TType>//,class TParser = AutoParser>
struct VSMatrix
{
    VSMatrix(unsigned int row,unsigned int col,bool autogen);
    VSMatrix(const VSMatrix& other);
    VSMatrix(const TType*& other);


    VSMatrix& operator=(const VSMatrix& other);
    bool operator==(const VSMatrix& other) const;
    VSMatrix operator*(const VSMatrix& other) const;


    ~VSMatrix();
    void printme();
private:    
    unsigned int _mrow;
    unsigned int _ncol;
    TType* _matrix;
    TType* _tmatrix;
    unsigned long _hashvalue;
    bool _autogen;
};

//-----------
    VSMatrix operator*(const VSMatrix& other) const;

//--------

template <class TType> VSMatrix<TType>::VSMatrix(const TType*& other,size_t irow,size_t icol):_mrow(irow),_ncol(icol),_matrix(new TType[mrow*ncol]),_tmatrix(new TType[mrow*ncol]),_autogen(false){
    memcpy(_matrix,other,irow*icol*sizeof(TType));
    for(int r=0;r<_mrow;++r){
        for(int c=0;c<_ncol; ++c){
            _tmatrix[r+c*_mrow] = _matrix[c + r*_ncol];
            _hashvalue += (c + r*_ncol) ^ _matrix[c + r*_ncol];
        }
    }
}

template <class TType> VSMatrix<TType>::VSMatrix(unsigned int mrow,unsigned int ncol,bool autogen):_mrow(mrow),_ncol(ncol),_matrix(new TType[mrow*ncol]),_tmatrix(new TType[mrow*ncol]),_autogen(autogen)
{    
    unsigned long mn = mrow*ncol;

    for(int i = 0; i< mn; ++i ){
        _matrix[i] = _autogen ? rdvalue(genno): 0 ;
        _hashvalue += i ^ _matrix[i];
    }

    for(int r=0;r<_mrow;++r){
        for(int c=0;c<_ncol; ++c){
            _tmatrix[r+c*_mrow] = _matrix[c + r*_ncol];
        }
    }
}


template <class TType> VSMatrix<TType>::VSMatrix(const VSMatrix& other):_mrow(other._mrow),_ncol(other._ncol),_matrix(new TType[_mrow*_ncol]),_tmatrix(new TType[_mrow*_ncol]),_hashvalue(other._hashvalue),_autogen(false)
{
    memcpy(_matrix,other._matrix,_mrow*_ncol*sizeof(TType));
    memcpy(_tmatrix,other._tmatrix,_mrow*_ncol*sizeof(TType));
}

template <class TType> VSMatrix<TType>::~VSMatrix()
{
    delete [] _matrix;
    delete [] _tmatrix;
}

template <class TType> VSMatrix<TType>& VSMatrix<TType>::operator=(const VSMatrix<TType>& other)
{
    _mrow = other._mrow;
    _ncol = other._ncol;
    unsigned long mn = _mrow*_ncol;
    //not safe : but for now~
    if(_matrix){
        delete [] _matrix;
    }
    _matrix = new TType[mn];

    if(_tmatrix){
        delete [] _tmatrix;
    }
    _tmatrix = new TType[mn];

    for(int i=0;i<mn ; ++i){
        _matrix[i] = other._matrix[i];
    }
    for(int i=0;i<mn ; ++i){
        _tmatrix[i] = other._tmatrix[i];
    }

    return *this;
}

template <class TType> bool VSMatrix<TType>::operator==(const VSMatrix& other) const
{  
    if(_mrow != other._mrow || _ncol != other._ncol){
        return false;
    }

    if(_hashvalue == other._hashvalue)
        return true;
    else return false;
}

template <class TType> void VSMatrix<TType>::printme()
{
#include <iostream>
    using namespace std;
    cout << "**Print the matrix : ";
    for(int i = 0 ; i<_mrow*_ncol ; ++i){
        if(i%_ncol== 0){
            cout << endl;
        }
        cout << _matrix[i] << " " ;
    }

    cout << endl;

    cout << "**Print the tmatrix : ";
    for(int i = 0 ; i<_mrow*_ncol ; ++i){
        if(i%_mrow == 0){
            cout << endl;
        }
        cout << _tmatrix[i] << " " ;
    }
}

VERBALSAINTNSEND

#endif // VSMATRIX_H

