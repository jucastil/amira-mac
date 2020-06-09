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
#ifndef QXDICOM3TABLE_H
#define QXDICOM3TABLE_H

#include <hxdicom/QxDicom3ValueEdit.h>

#include <q3table.h>
#include <qcombobox.h>
#include <qstringlist.h>

#include <amiramesh/HxParamBundle.h>
#include <amiramesh/HxParameter.h>

typedef enum { DICOM_TABLE = 0, PATIENT_TABLE } TableType;

class QxDicom3TableItem : public Q3TableItem
{

public:
    QxDicom3TableItem( Q3Table *t, EditType et, const char* content="CS" );
    QWidget* createEditor() const;
    void setContentFromEditor( QWidget *w );
    void setText( const QString &s );
    int alignment() const { return Qt::AlignLeft | Qt::AlignVCenter; };

protected:
    void paint( QPainter *p, const QColorGroup &cg,
		const QRect &cr, bool selected );
private:
    Q3ComboBox* vrEdit;
    QxDicom3ValueEdit* valEdit;
};

class QxDicom3Table : public Q3Table
{

    Q_OBJECT

public:
    QxDicom3Table(QWidget * parent = 0, const char * name = 0,
		  TableType tableType = DICOM_TABLE);
    void replaceContentWithBundle(HxParamBundle* dicomBundle);
    void sortColumn( int col, bool ascending, bool);
    void adjustAll();
    //    void resizeData(int) {};
    TableType getTableType() { return tableType; };
    HxParamBundle* getContentAsDicomParamBundle();

public slots:
    void addNewItem();
    void delCurrentItem();
    void setEnabled(bool enabled);

private slots:
    void update( int row, int col );
    void VRChanged(const QString& VRString);

private:
    TableType tableType;
    int oldSelectedRow;
};

#endif // QXDICOM3TABLE_H

/// @}
