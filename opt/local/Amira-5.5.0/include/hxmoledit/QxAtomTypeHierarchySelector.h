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
#ifndef QxAtomTypeHierarchySelector_H
#define QxAtomTypeHierarchySelector_H

#include "HxMolEditWinDLLApi.h"
#include <hxmoledit/ui_QxAtomTypeHierarchySelectorBase.h>

class Molecule;
class McBitfield;
struct TreeEntry;
template <class T> class McDArray;
template <class T> class McGeneralTree;

namespace molchem {
    class Logger;
}
class QxAtomTypeHierarchySelector;
class AtomTypeSelectorNotifier {
public:
    virtual ~AtomTypeSelectorNotifier() {}
    virtual void notifySelectorApply(QxAtomTypeHierarchySelector*) {}
};

class HXMOLEDIT_API QxAtomTypeHierarchySelector : public QDialog, public Ui_HierarchySelectorBase
{ 
    Q_OBJECT
public:
    QxAtomTypeHierarchySelector( 
        QWidget* parent = 0, 
        const char* name = 0, 
        Qt::WFlags fl = 0
        );

    ~QxAtomTypeHierarchySelector();
    void setNotifier(AtomTypeSelectorNotifier* n) { notifier = n;}
    AtomTypeSelectorNotifier* notifier;
    void getAtomMask(const Molecule* mol,McBitfield& atoms) const;
    void getAtomTypeMask(McBitfield& atoms) const;
    void getAtomTypeIx(const Molecule* mol,McDArray<int>& type) const;
    void setAtomTypeNumber(const McDArray<int>& num);

private slots:
    void applyClicked();
    void clearClicked();
private:
    McDArray<TreeEntry*>* treeEntries;
    McGeneralTree<int>* tree;
    McDArray<TreeEntry*>* treeLeafs;
    static molchem::Logger* logger;
};

#endif 

/// @}
