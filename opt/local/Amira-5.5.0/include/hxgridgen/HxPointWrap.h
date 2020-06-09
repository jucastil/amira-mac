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

/// @addtogroup hxgridgen hxgridgen
/// @{
#ifndef HX_POINTWRAP
#define HX_POINTWRAP

#include <hxgridgen/HxGridGenWinDLLApi.h>

#include <hxcore/HxVertexSet.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>

#include <hxgridgen/PointTable.h>

class HXGRIDGEN_API HxPointWrap : public HxCompModule 
{

    HX_HEADER(HxPointWrap);

protected:

    struct Job
    {
        mclong    vertices[3];
        mclong    face;

        Job(){};

        Job(mclong v0, mclong v1, mclong v2, mclong oldFace)
        {
            vertices[0] = v0;
            vertices[1] = v1;
            vertices[2] = v2;
            face = oldFace;
        }
    };

    McDArray<Job>       queue;
    ///
    HxPortFloatSlider   portProbeRadius;
    ///
    HxPortRadioBox      portSearchAxis;
    ///
    HxPortRadioBox      portAdaptiveProbeSize;
    ///
    HxPortFloatSlider   portEnlargementFactor;
    ///
    HxPortIntSlider     portMaxAttempts;
    ///
    HxPortDoIt          portAction;

    /// vertex data
    mclong          numPoints;

    /// point coordinates
    McVec3f       * coords;
    McBox3f         bbox;
    float           probeRadius;

    /// 3D array, used to quickly find neighboring points.
    PointTable    * pointTable;
    ///



    mclong      findEdge(mclong v0, mclong v1);

    mclong      computeReducedSurface();
    
    mclong      findInitialFace(mclong searchAxis, mclong facePoints[3], McVec3f &faceNormal);

    inline void handleEdge(mclong v1, mclong v2, mclong v3, mclong face);
    
    mclong      isProbePlacementPossible(McVec3f probePos, mclong idx[3], float radius); 

    /// returns face index
    mclong      insertNewTriangle( mclong orientedVertices[3], McVec3f faceNormal);

    void        insertEdge(mclong v0, mclong v1, mclong face);    
    
    void        clear();


public:

    HxPointWrap();
    ~HxPointWrap();


    virtual void update();
    virtual void compute();


    ////////////////////////////////////////////////////////////
    // helper class 
    ////////////////////////////////////////////////////////////
    class MyEdge
    {
    public:
        void set(mclong v0, mclong v1, mclong face )
        {
            _vertexIdx[0] = v0; 
            _vertexIdx[1] = v1;
            _faces[0]     = face;
            _numFaces     = 1;
        }
    
        void addFace(mclong face)
        {
            if (_numFaces==2) return;

            if (_numFaces==1) 
	            _faces[1] = face;
            else
	            _faces[0] = face;
            _numFaces++;
        }
       
        mclong hasTwoFaces()
        { 
            return (_numFaces==2); 
        }

        mclong theOtherPoint( mclong vertex )
        {
            return ( _vertexIdx[0]==vertex) ? _vertexIdx[1] : _vertexIdx[0];
        }


        mclong            _vertexIdx[2];
        unsigned char     _numFaces;
        mclong            _faces[2]; // face index
    };


    class MyFace
    {
    public:
        void set(mclong vIdx[3], McVec3f & normal)
        {
            _edge[0] = _edge[1] = _edge[2] = -1;
            _orientedVertexIdx[0] = vIdx[0];
            _orientedVertexIdx[1] = vIdx[1]; 
            _orientedVertexIdx[2] = vIdx[2];
            _normal = normal;
            _pending = 1;
            _deleted = 0;            
        }

        void getVertexIdx(mclong v[3])
	    { 
            v[0] = _orientedVertexIdx[0]; 
            v[1] = _orientedVertexIdx[1]; 
            v[2] = _orientedVertexIdx[2]; 
        }
    
        mclong * getVertexIdx()
        { 
            return _orientedVertexIdx; 
        }
    
        McVec3f & getFaceNormal() 
        { 
            return _normal; 
        }
    
        void addEdge( mclong edge )
        {
            if (_edge[0]<0) 
            {
	            _edge[0] = edge;
	            return;
            }
            if (_edge[1]>0) 
            {
	            _edge[1] = edge;
	            return;
            }
            if (_edge[2]<0)
	            _edge[2] = edge;
        }

        void setDeleted() 
        { 
            _deleted = 1;
        }
        
        mclong isDeleted()  
        { 
            return _deleted;
        }

        void setPending() 
        { 
            _pending = 1;
        }


        unsigned char     _pending;
        unsigned char     _deleted;
        mclong            _edge[3]; // edge index
        mclong            _orientedVertexIdx[3];
        McVec3f           _normal;
    };

    mclong isFacePending( mclong faceIdx )
    {
        mclong   i;
        MyFace & f  = _allFaces[faceIdx];
        // edge 0
        i = f._edge[0];
        if (i<0) return 1;
        if (!_allEdges[i].hasTwoFaces()) return 1;
        // edge 1
        i = f._edge[1];
        if (i<0) return 1;
        if (!_allEdges[i].hasTwoFaces()) return 1;
        // edge 2
        i = f._edge[2];
        if (i<0) return 1;
        if (_allEdges[i].hasTwoFaces()) return 1; // is this a bug ?

        return 0;
    }


    ////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////
    McDArray<MyFace>                    _allFaces;
    McDArray<MyEdge>                    _allEdges;

    McDArray< McSmallArray<mclong,6> >  _edgesPerPoint;
    McDArray<int>                       _facesPerPoint;

    
    ////////////////////////////////////////////////////////////
    // math stuff
    ////////////////////////////////////////////////////////////

    static void computeTorusForPoints(const McVec3f &coords1, const McVec3f &coords2,
				      float radius, McVec3f &torusCenter, float &torusRadius);

    static float computeDensity(const McBox3f &bbox, mclong N);

    static mclong computeProbePos(McVec3f a, McVec3f b, McVec3f c, float probeRadius,
			        McVec3f &basePoint, McVec3f &baseTriNormal, float &probeHeight);

    static mclong coplanar(mclong * idx, McVec3f normal, mclong * idxOther, McVec3f normal2);
};

#endif

/// @}
