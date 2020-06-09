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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef HX_MOSAICTODISKDATA_H
#define HX_MOSAICTODISKDATA_H

#include "HxSkeletonWinDLLApi.h"
#include <Inventor/SbLinear.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxCompModule.h>

class HxDiskData;
class HxLattice3;
class HxLDAfile;
class HxTabBox;
class HxMosaic;

/** Takes an HxMosaic as input and samples all the bricks onto a HxLDAfile.
    The first brick must be a HxUniformScalarField3 and
    specifies the type of the field.
  */
class HXSKELETON_API HxMosaicToDiskData : public HxCompModule {

    HX_HEADER (HxMosaicToDiskData);

    public:
        ///
        HxMosaicToDiskData (bool slave = FALSE);
        ///
        ~HxMosaicToDiskData ();

        ///
        HxPortInfo portInfo;

        ///
        HxPortFilename portFilename;

        ///
        HxPortMultiMenu portInterpol;

        ///
        HxPortToggleList portOptions;
        ///
        HxPortRadioBox portSpecify;
        ///
        HxPortFloatTextN portDims;
        ///
        HxPortFloatTextN portVoxelSize;
        ///
        HxPortIntTextN portBorder;
        ///
        HxPortDoIt portAction;

		HxDiskData* res;

        ///
        virtual void update ();

        ///
        virtual void compute ();

        /// interpol: 0 - NN, 1 - linear, 2 - lanczos
        void sampleAll (HxMosaic* src, HxDiskData* res
                              , int interpol = 1, int blend = 0);

        ///
        virtual int parse(Tcl_Interp* t, int argc, char **argv);
    private:

		bool slaveStatus;
};

#endif

/// @}