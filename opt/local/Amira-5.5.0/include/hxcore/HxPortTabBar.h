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
#ifndef HX_PORT_TAB_BAR
#define HX_PORT_TAB_BAR

#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>

#include <hxcore/HxPort.h>

class QWidget;
class QTabBar;
class QTab;


class HXCORE_API HxPortTabBar : public HxPort
{
  MC_ABSTRACT_HEADER(HxPortTabBar);

public:

    ////////////////////////////////////////
    // overload HxPort
    ////////////////////////////////////////

    /// Parse method.
    virtual int parse( Tcl_Interp* t, int argc, char **argv );

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    //
    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);


protected:

    virtual void guiCallback();
    virtual void createWidget( QWidget * parent );


public:

    /// Constructor.
    HxPortTabBar( HxObject * object, const char * inPortName, int inNumTabs );

    /// Constructor.
    HxPortTabBar( HxEditor * editor, const char * inPortName, int inNumTabs );

    /// Destructor.
    ~HxPortTabBar();

    /// Returns the number of tabs.
    int getNum() const;

    /// Sets current active Tab.
    void setValue( int inTabIndex );

    /// Gets current active Tab index.
    int getValue() const;

    // Included for backward compatibility only, use setValue() instead.
    void setIndex( int inTabIndex );

    // Included for backward compatibility only, use getValue() instead.
    int	getIndex() const;

    /// Sets label of port.
    void setLabel( const char * inLabel );

    /// Returns label of port.
    const char * getLabel() const;

    /// Set Tab label
    void setLabel( int inTabIndex, const char * inLabel );

    /// Gets Tab label
    const char * getLabel( int inTabIndex ) const;

    /// Activates or deactivates a Tab.
    void setSensitivity( int inTabIndex, int inFlag );

    /// Checks whether the specified Tab is enabled or not.
    int getSensitivity( int inTabIndex ) const;

    /// Adds a port to a Tab.
    void portAdd( int inTabIndex, HxPort * inPort );

    /** Adds a list of ports to a tab item. The last argument must be NULL.
        Note: Do not pass 0 (instead of NULL) as the last argument because
        this may cause problems on 64-bit architectures. */
    void portsAdd( int inTabIndex, HxPort * inPort1, ... );

    /// Adds a port to a tab item. The port is specified by its label and the label of the ports parent object.
    void portAdd( int inTabIndex, char * inObjectName, char * inPortName );

    /// Removes a port from a tab item.
    void portRemove( int inTabIndex, HxPort * inPort );

    /// Removes a port from a tab item. The port is specified by its label and the label of the ports parent object.
    void portRemove( int inTabIndex, char * inObjectName, char * inPortName );

    /// Removes a port from all tabs.
    void portRemove( HxPort * inPort );

    /// check if a given port was added to the tabbar
    bool portIsAdded( HxPort * inPort );



protected:
    
    void updateVisibility();


protected:

    // for each port that was added to this tab bar
    class MyPort
    {
    public:

        MyPort( 
            HxPortTabBar * inTabPort
        ,   HxPort       * inHxPort
        );

       ~MyPort();

        HxPortTabBar  * mHxPortTabBar;
        HxPort        * mHxPort;
        int             mNumTabs;   // number of tabs this port was added to
        bool            mIsHiddenByTabBar;

        void updateVisibility();
    };
    // TODO: using pointers as hash key is bad
    McHashTable< HxPort *, MyPort * >   mPorts;


    // foreach tab
    class MyTab
    {
    public:

        MyTab(
            HxPortTabBar * inTabPort
        );
       ~MyTab();

        int  myCurrIndex();
        void portRemove( MyPort * inPort );
        void portAdd   ( MyPort * inPort );

        HxPortTabBar      * mHxPortTabBar;
        // Qt's ID of the Tab object
        int                 mQtId;
        McString            mLabel;
        // the list of ports controlled by this tab
        McDArray<MyPort*>   mMyPorts;
        bool                mEnabled;
    };
    McDArray<MyTab*>  mTabs;


    // the tab bar
    QxGuardedPtr<QTabBar> mQBar;

    // index of the current selected tab
    int                   mCurrTabIndex;
};

#endif


/// @}
