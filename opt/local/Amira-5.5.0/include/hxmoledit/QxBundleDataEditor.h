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
#ifndef QX_BundleDataEDITOR_H
#define QX_BundleDataEDITOR_H

#include <hxmoledit/ui_QxBundleDataEditorBase.h>
#include <hxmoledit/HxMolEditWinDLLApi.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class HxMolTrajectoryBundle;
class QxSelectItem;
class MolTopology;
class McBitfield;
class QKeyEvent;
/** this class implements Data editing of a molecule
    the widget is defined in DataEditor.ui and
    implemented in QxBundleDataEditorBase **/ 

class HXMOLEDIT_API QxBundleDataEditor : public QDialog, public Ui_QxBundleDataEditorBase
{ 
    Q_OBJECT
    static QByteArray currentGeometry;
    HxMolTrajectoryBundle *bundle;
    bool update;
    QxSelectItem* molSelector;
    // return whether data with given index is selected
    bool isDataSelected(int dataIx);
    // return whether trajectory with given index is selected
    bool isTrajectorySelected(int trajIx);
    // return bitfield containing which residues are selected
    void getTrajectorySelection(McBitfield& residues);
    // returns bitfield containing whether each row is selected or not
    void getRowSelectionBf(McBitfield& bf);
    // converts row index to trajectory index
    int rowToTrajIx(int row);
    // sets selection of rows
    void setRowSelection(const McBitfield& rowBf);
    McString columnToDataName(int column);
    // converts bitfield with trajectory indices to bitfield of row indices
    void trajectoryBitfieldToRowBitfield(const McBitfield& trajBf,McBitfield& rowBf) const;
    // parses and matches atom exression and selects all trajectories in bitfield for which at least one atom was matched
    bool atomExpressionToMatchedTrajectoryIx(const McString& expression,McBitfield& bf) const;
    /** sets value of molecule data field to new string
        Throws McException if setting fails */
    void setDataValue(int row, int column,const char* str);
public:
    QxBundleDataEditor( HxMolTrajectoryBundle* mol,QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~QxBundleDataEditor();

     void bundleChanged();

protected:
    virtual void keyPressEvent(QKeyEvent * event);

signals:
    /** exit is emitted when QxBundleDataEditor is ended by the user **/
    void exit(bool ok);

public slots:
    void updateTable();

protected slots:
    /// reacts on editing in the DataTable
    void cellChanged(int row,int column);
    void newData();
    void deleteData();
    void addTrajectories();
    void deleteTrajectories();
    void restrictTrajectories();
    void applySortOrder();
    void closeEvent( QCloseEvent* ce );
    void reject();
    void addOther();
    void endMolSelector();
    void cellDoubleClicked ( int,int);
    void openHelp();
    void selectByAtomExpression();
    void newDataFromSelection();
    void selectionAdd();
    void selectionRemove();
    void selectionReplace();
    void selectionAll();
    void selectionClear();
};

#endif // DataEDITOR_H

/// @}
