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

/// @addtogroup hxsplats hxsplats
/// @{
#ifndef TETRA_VISIBILITY_SORT_MPVONC_H
#define TETRA_VISIBILITY_SORT_MPVONC_H

#include <Inventor/SbLinear.h>
#include <mclib/McDArray.h>
#include <mclib/McPrimType.h>
#include <mclib/McMat4f.h>

class TetraVisibilitySortMPVONC {
public:
    TetraVisibilitySortMPVONC(int            nTetras, 
                              int            nFaces,
                              const McVec4f* faces,
                              const int*     lowerTetras,
                              const int*     upperTetras,
                              int            nBoundaries,
                              const int*     boundaryTetras,
                              McMat4f        MVPInverse,
                              const McVec3f* vertices,
                              const int*     tetraVertices,
                              McDArray<int>& sortedTetras);


    static void sort(int            nTetras, 
                     int            nFaces,
                     const McVec4f* faces,
                     const int*     lowerTetras,
                     const int*     upperTetras,
                     int            nBoundaries,
                     const int*     boundaryTetras,
                     McMat4f        MVPInverse,
                     const McVec3f* vertices,
                     const int*     tetraVertices,
                     McDArray<int>& sortedTetras);

protected:
    int            m_nTetras; 
    int            m_nFaces;
    const McVec4f* m_faces;
    const int*     m_lowerTetras;
    const int*     m_upperTetras;
    int            m_nBoundaries;
    const int*     m_boundaryTetras;
    McMat4f        m_MVPInverse;
    const McVec3f* m_vertices;
    const int*     m_tetraVertices;
    McDArray<int>& m_sortedTetras;

    void preparePredecessorGraph();

    void dfs(int iTetra);

    struct StartNodeElement {
        float distanceToViewpoint;
        int   tetraId;
        StartNodeElement(float dist, int tetraId) : distanceToViewpoint(dist), tetraId(tetraId) {};
        StartNodeElement(){};

    };

    static int compareStartNodeElements(const StartNodeElement& sne1, const StartNodeElement& sne2);

    struct GraphVertex {
        GraphVertex() {
            outDegree = 0;
            adjacent[0] = adjacent[1] = adjacent[2] = 0; 
        };

        void addAdjacent(int iVertex) {
          //  assert(outDegree<3);
          // Pascal Doux (3-Jan-2008): 
         // We have found once a case where this test was false so the program crashed.
          // This is probably due to a wrongdata file but it shouldn't crash...
            if (outDegree<3) {
              adjacent[outDegree] = iVertex;
              outDegree++;
            }
        }

        int outDegree;
        int adjacent[3];
    };
    McDArray<GraphVertex> m_graph;

    McDArray<StartNodeElement> m_startNodeList;

    McDArray<bool> m_visited;
    McDArray<bool> m_visitedOnThisDescent;


};


#endif



/// @}
