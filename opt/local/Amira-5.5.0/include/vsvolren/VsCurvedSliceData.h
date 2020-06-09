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
#ifndef _VS_CURVED_SLICE_DATA_H
#define _VS_CURVED_SLICE_DATA_H

#include "VsSliceData.h"
#include "VsQuadMesh.h"

// VsCurvedSliceData implements the interface of VsSliceData.
// The main purpose is to build a wrapper that uses the VsQuadmesh class and 
// that implements the VsSliceData interface.
class VsCurvedSliceData : public VsSliceData
{
 public:
 
    // TODO: this is not used yet
    // for later extensions, e.g. triangular slice data 
    enum MeshType {QUAD_MESH, TRIANGLE_MESH, GENERIC_MESH};
    
    VsCurvedSliceData(VsVolume * vol, VsData * data);
    ~VsCurvedSliceData();

    /// Set a transformation matrix
    virtual VSRESULT setTransformationMatrix( const McMat4f & inMatrix );

    // --------------------------------------
    // Overloaded from VsSliceData
    // --------------------------------------
    /// Returns the projected compute time for that slice in milliseconds
    virtual float computeTime(float setupTimePerPixelNS, int level, int stride);

    /// Extract the curved slice from object - setup an appropriate render geometry with the right texture coordinates 
    virtual VSRESULT compute(bool & needReload, VsObject &object);
    /// Returns whether the slice was extracted with full quality
    virtual bool isHighQuality() const { return VsSliceData::isHighQuality() && mFilter == VsSlice::LINEAR; };

    /// Returns the actual number of thick slices.
    virtual int numThickSlices() const;

    /// Returns texDims, the smallest 2^n  >=  sliceDims
    virtual const int * texDims() const;

#if 0
    //!! TODO: not used any more - remove occationally
    /// Returns texture coordinate for 3D position
    virtual bool mapToTextureCoord(McVec3f & inPosition, int &x, int &y) const;
#endif

    /// Access the geometry, that was used for sampling the volume data
    virtual const VsMesh * sampleGeometry() const { return m_pCutMesh; }
    /// Access the geometry, that should be used for displaying the sampled data
    virtual const VsMesh * renderGeometry() const { return m_pRenderMesh; }

    /// Dumps additional object information into a head-up display
    virtual void dump(VsHeadUpDisplay & hud, VsHeadUpDisplay::Placement placement);

    // --------------------------------------
    // New methods
    // --------------------------------------
    
    /// Set a sampling geometry
    VSRESULT setCutGeometry(VsQuadMesh* quadMesh);
    /// Set a rendering geometry
    VSRESULT setRenderGeometry(VsQuadMesh* quadMesh);

 private:

    /// Do the slice extraction
    bool extractSlice(VsObject &object);

    /// Access for timing statistics for a given level
    float & extractionTime(int filter, int level);
    /// Update the timing statistics for the current level
    void updateTimings(float extractionTimeMS);

    /// Returns the number of voxels for a specific resolution level.
    int computeVoxels(int level) const;

 private:

    // moved from VsSliceData to VsPlanesliceData and VsCurvedSliceData
    MeshType m_meshType;
  
    // TODO: right handling of "hiresdata" (high res data is currently no requirement for curved slices)
    
    /// Timing statistics for slice extraction - used for calculating projected compute time
    float m_ExtractionTimePerVoxelNS[2][3];
    /** The image size that would represent the full resolution - usually same as sliceDims() but may 
        be larger to compensate for a downsampling */
    McVec2i m_logicalSliceDims;
    /// The level where the slice was extracted
    int m_logicalLevel;

    // The mesh that is used to extract the textures.
    McHandle<VsQuadMesh> m_pCutMesh;

    // The rendermesh is basically equal to the cut mesh,
    // i.e. the textures, texture coords, number of vertices are usually equal,
    // but the coords of the vertices can be different
    McHandle<VsQuadMesh> m_pRenderMesh;

    /// Flag indicating that the internal polygon list needs recomputation
    bool m_RenderGeometryDirty;
};

#endif

/// @}
