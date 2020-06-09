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

/// @addtogroup hxcore hxcore
/// @{
#ifndef  _SO_MF_BIT_
#define  _SO_MF_BIT_

#include <Inventor/fields/SoMFUInt32.h>

#include <hxcore/HxAmiraWinDLLApi.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFBit subclass of SoMFUInt32.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of bits.
 */ 

class HXCORE_API SoMFBit : public SoMFUInt32 {

  SO_MFIELD_DERIVED_HEADER(SoMFBit, uint32_t, uint32_t);
  SO_MFIELD_SETVALUESPOINTER_HEADER(uint32_t);

  public: 
    /* Set number of bits */ 
    void setNumBits(int num);

    /* Get indexed value */ 
    bool getBit(int i) const;

    /* Set 1 value at given index */ 
    void setBit(int index, bool newValue); 

  SoINTERNAL public:
    static void initClass();
    static void exitClass();
};

#endif /* _SO_MF_BIT_ */


/// @}
