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

/// @addtogroup hxdicom hxdicom
/// @{
#ifndef QX_DICOM3_VALUE_EDIT_H
#define QX_DICOM3_VALUE_EDIT_H

#include <dicom/dicom.h>
#include <hxdicom/HxDicomWinDLLApi.h>
#include <hxdicom/Dicom3Operations.h>

#include <q3hbox.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qstring.h>
//Added by qt3to4:
#include <QFocusEvent>
#include <QKeyEvent>

#define DEFAULT_VR ST


class HXDICOM_API QxDicom3ValueEdit : public Q3HBox
{

    Q_OBJECT

public:
    QxDicom3ValueEdit(valRep valueType = DEFAULT_VR,
		      QWidget * parent = 0, const char * name = 0);
    QxDicom3ValueEdit(const QString &, valRep valueType = DEFAULT_VR,
		      QWidget * parent = 0, const char * name = 0);
    ~QxDicom3ValueEdit();

    void setText(const QString &text, bool skipSave = false);
    QString text();

protected:
    void focusInEvent (QFocusEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

private slots:
    void createDialog();
    void init();
    void parseText();

private:
    valRep valueType;
    QString initialText;

    // internal GUI
    QComboBox* ageCombo;
    QPushButton* dialogButton;
    QLineEdit* lineEdit;
};

#endif // QX_DICOM3_VALUE_EDIT_H

/// @}
