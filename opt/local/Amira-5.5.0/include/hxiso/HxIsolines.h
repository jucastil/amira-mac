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

/// @addtogroup hxiso hxiso
/// @{
#ifndef HX_ISOLINES2_H
#define HX_ISOLINES2_H

#include <mclib/McDArray.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxiso/HxIsoWinDLLApi.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFontSelection.h>

class SoLineSet;
class SoMFVec3f;
class SoMFUInt32;
class HxScalarField3;
class HxLineSet;

/// This module draws isolines of a scalarfield on top of an arbitrary plane.

class HXISO_API HxIsolines : public HxOverlayModule {

  HX_HEADER(HxIsolines);

  public:
    /// Constructor.
    HxIsolines(GraphicalRepMgtType graphicalRepMgtType = MANAGED_BY_BACKGROUND_MOD);

    /// Update method shows/hides some ports.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Indicates how isoline are defined, uniformly or explicitly.
    HxPortRadioBox portSpacing;

    /// Value of first and last isoline, total number of isolines.
    HxPortFloatTextN portUniform;

    /// Explicit definition of all isolines.
    HxPortText portExplicit;

    /// Parameters: 0=resolution of sample grid, 1=line width.
    HxPortFloatTextN portParameters;

    /// Options: 0=update min-max, 1=resample tetrahedral grid, 2=AnnotatesIsolines
    HxPortToggleList portOptions;

    /// Colormap to be used.
    HxPortColormap portColormap;

    /// The annotation path: Tangential or Camera aligned
    enum { PATH_TYPE=0, CONTOUR_CLIP=1 };
    HxPortGeneric portAnnotationsPath;
        
    /// To select the font attributes.
    HxPortFontSelection portFont;
 
    /// The font size scale
    HxPortFloatSlider portFontScale;

    /// The text gap
    HxPortFloatSlider portTextGap;

    // Major lines and fist major
    HxPortIntTextN portAnnotationPeriod;

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    enum Parameters { RESOLUTION=0, LINEWIDTH=1 };

    enum Options { UPDATEMINMAX=0, RESAMPLE=1, ANNOTATED=2 };

    enum AnnotationsPeriod { MAJOR_PERIOD=0, FIRST_MAJOR=1 };

    enum AnnotationsPath { TANGENTIAL_PATH=0, CAMERA_ALIGNED=1 };

    /**
        Exports the current displayed lines as HxLineSet. The IsoValues are added as data field.
    */
    HxLineSet* exportAsLineSet();

  protected:
    // Destructor.
    virtual ~HxIsolines();

    void createTextSceneGraph();

    // Inventor shape kit containing a line set node
    McHandle<SoShapeKit> shapeKit;

    // Inventor separator
    McHandle<SoSeparator> mGraphSepartor;
    McHandle<SoSeparator> mTextSepartor;

    // Scaled plane vectors
    SbVec3f orig, norm, uVec, vVec;

    // Array containing all isoline values.
    McDArray<float> isoValues;

    // Array containing colors of all iso-values.
    McDArray<unsigned int> isoRGBA;

    // Inventor field containing all vertices.
    SoMFVec3f* vertex;
    int nMaxVertices, nVertices;

    // Inventor field containing all color tuples.
    SoMFUInt32* orderedRGBA;
    int nMaxOrderedRGBA, nOrderedRGBA;

    // Indicates if range should be reset if a new data object is attached.
    unsigned int resetRangeFlag:1;

    // Indicates that coordinates must be adjusted.
    unsigned int transformFlag:1;

    // Required for coord adjustment in case of transformations.
    SbMatrix mat;

  public: // seems to be required on HP-UX 10.20
    struct Vertex3 {
        SbVec3f vec;
        float z, val;
    };

    struct Polygon {
        int n;
        Vertex3 v[4];
    };

    struct TextVertex{
        SbVec3f vec;
        McString value;
    };

  protected:

    void resetRange(HxScalarField3* field);
    void determineIsoValues();
    void computeIsolines();
    void doGeneric();
    void doIntersection();

    /**
        Do isoline computation for iso value @c isoValue in a quad cell defined
        by four verices @c p with data values @c v. Vertex numbers are ordered
        counter-clockwise.

        Vertices are cached for adjacent cells. If a vertex was found in a previous
        cell, the vertex numbers are stored in @c lastRowVertex and @c lastColVertex.
        This function updates these values. A value of -1 indicates that no
        previous vertex was computes (As it is the case for the first colums/row).

        New vertices are appended in the vertex array. In lineSegments the segment end points
        for a vertex are stored. Segments are oriented consistently.
    */
    void processCell(  float isoValue, SbVec3f* p, float* v
                     , McDArray<SbVec3f>& vertices, McDArray<int>& lineSegments
                     , int& lastRowVertex, int& lastColVertex) const;

    void isoPoly3(const Polygon& p);
    void isoPoly4(const Polygon& p);
    int getTransform(SbMatrix& mat);

    inline void intersect(const Vertex3& a, const Vertex3& b, Vertex3& res);
    inline void doIso(const Polygon&, const float&, const int&, const int&,
    const int&, const int&, SbVec3f res[2]);

    /**
        Stores the corresponding iso-value for every extracted line.
    */
    McDArray<float> m_isoValuesPerLine;

    McDArray<TextVertex> m_CameraPathText;

    virtual void removeOverlay();

    bool isAnnotated() const;

    bool isContourClip();

};

#endif

/// @}
