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
#ifndef MC_RECTMEM_H
#define MC_RECTMEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


/** Class @c McRectMem provides access to \'rectangular\' regions of
  memory. McRectMem does not allocate or free memory itself, but uses
  pointers to custom memory regions. */

template<class T> class McRectMem
{
  public:

    ///
    McRectMem(T* mem,int width,int height) :
        data(mem),
        size(width,height),
    {
    }

    /** Copy rectangular region to destPos.*/
    paste(const McRectMem<T>& from,const McBox2i& srcRect,const McVec2i& destPos) {
        McBox2i me(McVec2i(0),size);
        destRect(destPos,srcRect.getSize());
        destRect.clip(me);
        T* src,*dest;
        McVec2i srcOrigin = srcRect.getMin() + destRect.getMin()-destPos;
        src  = from.data + srcOrigin.y*from.size.x+srcOrigin.x;
        dest = data + destRect.getMin().y*size.x+destRect.getMin().x;

        int srcIncrement  = from.size.x-destRect.getSize().x;
        int destIncrement = size.x - destRect.getSize().x;
        for (int j=destRect.getSize().y ; j ; j--) {
            for (int i=destRect.getSize().x ; i ; i--) {
                *dest++=*src++;
            }
            dest+=destIncrement;
            src+=srcIncrement;
        }
    }

protected:
    T *data;
    McVec2i size;
};

#endif

/// @}
