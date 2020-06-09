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

/// @addtogroup hxmoviemaker hxmoviemaker
/// @{
#ifndef _HX_LCS_H
#define _HX_LCS_H

#include <Inventor/SbLinear.h>
#include <hxmoviemaker/HxTree.h>


class HxLCS : public HxTree< HxLCS >
{
public:

     HxLCS();
    ~HxLCS();                              // Unhook from hierarchie
  
    void  update();                        // this will update all childs...
    void  trans( double x, double y, double z=0 );// translate the LCS
    void  trans( SbVec3f & s );// translate the LCS
    void  scale( double x, double y, double z=1 );
    void  scale( SbVec3f & s );
    void  identity();

    void  set(SbMatrix & m);               // set the matrix by hand
    SbMatrix getTrans( HxLCS & to );

public:

    SbMatrix          _containerToLocal;
    SbMatrix          _localToContainer;
    SbMatrix          _localToParent;
};


////////////////////////////////////////////////////////////////////////////////
inline HxLCS::HxLCS()
{
  _containerToLocal.makeIdentity();
  _localToContainer.makeIdentity();
  _localToParent.makeIdentity();
}


////////////////////////////////////////////////////////////////////////////////
inline HxLCS::~HxLCS()
{
}

 
////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::update()
{
    _localToContainer = _localToParent;

    if( getParent() ) 
        _localToContainer.multRight( getParent()->_localToContainer );

    _containerToLocal = _localToContainer;
    _containerToLocal = _containerToLocal.inverse();

    // update all children ...
    for( HxLCS * sib = getFirstChild() ; sib ; sib = sib->getNextSibling() )
        sib->update();
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::trans(SbVec3f & t)
{
    SbMatrix tmp;
    tmp.setTranslate( t );
    _localToParent.multRight( tmp );
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::trans(double x, double y, double z)
{
    SbVec3f t(x,y,z);
    trans( t );
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::scale( SbVec3f & s)
{
    SbMatrix tmp;
    tmp.setScale( s );
    _localToParent.multRight( tmp );
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::scale(double x, double y, double z)
{
    SbVec3f t(x,y,z);
    scale( t );
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::set(SbMatrix & m)
{
    _localToParent = m;
}


////////////////////////////////////////////////////////////////////////////////
inline SbMatrix HxLCS::getTrans( HxLCS & to )
{
    SbMatrix tmp(_localToContainer);
    return tmp.multRight(to._containerToLocal);
}


////////////////////////////////////////////////////////////////////////////////
inline void HxLCS::identity()
{
    _localToParent.makeIdentity();
}


#endif // _HX_LCS_H


/// @}
