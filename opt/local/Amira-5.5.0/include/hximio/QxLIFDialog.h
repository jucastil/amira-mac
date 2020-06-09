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

/// @addtogroup hximio hximio
/// @{
#ifndef QX_LIF_DIALOG_H
#define QX_LIF_DIALOG_H

#include <hximio/ui_QxLIFDialogBase.h>

#include <hxcore/HxMain.h>
#include <hxcore/HxParamDialog.h>

#include "HxImFormatLIF.h"

#include <QTreeWidgetItem>

class HXIMIO_API QxLIFDialog : public QDialog, public Ui::QxLIFDialogBase
{
    Q_OBJECT

public:
    /// Constructor
    QxLIFDialog ( const char* title  = "LEICA LIF Loader",
                QWidget* parent = theMainWindow );

    /// initializes the dialog with a LIF File-object
    /// @param inLeica leica object to initialize from
    void addElement( SElementDesc& element);

    ///
    void setReader( HxImFormatLIF * reader) { mLIFreader = reader; }

    /// Destructor
    ~QxLIFDialog ();

    /// Called if load cmd is executed
    void loadImage(int elementIdx);

protected slots:

    /// overloaded QDialog method
    void accept (void);

    /// inverts selection state of all series of the file
    void selectionInvert();

    /// selects all series of the file
    void selectionAll();

    /// de-selects all series of the file
    void selectionNone();

    /// sets the status label in the kind "X of Y series selected..."
    void selectionChanged();

    /// show a dialog with tha actual series parameter bundle
    void showInfo();

private:
    /// returns the number of selected series
    /// @return The number of selected series
    int getNumSelected();

    McDArray<QTreeWidgetItem*>   _listItems;
    HxParamDialog*              _paramDlg;

    McDArray<SElementDesc>   mElements;

    HxImFormatLIF*              mLIFreader;
};

#endif // QX_LIF_DIALOG_H

/// @}
