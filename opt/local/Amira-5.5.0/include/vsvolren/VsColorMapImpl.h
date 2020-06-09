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
#ifndef _VS_COLORMAP_IMPL_H
#define _VS_COLORMAP_IMPL_H

#include "VsColorMap.h"
#include "VsObjectImpl.h"
#include <mclib/McString.h>

////////////////////////////////////////////////////////////////////////////////
class VsColorMapImpl : public VsObjectImpl
{
    VS_IMPLEMENTATION( VsColorMapImpl, VsObjectImpl, VsColorMap )

public:

    float       mScale;
    float       mBias;
    float       mDataWindow[2];
    McString    mFileName;
    bool        mNameTranslated;


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VSRESULT    setDataWindow( float min, float max );
    float       dataWindowMin() const;
    float       dataWindowMax() const;
    McVec4f     rgba( float x ) const;
    McColor     color( float x ) const;
    float       alpha( float x ) const;
    McVec4f     rgba1( float u ) const;
    McColor     color1( float u ) const;
    float       alpha1( float u ) const;

    bool nameTranslated() const;
    void setNameTranslated(bool flag);


private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT    vimpl_RGBAVector( int n, McVec4f * dst ) const;
    VSRESULT    vimpl_colorVector( int n, McColor * dst ) const;
    VSRESULT    vimpl_alphaVector( int n, float * dst ) const;
    float vimpl_leftmostOpaque(float threshold) const; 
    float vimpl_rightmostOpaque(float threshold) const;
};

#endif


/// @}
