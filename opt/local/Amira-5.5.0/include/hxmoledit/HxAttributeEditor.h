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
#ifndef HX_ATTRIBUTE_EDITOR_H
#define HX_ATTRIBUTE_EDITOR_H

#include "HxMolEditWinDLLApi.h"
#include <hxcore/HxEditor.h>
#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>
#include <hxmolecule/ComputeListener.h>

class HxMolecule;
class SoEventCallback;
class QxAttributeEditor;
class QxEditorNotifier;
class readOperation;
class MtGroupAttribute;

/** HxAttributeEditor is the interface between the
    outside world and the QT user interface 
    as implemented in QxAttributeEditor. It
    contains all editor functions that can 
    be accessed by external libraries as static methods. 
    An instance of it should only be created by
    Amira. The QxAttributeEditor will be created as soon
    as the data object is known (when startEditing
    is called)
    It uses an HxMoleculeEvenCB to ensure that it is
    notified in case of selection event
    A QxEditorNotifier is used for passing the exit
    signal of the QxMolEditor on to this object
**/

class HXMOLEDIT_API HxAttributeEditor : public HxEditor, public ComputeListener {

    HX_HEADER(HxAttributeEditor);

public:
    /// Default constructor.
    HxAttributeEditor();
  
    /// Called whenever a port changes.
    virtual void fire();

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);


    /// function used for selection event callbacks
    void computeCalled(HxObject *);

    /** export attributes of molecule mol to a file filename, formatString
        contains information of which attributes and in which format the
        output will have, if selectedOnly is set the highlighing of mol
        will be checked to decide which groups to write
        will return whether successfull */
    static bool exportAttributes(
        const HxMolecule* mol,
        const McString& formatStr,
        const McString& filename,
        bool selectedOnly=false);

   /** import attributes to molecule mol from file filename, formatString
        contains information of which attributes and in which format the
        input will have
        will return whether successfull 
        if writeDebugFile is true it will write debug info to c:\tmp\attributeImport.dbg
        or ~/attributeImort.dbg */
    static bool importAttributes(
        HxMolecule* mol,
        const McString& formatStr,
        const McString& filename,
        bool writeDebugFile=false);

protected:
    ~HxAttributeEditor();

    virtual void molChanged();

private:
    McHandle<HxMolecule> molecule;
    QxAttributeEditor* attrEdit;
    QxEditorNotifier* notifier;

    /// Initialize ports here.
    void startEditing(HxData *data);

    /// Remove selection callbacks here.
    void stopEditing();

    // -----------------------------------------------------------------
    // methods for parsing export and import format strings
    
    /* parse an specifier (everything behind a '%') of an 
       export format string
       pos must be the acutal parse position in the format string
           will be adjusted to the new acutal position
       levelName will return the name of level, "" if there was none
       attrName will return the attribute name, "" if there was none
       return value will be whether specifier string was of valid form*/
    static bool parseSpecifierExport(
        const char*& pos,
        McString& levelName, 
        McString& attrName);
    /* will parse to the next specifier ('%' char) 
       pos must be the acutal parse position in the format string
           will be adjusted to the new acutal position
       text will contain everything parsed until the % was found
       return value will be whether parsing did suceed */
    static bool parseToNextSpecifier(
        const char*& pos,
        McString& text);
    /* parse an specifier (everything behind a '%') of an 
       import format string
       pos must be the acutal parse position in the format string
           will be adjusted to the new acutal position
       width will return a width value, will return 0 if there was none
       levelName will return the name of level, "" if there was none
       attrName will return the attribute name, "" if there was none
       attrType will return the attribute type, "" if there was none
       skipChars will return skipChars, "" if there were none
       hadAsterik will return whether the specifier was ended by an asterik
            (skip or jump specifier) or not (startContext or attr specifier)
       return value will be whether specifier string was of valid form*/
    static bool parseSpecifierImport(
        const char*& pos,
        int& width,
        McString& levelName, 
        McString& attrName,
        McString& attrType,
        McString& skipChars,
        bool& hadAsterik);
    /* get the next operation from a import format string
       mol must be the molecule on which the import is to be applied
       pos must be the actual parse position in the format string
           will be adjusted during the operation to the new actual
           parse position
       op will return the pointer the a operation allocated on the heap
           (must be deleted by the user) or NULL if no operation could be
           found 
       return value will be whether individual parse operation suceeded */
    static bool getNextOperation(
        HxMolecule* mol,
        const char*& pos,
        readOperation*& op);
    /* sets the value of the groupIx'th element of attr to
       val, will automatically determine the type of attr
       and convert val into the appropiate type */
    static void setAttributeValue(
        MtGroupAttribute* attr,
        const McString& val,
        int groupIx);
};

#endif


/// @}
