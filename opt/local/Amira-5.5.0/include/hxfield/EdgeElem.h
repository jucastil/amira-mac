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
#ifndef EDGE_ELEM_H
#define EDGE_ELEM_H

#include <string.h>
#include <stdlib.h>
#include <math.h>

class Jacobian;

////////////////////////////////////////////////////////////////////////
//
//  Geometric entities
//
struct POINT2D { float x[2]; };  // a point in 2D-space

struct POINT3D { float x[3]; };  // a point in 3D-space

struct TR  // geometric representation of a triangle
{
    POINT2D p[3];  // the three points of the triangle
    void unitCoordinates(float u[2], const float x[2],
        const Jacobian& Jac) const;
};

struct TET // geometric representation of a tetrahedron
{
    POINT3D p[4];  // the four points of the tetrahedron
    void unitCoordinates(float u[3], const float x[3],
        const Jacobian& Jac) const;
};

////////////////////////////////////////////////////////////////////////
//
//  Jacobian matrix
//
class Jacobian
{
  public:
    float detJ;
    float J[3][3];              // Jacobian
    float Jinv[3][3];           // inverse Jacobian

    Jacobian() { }
    void compJ(TET& t);
    void compJ(TR&  t);
};

////////////////////////////////////////////////////////////////////////
//
//  Edge element in 3D-space
//
class EdgeElement3
{
  public:
    EdgeElement3();
    ~EdgeElement3();

    /*
    static const int SpaceDim;
    static const int LDim;
    static const int NoOfPoints;
    static const int NoOfNodes;
    static const int NodesOnPoint;
    static const int NodesOnEdge;
    static const int InnerNodes;
    static const int NoOfEdges;
    static const int NoOfFaces;
    */

    enum {
        SpaceDim = 3,
        LDim = 4,
        NoOfPoints = 4,
        NoOfNodes = 6,
        NodesOnPoint = 0,
        NodesOnEdge = 1,
        InnerNodes = 0,
        NoOfEdges = 6,
        NoOfFaces = 4
    };

    void vectorAt(float vec[SpaceDim], const float xUnit[SpaceDim],
                const Jacobian& Jac, const float sol[NoOfNodes]) const;

    void complexVectorAt(float vecRe[SpaceDim], float vecIm[SpaceDim],
                         const float xUnit[SpaceDim], const Jacobian& Jac,
                         const float solRe[NoOfNodes],
                         const float solIm[NoOfNodes]) const;

    void complexVectorAt5Points(float res[10*SpaceDim],
                                const Jacobian& Jac,
                                const float solRe[NoOfNodes],
                                const float solIm[NoOfNodes]) const;

    void curlAt(float curl[3], const float xUnit[SpaceDim],
                const Jacobian& Jac, const float sol[NoOfNodes]) const;

    void complexCurlAt(float curlRe[3], float curlIm[3],
                       const float xUnit[SpaceDim],
                       const Jacobian& Jac,
                       const float solRe[NoOfNodes],
                       const float solIm[NoOfNodes]) const;

    void projComplexConst2EdgeSimple(const float vecRe[3], const float vecIm[3],
                                     const Jacobian& J,
                                     float solre[NoOfNodes],
                                     float solim[NoOfNodes]);

    void projComplexConst2EdgeDiag(const float vecRe[3], const float vecIm[3],
                                   const Jacobian& J,
                                   float solre[NoOfNodes],
                                   float solim[NoOfNodes],
                                   float diagMass[NoOfNodes]);

    void projComplexConst2EdgeLumped(const float vecRe[3], const float vecIm[3],
                                     const Jacobian& J,
                                     float solre[NoOfNodes],
                                     float solim[NoOfNodes],
                                     float lumpedMass[NoOfNodes]);

    void projComplexConst2EdgeComplete(const float vecRe[3], const float vecIm[3],
                                       const Jacobian& J,
                                       float solre[NoOfNodes],
                                       float solim[NoOfNodes],
                                       float localMassMat[6][6],
                                       int assembleMassMat=1);


  protected:
    static const int Vert[NoOfEdges][2]; // the two vertices of an edge

    void compdL(float dL[LDim][SpaceDim], const Jacobian& Jac) const;

    void compL (float L[LDim], const float xu[SpaceDim]) const;

    void compW (float W[NoOfNodes][SpaceDim],
        const float L[LDim], const float dL[LDim][SpaceDim]) const;

    void compCurlW(float curlW[NoOfNodes][3],
        const float dL[LDim][SpaceDim]) const;

    void crossProduct(float z[3], const float x[3], const float y[3]) const;
};

#endif // EDGE_ELEM_H

/// @}
