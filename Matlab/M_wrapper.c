#include "mex.h"
#include "../C/src/stats.h"
#include "../C/src/helper_functions.h"
#include "../C/src/CO_NonlinearAutocorr.h"

void M_wrapper_double( int nlhs, mxArray *plhs[], 
    int nrhs, const mxArray*prhs[], 
    double (*f) (const double*, const int), int normalize )
     
{ 
    double *inMatrix;       /* 1xN input matrix */
    int ncols;
    double *outMatrix; /* output matrix */
    
    // check inputs
    if(nrhs != 1) {
        mexErrMsgIdAndTxt("catchaMouse16:nrhs",
                          "One input required.");
    }
    if(nlhs > 1) {
        mexErrMsgIdAndTxt("catchaMouse16:nlhs",
                          "One output required.");
    }
    if( !mxIsDouble(prhs[0]) || 
        mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("catchaMouse16:notDouble",
            "Input vector must be type double.");
    }
    if(mxGetM(prhs[0]) != 1) {
        mexErrMsgIdAndTxt("catchaMouse16:notRowVector",
                          "Input must be a row vector.");
    }
    
    // get input
    inMatrix = mxGetPr(prhs[0]);
    ncols = mxGetN(prhs[0]);
    
    // set output
    plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    outMatrix = mxGetPr(plhs[0]);
    
    // calculate result
    if (normalize){
        
        double * y_zscored = malloc(ncols * sizeof * y_zscored);
        zscore_norm2(inMatrix, ncols, y_zscored);

        outMatrix[0] = f(y_zscored, ncols);

        free(y_zscored);
    } 
    else {
        outMatrix[0] = f(inMatrix, ncols);
    }   
    
    return;
    
}

void M_wrapper_int( int nlhs, mxArray *plhs[], 
    int nrhs, const mxArray*prhs[], 
    int (*f) (const double*, const int), int normalize )
     
{ 
    double *inMatrix;       /* 1xN input matrix */
    int ncols;
    int *outMatrix; /* output matrix */
    
    // check inputs
    if(nrhs != 1) {
        mexErrMsgIdAndTxt("catchaMouse16:nrhs",
                          "One input required.");
    }
    if(nlhs > 1) {
        mexErrMsgIdAndTxt("catchaMouse16:nlhs",
                          "One output required.");
    }
    if( !mxIsDouble(prhs[0]) || 
        mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("catchaMouse16:notDouble",
            "Input vector must be type double.");
    }
    if(mxGetM(prhs[0]) != 1) {
        mexErrMsgIdAndTxt("catchaMouse16:notRowVector",
                          "Input must be a row vector.");
    }
    
    // get input
    inMatrix = mxGetPr(prhs[0]);
    ncols = mxGetN(prhs[0]);
    
    // set output
    plhs[0] = mxCreateNumericMatrix(1,1, mxINT32_CLASS, mxREAL);
    outMatrix = (int*)mxGetData(plhs[0]);
    
    // calculate result
    if (normalize){
        
        double * y_zscored = malloc(ncols * sizeof * y_zscored);
        zscore_norm2(inMatrix, ncols, y_zscored);

        outMatrix[0] = f(y_zscored, ncols);

        free(y_zscored);
    } 
    else {
        outMatrix[0] = f(inMatrix, ncols);
    }   
    
    return;
    
}
