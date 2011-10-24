#ifndef MEXEXCEPTION_H
#define MEXEXCEPTION_H
#include "headers.h"



VERBALSAINTNS(MEX)

using namespace std;

class MexException : public exception{
private:
    string _errorid;
    string _errormsg;
    string _wholemsg;
public:
    MexException(string mexFunction,string where){
        stringstream ss;
        ss << "MATLAB:" ;
        ss << mexFunction;
        ss << where;
        _errorid = ss.str();
    }
    virtual ~MexException() throw(){

    }
    virtual const char* what() const throw(){

        return _wholemsg.c_str();
    }
    //---Mex
    void MEXErrMsgIdAndTxt(){
        mexErrMsgIdAndTxt(_errorid.c_str(),_errormsg.c_str());
    }
    void MEXWarnMsgIdAndTxt(){
       mexWarnMsgIdAndTxt(_errorid.c_str(),_errormsg.c_str());
    }
    void setErrorMsg(string emsg){
        _errormsg = emsg;
        _wholemsg = _errorid + _errormsg;
    }
};

VERBALSAINTNSEND
#endif // MEXEXCEPTION_H
