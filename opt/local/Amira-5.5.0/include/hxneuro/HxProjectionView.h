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

/// @addtogroup hxneuro hxneuro
/// @{
#ifndef HX_PROJECTION_VIEW
#define HX_PROJECTION_VIEW

#include <mclib/McBox3i.h>
#include <mclib/McHandle.h>
#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxPortMultiChannel.h>
#include <hxneuro/HxNeuroWinDLLApi.h>

#include <hxlattice/HxCylinderSlice.h>
#include <hxcore/HxRoiInterface.h>

#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

class SoShapeKit;
class SoCoordinate3;
class SoTabBoxDragger;
class SoComplexity;
class SoTextureCoordinate2;
class SoTexture2;
class SoFaceSet;
class SoSeparator;
class SoTransform;
class SoCoordinate3;
class SoDragger;
class SoTranslate1Dragger;
class SoEventCallback;
class SoMouseButtonEvent;
class HxColorwash;

/// Prototype of projection view pick event callback.
typedef int (*PickEventCallback)(const SbVec3f& pos,
    const SoMouseButtonEvent* event, void* userData);

/// Class for computing and displaying projections along the main axes.
class HXNEURO_API HxProjectionView : public HxModule
{
  HX_HEADER(HxProjectionView);
  
  public:
    /// Constructor.
    HxProjectionView();
  
    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    // Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Register a pick event callback. The callback is invoked whenever
	the user picks the plane with the mouse. This can be used by
	other modules for example to evaluate the field at a particular
	location or to define a seed point for region growing. If the
	callback returns 0, the translational dragger is inhibited.
	Otherwise the plane can be dragged as usual. */
    void addPickCallback(PickEventCallback f, void* data);

    /// Remove a pick event callback.
    void removePickCallback(PickEventCallback f, void* data);

    /// Given pointOnSlice, find the brightest point in the volume.
    bool findPoint3D(McVec3f& point3D, const McVec3f& pointOnSlice, int orientation=-1);

    /// Connection to a HxRoiInterface or a HxCylinderSlice
    HxConnection portVolume;

    /// Options port (interpolate, inverse, lighting)
    HxPortToggleList portInterpolate;

    /// Slices to be displayed (yz, xz, xy)
    HxPortToggleList portSlices;

    /// Projection mode (max, min, depth, depth+max, average) and mapping (linear, histo, colormap)
    HxPortMultiMenu portProjectionMapping;

    /// Multi-channel toggles
    HxPortMultiChannel portMultiChannel;

    /// Data window for linear mapping
    HxPortFloatTextN portLinearRange;

    /// Contrast control for histo mapping
    HxPortIntTextN portContrastLimit;

    /// Colormap for pseudo-color mapping
    HxPortColormap portColormap;

    /// Min i,j,k indices of clipped ROI (used if restrict option is enabled)
    HxPortIntTextN portMinimum;

    /// Max i,j,k indices of clipped ROI (used if restrict option is enabled)
    HxPortIntTextN portMaximum;

    /// Apply button
    HxPortDoIt portUpdate;    

    /// Returns the current bounding box (possibly restricted)
    void getBox(McBox3f &box) const;

  protected:
    virtual ~HxProjectionView ();
     
    HxUniformScalarField3* scalarField;
    HxUniformColorField3* colorField;
    HxMultiChannelField3* multiChannelField;
    HxLattice3* lattice;
    SbMatrix mTransform;
   
    McBox3f bbox; // unclipped bounding box (world space)
    McBox3f mClippedBox; // restricted box (world space)
    McBox3i mROI; // sub box to be processed (index space)
    const int* dims;
    int blockDragger;
    int inverseMapping;
    int numSlices;
    int sliceNumber;
    int sliceOrientation;
    int contrastLimit;
    int lastProjectionType;
    int lastNumChannels;
    float minVal;
    float maxVal;
    float maxTrans; // max allowed translation for dragger
    int newData; // flag that indicates modified data

    McHandle<SoSeparator> separator;
    McHandle<SoEventCallback> soEvent;
    McHandle<SoTabBoxDragger> dragger;
    McHandle<SoFaceSet> faceSet[3];
    McHandle<SoTexture2> texture[3];
    McHandle<SoTextureCoordinate2> textureCoordinate2[3];
    McHandle<SoCoordinate3> coords[3];
    McHandle<SoComplexity> complexity;
    McHandle<SoMaterial> material;
    
    HxRoiInterface* mSubBox; // connected SelectROI module
    HxCylinderSlice* mSubCylinder; // connected CylinderSlice module

    McPrimType slicesPrimType; // this is either int32 or float
    void* slices[16][3]; // space for projection images of up to 16 channels
    int* depth[16][3];
    mculong sliceDims[3][2];
    void makeSlices();
    void computeTextures();
    void freeSlices();

    struct Pick {
	PickEventCallback f;
	void *userData;
    };

    McDArray<Pick> pickCallbacks;

    /// creates an object for each slice in the object pool and returns slice labels
    McString createImage(const char* name =0);

    void setTexCoords(SoShapeKit *sliceShape);
    void mapLinear(unsigned char* res, void* input, int nx, int ny, int dx, int dy, McPrimType);
    void mapColor(unsigned char* res, void* input, float scale,int nx, int ny,int dx, int dy, McPrimType);
    void mapColorHistogram(unsigned char* res, void* input, int nx, int ny,int dx, int dy, McPrimType);
    void mapHistogram(unsigned char* res, void* input, int nx, int ny,int dx, int dy, McPrimType);
    void addColorMap(unsigned char* res, HxColormap* cmap, int nx, int ny, int dx, int dy, void* input, McPrimType primType);
    void multColor(unsigned char* res, int* input2, unsigned char* colmap, int nx, int ny, int dx, int dy);
    void computeTexture(int which, SoTexture2* texture, void* img, int* img2,
        unsigned char* colmap, float scale, int nx, int ny, McPrimType imgPrimType);
    
    void updatePlanes();
    void finishDragging();
    void constrainDragger();
    static void finishDraggingCB(void* userData, SoDragger*);
    static void constrainDraggerCB(void* userData, SoDragger*);
    void adjustDragger();
    void setMinMax(const McVec3f& bmin,const McVec3f& bmax);
    static void pickEventCB(void *userData, SoEventCallback *eventCB);
    void pickEvent(SoEventCallback *eventCB);
    int computeROI(); // sets bbox, mClippedBox, and mROI

    /// Checks if a point is inside a cylindrical ROI
    inline bool insideCylinder(int i, int j, int k) {
        if (mSubCylinder) {
            McVec3f p1;
            SbVec3f p2;
            lattice->coords()->pos(i,j,k, &p1.x);
            mTransform.transpose().multMatrixVec(SbVec3f(p1[0],p1[1],p1[2]), p2);
            return mSubCylinder->insideCylinder(p2);
        }
        return true;
    }

    HxUniformColorField3* createColoredData(SoTexture2* srcTexture, int width, int height, int xmin, int xmax, int ymin, int ymax);
};
#endif

/// @}
