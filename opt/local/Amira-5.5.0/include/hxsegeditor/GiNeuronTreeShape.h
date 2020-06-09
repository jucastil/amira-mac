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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GiPROJECTIONBOXSHAPE_H
#define GiPROJECTIONBOXSHAPE_H

#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include "GiShape.h"

class GiFrameBuffer;
class GiEvent;
class GiProjector;
class Gi;
class HxNeuronTree;
class HxUniformScalarField3;

/** display line set in projection mode.*/

class GiNeuronTreeShape : public GiShape {

  public:
    /** Constructor*/
    GiNeuronTreeShape(Gi* );

    ///
    void setNeuronTree(HxNeuronTree* n) {
        lineSet = n;
    }
    ///
    ~GiNeuronTreeShape() {}

    /** Draw this shape into the specified frame buffer*/
    void render(GiFrameBuffer* frameBuffer,const McBox2i&);

    /** handle events
      @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer*, McEvent* event);

    int lineInBox(int i);

    //static McVec2f pointReal3DTo2D(McVec3f& p3, HxUniformScalarField3*, int o);
    static McVec2f pointReal3DTo2D(McVec3f& p3, HxLattice* image, int o);
    //static McVec3i pointReal3DTo3Di(McVec3f& p3, HxUniformScalarField3* field);
    static McVec3i pointReal3DTo3Di(McVec3f& p3, HxLattice* image);
    //static float getZValue(McVec3f& p3, HxUniformScalarField3* field, int o);
    static float getZValue(McVec3f& p3, HxLattice* field, int o);

  protected:
    void getHighlighted(McDArray<int>& hl,int which=0);
    HxNeuronTree* lineSet;
    GiProjector* projector;
    Gi* theGi;
public:
    static int showEndpoints;
    static int showBranchingpoints;
    static int showLines;
    static int showLinesInBoxOnly;
};

#endif

/// @}
