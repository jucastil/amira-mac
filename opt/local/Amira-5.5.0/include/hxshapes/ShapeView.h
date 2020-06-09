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

/// @addtogroup hxshapes hxshapes
/// @{
#ifndef SHAPEVIEW_H
#define SHAPEVIEW_H

#include "HxShapesWinDLLApi.h"

class SbString;
class SoEventCallback;
class SoTriangleStripSet;
class SoIndexedTriangleStripSet;
class SoIndexedLineSet;
class SoShapeHints;
class SbColor;
class SoSeperator;
class SoMaterial;
class SoVertexProperty;
class SoFaceSet;
class SoGroup;
class SoDetail;
class SoPickedPoint;
class SoDrawStyle;
class SbVec3f;
class McBitfield;

#include <mclib/McHandable.h>
#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>

class McVec3f;
class McVec2f;
class McColor;


const int subDivisionMin    = 3;
const int subDivisionFactor = 25;

/* following classes allow easy creation and handling of OI shapes
   incl. a mechanism to reconstruct the indices of picked parts from 
   SoDetail Information given by a picking event */

// ----------------------------------------------------------------
//          ShapeView

class HXSHAPES_API ShapeView : public McHandable {

public:

    virtual void show();
    virtual void hide();
    /* will set the name of the rootnode of this shape to 
       @c name to allow identification of the object when
       doing event processing 
       note that an inventor eventCB will return a subnode
       of this group as tail of the picked path,
       thus you have to follow the path up until you
       found a node with a namelength>0 */
    virtual void setName(const char* name);
    virtual void setName(SbName name);

    virtual void setColor(const SbColor& col);
    virtual void setColor(const McColor& col);
    virtual void setColorTransparency(uint32_t);
    virtual void setTransparency(float t);
    virtual void setDrawStyle(SoDrawStyle* d);
    virtual void setShininess(float s);

protected:

    // parent group given in constructor
    SoGroup* parent;
    // subseperator inserted as child of parent
    SoSeparator* s;
    // material node (might be inserted as child of s)
    SoMaterial*  material;
    // drawstyle node (might be inserted as child of s)
    SoDrawStyle* style;

    /* constuctor, @c parent is root seperator of object subgraph */
    ShapeView(SoGroup* parent);

    /* destructor, automatically removes structure from parent node */
    virtual ~ShapeView();
};

// ----------------------------------------------------------------
//          PointSequenceView

class HXSHAPES_API PointSequenceView : public ShapeView {

public:
    
    /* each edge between 2 coordinates is called a coPart
       this method will transform the information of 
       a picking event (picked face) to the index  of
       the picked coPart which will be returned
       if something went wrong (e.g. picked point not 
       part of this shape) then -1 will be returned */
    int getPickedPart(const SoPickedPoint* p) const;

protected:

    PointSequenceView(SoGroup* parent);

    virtual int _getPickedPart(const SoPickedPoint* p) const = 0;
    
    virtual ~PointSequenceView();
    
};

// ----------------------------------------------------------------
//          AngleView

class HXSHAPES_API AngleView : public ShapeView {

public:

    AngleView(SoGroup* parent);

    bool draw(const McVec3f& posVec,const McVec3f& dir1Vec,const McVec3f& dir2Vec);

protected:   

    virtual ~AngleView();

private:

    SoFaceSet* angleIcon;

};

// ----------------------------------------------------------------
//          PlaneView

class HXSHAPES_API PlaneView : public ShapeView {

public:

    PlaneView(SoGroup* parent);

    bool draw(const McVec3f& posVec,
              const McVec3f& dir1Vec,
              const McVec3f& dir2Vec);

protected:   

    virtual ~PlaneView();

private:

    SoTriangleStripSet* surface;

};

// -------------------------------------------------------------------------
//                     RibbonView

class HXSHAPES_API RibbonView : public PointSequenceView {

public:
    
    RibbonView(SoGroup* parent);

    bool draw(const McDArray<McVec3f>& coords,
              const McDArray<McVec3f> translationNormals,
              const McDArray<float>& widths,
              int stripNum,
              int interpolationPointNumber,
              bool colorPerVertex,          
              const McDArray<uint32_t>& col);

    bool reColor(const McDArray<uint32_t>& col);

protected:   
    
    virtual ~RibbonView();

    virtual int _getPickedPart(const SoPickedPoint* p) const;

private:

    SoIndexedTriangleStripSet* ribbon;
    SoShapeHints* hints;

    // following info is needed to reconstruct the picked part

    int interpolationPointNumber;  

};

class HXSHAPES_API SolidRibbonView : public PointSequenceView {

public:
    
    SolidRibbonView(SoGroup* parent);

    bool draw(const McDArray<McVec3f>& coords,
              const McDArray<McVec3f> translationNormals,
              const McDArray<float>& widths,
              const McDArray<float>& height,
              int stripNum,
              int interpolationPointNumber,
              bool colorPerVertex,          
              const McDArray<uint32_t>& col,
              const McBitfield* isShown=0);      // [optional] isShown for each linePart
    bool reColor(const McDArray<uint32_t>& col);
    
protected:   
    
    virtual ~SolidRibbonView();

    virtual int _getPickedPart(const SoPickedPoint* p) const;

private:

    SoIndexedTriangleStripSet* ribbon;
    SoShapeHints* hints;

    // following info is needed to reconstruct the picked part
  
    McDArray<int> partIx2edgeIx; 

};

// -------------------------------------------------------------------------
//                     ThreadView

class HXSHAPES_API ThreadsView : public PointSequenceView {

public:

    ThreadsView(SoGroup* parent);

    bool draw(const McDArray<McVec3f>& coords,
              const McDArray<McVec3f>& translationNormals,
              const McDArray<float>& widths,
              int threadsNum,
              int interpolationPointNumber,
              int lineWidth,
              const McDArray<uint32_t>& col,
              bool colorPerVertex=false);
    
    bool reColor(const McDArray<uint32_t>& col);

protected:  

    virtual ~ThreadsView();

    virtual int _getPickedPart(const SoPickedPoint* p) const;

private:

    SoIndexedLineSet* threads;

    // following info is needed to reconstruct the picked part

    int interpolationPointNumber;  
    McDArray<McVec2i> partStartEndLineIx; // start and end face ix of each stripset part
};


// -------------------------------------------------------------------------
//                     ArrowView

class HXSHAPES_API ArrowView : public PointSequenceView {

public:

    ArrowView(SoGroup* parent);

    bool draw(  const McDArray<McVec3f>& coords,  // coordinates as point sequence
                const McDArray<McVec3f>& normals, // normals per coordinate
                float width,                      // arrow width
                float height,                     // arrow height
                int headCoNum,                    // number of coordinates which will form the head
                float headWidthFac,               // how much bigger shall the begining of the head be than the tail
                bool colorPerVertex,              // colaration per vertex
                const McDArray<uint32_t>& col,     // [optional] colors
                const McBitfield* isShown=0);      // [optional] isShown for each linePart

    virtual bool reColor(const McDArray<uint32_t>& col);
   
protected:   

    virtual ~ArrowView();

    virtual int _getPickedPart(const SoPickedPoint* p) const;

private:
    
    void computeIndexNum(int numCoords,
                         int headCoPartNum,
                         bool broadHead,
                         bool showIn3D,
                         int* indexNum) const;
    
    int computeVertNum(int coordNum,
                       int headCoPartNum, 
                       bool showIn3D) const;
    
    enum ArrowPart {
        HEAD_TOP=0,
        HEAD_BOTTOM=1,
        HEAD_START_LEFT=2,
        HEAD_START_RIGHT=3,
        HEAD_LEFT=4,
        HEAD_RIGHT=5,
        START=6,
        END=7,
        TOP=8,
        BOTTOM=9,
        LEFT=10,
        RIGHT=11
    };

    SoIndexedTriangleStripSet* arrow;
    SoShapeHints* hints;

    // following info is needed to reconstruct the picked part

    McDArray<int> faceIx2edgeIx; 
};


// -------------------------------------------------------------------------
//                     TubeView

class HXSHAPES_API TubeView : public PointSequenceView {

public:
    
    TubeView(SoGroup* parent);    

    enum capShape { HEMISPHERE, CONE, CONE_INWARD, FLAT, NONE };

    virtual bool draw(const McDArray<McVec3f>& coords,
        capShape capType,
        float radius,
        float complexity,
        const McDArray<uint32_t>& col,
        bool colorPerVertex=true,
        McBitfield* show = 0);

    virtual bool drawMultipleRadius(const McDArray<McVec3f>& coords,
        capShape capType,
        McDArray<float> radius,
        float complexity,
        const McDArray<uint32_t>& col,
        bool colorPerVertex=true,
        McBitfield* show = 0);

	virtual bool drawAll(McDArray<McDArray<SbVec3f> > coordinates, 
        McDArray<McDArray<capShape> > capTypes, 
        McDArray<McDArray<uint32_t> > colorsOfTubes,					  
        McDArray<McDArray<float > > radius,
        float complexity);

    
    virtual bool reColor(const McDArray<uint32_t>& col);

	virtual bool reColor(const McDArray<McDArray<uint32_t> > & col);

protected:

    virtual ~TubeView();

    virtual int _getPickedPart(const SoPickedPoint* p) const;

private:

    void computeCapNumbers(capShape capType,int subDivision, 
                           int &nPerCapCoords, int &nPerCapNormals, 
                           int &nPerCapCoInd, int &nRingsPerHead);
    
    void addConeLikeCap(const McDArray<McVec3f>& coords,
                        int coIx, 
                        bool capNormalDir,
                        bool ellipticProfile,
                        McVec2f& semiAxesLength,
                        float radius,
                        capShape capType,
                        int subDivision, 
                        McDArray<SbVec3f>& co,McDArray<SbVec3f>& no,
                        McDArray<int>& coInd, McDArray<int>&  noInd, 
                        McDArray<int>& colInd,
                        bool& coloration);
    void addHemisphereLikeCap(const McDArray<McVec3f>& coords,
                              int coIx, 
                              bool capNormalDir,
                              bool ellipticProfile,
                              McVec2f& semiAxesLength,
                              float radius,
                              capShape capType,
                              int subDivision, 
                              McDArray<SbVec3f>& co,McDArray<SbVec3f>& no,
                              McDArray<int>& coInd, McDArray<int>&  noInd, 
                              McDArray<int>& colInd,
                              bool& coloration);    
    SoIndexedTriangleStripSet* tube;
    SoShapeHints* hints;
    bool colorPerVertex;    
    
    // following info is needed to reconstruct the picked part
    
    McDArray<int> faceIx2edgeIx; 
};

class HXSHAPES_API BondView : public PointSequenceView {
    
public:

    BondView(SoGroup* parent);
    /// This constructor assumes that @c strip has already been added
    /// to @c parent outside the constructor using addChild(..).
    BondView(SoGroup* parent, SoIndexedTriangleStripSet* strip);


    enum capShape { HEMISPHERE, CONE, CONE_INWARD, FLAT, NONE };

    virtual bool drawAll(McDArray<McDArray<SbVec3f> > coordinates, 
                         McDArray<McDArray<capShape > > capTypes, 
                         McDArray<McDArray<uint32_t> > colorsOfTubes,
                         float complexity, 
                         float radius);
    
    
    
    virtual bool reColor(const McDArray<uint32_t>& col);
protected:
    
    virtual ~BondView();
    virtual int _getPickedPart(const SoPickedPoint* p) const;
    
    SoIndexedTriangleStripSet* tube;
    SoShapeHints* hints;
    bool colorPerVertex;    
    // following info is needed to reconstruct the picked part
    
    McDArray<McVec2i> partStartEndFaceIx; // start and end face ix of each stripset part
};

#endif



/// @}
