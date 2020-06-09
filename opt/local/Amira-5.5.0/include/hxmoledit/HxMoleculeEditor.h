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
#ifndef HX_MOLECULE_EDITOR_H
#define HX_MOLECULE_EDITOR_H

#include "HxMolEditWinDLLApi.h"
#include <hxcore/HxEditor.h>
#include <mclib/McHandle.h>
#include <hxmolecule/ComputeListener.h>

class HxMolecule;
class SoEventCallback;
class QxMolEditor;
class QxEditorNotifier;
class MolTrajectory;
class McString;
class McBitfield;
class Molecule;
class SbMatrix;
class SbVev3f;
class McVec3f;

/** HxMoleculeEditor is the interface between the outside world and
    the QT and OI user interface as implemented in QxMolEditor.  It
    contains all editor functions that can be accessed by external
    libraries as static methods.  An instance of it should only be
    created by Amira. The QxMolEditor will be created as soon as the
    data object is known (when startEditing is called) It uses an
    HxMoleculeEventCB to ensure that highlighting events are reported
    A QxEditorNotifier is used for passing the exit signal of the
    QxMolEditor on to this object
*/

class HXMOLEDIT_API HxMoleculeEditor : public HxEditor, public ComputeListener {

    HX_HEADER(HxMoleculeEditor);

public:
    /// Default constructor.
    HxMoleculeEditor();
  
    /// Called whenever a port changes.
    virtual void fire();

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Interpretes mouse click events.
    virtual void mouseClick(SoEventCallback *eventCB);
    /// Interpretes selection changed events.
    virtual void selectionChanged();
    virtual void molChanged();

    /**  ----- connection ------ 
          the following methods will change the
          connectivity of the atoms of the molecule, each method uses
          a bitfield sel to determine which atoms to handle */
    /** add bonds between selected atoms which are not away further
      than the cutoff dist */
    static bool autoConnectSelection(
        HxMolecule* mol,
        const McBitfield& sel,
        float cutOffDist);
    /// add bonds between all selected atoms 
    static bool allConnectSelection(
        HxMolecule* mol,
        const McBitfield& sel);
    /// removes all bonds between selected atoms
    static bool removeBondsInSelection(
        HxMolecule* mol,
        const McBitfield& sel);
    /// removes all bonds between seleted atoms which violate cutoff distance
    static bool removeUnfitBondsInSelection(
        HxMolecule* mol,
        const McBitfield& sel,
        float cutOffDist);
    /// removes all bonds between selected and unselcted atoms
    static bool removeExternalBondsInSelection(
        HxMolecule* mol,
        const McBitfield& sel);
    /// add bonds between selected atoms using standard residue database
    static bool standardConnectSelection(
        HxMolecule* mol,
        const McBitfield& sel);
    /// add bonds between selected atoms using bond length table
    static bool bondLengthConnectSelection(
        HxMolecule* mol,
        const McBitfield& sel);
    /** add bonds between selected atoms using standard residue database
        note: this method will not touch the neccessary HxMolecule flags
        and is only for reader purposes where the HxMolecule is not yet set 
        usually you should use the method standardConnectSelection(HxMolecule*...
        instead*/
    static bool standardConnectSelection(
        Molecule* mol,
        const McBitfield& sel);

    /*  ----- changeTopolgy ------ */
    /** splits all selected atoms as specified in sel from
        the molecule mol and adds them to the molecule target
        if target is undefined a new HxMolecule will be created
        (the topology of target will be overwritten)
        and target will return its pointer
        if addToObjectPool is true the target molecule will be
        added to the Object Pool */
    static void splitSelected(
        HxMolecule* mol,
        const McBitfield& sel,
        HxMolecule* target=NULL,
        bool addToObjectPool=true);
    /** copies all selected atoms as specified in sel from
        the molecule mol and writes them to the molecule target
        (the topology of target will be overwritten)
        if target is undefined a new HxMolecule will be created
        and target will return its pointer
        if addToObjectPool is true the target molecule will be
        added to the Object Pool */
    static void copySelected(
        const HxMolecule* mol,
        const McBitfield& sel,
        HxMolecule*& target,
        bool addToObjectPool=true);
    /** adds all atoms of molecule target which are specified in bf
        to the molecule target */
    static void addOther(
        const HxMolecule* source,
        HxMolecule* target,
        const McBitfield& bf);

    /*  ----- transformation ------ */
    /** moves parts of the molceucle (as specified by sel) by the 
        transformation transform*/
    static void move(
        HxMolecule* mol,
        const McBitfield& sel,
        const SbMatrix& m);
    /** moves parts of the molceucle (as specified by sel) by the 
        translation r*/
    static void move(
        HxMolecule* mol,
        const McBitfield& sel,
        const McVec3f& r);
    /** moves parts of the molceucle (as specified by sel) by the 
        rotation rotAxis, rotAngle and rotCenter*/
    static void move(
        HxMolecule* mol,
        const McBitfield& sel,
        const McVec3f& rotAxis,
        const McVec3f& rotCenter,
        const float& angle);

    /// function used for event callbacks
    void computeCalled(HxObject* hxMol);

protected:
    ~HxMoleculeEditor();

private:
    McHandle<HxMolecule> molecule;
    QxMolEditor* molEdit;
    QxEditorNotifier* notifier;

    /// Initialize ports here.
    void startEditing(HxData *data);

    /// Remove selection callbacks here.
    void stopEditing();

    /// static pointers to residue database file 
    static McDArray<McHandle<MolTrajectory> > traj;

};

#endif


/// @}
