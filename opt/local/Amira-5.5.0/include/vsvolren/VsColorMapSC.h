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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_COLORMAPSC_H
#define VS_COLORMAPSC_H

#include "VsVolrenAPI.h"
#include "VsColorMap.h"
#include <mclib/McDArray.h>
#include <mclib/McVec4f.h>

// VS_RELAY_CLASS VsColorMapSC VsColorMapRelay

/** Colormap defined by superposed curves.
    Piece-wise linear curves and cubic splines are supported.
  */
class VSVOLREN_API VsColorMapSC : public VsColorMap
{
    VS_DECL_INTERFACE        ( VsColorMapSC )
    VS_DECL_INTERFACE_IMPL   ( VsColorMapSC )
    VS_DECL_INTERFACE_FACTORY( VsColorMapSC )
    VS_DECL_INTERFACE_RELAY  ( VsColorMapSC )

  public:

    int numCurves() const;

    int curveAt(int idx) const;

    int addCurve(const char* name, bool active); // VS_RELAY

    void removeCurve(int curveId); // VS_RELAY

    void clear(); // VS_RELAY

    const char* curveName(int curveId) const;

    void setCurveName(int curveId, const char* name); // VS_RELAY

    bool isCurveActive(int curveId) const;

    bool isCurveActiveNoLock(int curveId) const;

    void setCurveActive(int curveId, bool value); // VS_RELAY

    int numNodes(int curveId) const;

    void getNode(int curveId, int iNode, float& outU, McVec4f& outRGBA);

    void setNode(int curveId, int iNode, float inU, const McVec4f& inRGBA); // VS_RELAY

    void addNode(int curveId, float u, const McVec4f& inRGBA); // VS_RELAY

    void addNodes(int curveId, const McDArray<float>& inU, const McDArray<McVec4f>& inRGBA); // VS_RELAY

    void removeNode(int curveId, int i); // VS_RELAY

    void mapRGBA(int curveId, float u, McVec4f& outRGBA) const;

    virtual void mapRGBA(float u, McVec4f& outRGBA) const;

    VsColorMapSC& copyFrom(const VsColorMapSC* other); // VS_RELAY

    /** reads a file which contians the information of a color map */
    static VsColorMapSC* readVisage(const char* filename);

    /** writes a file which contians the information of this color map */
    int writeVisage(const char* filename); // FORBIDDEN_ON_SERVER

    /** serialize the state of the class to a Msg format
        \return 
                the State of the color map in a serialize msg form.
    */
    VsMsg serializeState(); // VS_SYNC_CALL
};

#endif


/// @}
