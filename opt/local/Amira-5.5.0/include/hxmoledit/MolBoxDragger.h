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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef MOLBOXDRAGGER_H
#define MOLBOXDRAGGER_H

#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortInfo.h>
#include "HxMolEditWinDLLApi.h"

class SoDragger;
class SoSeparator;
class McVec3f;
class Molecule;
class McBox3f;
class McVec3i;
class MolBoxDragger;

class HxObject;
class SoSeparator;

class HXMOLEDIT_API MolBoxDraggerNotifier {
public:
    virtual ~MolBoxDraggerNotifier() {}
    virtual void notifyFinishDragger(MolBoxDragger* d) = 0;
};

class HXMOLEDIT_API PortFieldDimension : public MolBoxDraggerNotifier {
public:
    PortFieldDimension(HxObject* parent);
    virtual ~PortFieldDimension();
    ///
    void update();
    ///
    void compute();

    void setBoundingBox(const McBox3f&);
    void getBoundingBox(McBox3f& b) const;
    float getVoxelSize() const;
    void setVoxelSize(float);
    void getDimensions(McVec3i& dim) const;

    void show();
    void hide();

    void notifyFinishDragger(MolBoxDragger*);
    int parse(Tcl_Interp* t, int argc,char **argv);    
    void savePorts(FILE* fp, const char * name);

    HxPortRadioBox portBox;
    HxPortFloatSlider portVoxelSize;
    HxPortInfo        portDimsInfo;

protected:

    SoSeparator* sep;
    MolBoxDragger* box;
    HxObject* parent;
};

class MolBoxDragger {
public:
    /** */
    enum BoxType {NOBOX=0, XFORMBOX=1, TABBOX=2 };
    /** */
    MolBoxDragger();
    /** */
    ~MolBoxDragger();
    /** Sets the box type. */
    void setBoxType(int b);
    /** Returns the current box type.*/
    int getBoxType() const;
    /** Sets the bounding box.*/
    void setBBox(const McBox3f& bbox);
    /** Returns the current bounding box. */
    void getBBox(McBox3f& bbox) const;
    /** */
    void getDefaultTransform(const McBox3f& bbox,McVec3f& trans, McVec3f& scale) const;
    /** */
    void getDefaultTransform(const Molecule* mol,McVec3f& trans, McVec3f& scale) const;
    /** */
    void getFieldBBox(float *extBBox) const;
    /** Sets a notifier which will be called if the dragger has been moved by the user.
    */
    void setNotifier(MolBoxDraggerNotifier* mbdnot); 
    /** Returns an always valid root node of dragger which the user can 
        insert into his scene graph. */
    SoNode* getNode() const;
    /** */
    static void molBoxDraggerFinishCB(void*, SoDragger*);

private:
    friend void molBoxDraggerFinishCB(void*, SoDragger*);

    void finish();
    void showBoxGeom();
    void updateBox();
    int boxType;
    void createBox();
    void removeBox();

    SoSeparator* node;
    SoDragger* box;
    McBox3f* bbox;
    MolBoxDraggerNotifier* notifier;
};

#endif

/// @}
