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

/// @addtogroup hxlatticex hxlatticex
/// @{
#ifndef HX_LATTICE_GEOM_H
#define HX_LATTICE_GEOM_H

#include "HxLatticeXWinDLLApi.h"
#include <mclib/McInterface.h>
#include <mclib/McHandle.h>

class McRectPositions;
class McBoundingBox;
class McDataSpace;
class HxLatticeType;

// Tell createBuildSystem to not run autoinit on this file.
// Using header macros after #if 0 causes problems.
// NO_AUTO_INIT

#if 0 // could perhaps be useful in the future
/** \brief Provide access to the geometry of a lattice. This interface
           is a minimal base class. Itself it doesn't add any value
           to the HxLattice. All the information are already present there.
            
           In derived classes thought, more information might be provided.
  */
class HXLATTICEX_API HxLatticeGeom : public HxDynamicInterface {
        MC_ABSTRACT_HEADER(HxLatticeGeom);

    public:
        /// returns the dataspace of the lattice (i.e. the combinatorical topology of the grid)
        virtual McDataSpace getDataSpace () = 0;

        /** \brief A Bounding box in all dimensions. If a dataspace is
                   provided, the McBoundingBox should be 
                   initialized to a volume containing the hyperslab
                   selected in dataspace.
                   If the implementation is not capable of doing this
                   it might initialized to the full bounding box.
          */
        virtual McBoundingBox getBoundingBox (const McDataSpace* dataspace) = 0;

        /** Lattice/grid type.

            Depending on the lattice type the geometry information must be accessed in 
            different ways:
                - c_uniform: Dataspace and BoundingBox provide all necessary information
                - c_stacked: 
                - c_curvilinear:  
          */
        virtual HxLatticeType latticeType () = 0;
};
#endif

#if 0
// another simple inteface might be something like
class HXLATTICEX_API HxSimplePos3LatticeGeom : public HxDynamicInterface {
        MC_ABSTRACT_HEADER(HxSimplePos3LatticeGeom);

    public:
        virtual void pos3 (const int*, float pos[3]) = 0;
};

#endif


class HXLATTICEX_API HxPartRectLatticeGeom : public McInterface {
        MC_ABSTRACT_HEADER(HxPartRectLatticeGeom);

    public:
        HxPartRectLatticeGeom (McInterfaceOwner* owner) : McInterface (owner) {}
        
        /** fill pos with the 1d position vectors of this lattice geometry. 

            Depending on the lattice type restrictions on pos are imposed:
                - uniform dims 0, 1, 2 are always uniform
                - stacked dims 0, 1 are uniform
                - rectilinear any dim might be stacked
                - curvilinear dims 0, 1, 2 are irrelevant. The positions
                                have to be accessed throught a postions dataset.
                                dims > 2 though are either stacked or uniform.
          */
        virtual void getRectPositions (McRectPositions& pos) {
            doGetRectPositions (pos);
        } 
    private:
        virtual void doGetRectPositions (McRectPositions& pos) = 0;
};

template <class PROXY>
class HxPartRectLatticeGeomProxyTemplate : public HxPartRectLatticeGeom {
    MC_ABSTRACT_TEMPLATE_HEADER (HxPartRectLatticeGeomProxyTemplate<PROXY>);
    public:
        HxPartRectLatticeGeomProxyTemplate (McInterfaceOwner* owner, PROXY* p) : HxPartRectLatticeGeom (owner), proxy(p) { }

        HxPartRectLatticeGeomProxyTemplate (McInterface* iface, PROXY* p) 
            : HxPartRectLatticeGeom (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId())))
            , proxy(p) { }

    private:
        void doGetRectPositions (class McRectPositions& pos) {
            proxy->getRectPositions (pos);
        };

        PROXY* proxy;
};

#endif

/// @}
