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
#ifndef QX_ATTRIBUTEEDITOR_H
#define QX_ATTRIBUTEEDITOR_H

#include <hxmoledit/ui_AttributeEditor.h>
#include <hxmoledit/HxMolEditWinDLLApi.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class HxMolecule;
class QxSelectItem;
class MolTopology;

/** this class implements attribute editing of a molecule
    the widget is defined in AttributeEditor.ui and
    implemented in QxAttributeEditorBase **/ 

class HXMOLEDIT_API QxAttributeEditor : public QDialog, public Ui::AttributeEditorBase
{ 
    Q_OBJECT

    HxMolecule *mol;
    MolTopology * T;

    QxSelectItem *selectItem;
    /// indices of all selected groups in level currentLevel
    McDArray<int> selectedGroups;
    ///
    int currentLevel;
public:
    QxAttributeEditor( HxMolecule* mol,QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~QxAttributeEditor();

signals:
    /** exit is emitted when QxAttributeEditor is ended by the user **/
    void exit(bool ok);

protected slots:
    /// reacts on editing in the AttributeTable
    void attributeTableChanged(int row,int column);
    /// reacts on the addAttributeButton
    void addAttribute();
    /// reacts on the removeAttributeButton
    void removeAttribute();
    /// redraws the attribute table
    void updateTable();
    /// reacts on adjustment of the current level in the combo box
    void levelChanged();

    void exportAttributes();
    void exportFileRequester();
    void exportSelectPredefinedSpecification();
    void exportLoadPredefinedSpecification();
    
    void importAttributes();
    void importFileRequester();
    void importSelectPredefinedSpecification();
    void importLoadPredefinedSpecification();

    void endSelectItem();
    void reject();
public:
    /** this function checks and does everything neccessary if 
        the selection of atoms of the molecule has changed **/
    void selectionChanged();
    void fire();
    // true while editor fires the master connection
    bool hasFired;
private:
    /** set the current text in the attribute table  cell in row 
        @c row and column @c col to @c text
        @c editable determines whether cell is editable
        @c singleGroup determines whether only one group has been selected
        @c singleValue determines if selected groups have different values
    **/
    void setTableText(int row,int col, QString text,
            bool editable=true,
            bool singleGroup=true, 
            bool singleValue=true);

    /** overloads qt method to enable the editor to be closed
        instead of hidden when the close widget is pushed **/
    void closeEvent( QCloseEvent* ce );
    
    McString loadPredefinition(McString filename,int index);
    McDArray<McString> loadPredefinitionTitles(McString filename);

    void blockAttributeTableChangedEvents(const bool blockEvents);
    bool isBlockedAttributeTableChangedEvents();

private:
    /// saves current state for use when next MoleculeEditor opens
    static int currentLevelIx;
    static QByteArray currentGeometry;
    static int currentTabIx;
    static QString exportFormatTxt;
    static QString exportFileTxt;
    static bool exportSelectedOnly;
    static QString importFormatTxt;
    static QString importFileTxt;

    bool m_blockAttributeTableChangedEvents;
};

#endif // ATTRIBUTEEDITOR_H

/// @}
