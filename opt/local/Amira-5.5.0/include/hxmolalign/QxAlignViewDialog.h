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

/// @addtogroup hxmolalign hxmolalign
/// @{
#ifndef QX_ALIGNVIEWDIALOG_H
#define QX_ALIGNVIEWDIALOG_H

#include <QDialog>
#include <QLabel>

#include <hxcore/HxModule.h>

#include <hxmolalign/HxMolAlignWinDLLApi.h>
#include <hxmolalign/QxAlignView.h>

class QResizeEvent;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

/** This class implements a QDialog window, which is used for
    displaying the results of a local sequence alignment. It contains
    several widgets, most important an QxAlignView widget, which is
    inherited from QScrollView. Into this scroll view all alignment
    information is drawn. Furthermore there are a couple of buttons,
    which are needed to invoke actions in the HxSeqAlign module. 

    You can select one or several alignments and then register those
    alignments as levels in the aligned molecules. In order to do
    this, click on the label <tt>n-th Alignment</tt>. Immediately it turns
    black. Clicking on the label a second time deselects the
    alignment. Ctrl-clicking on a label keeps the old selections and
    adds new ones. Selected alignments are transfered to the
    HxSeqAlign module by pressing the <Accept>-button. All alignments
    can be transfered by pressing the <AcceptAll>-button. The
    <Close>-button closes the window and does nothing else.
    
    Another feature is the possibility to click into a sequence and 
    get information about were in the original sequence we are. This 
    information is displayed by the QLabel widget @c info. */
 
class HXMOLALIGN_API QxAlignViewDialog : public QDialog
{
    Q_OBJECT
    
private: 
    QxAlignView * alignView; // scroll view into which everything is drawn
    QPushButton * acceptButton;
    QPushButton * acceptAllButton;
    QPushButton * closeButton;
    QLabel      * info;

    HxModule * hxParent; // pointer to HxSeqAlign module

protected:
    QHBoxLayout* hbox;
    QVBoxLayout* vbox;

public:
    QxAlignViewDialog(HxModule* module, QWidget * parent=0);
    
    ~QxAlignViewDialog();
    
    QxAlignView * getAlignView() { return alignView; }

    bool close();

    QLabel * getInfoLabel() { return info; }
    
protected slots:
    void accept();
    void acceptAll();
    void reject();
};

#endif

/// @}
