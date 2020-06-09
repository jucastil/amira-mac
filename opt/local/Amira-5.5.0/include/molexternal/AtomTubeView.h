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
#ifndef _ATOMTUBE_H
#define _ATOMTUBE_H

class MoleculeInterface;
class ResidueSelectionCallback;
class SoSeparator;
class SoNode;
class SoHandleEventAction;

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbString.h>

#include <molexternal/MolExternalWinDLLApi.h>
#include <hxshapes/ShapeView.h>
#include <molexternal/Base.h>

// --------------------------------------------------------------------------
    
class MOLEXTERNAL_API AtomTubeView : public ModuleBase
{ 
public:    

    /** get SceneGraph */
    virtual SoNode *getSceneGraph();
    
    /** set source data object. Must be called again after any
        changes of the molecule. */
    void setMolecule(MoleculeInterface* molecule);

    /** update existing SceneGraph after parameter change or after 
        setting a new molecule. */
    virtual void update();
    
    AtomTubeView();
    ///
    virtual ~AtomTubeView();

    enum InterpolationMethod {
        NONE,
        CUBIC_SPLINE,
        BEZIER_SPLINE
    };

    /** enum of triangulation type for caps of tubes */
    enum TubeCapType {
        TCT_HEMISPHERE, 
        TCT_CONE, 
        TCT_CONE_INWARD, 
        TCT_FLAT, 
        TCT_NONE
    };

    enum ColorMode {
        CM_PER_FACE,
        CM_PER_VERTEX
    };

    /// sets number of interpolation points between each atom coordinate
    void setInterpolationPointNumber(int n);
    /** sets triangulation complexity of tubes, must be in interval [0,1]
        where 1 is maximal complexity **/
    void setComplexity(float c);
    /// adds a set of atoms to be shown as connected by a tube
    void addAtomSet(McDArray<int>& atomIx);
    /// clears all atom sets
    void clearAtomSets();
    /// sets the interpolation method
    void setInterpolationMethod(InterpolationMethod m);
    /** sets the atom colors, @c atomColors must be of the same
        same size as the number of atoms in the molecule **/
    void setAtomColors(McDArray<SbColor>& atomColors);
    /// sets the color of the atom with index @c atomix
    void setAtomColor(int atomix,SbColor& col);
    /// 
    void setHighlighting(int atomix,bool highlighted);
    ///
    void setHighlighting(McBitfield& highlighted);
    ///
    void setHighlightingColor(const SbColor& highlighting);
    /// 
    void setTubeRadius(float r);

    /** sets the cap type of tubes */
    void setTubeCapType(TubeCapType tct);

    /** sets the coloration mode */
    void setColorMode(ColorMode cm);

    /** set selection callback 
        callback will be called whenever a atom has been selected,
        after a lasso selection has been processed the callback will
        be called with atom  Index -1
        note: picking and highlighting are two different concepts
        structures selected by picking events will not automatically 
        be set to selected (=highlighted) to allow that picking events
        received in certain modes may be reprocessed or used for other
        tasks than highlighting by the callback 
        if you want to highlight the picked structure you will need to
        call setHighlighting during the callback */
    void setSelectionCallback(SelectionCallback* cb);
    
    /** method allows handling of an external lasso selection
        will call the selection callback for all residues which are selected
        by the lasso given as lassoCoords in device coordinates while using
        camera, viewport and transformation information from the 
        SoHandleEventAction */
    void performLassoSelection(const SoHandleEventAction* action,
                               const SbVec2s* lassoCoords, int nCoords);
private:


////////////////////////////////////////////////////////////////
//
//        Private members

private:
   // touch flags
    enum {
        TF_HIGHLIGHTING      = 0x00000001,        
        TF_COLORS            = 0x00000002,        
        TF_ALL               = 0xffffffff
    };

    /* touching is done automatically if any method which sets a 
       parameter is called, you only need to touch the module if the data
       of one of the interfaces used by the module has changed externally 
     */
    void touch(unsigned int mask=TF_ALL) { touchFlags |= mask; }
    
    unsigned int touchFlags;
    ///
    bool isTouched(unsigned int mask=TF_ALL) const { return touchFlags & mask; }
    ///
    bool areTouched(unsigned int mask=TF_ALL) const { return ((touchFlags & mask)==mask); } 
    ///
    void unTouch(unsigned int mask=TF_ALL) { touchFlags &= ~mask; }
    
    void cleanUp();
    
    // root seperator of viewer
    McHandle<SoSeparator> root;
    McHandle<SoSeparator> tubes;
    McDArray<McHandle<TubeView> > viewer;

    InterpolationMethod interpolationMethod;
    TubeCapType tubeCapType;
    int interpolationPointNumber;
    float complexity;
    McDArray<SbColor> atomColors;
    McDArray< McDArray<int> > atomSets;
    McBitfield highlighted;
    SbColor highlightingColor;
    float radius;
    ColorMode colorMode;
    
    MoleculeInterface* mol;
    SelectionCallback* cb;

    McBitfield atomsToConsider;
    /* list for saving atomIx of every coordinate for fast recoloring
       outer list over viewerIx, inner list over coordIx */
    McDArray<McDArray<int> > coIx2AtomIx;
    ///
    static void mouseClickCB(void *c,SoEventCallback *d) 
        { ((AtomTubeView*)c)->mouseClick(d);};

    /// 
    void mouseClick(SoEventCallback *d);
};

#endif

/// @}
