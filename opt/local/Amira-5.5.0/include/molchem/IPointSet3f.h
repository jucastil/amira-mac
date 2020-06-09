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
#ifndef MOLCHEM_IPOINTSET3F_H
#define MOLCHEM_IPOINTSET3F_H

#include "MolChemWinDLLApi.h"

template <class T> class McDArray;

class McVec3f;
class McMat4f;
class McBox3f;
class McBitfield;

namespace molchem {

    /** \brief Abstract base class for set of three-dimensional points of single floating point precision.

    IPointSet3f is an interface which provides methods to transform 
    and compute different information for sets of points in 3D space.
    To use it, inherit from IPointSet3f and implement the abstract methods, 
    or use the concrete implementations PointSet3f or the wrapper PointSet3fContainerWrapper. 
    
    */


    class MOLCHEM_API IPointSet3f {
    public:       
        // ---------------------- abstract interface -----------------------
        /* Developer node: Do not add new abstract methods that may change the size of the point set.
           It is a class invarant that the size may only be changed by code that knows the concrete type and not by the client.*/
        virtual McVec3f getPos(int ix) const = 0;
        virtual void setPos(int ix,const McVec3f& pos) = 0;
        virtual int size() const = 0;
       // -------------------------------------------------------------------
        void getPos(int ix,float& x,float&y,float&z) const;
        void getPos(int ix,double& x,double&y,double&z) const;
        IPointSet3f() {};
        virtual ~IPointSet3f() {}
        // Both point sets must! be of the same size 
        IPointSet3f& operator = (const IPointSet3f& ps);
        /** Translates 3f coodinates of all points set in the bitfield by transf. 
        
            \param[in] tranf Translation vector
            \param[in] points Mask of points determining which points will be transfomed. If omitted, all points.
        */
        void translate(const McVec3f  transf,const McBitfield* points=0);
        void translate(const McVec3f  transf,const McDArray<int>& points);
        
        void rotate( const McVec3f center, McVec3f from, McVec3f to,const McBitfield* a);
        void rotate( const McVec3f center, McVec3f from, McVec3f to,const McDArray<int>& a);

        void transform(const McVec3f from, const McVec3f to, McVec3f fromDir, McVec3f toDir,const McBitfield* mask=0);
        void transform(const McVec3f from, const McVec3f to, McVec3f fromDir, McVec3f toDir,const McDArray<int>& points);

        void transform(const McVec3f from, const McVec3f to, McVec3f fromXDir, McVec3f toXDir, McVec3f fromYDir, McVec3f toYDir,const McBitfield* mask=0);
        void transform(const McVec3f from, const McVec3f to, McVec3f fromXDir, McVec3f toXDir, McVec3f fromYDir, McVec3f toYDir,const McDArray<int>& points);
        
        /** Transforms 3f coodinates of all points set in the bitfield by transf. 
            
            \param[in] tranf 4*4 Transformation matrix
            \param[in] points Mask of points determining which points will be transfomed. If omitted, all points.
        */
        void transform(const McMat4f & transf,const McBitfield* points=0);
        void transform(const McMat4f & transf,const McDArray<int>& points);
        
        /** Return bounding box of part of the pointset. 

            \param[out] bbox Computed bounding box
            \param[in] points Mask of points for which bbox will be computed. If omitted, all points.
        */
        void computeBoundingBox(McBox3f& bbox,const McBitfield* points=0) const;
        void computeBoundingBox(McBox3f& bbox,const McDArray<int>& points) const;

        /** Calculate the (arithmetic-mean) center of parts of the pointset.
        
            \param[out] cog Computed center of gravity
            \param[in] points Mask of points for which cog will be computed. If omitted, all points. 
        */
        void computeCenter(McVec3f& centre,const McBitfield* points=0) const;
        void computeCenter(McVec3f& centre,const McDArray<int>& points) const;
       
        /** Calculates a rigid transformation that transforms the points of *this
            onto the points of the target molcule. Optimally in the sense of mean
            squared distances.

            \param[in] target Geometry onto which this geometry will be aligned
            \param[in] targetTransform Optional already existing transformation of target pointset
            \param[out] transform Computed optimal alignment tranformation
        */
        void computeAlignTransform(McMat4f & transform,
            const IPointSet3f * target, 
            const McMat4f* targetTransform=0);        
    };

 }

#endif

/// @}
