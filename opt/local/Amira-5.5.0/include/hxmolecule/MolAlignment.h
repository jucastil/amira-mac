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
#ifndef MOL_ALIGNMENT_H
#define MOL_ALIGNMENT_H

#include <mclib/McMat4f.h>
#include <mclib/McHandle.h>

#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxConnection.h>

#include <molecule/Molecule.h>

#include "HxMolecule.h"
#include "HxMoleculeWinDLLApi.h"

class HxAlignment;
class HxConnection;
class HxMolecule;

/** Supply of GUI and methods for aligning molecule atoms. */

class HXMOLECULE_API MolAlignment 
{
public:
    /// Connection to a molecule used for alignment.
    HxConnection     portMaster;

    ///
    HxMolecule * getMaster() const;
    ///
    const McDArray<int> & getMasterSelection() const;
    ///
    const McDArray<int> & getSlaveSelection() const;

private:
    /// Connection to precomputed alignment.
    HxConnection     portPrecomputed;
    
    /// Alignment options.
    HxPortMultiMenu  portTransformation;
    /// Selection used for alignment.
    HxPortButtonMenu portSelection;
    /// Some information in the GUI.
    HxPortInfo       portInfo;

    /* Used for alignment. */
    // pointer to molecule serving as master for alignment
    McHandle<HxMolecule> master;
    // store atoms that were selected in master 
    McDArray<int>        masterSelection; 
    /// Molecule to be transformed.
    HxMolecule         * slave;
    // store atoms that were selected in slave
    McDArray<int>        slaveSelection;  

    /// Transformations: @c transform is the current transformation due to alignment 
    /// to master molecule or cog, @c externalTransform is a transformation 
    /// that was explicitely set, @c relativeTransform also is a explicitely set
    /// transformation that is multiplied with the current master transformation
    /// to get the final transformation.
    McMat4f transform, externalTransform, relativeTransform;

    /// Touch flag.
    unsigned int isNewFlag:1;

    /// Test whether master and slave selections are identical.
    bool testIdenticalSelection();

public:
    /// Selection states.
    enum SelectionState {EMPTY, IDENTICAL, ALL_ATOMS, INDIVIDUAL};
    /// One of EMPTY, IDENTICAL, ALL_ATOMS, INDIVIDUAL.
    SelectionState selState;

    /// Constructor - parent (viewing module) need to be handed over.
    MolAlignment(HxObject * parent);
    /// Destructor.
    ~MolAlignment();

    /// Return current transform.
    const McMat4f & getTransform(int index, Molecule * mol);

    /// Update port.
    void update(HxConnection & portData);
    /// Compute 
    void compute(HxConnection & portData);
    /// Return whether alignment was changed.
    bool isNew();
    /// Show MolAlignment ports.
    void show();
    /// Hide MolAlignment ports.
    void hide();
    /// Overloaded function parsing tcl-commands.
    int parse(Tcl_Interp* t, int argc,char **argv);
    /// Writes port information to file.
    void savePorts(FILE* fp, const char * name);

    /// Set slave molecule, i.e., molecule to be transformed.
    void setSlave(HxMolecule * s);
    /// Set alignment to master.
    void setMasterAlignment(HxMolecule * hxMasterMol,
                            const McDArray<int> & masterSel,
                            const McDArray<int> & slaveSel);

    /// Set external transformation.
    void setExternalTransformation(const McMat4f & mat);
    /// Set relative transformation, i.e., a transformation relative 
    /// to the original coordinates of the master molecule. That means, 
    /// whenever the master is transformed, the slave will be transformed
    /// too, keeping the relative transformation of orientation to the 
    /// master molecule. The transform state is set to 
    /// KEEP_RELATIVE_TRANSFORMATION.
    void setRelativeTransformation(const McMat4f & mat);
    /** This function allows to set the precomputed alignment from a 
        different class. The transform state will be changed to PRECOMPUTED. */
    void setPrecomputedAlignment(HxAlignment * hxAlignment);
    
    /// Different sources of current transformation.
    enum TransformState {NONE, COG, MASTER, PRECOMPUTED, EXTERNAL, KEEP_RELATIVE_TRANSFORMATION};
    /// Return current source of transformation.
    int getTransformState() { return portTransformation.getValue(0); }
    /// Set new source of transformation.
    void setTransformState(int state) { 
        portTransformation.setIndex(0, state); 
    }
    
    /// Reset touch flag.
    void untouch() { isNewFlag = false; }
};

#endif

/// @}
