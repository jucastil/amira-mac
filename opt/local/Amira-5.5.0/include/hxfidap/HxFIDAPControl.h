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

/// @addtogroup hxfidap hxfidap
/// @{
#ifndef HX_FIDAP_CONTROL_H
#define HX_FIDAP_CONTROL_H

#include <math.h>
#include <stdio.h>
#include <mclib/McFilename.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxsurface/HxSurface.h>
#include <hxsurface/HxSurfaceField.h>
#include <hxsurface/HxSurfaceVectorField.h>
#include <hxsurface/HxSurfaceScalarField.h>
#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxTetraData.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxTetraScalarField3.h>
#include <hxfield/HxTetraVectorField3.h>
#include <hxtime/HxDynamicDataCtrl.h>

#include <hxfidap/HxFidapWinDLLApi.h>

/// Controller class for time series in FIDAP neutral format.
class HXFIDAP_API HxFIDAPControl : public HxDynamicDataCtrl {

  HX_HEADER(HxFIDAPControl);
  
  public:
    /// Constructor.
    HxFIDAPControl();

    /// Initializes the module with a new data file.
    void connectToFile(const char* filename);

    /// Overloaded method, called whenever a new time step should be read.
    void newTimeStep(int timeStep);

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Saves state of module as a script.
    virtual void savePorts(FILE* fp);

    /// Checks if result can be recomputed.
    virtual int canCreateData(HxData* data, McString &createCmd);

    /// Returns 0, thus preventing that a result can be connected by hand.
    virtual int checkResult(int&, HxData*);

    /// Returns the number of time steps.
    int getNumTimeSteps() const { return nTS; }

  protected:
    ~HxFIDAPControl();
    void readFields();
    int readBasics();
    char getSField(const char* );
    char getTField(const char* );

    int nTS;
    long tsbeg;
    FILE* fp;
    McDArray<long> posF;
    HxSurface* surface;
    HxTetraGrid* tetragrid;
    McFilename filename;
    int nNodes,nVel;
    int hasSurface,hasTetra,hasHexa;

    enum {
        surfaceId=0,
        tetraId,
        vFieldId,
        pFieldId,
        tFieldId,
        cFieldId,
        tkeFieldId,
        tdFieldId,
        dFieldId
    };
    
    HxSurfaceVectorField* vField;   
    HxSurfaceScalarField* pField;
    HxSurfaceScalarField* tField;
    HxSurfaceScalarField* dField;
    HxSurfaceScalarField* cField;
    HxSurfaceScalarField* tkeField;
    HxSurfaceScalarField* tdField;

    HxTetraVectorField3* vTField;   
    HxTetraScalarField3* pTField;
    HxTetraScalarField3* tTField;
    HxTetraScalarField3* dTField;
    HxTetraScalarField3* cTField;
    HxTetraScalarField3* tkeTField;
    HxTetraScalarField3* tdTField;
    
    char firstTime;

    float *pData,*tData,*dData,*cData,*tkeData,*tdData;
    McVec3f * vData;
};

#endif

/// @}
