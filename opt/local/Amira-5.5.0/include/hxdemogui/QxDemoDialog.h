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

/// @addtogroup hxdemogui hxdemogui
/// @{
#ifndef QX_DEMODIALOG_H
#define QX_DEMODIALOG_H

#include <hxdemogui/ui_QxDemoDialogBase.h>

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include "HxDemoGUIWinDLLApi.h"
class QxAttributesListView;
class QxAttributesListItem;

class QxDemoListView;
class QxDemoListItem;
class HxScriptObject;

class HXDEMOGUI_API QxDemoDialog : public QDialog, public Ui::QxDemoDialogBase
{
    Q_OBJECT

  public:

    // creates a new or returns the existing demo dialog
    static QxDemoDialog *  getTheDemoDialog (void);

    // parses a given directory for valid demos
    static bool  anyDemo (const char * demoDir = NULL);

    // default name of demo description files
    static char *  defaultDemoDescriptionFileName (void) { 
        return (char *)"description.xml"; 
    }

  protected:

    // singleton: there's only one demo dialog
    QxDemoDialog (void);

    ~QxDemoDialog (void);
   
    /** extracts all demos from a given directory:
        returns the number of valid demos.*/
    int  initialize (const char * demoDir, HxScriptObject * = 0);

    /** creates a new script object with the
        chosen demo sequence.*/
    HxScriptObject *  createDemoSequence (void);

  protected slots:

    void  setAddButtonEnableState (void);
    void  handleDemoSelection (void);
    void  removeSelected (void);
    void  addSelected (void);
    void  moveSelectionUp (void);
    void  moveSelectionDown (void);
    void  createDemo (void);
    void  accept (void);
    void  showHelp(void);
    void  applyFilter(void);
    void  handleFilterChanged(void);
    void  changeDemoDir(void);

  private:

    // filenames relative to $AMIRA_LOCAL
    QString  relativePath (const QString &);

    // resolve $AMIRA_LOCAL to absolute path
    QString  absolutePath (const QString &);

    /// the only dialog
    static QxDemoDialog  * _theDemoDialog;

    // check for a valid DemoSequence script object
    bool  validDemoSequence (HxScriptObject *);

    // retrieves demos from a given demoSequence script object
    void extract (McDArray< McString > & demoFiles, 
                  McDArray< McDArray < McString > > & demoSteps,
                  HxScriptObject * demoSequence);

    // fills the list view with demo items
    int  fillDemoList (const McDArray< McString > & demoFiles, QxDemoListView *, const char *);

    // removes demo steps that have not been previously selected
    void  removeDemoSteps (const McDArray< McDArray< McString > > & demoSteps, QxDemoListView *);

    // initialize the attributes list with the permitted attributes
    void fillAttributesList(void);

    // filter all demos by the selected attributes
    void filterDemoList(QxDemoListView *demoListView);

    // get the current demo directory
    const char* getDemoDirectory(void);

    // sets the demo directory only if it contains demos
    bool setDemoDirectory(const char* dir);

    // DemoSequence script that has been used for initialization
    HxScriptObject *  _demoSequence;
    
    // stores the permitted attributes 
    HxDemoAttributes demoAttributesDef;

    // the current demo directory
    QString demoDirectory;

    // indicates if this is the first time the singleton object is called
    bool firstTime;

};

#endif

/// @}
