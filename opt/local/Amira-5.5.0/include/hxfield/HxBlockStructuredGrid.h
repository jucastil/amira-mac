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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_FIELD_HX_BLOCK_STRUCTURED_GRID_H
#define HX_FIELD_HX_BLOCK_STRUCTURED_GRID_H

#include <hxcore/HxSpatialData.h>

#include "HxFieldWinDLLApi.h"

#include <hxfield/HxCoord3.h>

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

/**
    A structure for grids that are composed of a number of curvilinear zones.

*/
class HXFIELD_API HxBlockStructuredGrid : public HxSpatialData
{
    HX_HEADER(HxBlockStructuredGrid);

public:
    /** Create grid that contains all fields that are selected in the object pool.
      */
    HxBlockStructuredGrid();

    /** Create a grid containing the nCoords HxCoord3 objects that coords points to.
      */
    static HxBlockStructuredGrid* create(int nCoords, HxCoord3** coords);

    /**
        Gets the number of zones the grid is composed of.
    */
    int getNumZones() const;

    /**
        Gets a zone of the grid by number.
    */
    HxCoord3* getZone(int indexZone) const;

    /** Return bounding box.
      */
    virtual void getBoundingBox(float bbox[6]) const;

    /**
        Reconstructs 1-to-1 zone connectivity.  A tolerance for vertex
        similarity can be set.  HxBlockStructuredGridView uses the connectivity
        to avoid showing internal faces.
    */
    void recover1to1ZoneConnectivity(float tolerance = 0.0f);

    /**
        Descriptor for a quad of a zone's face.
    */
    struct QuadFaceDescriptor
    {
        /**
            The default constructor initializes the object to invalid.
        */
        QuadFaceDescriptor()
                    : idxZone(-1)
                    , idxFace(-1)
                    , idxQuad(-1)
        {
        }

        /**
            Initializes the object with given quad.

            Faces are numbered between 0 and 5. (pIdxFace/2) determines
            the constant index dimension, (pIdxFace%2) determines wether
            the minimum (=0) or maximum side is chosen. (pIdxFace+1)%3) is
            the fast varying index.

            @param dims Dimensions of the zone.
            @param pIdxZone Index of the zone in the block structured grid.
            @param pIdxFace face number within the zone.
            @param i First (fast varying) index of the quad within the face.
            @param j Second index of the quad within the face.
        */
        QuadFaceDescriptor(const int* dims, int pIdxZone, int pIdxFace, int i, int j)
                            : idxZone(pIdxZone)
                            , idxFace(pIdxFace)
                            , idxQuad(j * (dims[((pIdxFace >> 1) + 1) % 3] - 1) + i)
        {
        }

        /**
            returns validity of the object.
        */
        bool isValid() const
        {
            return idxZone >= 0;
        }

        /**
            index of the zone within the block structured grid.
        */
        int idxZone;

        /**
            Face number of the zone. Face numbers are I_MIN,I_MAX,J_MIN,J_MAX,K_MIN,K_MAX.
        */
        int idxFace;

        /**
            Linear index of the quad within a face.
        */
        int idxQuad;
    };

    /**
        Gets a descriptor to the adjacent quad of the given zone. Returns
        an invalid descriptor if the given quad has no 1-to-1 adjacent
        neighbor.
    */
    QuadFaceDescriptor getNeighbor_1to1(const QuadFaceDescriptor& quadDesc)
    {
        if (!m_connectivity_1to1.size())
            return QuadFaceDescriptor();

        return getNeighborRef(quadDesc);
    }

private:
    typedef McHandle<HxCoord3> ZonePtr;
    McDArray<ZonePtr> m_zones;

    virtual void info();

    void addZoneGrid(HxCoord3* coord3);

    struct ZoneConnectivity_1to1
    {
        void init(const int* dims)
        {
            for (int i=0; i < 6; i++)
            {
                const int dims1 = dims[((i >> 1) + 1) % 3] - 1;
                const int dims0 = dims[((i >> 1) + 2) % 3] - 1;

                faceConnectivity[i].resize(dims0*dims1);
            }
        }

        McDArray<QuadFaceDescriptor> faceConnectivity[6];
    };

    QuadFaceDescriptor& getNeighborRef(const QuadFaceDescriptor& quadDesc)
    {
        mcassert(quadDesc.isValid());
        return m_connectivity_1to1[quadDesc.idxZone].faceConnectivity[quadDesc.idxFace][quadDesc.idxQuad];
    }

    McDArray<ZoneConnectivity_1to1> m_connectivity_1to1;
};

#endif


/// @}
