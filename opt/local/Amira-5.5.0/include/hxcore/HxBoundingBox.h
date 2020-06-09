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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_BOUNDING_BOX
#define HX_BOUNDING_BOX

#include <hxcore/HxModule.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFontSelection.h>
#include <hxcore/HxPortFloatSlider.h>

#include <Inventor/SbColor.h>

class SoText2;
class SoShapeKit;
class SoSeparator;
class SoTranslation;
class SoIndexedLineSet;
class SoMaterial;
class SoFont;

/// This module displays the bounding box of any spatial data object.
class HXCORE_API HxBoundingBox : public HxModule {

  HX_HEADER(HxBoundingBox);

  public:
    /// Constructor.
    HxBoundingBox();

    /// Get the default bounding box.
    const McBox3f& getDefaultBoundingBox() const;

    /// Set the default bounding box.
    void setDefaultBoundingBox(const McBox3f& box);

    /// Bounding box options.
    enum { OPT_TEXT_CB = 0, OPT_COLOR_BTN, OPT_COLOR_LBL, OPT_REFINE_CB };
    HxPortGeneric portOptions;

    /// To change the lineWidth value.
    HxPortFloatSlider portLineWidth;

    /// To select the font attributes.
    HxPortFontSelection portFont;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Info methods prints bbox values.
    virtual void info();

    /// Tcl-comand interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Sets the line width of the bounding box.
    void setLineWidth(float width);

    /// Sets the color of the bounding box.
    void setColor(float r, float g, float b );

    ///add a line for bounding box refinement
    int addLine(SbVec3f start, SbVec3f end, SbVec3f *p,int ind, int numSteps );

    void makeBox(const float* b);

    SoShapeKit* getBoxRoot(){ return boxRoot;}

    void setRefineMesh( bool refineMesh ){ m_refineMesh = refineMesh;}

    /// To take into account the data transformation.
    void getTransformedBoundingBox(const float bbox[6], float transformedBBox[6]) const;

  protected:
    virtual ~HxBoundingBox();

    //handle projection activation
    virtual void projectionActivated();

    //handle projection deactivation
    virtual void projectionDeactivated();

    McBox3f boxDefault;

    SoShapeKit*       boxRoot;
    SoIndexedLineSet* lineSet;
    SoSeparator*      textRoot;
    SoTranslation*    trans1;
    SoTranslation*    trans2;
    SoText2*          text1;
    SoText2*          text2;
    SoFont*           font;
    SoMaterial*       textColor;

    // Refine mesh (used for projections)
    bool m_refineMesh;

    //Last used color
    SbColor m_color;

    //BBox refinement
    int m_numX;
    
    int m_numY;

    int m_numZ;

    virtual void makeText(const float* b);
};

#endif // HX_BOUNDING_BOX

/// @}
