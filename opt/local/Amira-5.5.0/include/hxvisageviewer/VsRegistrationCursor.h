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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef VS_REGISTRATIONCURSOR_H
#define VS_REGISTRATIONCURSOR_H


#include <vsvolren/VsNode.h>
#include <vsvolren/VsViewState.h>

#include <mclib/McColor.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

class VsRegistrationCursor : public VsNode
{
public:
    enum Mode { M_TRANSLATE,
                M_ROTATE,
                M_SCALE_HOR,
                M_SCALE_VER,
                M_SHEAR_HOR,
                M_SHEAR_VER
    };

    VsRegistrationCursor();

    virtual VsRenderResult render();

    virtual void setOrientation(McMat4f & mat);
    const McMat4f & orientation() const { return mOrientation; };

    virtual void setCenter(McVec3f & center);
    const McVec3f & center() const { return mCenter; };

    virtual void setAxis(McVec3f & firstAxis, McVec3f & secondAxis, McVec3f & thirdAxis);
    virtual void setAncor(McVec3f & ancor);

    virtual void setMode(Mode inMode);

    virtual bool hit(int x, int y, Mode area);

    virtual void * extension( int, void * );

private:

    /// Called by render() and extension() to collect all primitives to render
    void computeRenderElements( VsViewState & inState );

private:

    McDArray< McDArray<McVec3f> > mCurrVerts;
    McColor   mCurrColor;
    float     mCurrAlpha;

    McMat4f   mTransform;
    
    McMat4f   mOrientation;
    McVec3f   mCenter;
    McVec3f   mFirstAxis;
    McVec3f   mSecondAxis;
    McVec3f   mThirdAxis;
    McVec3f   mAncor;

    Mode      mMode;

    float     mSize;
    float     mWidth;

    bool      mAllowScaling;
    bool      mAllowShearing;
};

#endif // VS_REGISTRATIONCURSOR_H


/// @}
