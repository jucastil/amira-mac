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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef MOL_COLORING_H
#define MOL_COLORING_H

#include <mclib/McString.h>
#include <mclib/McHandle.h>

#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxHTML.h>
#include <Inventor/SbColor.h>

#include "hxcolor/HxPortColormap.h"

#include <molecule/MtGroupRef.h>

#include "HxMoleculeWinDLLApi.h"

class HxObject;
class HxColorEditor;
class Molecule;
class HxMolecule;
class MolLegend;
class MolTopology;

/** Supply of GUI and methods for coloring of a molecule's atom colors */
class HXMOLECULE_API MolColoring 
{

public:

    /**
        Subclass with a colortable for the user defined atom colors.
    */
    class HXMOLECULE_API MolColTable
    {
    private:
        struct SpecificColor
        {
            SbColor mColor;
            int     mRefs;
        };
        
    public:
        /// Constructor
        MolColTable();
        /// Destructor
        ~MolColTable();
        
    public:
        /// Returns the color of index.
        void getColor(int index, SbColor& color) const;
        /// Returns the number of user defined colors.
        int getNumColors() const;
        /// Returns for an atom the index of the color. Result is -1 if atom is unset.
        int getColorIndex(int atom) const;
        /// Initialize. Unsets all atoms and clears color table.
        void initialize (int numAtoms);
        /// Sets a color for a set of atoms.
        void setColor (McBitfield& atomSet, SbColor* color);
        /// Unsets color for a set of atoms.
        void unsetColor (McBitfield& atomSet);
        /// Unsets all atoms and clears colortable.
        void unsetAll ();
        
    private:
        McDArray< int >            mColorIndex;
        McDArray< SpecificColor >  mColors;
    };
    
public:
    /// Create molecule with reference to a given topology
    MolColoring(HxObject *parent, SbColor defaultColor=SbColor(0,0,1));    
    /// Destructor.
    ~MolColoring();

    /// Return parent module.
    HxObject * parent() { return _parent; }

    /// Return color of the @c index'th atom.
    const SbColor & atomColor(int index);
    /// Return complete color table (one color per atom).
    const SbColor * atomColorTable() const;

    /// Returns the currently selected attribute.
    int getAttribute();

    /// Returns the currently selected level.
    int getLevel();

    /// Returns a pointer of the specific molecule color table.
    MolColTable* getIndexedAtomColorTable();

    /// 
    SbColor * groupColorTable(int level, int mapping);

    /// Show ports of MolColoring object.
    void show();
    /// Show ports of MolColoring object.
    void hide();

    /// Update user interface, i.e. ports etc.
    void update(HxConnection * portData=0);
    /// Handle modification of input data.
    void compute(HxConnection & portData);
    /// Does the actual computation.
    void compute(Molecule * , int newTopo=1);

    ///
    void setLabel(const char *str, int which=0);
    ///
    void rename(const char *str);

    /// 
    void setScheme(int lev,int attr);
    /// 
    void setScheme(const char * lev, const char * attr);

    ///
    bool isNew();

    /// Override colors defined by group attributes.
    void setUserDefinedColors(McDArray<MtGroupRef> & gRefs, bool setOrUnset, 
                              SbColor * color=0);
    /// Override colors defined by group attributes.
    void setUserDefinedColors(McBitfield & atomBitfield, bool setOrUnset, 
                              SbColor * color=0);

    ///
    void saveSpecials(FILE* fp, const char * name);

    ///
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// bit mapping for touchflags
    enum { TOPO           = 0x001,
           SCHEME         = 0x002,   // color scheme
           MAPPING        = 0x004,   // color mapping 
           LEVEL          = 0x008,   // change of number of levels
           DISC_CMAP      = 0x010,   // discrete colormap
           CONT_CMAP      = 0x020,   // continuous colormap
           CMAP           = 0x030,   // any colormap
           ATTVALS        = 0x040,   // attribute values changed
           USERDEFINED    = 0x080,
           ALL            = 0xffff};
    
private:
    ///
    int touchFlags;

    ///
    void touch(int mask) { touchFlags |= mask; }
    
    ///
    bool isTouched(int mask=ALL) { return touchFlags & mask; }

    MolColoring(MolColoring&);
    void operator=(MolColoring&);

public:
    ///
    void unTouch(int mask=ALL) { touchFlags &= ~mask; }

    /** adds name to the list of shown levels, list of hidden levels
        is removed */
    void showLevel(const char * name);

    /** adds name to the list of hidden levels, list of shown levels
        is removed */
    void hideLevel(const char * name);

    void colorEditCB(const HxColorEditor &colEd);
    static void colorEditCBS(void *userData, const HxColorEditor &colEd);
    ///
    HxPortButtonMenu portColorScheme;

    ///
    HxPortColormap portContinuousColormap;

    ///
    HxPortColormap portDiscreteColormap;

    ///
    HxPortButtonList portDefineColor;

private:
    ///
    const SbColor * computeAtomColorTable(int flags=0);

    ///
    void compute();

    ///
    void updateTopology();

    McString theName;

    ///
    HxObject * _parent;

    ///
    McHandle<Molecule> molecule;
    
    ///
    McHandle<HxMolecule> hxmolecule;

    ///
    McHandle<MolTopology> topology;
    
    ///
    McBitfield userDefined;
    
    ///
    McDArray<SbColor> colorTable;

    ///
    int colorLevel, colorMapping;

    ///
    McDArray<int> levelMap;
    
    ///
    bool hideMaskedLevels;

    ///
    McDArray<McString> maskedLevels;
    
    ///
    McHandle<MolLegend> legend;

    ///
    McDArray<SbColor> typeMap;

    ///
    int gacmLevel, gacmMapping;

    ///
    const McDArray<SbColor> & groupAttributeColorMap(int scheme,int mapping);

    ///
    SbColor restColor;

    int wasColorChooserOpen:4;
    int whichButton:4;
    int hideColormaps:4;

    MolColTable molColTable;
};

#endif


/// @}
