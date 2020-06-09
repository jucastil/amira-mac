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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_CYLINDER_SLICE_H
#define HX_CYLINDER_SLICE_H

#include <qwidget.h>

#include <mclib/McMath.h>

#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxTightConnection.h>


#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatSlider.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortButtonList.h>

#include <hxlattice/HxLatticeWinDLLApi.h>

#include <hxfield/HxScalarField3.h>
#include <hxfield/HxPortMultiChannel.h>



#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/draggers/SoTabPlaneDragger.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoTransform.h>


class QxLightBox;

class Cylinder {

private:

    McVec3f mCenter, mAxis1, mAxis2, mAxis3;
    float mRadius1, mRadius2, mHeight;

    SbMatrix mTransf; //!> transformation to cylinder coord system, used for inside test
	

public:

    Cylinder();

    Cylinder(const McVec3f &center, const McVec3f &v1, const McVec3f &v2, 
        float a, float b, float c);

    void init(const McVec3f &center, const McVec3f &v1, const McVec3f &v2, 
        float a, float b, float c,
        const SoTransform *transform=0);

    /** check if point inside. 
    only for true cylinder (circular) */
    void updateTransform(const SoTransform *transform=0);

    /// checks if point is inside cylinder
    inline bool isInside(const SbVec3f &point) const
    {	
        SbVec3f p;
        mTransf.multMatrixVec( point, p);
        return  ( fabs(p[2])  < 0.5 * mHeight && sqrt(p[0]*p[0] + p[1]*p[1]) < mRadius1) ;
    }

    inline McVec3f getCenter() const { return mCenter; }

    inline float getRadius() const { return 0.5 * (mRadius1 + mRadius2) ; }

    inline float getHeight() const { return mHeight; }

    inline void setHeight(float height) { mHeight = height;}

    void setCenter(const McVec3f &center) { mCenter = center;}

    inline McVec3f eval(float omega, float t) const
    {

        return mCenter + t * mAxis3 + cos(omega) * mAxis1 + sin(omega) * mAxis2;  
    }

    void set(float x, float y, float r)
    { 
        mCenter += x * mAxis1 + y * mAxis2; 
        mRadius2 = mRadius1 = r;
    }
};


///
class HXLATTICE_API HxCylinderSlice : public HxOverlayModule {

    HX_HEADER(HxCylinderSlice);

protected:
    /// circle and start marker 
    void addCircleToDragger();

    /// called by draggerFinishCB to update ports
    void updateDraggerPorts(); 

    static void draggerCB(void *userData,SoDragger* dragger);
    static void draggerFinishCB(void *userData,SoDragger* dragger);

    // DATA
    McHandle<SoSeparator> draggerRoot;
    McHandle<SoTransform> xform;
    McHandle<SoTabPlaneDragger> dragger;
    McHandle<SoTransform> ivTransform;
    McHandle<SoSeparator> cylinderRoot;

    SoSeparator* mDraggerCircle;   ///>  circle and marker on the dragger

    /// extra viewer
    QxLightBox* mViewer;

    Cylinder mCylinder;

    int alphaThreshold;
    unsigned int isLabelLat:1;
    unsigned int isMultiChannel:1;
    unsigned int hasField:1;

    /// orientation of base
    int mOrientation; 

    // This is true if a color field is processed.
    int rgbaSlice;

    // This is @c mc_int32 in case of color fields, @c mc_float otherwise. 
    McPrimType sliceDataType;

    /// data field for texture
    float* mTexture;
	
	/// allocated buffer for the texture
	unsigned char *mTextureBuffer;

	///allocated buffer size
	int mBufferSize;

	SoTexture2 *mTexture2;

    /// scalar data field
    HxScalarField3* mField;

    /// Length of diagonal of the input's bounding box.
    float diagonal;

    /// sets the zero angle where the slice is cut
    float mAngle;

    /// Size of texture image (128x128 on default, 256x256 in high res mode).
    SbVec2s size;

    /// stores resolutions for all levels.
    McDArray<SbVec2s> sizeTable; 

    /// current resolution level
    int mResolution;

public:
    enum SamplingMode {
        RESOLUTION=0,
        INTERPOL_DATA=1,
        INTERPOL_TEXTURE=2
    };

    /// Constructor.
    HxCylinderSlice();

    /// Destructor.
    ~HxCylinderSlice();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Automatically connects to a scalar field.
    virtual int autoConnect(HxObject* primary);

    /// show viewer
    HxPortButtonList portViewer;

    /// 0=linear range, 1=histogram equalization, 2=colormap mode
    HxPortMultiMenu portMappingType;

    /// Defines grey level window if mapping type is 0.
    HxPortFloatTextN portLinearRange;

    /// Parameter used for histogram equalization.
    HxPortIntTextN portContrastLimit;

    /// Connection to colormap.
    HxPortColormap portColormap;

    /// 0=resolution, 1=interpol uniform fields, 2=high texture quality
    HxPortGeneric portMoreOptions;

    /// How multiple slices are combined, 0=add, 1=multiply.
    HxPortMultiMenu portCombineMethod;

    /// How to use transparency (currently colorfield only)
    HxPortRadioBox portTransparency;

    /// show dragger
    HxPortToggleList portDragger;

    /// current state of dragger in plane.
    HxPortFloatTextN portCylinder;

    /// distance to cylinder center to image center in slice
    HxPortInfo portDistance;

    /// angle (in degrees) that determines the position of the vertical line along which the cylinder surface is "cut" to be then mapped on the planar slice. 
    HxPortFloatSlider portZeroAngle;

	/// high resolution
	bool mHighResolution;

    /** Check if point inside cylinder. Used when CylinderSlice defines a ROI. */
    inline  bool insideCylinder(const SbVec3f &point) const
    { return mCylinder.isInside(point); }

    /// set the resolution of level to s1 x s2
    McString setResolution(int level, int s1, int s2);

    void setZeroAngle(float angle) 
    { mAngle = McDegToRad(angle); portZeroAngle.setValue(angle); addCircleToDragger();  }     
    

protected:

    virtual void savePorts(FILE *fp);

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    // do sampling
    void sampleCylinder();

    // generate the texture object
    void computeTexture();

    void setTexture(SoTexture2* texture, int nc, int alpha=0);

    void computeSize();


    /// extracts the slice and adds it to the object pool.
    virtual McString createImage(const char* name =0);

    /// Hide displayed geometries.
    virtual void removeOverlay();




};
#endif

/// @}
