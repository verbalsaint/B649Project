#ifndef VSTEST_H
#define VSTEST_H
#include "headers.h"
#include "mexexception.h"
#include "mexargcheck.h"
#include "mexpackage.h"
#include "vstbbmatrix.h"




/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{    
    UV(MEX)
    UV(TBB)
    using namespace std;
    using namespace tbb;
    string FUNCNAME("tbbtest");

    size_t aRow;
    size_t aCol;
    size_t bRow;
    size_t bCol;
    /* variable declarations here */
    try{
        MexArgChecker mac(1/*nlhs number*/,2/*nrhs number*/);
        if(mac.checkLhsArgNo(nlhs) == -1){
            MexException me(FUNCNAME,"MexArgChecker.checkLhsArgNo");
            me.setErrorMsg("nlhs is not 1");
            throw me;
        }
        if(mac.checkRhsArgNo(nrhs) == -1){
            MexException me(FUNCNAME,"MexArgChecker.checkRhsArgNo");
            me.setErrorMsg("nrhs is not 2");
            throw me;
        }
        aCol = mxGetN(prhs[0]);
        bRow = mxGetM(prhs[1]);

        if(aCol != bRow){
            MexException me(FUNCNAME,"ColNotEqRow");
            me.setErrorMsg("Lhs Col != Rhs Row");
            throw me;
        }

        aRow = mxGetM(prhs[0]);
        bCol = mxGetN(prhs[1]);
    }
    catch(MexException& ME){
        ME.MEXErrMsgIdAndTxt();
    }

    stringstream ss;
    ss << "aRow : " << aRow << " aCol : " << aCol << " bRow:" << bRow << " bCol:"<< bCol << endl;
    MexPackage::MEXPrintf(ss.str());
    ss.str("");

    double *inMatrixA;      /* In matrix A*/
    double *inMatrixB;      /* In matrix B*/
    double *outMatrix;      /* output matrix */
    //    Add these statements to the code section of mexFunction:
    inMatrixA = mxGetPr(prhs[0]);
    inMatrixB = mxGetPr(prhs[1]);

//    for(int i = 0; i<aRow*aCol; ++i){
//        ss << inMatrixA[i] << " ";
//    }
//    ss<<endl<<endl;
//    MexPackage::MEXPrintf(ss.str());
//    ss.str("");

//    for(int i = 0; i<bRow*bCol; ++i){
//        ss << inMatrixB[i] << " ";
//    }
//    ss<<endl<<endl;
//    MexPackage::MEXPrintf(ss.str());
//    ss.str("");

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(aRow,bCol,mxREAL);
    /* get a pointer to the real data in the output matrix */
    outMatrix = mxGetPr(plhs[0]);

    TBBMatrix tmt(inMatrixA,aRow,aCol,inMatrixB,bRow,bCol,outMatrix);

    task_scheduler_init init;

    tick_count t0 = tick_count::now();
    parallel_for(blocked_range<size_t>(0,aRow*bCol),tmt,auto_partitioner());
    //    for(int i=0;i<9;++i){
    //        if(i % 3 == 0)
    //            cout << endl;
    //        cout << r[i] << " ";
    //    }
    //    cout << endl;
    tick_count t1 = tick_count::now();

    ss << "TBB Time : " << (t1-t0).seconds() <<endl;
    MexPackage::MEXPrintf(ss.str());
    init.terminate();

}



#endif // VSTEST_H
