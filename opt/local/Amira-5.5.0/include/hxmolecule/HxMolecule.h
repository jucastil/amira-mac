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
#ifndef HX_MOLECULE_H
#define HX_MOLECULE_H

#include <Inventor/sensors/SoNodeSensor.h>

#include <mclib/McList.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McMat4f.h>

#include <hxcore/HxVertexSet.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortSeparator.h>

#include <molecule/Molecule.h>
#include <molecule/MtGroup.h>
#include <molecule/MolTrajectory.h>

#include <hxtime/HxPortTime.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <hxmolecule/ComputeListenerHandler.h>

class HxLattice3;
class QxMolSelectionBrowser;
class MolFilter;
class MolColoring;
class MolAlignment;
class MolHighlighting;
class HxMolLabel;
class HxMolecule;
class HxObject;
class SoEvent;
class HxViewer;
class MoleculeBundle;

#define DECLARE_SoSensor_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoSensor *d) \
        { ((Class*)c)->CBFunc(d);};\
        void CBFunc(SoSensor *d)

/** event callback function, will give as paramters the
    HxMolecule which did change and the object that 
    was registered in the callback */
typedef void HxMoleculeEventCB(const HxMolecule &hxMol, void *object);

/** This is the Amira wrapper for the @c Molecule class. All structural
    information about the molecule are contained in the @c Molecule
    class. In this class additional information is stored. This
    information includes a list of highlighted atoms. We also store
    how the molecule is currently transformed and if it was changed,
    what has been changed. */

class HXMOLECULE_API HxMolecule : public HxVertexSet {
    HX_HEADER(HxMolecule);

    friend class QxMolSelectionBrowser;
    
public:
    // ==================== Subclass declaration ====================

    /**@name Subclass declaration */ //@{
    /// HighlightedAtom struct is needed to store highlighted atoms in a list.
    struct HXMOLECULE_API HighlightedAtom {
        void *_pre; // needed for McList
        void *_suc; // needed for McList
        int  id;
        // if _suc == _mcListNullPtr_ then item is not in list
        HighlightedAtom() { _suc = _mcListNullPtr_; }
    };

    /// Additional touch flags for molecules that may be set and asked for.
    enum TouchFlags { 
        NEW_ATOMS          = 0x000100,
        NEW_BONDS          = 0x000200,
        NEW_GROUPS         = 0x000400,
        NEW_LEVEL          = 0x000800,
        NEW_TOPO           = 0x000f00, 
        // NEW_TOPO implies NEW_ATOMS|NEW_BONDS|NEW_GROUPS|NEW_LEVEL
        NEW_HIGHLIGHTING   = 0x001000, 
        NEW_SEGMENTATION   = 0x002000,  // IS_SEGMENTATION flag changed
        NEW_ATTRIBUTE      = 0x004000,  // attribute deleted or new
        NEW_ATTRIBUTEVALUE = 0x008000,  // attribute enty changed
        NEW_HBONDS         = 0x010000,
        NEW_MOLDATA        = 0x020000
    };

public:
    /// Connection to object of class @c HxMolTrajectory.
    HxConnection     portData;

    /// If molecule is connected to trajectory, select a time step.
    HxPortTime       portTime;

    HxPortSeparator  portGuiSeparator;
    /// Alignment functionality mean squared distance.
    MolAlignment     * alignment;

    HxPortSeparator  portGuiSeparator2;
    /// Show button for selection browser.
    HxPortButtonList portSelectionWindow;
    /// Buttons to apply and reset transformations.
    HxPortButtonList portTransform;
    
protected:
    // Pointer to object of class @c Molecule.
    McHandle<Molecule> mol;
    // Topology of molecule.
    McHandle<MolTopology> topology;
    // Trajectory the molecule belongs to.
    McHandle<MolTrajectory> traj;

    MoleculeBundle* molbundle;

    int nTimeSteps;
    int curTimeStep;
    unsigned int newData:1;
    unsigned int newHighlighting:1; 
    unsigned int hasLastHighlighting:1; 
    
    /* Used for highlighting. */
    // Each atom is represented once in the array.
    McDArray<HighlightedAtom> atoms;
    // If an atom is selected it will be found in this list.
    McList<HighlightedAtom> highlighted;
    // Bitfield to undo last highlighting.
    McBitfield lastHighlighted;
    // Number of highlighted atoms.
    int nHighlighted;

    /* Selection browser stuff. */
    QxMolSelectionBrowser * selectionBrowser;
    McDArray<HxObject *> registeredObjects;
    McDArray<MolFilter *> registeredFilters;
    McDArray<MolColoring *> registeredMolColorings;
    McDArray<MolHighlighting *> registeredHighlightPorts;

public:
    /// Constructor. If mol pointer is 0, an empty molecule will be created.
    HxMolecule(Molecule* mol=0);
    /// Destructor.
    ~HxMolecule();

    /// Handler that allows registering compute listeners
    ComputeListenerHandler computeListenerHandler;    

    /// Duplicates the current HxMolecule object
    virtual HxData *duplicate() const;
    /// Virtual function returning the number of atoms.
    virtual int getNumPoints() const;
    /// Virtual function returning a pointer to the atoms coordinates.
    virtual McVec3f* getCoords() const;
    /// Virtual function compute - 
    ///   called if the object has been touched and fired.
    virtual void compute();
    /// Virtual function update - 
    ///   called if the object has been touched and fired.
    virtual void update();
    /// Same as with function update().
    virtual void info();
    /// ...
    virtual void fire(int shouldCompute=1);
    /** version of fire which ensures that if the molecule is part of a
        trajectory, the trajectory is fired instead (fire cascade is
        initiated in the upstream object). This command must be called
        instead of fire whenever an edit of the molecule affects the trajectory.*/
    void fireUpstream();

    void copyMolecule(const HxMolecule & hxMol);
    
    /** Initialize the object @c HxMolecule. 
        If the mol pointer is invalid, an empty molecule will be created */
    void setMolecule(Molecule *mol, MolTrajectory *molTraj=0);
    /// Return the real molecule. The pointer is guaranteed to be valid.
    Molecule * getMolecule() const { return mol; }

    /// Return pointer to @c MolTrajectory.
    MolTrajectory * getTrajectory() { return traj; }

    /// Return name of trajectory.
    const char * getTajectoryName() { 
        return traj ? traj->getName() : 0; }

    /// If two atom coords are too close they will be considered as duplicate.
    void checkForDuplicateAtoms();

    SoNodeSensor trafoSensor;
    DECLARE_SoSensor_CB(transformSet, HxMolecule);
    // Use this function if you want to set a transform from any
    // member function of HxMolecule -> transformation sensor will not
    // be notified of the transformation change.
    void setInternalTransform(const McMat4f & matrix);

    /// Write bounding box to bbox.
    void getBoundingBox(float bbox[6]) const;
    
    /// Returns the number of fields.
    int getNumFields();
    /// Get field names such as potential energy, temperature etc.
    int getFieldNames(char** names);
    /// Write field to lattice @c lat.
    int getField(int fieldId, HxLattice3 & lat, float * bbox);
    
    void findSelection(int idx, int level, McDArray<int> &selAtoms,
                       MolFilter * filter=0);
    void findSelection(McDArray<int> &inputList, int level, 
                       McDArray<int> &selAtoms, 
                       MolFilter * filter=0, McBitfield * bf=0);
    /* If @c fromViewer is true, highlighting is passed on to
       sel. browser.  @c list and @c b contain highlighted atoms. Atoms
       are either added or removed or newly set, respectively. */
    void addHighlighted(const McDArray<int> & list, bool fromViewer=true);
    void addHighlighted(const McBitfield& b, bool fromViewer=true);
    void setHighlighted(const McDArray<int> & list, bool fromViewer=true);
    void setHighlighted(const McBitfield& b, bool fromViewer=true);
    void removeHighlighted(const McDArray<int> & list, bool fromViewer=true);
    void removeHighlighted(const McBitfield& b, bool fromViewer=true);
    // Decode string abc and highlight atoms.
    void highlightAtoms(const char* abc);
    ///
    void removeAllHighlighted(bool fromViewer=true);
    // Get highlighted atom as bitfield.
    int  getHighlighted(McBitfield& isHighlighted) const;
    // Get highlighted atom as ordered list (ordered by the time of selection).
    int  getHighlighted(McList<HighlightedAtom> *& list)  const;
    int  getHighlighted(McDArray<int>& atomIx) const;
    // Is atom with @c atomId highlighted ? 
    bool isHighlighted(int atomId) const;
    // Are all atoms in list @c atoms highlighted ?
    bool isHighlighted(const McDArray<int> & atoms) const;
    // Are all atoms in bitfield @c atoms highlighted ?
    bool isHighlighted(const McBitfield & atoms) const;
    // Are all atoms of group @c gRef highlighted ?
    bool isHighlighted(const MtGroupRef& gRef) const;
    // Return number of highlighted atoms.
    int  getNumHighlighted() const;
    // Return number of highlighted groups of level @c levelIx
    int numHighlighted(int levelIx) const;
    // return number of highlighted groups of level @c levelName
    int numHighlighted(const char* levelName) const;
    // Write highlighted atoms to file.
    bool writeHighlightedAtoms(const char * name);
    // Encode highlighted atoms in string and write string to @c out.
    void getHighlightedAtoms(ostream& out);
    // Save last highlighting.
    void saveLastHighlighting();
    // Undo last highlighting (only one step back).
    void undoLastHighlighting();
    // Print selection information. Number of previously selected
    // atoms and residues must be given as parameters.
    void printSelectionChanges(int atomsOldHighlighted, 
                               int residuesOldHighlighted);

    // Open and initialize selection browser.
    void openSelectionBrowser();
    // Update selection window due to changes in filter.
    void updateSelectionWindow(MolFilter * filter);
    // Register filter - filter is passed on to selection browser.
    void registerFilter(MolFilter * filter);
    // Remove filter from registered list.
    void unregisterFilter(MolFilter * filter);
    // Register molColoring - molColoring is passed on to selection browser.
    void registerMolColoring(MolColoring * molColoring);
    // Remove molColoring from registered list.
    void unregisterMolColoring(MolColoring * molColoring);
    // Update selection window due to changes in filter.
    void updateSelectionWindow(MolColoring * molColoring);
    // Register highlighting object - passed on to selection browser.
    void registerHighlightPort(MolHighlighting * highlighting);
    // Remove highlighting object from registered list.
    void unregisterHighlightPort(MolHighlighting * highlighting);
    // Get filter by id - called from selection browser.
    MolFilter * filter(int id) { return registeredFilters[id]; }
    // Get molColoring by id - called from selection browser.
    MolColoring * molColoring(int id) { return ( id < registeredMolColorings.size() ? registeredMolColorings[id] : 0); }
    // Return number of highlighting objects.
    int getNumHighlightPorts() { return registeredHighlightPorts.size(); }
    // Get highlight object by id - called from selection browser.
    MolHighlighting * highlightPort(int id) { 
        return registeredHighlightPorts[id];
    }
    
    // Called by viewer.
    ///
    enum Modifiers { NONE  = 0x0,
                     SHIFT = 0x1,
                     CTRL  = 0x2 };
    ///
    void handleMouseClick(int level, int idx, int modifierFlags);
    ///
    void handleMouseClick(int level, McDArray<int> idxs, int modifierFlags);
    ///
    int determineSelectionLevel(int level) const;
private:
    ///
    MtGroupRef lastClicked;
    ///
    void handleMouseClick(McDArray<MtGroupRef> & grRefs, int modifierFlags);
    ///
    static int keyboardEventCallback(const SoEvent*, HxViewer*, void*);
    ///
    static int callbackRefs;
    /* Global selection level. If the molecule has a level of this name
       the level will be used to generate the selection if a part of the molecule was clicked upon.
       If it does not exist, the default coloring level of the viewer module will be used.
       The selectionLevel can be changed either by the local and global tcl command setSelectionLevel or
       by level specific keyboard shortcuts (see keyboardEventCallback). */
    static McString selectionLevel;
public:
    // Called by HxMolLabel.
    float getLabelOffset(const McVec3f & labCoord, MtGroupRef & gref);
    float computeLabelOffset(const McVec3f & labCoord, MtGroupRef & gref);
    void computeLabelCoord(McVec3f & labCoord, MtGroupRef & gref, int recursion=0);

    /// deletes all selected atoms as specified in sel from molecule
    void deleteAtoms(const McBitfield& sel);

    // Overloaded function.
    void touch(unsigned int mask=0xffffffff);
    // Overloaded function - parse tcl commands.
    int parse(Tcl_Interp* t, int argc,char **argv);
    // Overloaded function - connect portData to @c HxMolTrajectory.
    int autoConnect(HxObject* primary);
    // Overloaded function - write load or create command to script. 
    int saveCreation(FILE* fp, const char* dataDir, int savingFlags);
    // Overloaded function - write port info to script.
    void savePorts(FILE* fp);

protected:
    // Initialize atom indices for objects of <tt>struct Atom</tt>.
    void initAtomIds(int nAtoms);
    // for convenience
    void updatePortTransform();

private:
    
    McDArray<McMat4f> undoTransforms;

    friend class MolHighlighting;
};

#endif

/// @}
