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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef NEURONEDITORSELECTIONHELPERS_H 
#define NEURONEDITORSELECTIONHELPERS_H

#include <vsvolren/Vs.h>

class SpatialGraphSelection;
class HxSpatialGraph;
class SoEvent;
struct SpatialGraphPoint;

namespace SelectionHelpers {

    enum Modifier {
        NO_MODIFIER = 0, 
        SHIFT, 
        CONTROL, 
        ALT,
        SHIFT_CONTROL,
        SHIFT_ALT,
        CONTROL_ALT,
        SHIFT_CONTROL_ALT
    };

    SelectionHelpers::Modifier getModifier(const SoEvent* e);

    SelectionHelpers::Modifier getModifier(const Vs::ButtonState state);

    // \a existingSel is replaced by a single selected element
    void selectSingleElement(SpatialGraphSelection& existingSel,
                             const int vertexId,
                             const int edgeId,
                             const SpatialGraphPoint pointId);

    // The selection of a single selected element is toggled.
    void toggleSingleElement(SpatialGraphSelection& existingSel,
                             const int vertexId,
                             const int edgeId,
                             const SpatialGraphPoint pointId);

    // \a existingSel is replaced by the connected component,
    // selected by either \a vertexId, \a edgeId, or \a pointId.
    void selectConnectedComponent(SpatialGraphSelection& existingSel,
                                  const HxSpatialGraph* graph,
                                  const int vertexId,
                                  const int edgeId,
                                  const SpatialGraphPoint pointId);

    // \a existingSel is modified by toggling the connected component, 
    // selected either by \a vertexId, \a edgeId or \a pointId.
    // Connected components are toggled in their entirety, i.e.
    // clicking on a partly selected connected component 
    // results in selection of the entire connected component.
    void toggleConnectedComponent(SpatialGraphSelection& existingSel,
                                  const HxSpatialGraph* graph,
                                  const int vertexId,
                                  const int edgeId,
                                  const SpatialGraphPoint pointId);
}

#endif


/// @}
