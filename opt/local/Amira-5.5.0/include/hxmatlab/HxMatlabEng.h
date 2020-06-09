/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxmatlab hxmatlab
/// @{
#ifndef HX_MATLAB_ENG_H
#define HX_MATLAB_ENG_H

#include <hxcore/HxDSO.h>
#include <hxmatlab/HxMatlabWinDLLApi.h>

// Only needed for type definitions, not for function declarations.
#include <matlab/mat.h>
#include <matlab/engine.h>

#define theMatlabEng HxMatlabEng::getInstance()

/** This Singleton allows the dynamic loading of the Matlab libraries mx, mat, eng.
  * Their respective methods are dynamically linked.
  */
class HXMATLAB_API HxMatlabEng
{
  public:

    static HxMatlabEng * getInstance();

    Engine * getMatlabEngine(const char *startcmd);

    //This int counts the number of instances that uses the same Matlab engine. 
    //It needs to be public since we need to reset this counter if we want to 
    //close the Matlab engine in HxCrashCleanUp independently of the number of instances. 
    int mNrMatlabInstances;

#define MATLAB_WRAPPER(ret,name,args) \
  public:                             \
    ret name args;                    \
  private:                            \
    typedef ret (*name##Ptr)args;     \
    name##Ptr m_##name;

    // http://www.mathworks.com/access/helpdesk_r13/help/techdoc/apiref/mx-c.html
    MATLAB_WRAPPER(mxArray*    , mxCreateNumericArray    , (int ndim,const int* dims,mxClassID classid,mxComplexity flag))
    MATLAB_WRAPPER(mxArray*    , mxCreateNumericMatrix   , (mwSize m, mwSize n, mxClassID classid, mxComplexity flag))
    MATLAB_WRAPPER(mxArray*    , mxCreateDoubleScalar    , (double value))
    MATLAB_WRAPPER(double      , mxGetScalar             , (const mxArray* pa))
    MATLAB_WRAPPER(double*     , mxGetPr                 , (const mxArray* pa))
    MATLAB_WRAPPER(void*       , mxGetData               , (const mxArray* pa))
    MATLAB_WRAPPER(void*       , mxGetImagData           , (const mxArray* pa))
    MATLAB_WRAPPER(const int*  , mxGetDimensions         , (const mxArray* pa))
    MATLAB_WRAPPER(mxArray*    , mxGetCell               , (const mxArray* pa,int i))
    MATLAB_WRAPPER(int         , mxGetString             , (const mxArray* pa,char* buf,int buflen))
    MATLAB_WRAPPER(const char* , mxGetClassName          , (const mxArray* pa))
    MATLAB_WRAPPER(mxClassID   , mxGetClassID            , (const mxArray* pa))
    MATLAB_WRAPPER(int         , mxGetNumberOfDimensions , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsComplex             , (const mxArray* pa))
    MATLAB_WRAPPER(double*     , mxGetPi                 , (const mxArray* pa))
    MATLAB_WRAPPER(void        , mxDestroyArray          , (mxArray* pa))
    MATLAB_WRAPPER(void        , mxFree                  , (void* ptr))
    MATLAB_WRAPPER(int         , mxGetM                  , (const mxArray* pa))
    MATLAB_WRAPPER(int         , mxGetN                  , (const mxArray* pa))
    MATLAB_WRAPPER(int         , mxGetNumberOfElements   , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsSparse              , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsDouble              , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsSingle              , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsInt32               , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsUint32              , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsInt16               , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsUint16              , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsInt8                , (const mxArray* pa))
    MATLAB_WRAPPER(bool        , mxIsUint8               , (const mxArray* pa))
    MATLAB_WRAPPER(void        , mxSetFieldByNumber      , (mxArray* pa, mwIndex index, int fieldnumber, mxArray *value))
    MATLAB_WRAPPER(int         , mxGetFieldNumber        , (const mxArray* pa, const char *filename))
    MATLAB_WRAPPER(mxArray*    , mxGetFieldByNumber      , (const mxArray* pa, int index, int fieldnumber))
    MATLAB_WRAPPER(mxArray*    , mxGetField              , (const mxArray* pa, int index, const char *filename))
    MATLAB_WRAPPER(mxArray*    , mxCreateString          , (const char* str))
    MATLAB_WRAPPER(mxArray*    , mxCreateStructArray     , (int ndim, const int *dims, int nfields, const char **fieldNames))
    MATLAB_WRAPPER(mxArray*    , mxCreateStructMatrix    , (mwSize m, mwSize n, int nfields, const char **fieldNames))
    MATLAB_WRAPPER(mxArray*    , mxCreateCellArray       , (mwSize ndim, const mwSize *dims))
    MATLAB_WRAPPER(mxArray*    , mxCreateCellMatrix      , (mwSize m, mwSize n))
    MATLAB_WRAPPER(void        , mxSetCell               , (mxArray *pa, mwIndex i, mxArray *value))

    // http://www.mathworks.com/access/helpdesk_r13/help/techdoc/apiref/mat-c.html
    MATLAB_WRAPPER(MATFile* , matCreateMATFile       , (const char* filename,FILE* fp,const char* mode))
    MATLAB_WRAPPER(MATFile* , matOpen                , (const char* filename,const char* mode))
    MATLAB_WRAPPER(int      , matClose               , (MATFile* pMF))
    MATLAB_WRAPPER(FILE*    , matGetFp               , (MATFile* pMF))
    MATLAB_WRAPPER(int      , matPutVariable         , (MATFile* pMF,const char* name,const mxArray* pA))
    MATLAB_WRAPPER(int      , matPutVariableAsGlobal , (MATFile* pMF,const char* name,const mxArray* pA))
    MATLAB_WRAPPER(mxArray* , matGetVariable         , (MATFile* pMF,const char* name))
    MATLAB_WRAPPER(mxArray* , matGetNextVariable     , (MATFile* pMF,const char** nameptr))
    MATLAB_WRAPPER(mxArray* , matGetNextVariableInfo , (MATFile* pMF,const char** nameptr))
    MATLAB_WRAPPER(mxArray* , matGetVariableInfo     , (MATFile* pMF,const char* name))
    MATLAB_WRAPPER(int      , matDeleteVariable      , (MATFile* pMF,const char* name))
    MATLAB_WRAPPER(char**   , matGetDir              , (MATFile* pMF,int* num))

    // http://www.mathworks.com/access/helpdesk_r13/help/techdoc/apiref/eng-c.html
    MATLAB_WRAPPER(int      , engEvalString    , (Engine* ep,const char* string))
    MATLAB_WRAPPER(Engine*  , engOpenSingleUse , (const char* startcmd,void* reserved,int* retstatus))
    MATLAB_WRAPPER(int      , engSetVisible    , (Engine* ep,bool newVal))
    MATLAB_WRAPPER(int      , engGetVisible    , (Engine* ep,bool* bVal))
    MATLAB_WRAPPER(Engine*  , engOpen          , (const char* startcmd))
    MATLAB_WRAPPER(int      , engClose         , (Engine* ep))
    MATLAB_WRAPPER(mxArray* , engGetVariable   , (Engine* ep,const char* name))
    MATLAB_WRAPPER(int      , engPutVariable   , (Engine* ep,const char* var_name,const mxArray* ap))
    MATLAB_WRAPPER(int      , engOutputBuffer  , (Engine* ep,char* buffer,int buflen))

#undef MATLAB_WRAPPER

  private:

    Engine * mMatlabEngine;

    HxMatlabEng();
    ~HxMatlabEng();

    enum MatlabVersion {R2007b, R2008a};

    MatlabVersion mVersion;
    MatlabVersion getmVersion(Engine * m_eng);

    HxDSO libmx;
    HxDSO libmat;
    HxDSO libeng;
};
#endif

/// @}
