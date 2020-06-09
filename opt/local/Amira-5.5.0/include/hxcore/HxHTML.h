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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_HTML_H
#define HX_HTML_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxBase.h>

class QxTabWidget ;
class QxMimeSourceFactory;
class QxHelpBrowser;
class QFrame;

/** An HTML text browser with optional navigation buttons. There is one
    global instance of the HTML browser which is used to display the online
    user's guide in Amira. This instance can be accessed via the global
    pointer theBrowser. For each HTML browser there is a separate
    Tcl-command allowing to access the object in a script (this is the
    reason why @c HxHTML is derived from HxBase). The name of the
    global browser is @c html. */

class HXCORE_API HxHTML : public HxBase
{
    MC_HEADER(HxHTML);

  public:
    /// Constructor, no navigation buttons on default.
    HxHTML(int hasButtons=0);

    /// Destructor.
    ~HxHTML();

    /// Shows browser window.
    void show();

    /// Hides browser window.
    void hide();

    /// Reloads the first document loaded.
    void home();

    /// Undoes last backward command.
    void forward();

    /// Loads last document.
    void backward();

    /// Load specified document.
    void load(const McString & document);

    /// Reload current document.
    void reload();

    // Indicates if the help should be display in a top level window
    // or in the console tab.
    void setTopLevelHelp(bool topLevelHelp) ;
    bool isTopLevelHelp() const
    { return m_topLevelHelp ; }
    
    /// Sets browser content to str
    void setText(const McString & str);

    /// Sets browser title to str
    void setCaption(const McString & str);

    /// returns whether browser is visible
    bool isVisible();

    /// resizes the widget and its contents
    void resize(int width, int height);

    /// Find an \a item in the current page or the entire documentation
    /// depending on the \a global flag.
    bool find(const McString & item, bool global);

    /// Returns URL of current document.
    McString source() const;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    /// Set the tab widget which contains the help
    void setTabWidget(QxTabWidget *tabWidget) ;

    /// Returns global instance of HTML browser.
    static HxHTML* getTheBrowser();

    QxHelpBrowser* getBrowserGUI() const
    { return wBrowser ; }
  protected:

    //
    // Browsers GUI:
    // The help browser (wBrowser) is a QxHelpBrowser object.
    // It can be displayed into a tab widget (wTabWidget) which is usually
    // the console area or into a top level widget (wBrowserTopLevel).
    // When switching from one mode to another, wBrowser is simply reparented.
    //
    QxHelpBrowser* wBrowser;

    /**
     * To attach/detach the browser from the top level help to the tab widget (or vice versa).
     */
    void fixBrowserParentWidget();

  private:
    bool m_topLevelHelp ;

};

int HXCORE_API hxreadHTML(const char* filename);


#define theBrowser HxHTML::getTheBrowser()

#endif

/// @}
