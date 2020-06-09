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

/// @addtogroup hxmulticomp hxmulticomp
/// @{
#ifndef HX_SEPARATEMORPHO_H
#define HX_SEPARATEMORPHO_H

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxCompModule.h>

#include <mclib/McVec3i.h>
#include <hxfield/HxUniformScalarField3.h>

#include "HxMultiCompWinDLLApi.h"

/// Module for separating labels based on morphology
class HXMULTICOMP_API HxSeparateMorpho : public HxCompModule
{
    HX_HEADER(HxSeparateMorpho);

  public:

    /// Default constructor.
    HxSeparateMorpho();

    /// Compute method.
    void compute();

    /// Update method.
    virtual void update();

    // ignore objects that are too small
    HxPortIntTextN portMinimumSize;

    /// the number of erosion steps left for each object, objects are not sub-divided more than this
    HxPortIntTextN portErosionStop;

    /// Starts computation.
    HxPortDoIt portDoIt;

    struct Component {
        McVec3i seed;
        int count;
        int level; // at which level the component disappears
    };

  protected:
    // separate label given the minimum/maximum size in pixel
    template<class T>
    void separate(HxUniformScalarField3 *source);

    // fills in a components array
    template<class T>
    HxUniformScalarField3 *computeConnectedComponents(HxUniformScalarField3* source, McDArray<HxSeparateMorpho::Component> *components);

    // create a distance field with inside filled
    template<class T>
    McHandle<HxUniformScalarField3> computeDistanceMap(HxUniformScalarField3* source);

    // separate the different objects
    template<class T>
    HxUniformScalarField3 *computeSeparation(HxUniformScalarField3* source, HxUniformScalarField3* dist, McDArray<Component> *components);

    // return the number of objects in the field
    template<class T>
    McDArray<Component> *countObjects(HxUniformScalarField3 *o, HxUniformScalarField3 *dist);

    virtual int canCreateData(HxData* data, McString& createCmd);

    McDArray<Component> components;

    bool warningOverflowDisplayed;
};

#endif

/// @}
