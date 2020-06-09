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
#ifndef QXMOLEDITOR_H
#define QXMOLEDITOR_H

#include <hxmoledit/HxMolEditWinDLLApi.h>
#include <hxmoledit/ui_QxMolEditorBase.h>
#include <hxcore/HxBase.h>
#include <Inventor/SbLinear.h>
#include <molchem/OptimizerListener.h>
#include <mclib/McHandle.h>

#include <mclib/McBitfield.h>
#include <mclib/McVec3f.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QDialog>
#include <QString>

class QxSelectItem;
class Molecule;
class SbVec3f;
class SoSeparator;
class SoMatrixTransform;
class SoDragger;
class HxMolLabel;
class HxMolecule;
class Molecule;
class HxMolView;
class QKeyEvent;
class QxElementSelector;
class QButtonGroup;
class QAction;

namespace molchem {
    class Molecule;
    class Optimizer;
    class MolConverter;
}
namespace mmff94 {
    class MMFF94_ForceField;
}
/** class undoInfo will contain all information necessary to
    undo a specific transformation. Transformations can
    comprise several individual transformations of
    subsets of the atoms of the molecule. For each
    indivual transformation i the subset it is applied on
    is stored in atomsSelections[i] and the transformation
    matrix in transformations[i]
**/
class undoInfo {
public:
    McDArray<McBitfield> atomsSelections;
    McDArray<SbMatrix> transformations;
    void resize(int i) {
        atomsSelections.resize(i);
        transformations.resize(i);
    }
    void clear() {
        atomsSelections.clear();
        transformations.clear();
    }
    int size() const {
        return atomsSelections.size();
    }
};

/** class QxMolEditor contains all QT and OI dependant
    methods that form the interface of the molecule
    editor, including everything that does not need
    to be accessed by external libraries. 
    The QT interface is defined in the
    QtDesigner file MolEditor.ui, and implemented in
    QxMolEditorBase.
**/

class QxMolEditor : public QDialog, public Ui::MolEditorBase, public HxBase, public molchem::OptimizerListener
{ 
    friend class HxMoleculeEditor;
    Q_OBJECT

private:
    /** a QxSelectItem interface is created when
        a molecule of the object pool needs to be choosen **/
    QxSelectItem* molSelector;
    /** data object edited by this editor  **/
    HxMolecule* mol;
    /** a copy of the initial state of the molecule 
        is stored in oldMol (used for resetting the molecule) **/
    Molecule* oldMol;
    molchem::Molecule* mcMol;
    molchem::MolConverter* molConverter;

public:
    QxMolEditor(HxMolecule* mol, 
                QWidget* parent = 0, 
                const char* name = 0, 
                Qt::WFlags fl = 0
                );
    
    ~QxMolEditor();
signals:
    /** exit is emitted when QxMolEditor is ended by the user **/
    void exit(bool ok);
protected slots:
    void openHelp();
    /** -----  transformation -----
       following function manipulate atom positions for
       changing different coordinate types as specified
       by the lineEdits in the molEditors transform tab
       for each coordinate type there is an absolute function
       which sets it to an absolute value and a relative
       function which changes the current value by the given value 
    **/
    
    /// move the position as specified by the line edits
    void moveRelative();
    void moveAbsolute();
    
    /// rotate the bondTorsion as specified by the line edit
    void rotateRelative();    
    void rotateAbsolute();
    
    /// stretch the BondLength as specified by the line edit
    void stretchRelative();    
    void stretchAbsolute();
    
    /// bend the bondAngle as specified by the line edit
    void bendRelative();    
    void bendAbsolute();
    
    /** shows the different transformer draggers **/
    void showRotateDragger();
    void showMoveDragger();
    void showStretchDragger();
    void showBendDragger();

    /** undo the last transformation **/
    void undoTransformation();

    /** --------- building (Atoms) ----------------
    **/
    void kekule();
    void kekuleNR();
    void dekekule();

    void removeH();
    void removeApolarH();
    void addH();
    void addPolarH();
    void removeWater();
    void hideH(const QAction * hideHAction);

    void assignHNum();
    void assignStandardHNum();
    void assignFormalCharges();
 
    void assignCoordinates2D();

    void createRingLevel();
    void createRingSystemLevel();
    void createChainLevel();
    void createAngleLevel();
    void createDihedralLevel();
    void createOOPDihedralLevel();
    void writeEditorAttributes();
    void showLabel(QAction * action);

    void elementSelected(unsigned int atomicNum);
    void replaceAtomElementSelector();
    void replaceAtomC();
    void replaceAtomH();
    void replaceAtomO();
    void replaceAtomN();
    void replaceAtomS();
    void replaceAtomP();
    void replaceAtomF();
    void replaceAtomCl();
    void incAtomCharge();
    void decAtomCharge();
    void decAtomValency();
    void incAtomValency();

    void atomChirality();
   
    void setBondDouble();
    void setBondSingle();
    void setBondTriple();
    void setBondAromatic();

    void addTransChain();
    void addCisChain();
    void addRing();

    void deleteAtoms();
    void deleteBonds();

    void addSmiles();
    void addSmiles(const char*);

    void relax();
    void relaxAll();
    void minimize();

    void createMMFFChargeAttribute();
    void createMol2TypeAttribute();
    void createCharmmTypeAttribute();
    void createMMFFTypeAttribute();
    void createMMFFSymbolAttribute();
    void createMMFFParameterization();
    void createMMFFsParameterization();
    void createMMFFRadiusAttribute();
    void createRadiusAttribute();
    void createMassAttribute();
protected:
    void setBond(unsigned int bo);
    void replaceAtom(int atomicNumber);
    int getActiveAtom();
    void updateLabels();
    void hideLabels();
    // apply changes in molechem::Molecule to Molecule
    void updateMolecule();
    void setMcMoleculeIndices();
    void updateHybridizationButtons();
protected slots:    
    /**  ----- changeTopolgy ------
        following functions (which are called by the interface
        of the tools tab) manipulate the groups of molecule **/
    
    /// splits all selected atoms into new molecule
    void splitSelected();
    /// copies all selected atoms into new molecule
    void copySelected();
    /// deletes all selected atoms from molecule
    void deleteSelected();
    /// adds an other molecule 
    void addOther() ;
    /// starts selection dialog for choosing a molecule in the object area
    void startMolSelector();
    /// ends selection dialog
    void endMolSelector();
    
    /** ------  connection ---------
    **/

    /// removes all bonds between selected atoms
    void connectModeChanged(int);
    void connectAtoms();
    void disconnectAtoms();

    void setCutoff();
    void setCutoff(int);

    /** --------- misc ----------------
    **/

    /** tab changed will check everything neccessary for 
        if the user changes the current tab page **/
    void tabChanged(QWidget*);
    /// accepts is called if the user presses the ok button
    void accept();
    /// reject is called if the user presses the cancel button
    void reject();
    /// reset molecule will reset the moleucle to the initial state
    void resetMolecule();
    /// apply changes to the molecule
    void applyChanges();

public:
    /** flag that is set whenever hxmolecule is fired.
        The callback that informs about a changed molecule then knows
        that this change originated in the molecle editor and not somewhere else.*/
    bool hasFired;
    /// sets the hasFired flag,  fires the hxmolecule, and unsets the flag again
    void fire();
    /// takes the current dragger out of the viewer and deletes it
    void hideDragger();
   
    /** this function checks and does everything neccessary if 
        the selection of atoms of the molecule has changed **/
    void selectionChanged();

protected:
    
    /// removes all bonds between selected atoms
    void allDisconnectSelected();
    /// removes all bonds between seleted atoms which violate cutoff distance
    void distanceDisconnectSelected();
    /// removes all bonds between selected and unselcted atoms
    void externalDisconnectSelected();
    /// remove bonds that are not in standard residue database
    void standardDisconnectSelected();
    /// remove bonds that do not fit bond lenght table
    void bondLengthDisconnectSelected();
    
    /// add bonds between selected atoms which are not away further than the cutoff dist
    void distanceConnectSelected();
    /// add bonds using standard residue database
    void standardConnectSelected();
    /// add bonds using bond length table
    void bondLengthConnectSelected();
    /// fully connect selected 
    void allConnectSelected();
    
private:
    McDArray<McVec3f> oldCoords;

    void keyPressEvent ( QKeyEvent * e );
    float getCutoffDist();
    void updateTransformTab();

    HxMolLabel* label;
    HxMolView* view;
    SoSeparator* draggerSep;
    SoTransform* draggerTransform;
    SoDragger* dragger;

    /** transformation matrix of dragger at last event handling
        used for calculating the atom transformation from the
        new transformaion matrix **/
    McVec3f translation;
    McVec3f rotAxis;
    float rotAngle;
    SbRotation rotation;
    McVec3f scaleFactor;
    McVec3f rotCenter;

    SbMatrix lastDraggerTransform;

    /** selection information **/
    /// currently selected atoms
    McBitfield selection; 
    /// currently selected atoms
    McDArray<int> selList; 
    /** symmetric transformations will transform two parts of the molecule
        inversly, the two parts are stored in these bitfields and will be
        calculated by the init method of the respective transformation **/
    McBitfield atoms1;
    McBitfield atoms2;

    /** List used for storing last undo operation **/
    McDArray<undoInfo> lastOperations;

    /// adds uI to the list of last Operations
    void setUndoInformation(const undoInfo& uI);
    /// adds the given asymmetric transformation to the list of last operations
    void setUndoInformation(
        const McBitfield& atoms, 
        const SbMatrix& transformation);
    /// adds the given symmetric transformation to the list of last operations
    void setUndoInformation(
        const McBitfield& atoms1,
        const McBitfield atoms2,
        const SbMatrix& transformation1,
        const SbMatrix& transformation2);

    /** contains all transformations since startDragger
        used for storing undo information temporarily 
        until finishDragCB is called*/
    undoInfo currentDragUndoInfo;
    
    /** dragger trasnformations need to update currentDragUnoInfo
        until they are finally released (finishDraggerCB) **/        
    /// updates it for asymmetric dragger transformations
    void setCurrentDragUndoInformation(
        const SbMatrix& transformation);
    /// updates it for symmetric dragger transformations
    void setCurrentDragUndoInformation(
        const SbMatrix& transformation1,
        const SbMatrix& transformation2);

    
    /** callbacks function for OI dragger events
    **/
    static void draggerMotionCB(void* userData, SoDragger*);
    static void draggerStartCB(void* userData, SoDragger*);
    static void draggerFinishCB(void* userData, SoDragger*);

    void draggerMotion(SoDragger* dragger);
    void draggerStart(SoDragger* dragger);
    void draggerFinish(SoDragger* dragger);

    /** before any transformation can be applied to some definite
        selection some initial calculation need to be done **/
    void rotateInit();
    void moveInit();
    void stretchInit();
    void bendInit();
    
    void updateDragger();
    
    /** which of the draggers is currently active
        is stored in the following enum which will be set by the 
        inited functions of the transformations 
        (to values given in the enums) or set to NONE by 
        any method that will destroy the consitency of the
        information that was calculated by the inited methods 
        (this is only neccessary to keep in mind for transform
        methods because any switch between tab pages will unset
        inited automatically) **/
    enum MotionMode {
        MOTION_NONE,
        MOTION_ROTATE,
        MOTION_MOVE,
        MOTION_STRETCH,
        MOTION_BEND
    };
    MotionMode motionMode;

    /// flag for change of cutOffDistance port
    bool cutOffTouched;

    float dihedral(const McDArray<int>& atomList) const;
    float distance(const McDArray<int>& atomList) const;
    float angle(const McDArray<int>& atomList) const;

    /** overloads qt method to enable the editor to be closed
        instead of hidden when the close widget is pushed **/
    void closeEvent( QCloseEvent* ce );

    /** method must be called before anything in the Molecule changes
        will do anything neccessary to backup the original molecule */
    void startMolEditing();
    void applyButtonMotion(const SbMatrix& dTransform);
    void applyDraggerMotion(const SbMatrix& newDraggerTransform);

private:
    enum LabelMenuEntries {
        Hide_H = 0,
        Sep,
        Label_None,
        Label_Index,
        Label_Standard,
        Label_Formal_Charge,
        Label_Oxidation_Number,
        Label_Implicit_Hydrogens,
        Label_MMFF_Atom_Type_Symbol,
        Label_MMFF_Atom_Type_Index,
        Label_CHARMM_Atom_Type_Symbol,
        Label_MOL2_Atom_Type_Symbol,
        Label_Failed_Atom_Type,
        Label_Hybridization,
        Label_Lone_Pairs,
        Label_Radicals,
        Label_MAX  = Label_Radicals
    };

    /// saves current state for use when next MoleculeEditor opens
    static int currentTabIndex;
    static int currentConnectMode;
    static QByteArray currentGeometry;
    
    bool notifyOptimizerStep(const molchem::Optimizer* opt,int i,const double * co,int num, double val,const double * grad);
    void notifyOptimizerEnd(const molchem::Optimizer* opt,int i,const double * co,int num, bool success);
    
    double lastMinimizationValue;
    
    QxElementSelector* elementSelector;
    void resetMcMol();
    void updateView();
    void relax(const McBitfield* bf);
    void replaceAtomSmiles(int atomIx,const char* smileStr);

    void getBondedAtoms(int atomIx, McDArray<McDArray<int> >& bl,
                                    McBitfield& res, McDArray<int>& remDepth,
                                    int depth)  const;

    void getBondedAtoms(int atomIx, McDArray<McDArray<int> >& bl,
                                    McBitfield& res) const;
    void createLabelMenuEntriesMaps();

    QMenu* labelMenu;
    int labelType;
    bool hideHydrogens;
    QMenu* hMenu;
    QButtonGroup* ConnectModeButtonGroup;
    QMap<QString, int> * m_labelMenuEntriesMap;
    QMap<int, QString> * m_labelMenuEntriesInverseMap;

    mmff94::MMFF94_ForceField* mmff;


};

#endif // QXMOLEDITOR_H

/// @}
