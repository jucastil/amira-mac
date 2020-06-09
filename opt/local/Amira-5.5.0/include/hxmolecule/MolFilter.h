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
#ifndef MOL_FILTER_H
#define MOL_FILTER_H

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>

#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>

#include <molecule/Molecule.h>
#include <hxmolecule/HxMolecule.h>

#include "HxMoleculeWinDLLApi.h"

class HxObject;
class HxConnection;

/** Supply of GUI and methods for filtering molecule atoms. */

class HXMOLECULE_API MolFilter 
{
    friend class QxMolSelectionBrowser;

public:
    /// Main backbone mode 
    enum BackboneMode {
        RESTRICT_TO,  // restrict atoms that can be viewed to some subset
        COMBINE_WITH, // ensure that a subset of atoms is shown
        NONE          /* which atoms are shown simply depends on the
                         selected bitfield */
    };
    /// In case one of the first two backbone modes is selected, the
    /// submode determines the (predefined) subset of atoms that is used.
    enum BackboneSubMode {
        ALL,                               // all atoms belong to 'subset'
        BB, BB_ENRICHED, BB_REDUCED,       // amino acids and nucleotides
        P_BB, P_BB_ENRICHED, P_BB_REDUCED, // amino acids only
        R_BB, R_BB_ENRICHED, R_BB_REDUCED  // nucleotides only
    };
    /// Flags are used with getVisibleGroupsOfLevel and isGroupVisible.
    enum {ALL_IN, ANY_IN, MOST_IN};
    
    /// Filter buttons.
    HxPortButtonList portFilterBuffer;
    /// Filter toggle list for water and HET.
    HxPortToggleList portFilterOptions;

protected:
    // Parent object - usually a viewing module.
    HxObject * _parent;
    // the usual stuff
    McHandle<HxMolecule> hxmol;
    
    // Visibility of atoms according to buffer concept (subset).
    McBitfield backbone;
    /// This bitfield is ANDed of ORed with the backbone bitfield
    /// according to @c backboneMode.
    McBitfield selected;
    /// Ignored atoms. Set by portFilterOptions.
    McBitfield ignored;

    // See above.
    int backboneMode;
    int backboneSubMode;

    bool isNewFlag;
    bool useBackboneFilter; // used by selection browser
    bool noButtons;         // should buttons be shown

public:
    /** Constructor - parent (viewing module) need to be handed over.
        If @c showButtons is true, then set, unset, clear, and all
        buttons will be visible.
        If @c showToggles is true, additional toggles to ignore water
        and HET atoms will be visible.
    */
    MolFilter(HxObject * parent, bool showButtons=true, bool showToggles=false);
    /// Destructor.
    ~MolFilter();

    /// Return pointer to parent module.
    HxObject * parent() { return _parent; }
    /// Show port.
    void show();
    /// Hide port.
    void hide();
    /// Update port.
    void update();
    /// Fires parent.
    void fire();
    /// resize filters
    void compute();
    /// Compute new set of visible atoms.
    void compute(HxConnection & portData);
    /// Return whether filter was changed.
    bool isNew();
    /// Is atom @c idx visible?
    inline bool isAtomVisible(int idx) const { 
        switch (backboneMode) {
        case NONE:         return selected[idx] & !ignored[idx];
        case RESTRICT_TO:  return (selected[idx] & backbone[idx] & !ignored[idx]);
        case COMBINE_WITH: return ((selected[idx] | backbone[idx]) & !ignored[idx]);
        default:           return false;
        }
    }

    /// Set whether backboneFilter should be used or not.
    void setBackboneFilterFlag(bool flag) { useBackboneFilter = flag; }

    /** Returns in res a list of group refs to groups of the level
        levelix that are visible as specified by the flag calls
        isGroupVisible for all memebers of the level. */
    void getVisibleGroupsOfLevel(int levelIx, McDArray<MtGroupRef> res,
                                 unsigned int flag=ALL_IN);
    
    /** Returns whether the group ref is visible under condition of
        the flag (eg. ALL_IN means that all atoms of that group have
        to be visible for true being returned) */
    bool isGroupVisible(const MtGroupRef & ref, const unsigned int flag=ALL_IN);

    /** Set/unset bitfield of atoms. There are four modes:
        0=remove, 1=add, 2=replace, 3=addAll (in this case, selAtoms
        is ignored). */
    void setSelectedAtoms(const McBitfield & selAtoms, const int mode=1);

    /** Set/unset list of selected atoms. There are four modes:
        0=remove, 1=add, 2=replace, 3=addAll (in this case, selAtoms
        is ignored). */
    void setSelectedAtoms(const McDArray<int> & selAtoms, const int mode=1);

    /** Returns bitfield of size numAtoms in which all entries
        for visible atoms are set. */
    void getVisibleAtoms(McBitfield & visible);
    
    /// Overloaded function parsing tcl-commands.
    int parse(Tcl_Interp* t, int argc,char **argv);
    /// Writes port information to file.
    void savePorts(FILE* fp, const char * name, int filterId=-1);

private:
    // Set backbone bitfield according to atoms belonging to backbone.
    void computeBackbone();
    // Select atoms according to decoded string @c abc.
    void selectAtoms(const char* abc);
    // Encode selected atoms into string written to ostream @c out.
    void getSelectedAtoms(ostream& out);
};

#endif

/// @}
