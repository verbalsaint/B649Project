#include "headers.h"
#include "vstbbmatrix.h"
#include "mextest.h"

using namespace tbb;
using namespace std;
UV(TBB)

int main(int argc, char *argv[])
{


    // mexFunction(1,0,2,0);

    //    (int* lMatrix,int lrow,int lcol,int* rMatrix,int rrow,int rcol,int* ResultMatrix);


    task_scheduler_init init;

    double a[12] = {1,2,3,3,2,1}; //2 * 3
    double b[12] = {3,2,1,1,2,3}; // 3 * 2
    double r[9] = {0,0,0,0,0,0,0,0,0};
    TBBMatrix tmt(a,3,4,b,4,3,r);
    parallel_for(blocked_range<size_t>(0,4),tmt,auto_partitioner());
    for(int i=0;i<9;++i){
        if(i % 3 == 0)
            cout << endl;
        cout << r[i] << " ";
    }
    cout << endl;
    init.terminate();
    return 0;
}
