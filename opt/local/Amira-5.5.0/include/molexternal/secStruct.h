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

/// @addtogroup molexternal molexternal
/// @{
#ifndef SECSTRUCT_H
#define SECSTRUCT_H

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>

#include <hxshapes/ShapeView.h>
class SoPickedPoint;
class SecStructureView;
class SbColor;

/* The following classes implement a midlevel abstraction between
    the group based apporach in SecStructureView and the ShapeView
    approach
    The classes allow simple handling of viewModes for each
    secondary structure element. They implement viewing by
    using objects of the PointSequenceView class hierarchy.
    Viewing parameters are direclty taken from the SecStructureView
*/
    
class secStruct : public McHandable {

public:
    
    /* enum for different structures, backbone MUST be 0 */
    enum structType { 
        BACKBONE = 0,
        HELIX    = 1,
        SHEET    = 2,
        TURN     = 3
    };

    /* enum for update modes */
    enum updateMode { 
        UPDATE_SHAPE       = 0,
        UPDATE_COLORS      = 1,
        UPDATE_SELECTION   = 1,
    };

    /* class for saving the connection point between the two ends of a secStruct and
    the backbone */
    struct connectionPoints {
    public: 
        McVec3f start1;// first
        McVec3f start2;// second
        McVec3f end1; // last
        McVec3f end2; // second last
    };
    //    
    secStruct(const SecStructureView* ssv,const McBitfield& residues);
    //
    ~secStruct();
    // return the residues of this secStructrue
    const McBitfield& getResiduesBitfield() const;
    
    // returns type of secondary structure (corresponding to the enum)
    virtual int getStructType() const = 0;
    
    // returns if secStructure is shown in viewer
    bool isShown() const;
    
    // delete all viewer objects thus removing the secStuct from the viewer
    virtual void hide();
    virtual void hide(int viewerIx);
    
    // updates everything neccessary according to the updateMode
    virtual void update(updateMode mode);
    
    // will return the optimal label offset as used by MolLabel
    virtual float getLabelOffset() const = 0;
    
    //
    virtual bool containsRes(int resIx) const;
    
    //
    virtual bool containsRes(McBitfield res) const;
    
    //
    int firstRes() const;
    
    //
    int lastRes() const;

    virtual int getPickedResidue(int viewerIx,const SoPickedPoint* p ) const;

protected:

    virtual void _update(updateMode mode) = 0;
    uint32_t getResidueColor(int resIx) const;
    void colorListExpand(McDArray<uint32_t>& colors,int interpolationPointNum) const;
    void bitfieldExpand(McBitfield& bf,int iPolNum) const;
    bool isSingleColorOptimizationPossible(const McDArray<uint32_t>& colors,int minIx=-1,int maxIx=-1) const;

    // bitfield containing which residues belong to this secStruct
    McBitfield residues;
    // type of view (as defined by an enum in a subclass)
    int viewMode;
    // SecStructureView object that has created this secStruct
    const SecStructureView* ssv;
    // the viewer objects that will show the secStruct
    McDArray<McHandle<PointSequenceView> > viewer;
    // maps each part which has been set in a viewer to a residue
    // outer list over viewer, inner list over colorIx
    McDArray<McDArray<int> > partIx2ResIx;
};

// --------------------------------------------------------------------------

class helix : public secStruct {
public:    
    McVec3f  axisStart;
    McVec3f  axisEnd;
    connectionPoints edges;
    enum viewType { TUBE, RIBBON_FLAT,RIBBON_SOLID,CYLINDER};
    helix(const SecStructureView* ssv,const McBitfield& residues);
    virtual int getStructType() const;
    virtual float getLabelOffset() const;
    virtual int getPickedResidue(int viewerIx,const SoPickedPoint* p ) const;

protected:
    virtual void _update(updateMode mode);
    void updateTube(int viewerIx,updateMode mode);
    void updateRibbon(int viewerIx,updateMode mode);
    void updateCylinder(int viewerIx,updateMode mode);

};

// --------------------------------------------------------------------------

class sheet : public secStruct {
public:    
    connectionPoints edges;
    enum viewType { TUBE=0, ARROW=1};
    sheet(const SecStructureView* ssv,const McBitfield& residues);
    virtual int getStructType() const;
    void setViewType (viewType mode);
    virtual float getLabelOffset() const;

protected:

    // function will update the viewers as specified by viewmode
    // if viewMode is NEW the viewers will be created
    virtual  void _update(updateMode mode);
    void updateTube(int viewerIx,updateMode mode);
    void updateArrow(int viewerIx,updateMode mode);
    McDArray<McVec2i> partStartEndIx;
};

// --------------------------------------------------------------------------

class turn : public secStruct {
public:    
    connectionPoints edges;
    enum viewType { TUBE=0};
    turn(const SecStructureView* ssv,const McBitfield& residues);
    virtual int getStructType() const;
    virtual float getLabelOffset() const;
    //virtual int getPickedResidue(int viewerIx,const SoPickedPoint* p ) const;

protected:
    virtual  void _update(updateMode mode);
    void updateTube(int viewerIx,updateMode mode);

};


class backbone : public secStruct {
public:    
    McDArray<connectionPoints> edges;
    enum viewType { TUBE=0,THREADS=1,RIBBON_FLAT=2,RIBBON_SOLID=3};
    backbone(const SecStructureView* ssv,const McBitfield& residues);
    virtual int getStructType() const;
    virtual float getLabelOffset() const;

protected:

    // function will update the viewers as specified by viewmode
    // if viewMode is NEW the viewers will be created
    virtual  void _update(updateMode mode);
    void updateTube(updateMode mode);
    void updateThreads(updateMode mode);
    void updateRibbon(updateMode mode);
};

/* aproximates an axis through the point @c co
@c r returns the footpoint and @c v the axis vector */
void getAxis(const McDArray<McVec3f>& co,McVec3f& r, McVec3f& v);

#endif

/// @}
