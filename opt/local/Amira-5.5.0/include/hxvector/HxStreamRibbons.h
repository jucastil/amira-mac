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

/// @addtogroup hxvector hxvector
/// @{
#ifndef HX_STREAM_RIBBONS_H
#define HX_STREAM_RIBBONS_H

#include <hxvector/HxVectorWinDLLApi.h>
#include <mclib/McHandle.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/SoTransformerDraggerVR.h>
#include <hxfield/HxVectorField3.h>
#include <hxcolor/HxPortColormap.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoTriangleStripSet.h>

/// This module computes and displays stream ribbons in a vector field.
class HXVECTOR_API HxStreamRibbons : public HxModule {

  HX_HEADER(HxStreamRibbons);
  
  public:
    /// Constructor.
    HxStreamRibbons();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Parse method.
    // virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Colormap for pseudo-coloring
    HxPortColormap portColormap;

    /// Controls the resolution of the surface (exponent, 0=default).
    HxPortFloatSlider portResolution;

    /// Density scale.
    HxPortFloatSlider portDensity;

    /// Ribbon width
    HxPortFloatSlider portWidth;

    /// Ribbon length
    HxPortFloatSlider portLength;

    /// Seeds: 0=line, 1=ring, 2=square
    HxPortMultiMenu portSeedType;
    enum { SEED_LINE=0, SEED_RING=1, SEED_SQUARE=2 };

    /// Mode: 0=lines, 1=ribbons
    HxPortRadioBox portMode;

    /// Action: 0=Add, 1=Clear, 2=Show/hide dragger
    HxPortButtonList portAction;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    ~HxStreamRibbons();

    float hBase;
    float ribbonWidthScale;
    unsigned int draggerVisible:1;
    unsigned int draggerLocked:1;
    HxVectorField3* field;
    HxLocation3* loc;
    McDArray<SbVec3f> seedPoints;
    McHandle<SoTransformerDragger> dragger;
    McHandle<SoSeparator> seedGeometry;
    McHandle<SoSeparator> ribbonGeometry;
    McHandle<SoSeparator> stripGeometry;
    McHandle<SoTriangleStripSet> strip;
    McHandle<SoLineSet> ribbons;

    virtual void savePorts(FILE* fp);
    void computeSeedGeometry();
    void draggerChanged();
    void run(const SbMatrix& mat);
    void runLines();
    void runRibbons();
    void computeSeedPoints(const SbMatrix& mat);
    int torsion(const McVec3f& r, McVec3f& f,float&);
    int advance(float h, McVec3f& rLeft, McVec3f& rRight, McVec3f& fLeft, McVec3f& fRight,float&);
    int init(const McVec3f& r, McVec3f&, McVec3f&, McVec3f& fLeft, McVec3f& fRigh,float&t);
    static void draggerCB(void* userData, SoDragger* dragger);
    static int tangent(const McVec3f& r, McVec3f& f, void* userData);

};

#endif

/// @}
