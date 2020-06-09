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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_DEFINE_ROI_H
#define HX_DEFINE_ROI_H


#include <Inventor/SbLinear.h>
#include <mclib/McVec3f.h>

#include <hxcore/HxSpatialData.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxRoiInterface.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxFieldWinDLLApi.h>
#include <mclib/McHandle.h>
#include <Inventor/draggers/SoTabBoxDragger.h>
#include <hxcore/HxPortInfo.h>

class HxGLPolyLine;
/// This module defines a region-of-interest with the shape of an 
/// axis-aligned 3D box. This box can be used to restrict the output 
/// of many visualization modules.

class HXFIELD_API HxSelectRoi : public HxModule {

  HX_HEADER(HxSelectRoi);

  public:
    /// Default constructor.
    HxSelectRoi();

    ///
    ~HxSelectRoi();

    /// Invokes actual computation.
    virtual void compute();

    ///
    virtual void update();

    /// TODO: cleanup SP
//    virtual McTypedObject* getInterface(const McTypeInfo* t);

    virtual void getRoi(float bb[6]) const;

    virtual void getTransformation( McMat4f & outTrans ) const;

    class HxRoiInterfaceImpl;

    ///
    HxPortFloatTextN portMinimum;

    ///
    HxPortFloatTextN portMaximum;

    ///
    HxPortToggleList portOptions;

    /// Do it button.
    HxPortButtonList portAction;

    ///
    HxPortInfo portMemSizeInfo;


    McHandle<SoTabBoxDragger> dragger;

    void setMinMax(const McVec3f& bmin,const McVec3f& bmax);

 
    // The code of this method is in the header file because it is used
    // within hxvolumeviz/HxSelectROILDM.cpp which needs it to build the 
    // code from the template. It would be solved by linking hxfield 
    // with hxvolumeviz but it would introduce a cyclic dependency
    template<typename TYPE> static
    void computeSelectedDataSize(TYPE roiType)
    {
        McBox3f box;
        mcuint64 size;
        HxSpatialData* data;
        data  = hxconnection_cast<HxSpatialData>(roiType->portData);
        for ( int i=0 ; i<3 ; i++ )
        {
            box[2*i]   = roiType->portMinimum.getValue(i);
            box[2*i+1] = roiType->portMaximum.getValue(i);
        }
        if ( data && data->getMemSize(size,box) )
        {
            roiType->portMemSizeInfo.printf("%10.2f MB", (float)size/(float)(1024*1024));
            roiType->portMemSizeInfo.show();
        }
        else
        {
            roiType->portMemSizeInfo.hide();
        }
    }

  protected:

    //Make
    void doIt();

    HxGLPolyLine* polyLine;

    void cutIn();

    static void viewerSelectCB(void* userData);

    void viewerSelect();

    void getBoundingBox();
    void setPorts();
    void startDrawing();

    int initialized, blockDragger;


    float bbox[6],roibox[6];

    void finishDragging();
    void constrainDragger();
    static void finishDraggingCB(void* userData, SoDragger*);
    static void constrainDraggerCB(void* userData, SoDragger*);
    void adjustDragger();
    
};

#endif

/// @}
