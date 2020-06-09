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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASURE_GUI_FRAME
#define HX_MEASURE_GUI_FRAME

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxmeasure/HxMeasureGUIElem.h>

/** A container for other HxMeasureGUIElem. You can use it to store
some points and interprete them in the derived class as ..., 
e.g. HxMeasureGUILine, HxMeasureGUIAngle...
*/
class HXMEASURE_API HxMeasureGUIFrame : public HxMeasureGUIElem
{
public:
    ///
    HxMeasureGUIFrame(Mode m);
    ///
    virtual ~HxMeasureGUIFrame ();
    /// handle an Inventor event, pass to members.
    virtual int handleEvent (const SoEvent* event, int viewerId);

    /// redraw, pass to members.
    virtual void redraw (int viewerId); 
    /// getBBox, pass to members.
    virtual bool getBBox (McBox3f& box);
    /// checks if all members are fully initialized
    virtual int isFullyInitialized ();

    void preRender (int viewerId);

    /// The points coordinates
    virtual void fillPointsValue(McDArray<McVec3f> &points);
    /// interface for adding, removing, ... elements. 
    void addElem (HxMeasureGUIElem*); 
    /// See comments at HxMeasureGUI 
    void removeElem (HxMeasureGUIElem*);
    ///
    void clearElems ();
    ///
    int getNumElems () { return members.size (); };
    ///
    HxMeasureGUIElem* getElem (int n) { return members[n]; };
    ///
    virtual void setViewerId(int id);
protected:
    ///
    McDArray<HxMeasureGUIElem*> members;
};

#endif

/// @}
