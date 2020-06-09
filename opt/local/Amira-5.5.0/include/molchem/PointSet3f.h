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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_POINTSET3F_H
#define MOLCHEM_POINTSET3F_H

#include "MolChemWinDLLApi.h"
#include "IPointSet3f.h"
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

namespace molchem {

    /** Concrete implementation of IPointSet3f as a container of McVec3f.*/

    class MOLCHEM_API PointSet3f : public IPointSet3f {
    public:
        PointSet3f() {}
        PointSet3f(const IPointSet3f& p) : IPointSet3f(p) {}
        virtual ~PointSet3f() {}
        McDArray<McVec3f> pos;
        virtual McVec3f getPos(int ix) const { return pos[ix]; }
        virtual void setPos(int ix,const McVec3f& p) { pos[ix]=p; }
        virtual int size() const { return pos.size();}
    };

    /** IPointSet3f wrapper for McVec3f containers. Allows to use any 
        container class containing McVec3f as a point set.
        
        Example of use:
        McDArray<McVec3f> mycontainer;
        PointSet3fContainerWrapper<McDArray<McVec3f> > pscw(mycontainer);
        pscw.translate(McVec3f(1,0,0));
    */
    template <class T> class MOLCHEM_API PointSet3fContainerWrapper : public IPointSet3f {
    private:
        T* a;
    public:
        PointSet3fContainerWrapper(T& x) {  a=&x;}
        McVec3f getPos(int ix) const { return (*a)[ix]; }
        void setPos(int ix,const McVec3f& p) { (*a)[ix]=p; }
        int size() const { return a->size();}
    };

 }

#endif

/// @}
