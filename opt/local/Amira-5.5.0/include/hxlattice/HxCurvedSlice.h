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
#ifndef HX_CURVED_SLICE_H
#define HX_CURVED_SLICE_H

#include <hxcore/HxConnection.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxModule.h>


#include <hxfield/HxScalarField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxLocation3.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxPortMultiChannel.h>

#include <hximview/QxImageViewer.h>
#include <hxlines/HxCurve.h>

#include <hxlattice/HxMapToTexture.h>
#include <hxlattice/HxLatticeWinDLLApi.h>

#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>

/** This displays volume data on a curved slice.
    A curve and a vector on that curve is used to define
    a surface. The surface is visualized with a texture on 
    it that reflects the values of the volume at that point.
*/
class HXLATTICE_API  HxCurvedSlice : public HxModule {

    HX_HEADER(HxCurvedSlice);

protected:


    /// the curve
    HxCurve* mCurve;

    /// the extra viewer to display the texture
    QxImageViewer * mViewer;


    int alphaThreshold;
    unsigned int isLabelLat:1;
    unsigned int isMultiChannel:1;    

    /// height of slice
    double mHeight;

    /// width of slice
    double mWidth;

    // This is true if a color field is processed.
    int rgbaSlice;

    // This is @c mc_int32 in case of color fields, @c mc_float otherwise. 
    McPrimType sliceDataType;

    /// data field for texture
    float* mTexture;

    /// scalar data field
    HxScalarField3* mField;

    /// Length of diagonal of the input's bounding box.
    float diagonal;

    /// curved geometry surface
    SoQuadMesh* mSurface;

    /// scene for surface
    SoSeparator* mSurfaceSep;

    /// transformation
    SoTransform* mTransform;

    /// surface coordinates
    SoCoordinate3* mCoords;

    /// surface texture coordinates
    SoTextureCoordinate2* mTexCoords;

    /// inventor texture
    McHandle<SoTexture2> mSurfaceTexture;

    /// Size of texture image (128x128 on default, 256x256 in high res mode).
    SbVec2s size;

    /// const 2nd direction for curved slice
    McVec3f mDirection;

public:
    enum SamplingMode {
        RESOLUTION=0,
        INTERPOL_DATA=1,
        INTERPOL_TEXTURE=2
    };

    /// Constructor.
    HxCurvedSlice();

    /// Destructor.
    ~HxCurvedSlice();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    void resetTexture();

    /// connection to curve
    HxConnection portCurve;

    /// show or hide image viewer
    HxPortRadioBox portViewer;

    /// creates all color ports
    HxMapToTexture colorPorts;

    /// 0=resolution, 1=interpol uniform fields, 2=high texture quality
    HxPortGeneric portMoreOptions;

    /// mapping for profiles
    HxPortGeneric portMappingProfile;

    /// how to compute 2nd direction for slice
    HxPortRadioBox portDirection;

    /// generate a curve as input data
    HxPortButtonList portAction;

    /// allows to map voxels within a geometry shape
    virtual float putGeometry(const McVec3f &pos, float prev) { return prev; }


protected:

    virtual void savePorts(FILE *fp);

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    // do sampling
    void sampleSlice();

    // generate the texture object
    void computeTexture();

    void setTexture(int nc, int alpha=0);

    void computeSize(bool coarse = false);

    /// set surface node i,j to position (x,y,z) with texture coordinates (a,b)
    void setSurfaceNode(int i, int j, float x, float y, float z, float a, float b);

    /// compute best direction by PCA
    void setAutomaticDirection();


    /// extracts the slice and adds it to the object pool.
    virtual McString createImage(const char* name =0);

	//-1 : false 
	//0 : dimX =0;
	//1 : dimY =0;
	//2 : dimZ =0;
	int mFieldIsSlice;
	
	int mCurveSize;




};
#endif

/// @}
