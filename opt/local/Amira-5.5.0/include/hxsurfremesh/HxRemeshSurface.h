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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef HX_REMESH_SURFACE_H
#define HX_REMESH_SURFACE_H

#include <mclib/McHandle.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortRadioBox.h>

#include <hxsurface/HxSurfaceScalarField.h>

#include <hxsurfremesh/RmAtlasSurface.h>

#include "RemeshSurface.h"
#include "hxsurfremeshAPI.h"

class HxSurface;

class HXSURFREMESH_API HxRemeshSurface : public HxCompModule {

    HX_HEADER(HxRemeshSurface);

public:
    HxRemeshSurface();

    ~HxRemeshSurface();

    HxConnection       portDensityField;
    HxConnection       portEdgeLengthField;
    McDArray< HxConnection* > portSurfacePathSets;

    HxPortToggleList   portAdvancedOptions;
    HxPortMultiMenu    portObjective;
    HxPortIntTextN     portTriangleArea;
    HxPortIntTextN     portVertexValence;
    HxPortIntTextN     portTriangleQuality;
    HxPortIntTextN     portLloydRelaxation;
    HxPortButtonList   portDefaults;
    HxPortIntTextN     portDesiredSize;
    HxPortFloatTextN   portErrorThresholds;
    HxPortFloatTextN   portDensityContrast;
    HxPortFloatTextN   portDensityRange;
    HxPortRadioBox     portInterpolateOrigSurface;
    HxPortToggleList   portRemeshOptions1;
    HxPortToggleList   portSurfacePathOptions;
    HxPortRadioBox     portRemeshOptions2;
    HxPortIntTextN     portContourLayers;
    HxPortDoIt         portRemesh;
    HxPortButtonList   portModifyResult;

    virtual void update();
    virtual void compute();
    virtual void resultChanged(int id);
    virtual int  parse(Tcl_Interp* t, int argc, char **argv);

    static  void smoothDensityField(HxSurface* surf, float* curvature, int nVertices, int nRounds);
    static  void combineCurvatureFields(float* k, float* h, float* curvature, float alpha, float beta, int nVertices);

    /** Overwrite virtual function savePorts to allow handling of
        dynamic connection ports. */
    virtual void savePorts( FILE* fp );
    
private:
    enum {
        HIGH_REGULARITY    = 0,
        ISOTROPIC_SAMPLING = 1
    };

    McHandle<RemeshSurface>        surfaceRemesher;
    McHandle<RmAtlasSurface>       surfaceOnAtlas;
    McHandle<HxSurfaceScalarField> densityField;
    McHandle<HxSurfaceScalarField> sourceField;
    int                            m_numDesiredVertices;
    int                            m_desiredPercentage;
    // This flag keeps track about parameter changes.  In case the
    // parameter changes would require a restart of the remeshing
    // instead of a modification of the current result, this flag is
    // set to true.
    bool                           m_restartRemeshingFlag;
    // Remember the verbosity.  A value of 0 indicates that no debug
    // output will be printed.
    int                            m_verbosity;
    
    void setDefaults(const int objective);

    // If @c percentage is positive, the @c percentage of the number
    // of surface points, @c numSurfPoints, will be used as desired
    // size.  If @c percentage is not positive, then if @c numTris is
    // positive, the number of vertices will be computed from the
    // number of triangles, and vice versa.  To correctly update the
    // @c percentage, @c numSurfPoints is always required.
    void setDesiredNumberOfVerticesAndTriangles(const int numVert,
                                                const int numTris,
                                                const int percentage,
                                                const int numSurfPoints);
    
    void showRegularity();
    static float angleDeficitGaussCurvature(HxSurface* surf, int v);
    static float discreteMeanCurvature(HxSurface* surf, int v);
    void checkDisplayModule();

    /** Updates, i.e. deletes or creates new, dynamic connections to
        surface path sets. */
    void updateSurfacePathSetConnections();

    /** Get all surface paths that should be considered for remeshing;
        only vertex paths are allowed. */
    void getSurfacePathSets( McDArray< SurfacePathSet * > & surfacePathSets );

    /** Compute the density field that will determine the distribution
        of points on the final surface.  It takes the number of
        surface points as input. */
    HxSurfaceScalarField * computeDensityField( const int & nSurfacePoints );

    /** Get all control points from all surface paths of all @
        surfacePathSets. */
    void getSurfacePathSetsControlPoints( const McDArray< SurfacePathSet * > & surfacePathSets,
                                                McDArray< int >              & controlPoints );

    /** Initialize member variables @c surfaceOnAtlas and 
        @c surfaceRemesher from @c inputSurface, @c minEdgeLengths, 
        @c surfacePathSets, and @c fixPoints.  Here, @c minEdgeLengths
        is the surface scalar field specifying the minimum edge
        lengths of the resulting mesh. */
    void initAtlasSurfaceAndRemesher(       HxSurface                    * inputSurface,
                                      const float                        * minEdgeLengths,
                                      const McDArray< SurfacePathSet * > & surfacePathSets,
                                      const McDArray< int >              & fixPoints );

    /** Refine the surface edges according to the @c minEdgeLengths
        field.  After each refinement step, @c nMove remeshing steps
        are performed.  If @c ignoreContours is true, then contours
        will not be refined. */
    bool refineEdges( const float * minEdgeLengths,
                      const int     nMove,
                      const bool    ignoreContours );

    /** Reduce number of vertices in mesh until only 
        @c nDesiredVertices remain.  @c nMove remeshing steps are
        performed after each decimation step.  If @c ignoreContours is
        true, then contours will not be refined.  If 
        @c doContractBoundaryEdges is true, boundary edges will be
        contracted. */
    bool simplifyMesh( const int  nDesiredVertices,
                       const int  nMove,
                       const bool ignoreContours,
                       const bool doContractBoundaryEdges );

    /** Remesh the surface based on area criteria.  The number of
        remeshing steps is given by @c nRemeshingSteps.  The other
        parameter have the same meaning as in simplifyMesh(...). */
    bool remeshAreaBased( const int  nRemeshingSteps,
                          const int  nMove,
                          const bool ignoreContours,
                          const bool doContractBoundaryEdges );

    /** Remesh the surface such that the sampling of the vertices is
        as isotropic as possible according to the given vertex
        distribution.  This algorithm uses Lloyd relaxation.  The
        relaxation is performed in @c nVoronoiSteps and contours will
        be ignored, if @c ignoreContours is set to true. */
    bool remeshIsotropicSampling( const int  nVoronoiSteps,
                                  const bool ignoreContours );

    /** Remesh the surface such that the triangle mesh is as regular
        as possible, where regular means that the number of triangles
        attached to a single vertex should be 6.  This algorithm tries
        to explicitly improve the regularity.  The regularisation is
        performed in @c nRegularisationSteps.  After the
        regularisation an angle-based smoothing with 
        @c nSmoothingSteps is performed.  Contours will be ignored
        during regularisation and smoothing, if @c ignoreContours is
        set to true.  Boundary edges will be contracted if @c is set
        to true. */
    bool remeshHighRegularity( const int  nRegularisationSteps,
                               const int  nSmoothingSteps,
                               const bool ignoreContours,
                               const bool doContractBoundaryEdges );

    /** Output surface to object pool. */
    void setSurface(RmAtlasSurface * surfaceOnAtlas);
};

#endif

/// @}
