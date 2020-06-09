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
#ifndef QX_DICOM_LIST_VIEW_H
#define QX_DICOM_LIST_VIEW_H


#include <hxdicom/HxDicomWinDLLApi.h>
#include <hxdicom/QxDicomStackItem.h>
#include <hxdicom/QxDicomListItem.h>
#include <hxdicom/HxDicomImage.h>
#include <hxdicom/HxDicomImageStack.h>
#include <hxdicom/DicomLoadOption.h>
#include <hxdicom/QxDicomOptionDialog.h>

#include <qlist.h>
#include <q3popupmenu.h>
#include <qevent.h>

#include <q3listview.h>

#include <hxdicom/dynamicOnOff.h>

class DicomStackItem;

// DICOM image list (columns of DICOM data elements)
class HXDICOM_API DicomListView : public Q3ListView
{

    Q_OBJECT

public:

    /// Some filters for stacks
    enum StackFilter { S_UNIFORM  = 1 << 0,
                       S_SELECTED = 1 << 1 }; 

    DicomListView (QWidget *parent = 0, const char *name = 0);
    ~DicomListView (void);

    void initialize (const McDArray<HxDicomImage *> &images);

    // initialization of the list view (presorting of images)
    // if (reset==TRUE) default options are loaded
    // else the options from theLoadOptions will be inserted
    void initializeColumns (bool reset = FALSE);

    void parameterView (Q3ListViewItem *);
    void imagePreview (Q3ListViewItem *);
    bool exportImageStacks (McDArray<HxDicomImageStack *> &stacks, int filter);
    void setSorting (int column, bool increasing = TRUE);

    // returns sorting order for column (1 or -1 for ascending or descending respectively)
    int getSortOrder (int column);

    void setUniformTolerance(float tol);
    float getUniformTolerance();

    // returns the number of stacks that satisfy a certain filter criterion
    int countStacks(int filter);
    // returns true if some stack item satisfies the specified filter criterion
    bool satisfies(DicomStackItem * item, int filter);
    
    // list of DICOM load options
    McDArray<DicomLoadOption *>  theLoadOptions;

signals:

    void rightMouseButtonOnHeader (const QPoint &);
    void listViewChanged (const QString &);
    void stackIsSelected (const QString &);
    void stacksAreSelected (int);
    void noStackSelected (void);

public slots:

    void updateImageStacks (void);

    void sortingOrderChanged(int);
    void appendColumn (int, int, QString name = QString::null);
    void addLoadOption (int, int, QString name = QString::null);

    void saveSettings();
    void resetSettings();
    void loadSettings();

protected slots:

    void clearColumnsAndOptions();
    void popupItemMenu (Q3ListViewItem *, const QPoint &, int);
    void popupColumnMenu (const QPoint &);
    void deleteColumn (int);
    void loadOptionDialog (void);
    void parameterView (void);
    void imagePreview (void);
    void removeSelectedItems (void);
    void setDicomParameters (bool  attach) {dicomParameterRequest = attach;}
    void anonymizeDicomParameters (bool  anonymize) {anonymizedData = anonymize;}
    void removeLoadOption (QString  optionName);
    void updateStackInfo (Q3ListViewItem *);
    void updateStackInfo (void);

protected:

    void buildImageStacks (void);
    void setupLoadOptions (void);
    void loadImages (const McDArray<HxDicomImage *> &images);
    void setupListColumns (void);
    void cleanupListColumns (void);
    void cleanupAllStacks (void);
    void removeEmptyStacks (void);
    void adoptChildItems (void);
    void updateStackView (void);
    int  numStacks (void) {return(theStacks.size());}
    int  numImages (void);
    void updateDicomInfo (void);
    bool stackConsistency (void);
    void removeSelectedItem (Q3ListViewItem *);

    bool columnIsObsolete (int section);

    bool eventFilter (QObject *, QEvent *);
    
private:

    McDArray<HxDicomImage*> allImages;
    
    McDArray<int> sortOrder;
    const char **arrow[2];
    void sortItems ();
    float tolerance;
    const bool  ascending;
    const bool  descending;

    // internal list of image stacks
    McDArray<DicomStackItem *>  theStacks;

    // currently selected items in listview
    const McDArray<Q3ListViewItem *> &  getSelectedItems (void);

    // amount of selected images
    int  numSelectedImages (const McDArray<Q3ListViewItem *> &);

    // popup menu of Dicom list items
    Q3PopupMenu  *theImageMenu;

    // popup menu of tow Dicom list items
    Q3PopupMenu  *theTwoImagesMenu;

    // popup menu of Dicom stack items
    Q3PopupMenu  *theStackMenu;

    // popup menu of mixed list items
    Q3PopupMenu  *theMixedMenu;

    // pointer to non modal dialog
    DicomOptionDialog  *theOptionDialog;

    // request for having all DICOM parameters attached
    bool  dicomParameterRequest;

    // flag for anonymized parameters
    bool  anonymizedData;

#ifdef DYNAMIC
    bool  asDynamicRequest;
#endif
};


#endif

/// @}
