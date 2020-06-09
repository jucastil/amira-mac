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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef QXHIERARCHICALLABELSVIEWITEMS_H
#define QXHIERARCHICALLABELSVIEWITEMS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QToolButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <mclib/McColor.h>

class QxColorDialog;

/** 
 *  Base class for items appearing in HierarchicalLabelsViews
 */
class QxTreeWidgetBase : public QWidget {
    
public:
    QxTreeWidgetBase(QWidget *parent, QTreeWidgetItem *item, int labelId = -1, int column = -1);
    ~QxTreeWidgetBase(); 

    int mColumn;
    int mId;
    QTreeWidgetItem *mTreeWidgetItem;
};
///////////////////////////////////////////////////////////////////////////////////////

/** 
 *  Color icon for HierarchicalLabelsViews
 */
class QxTreeWidgetStaticColorIcon : public QxTreeWidgetBase {
    Q_OBJECT

public:
    QxTreeWidgetStaticColorIcon(QWidget *parent, QTreeWidgetItem *item, int labelId = -1, int column = -1);
    virtual ~QxTreeWidgetStaticColorIcon();

    void setColor(const McColor &color);
    void getColor(McColor &color) const;
    void createWidget();

protected:
    McColor mColor;
    QLabel* mLabel;
    QHBoxLayout *mLayout;
};
///////////////////////////////////////////////////////////////////////////////////////

/** 
 *  Editable color icon for HierarchicalLabelsViews
 */
class QxTreeWidgetEditableColorIcon : public QxTreeWidgetBase {
    Q_OBJECT

public:
    QxTreeWidgetEditableColorIcon(QWidget *parent, QTreeWidgetItem *item, int labelId = -1, int column = -1);
    virtual ~QxTreeWidgetEditableColorIcon();

    void setColor(const McColor &color);
    void getColor(McColor &color) const;
    void createWidget();

signals:
	void colorChanged(McColor newColor);

public slots:
    void buttonPushed();	
    
protected:
    void colorEditCB(const QxColorDialog & colEd);
    static void colorEditCBS(void *userData, const QxColorDialog &colEd);

    McColor mColor;
    QToolButton *mButton;
    QHBoxLayout *mLayout;
};

///////////////////////////////////////////////////////////////////////////////////////

/** 
 *  checkbox for HierarchicalLabelsViews
 */
class QxTreeWidgetCheckBox : public QxTreeWidgetBase {
    Q_OBJECT

public:
    QxTreeWidgetCheckBox(QWidget *parent, QTreeWidgetItem *item, int labelId = -1, int column = -1);
    virtual ~QxTreeWidgetCheckBox();

    void createWidget();

	bool isChecked() const;

    QCheckBox *mCheckBox;
    QHBoxLayout *mLayout;

signals:
    void clicked();
    void stateChanged(int);

protected slots:
    void forwardCheckBoxClickedSignal(); 
	void forwardCheckBoxStateChangedSignal(int state);
};

///////////////////////////////////////////////////////////////////////////////////////

#endif

/// @}
