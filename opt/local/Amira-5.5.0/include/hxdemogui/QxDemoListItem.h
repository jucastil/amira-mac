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
#ifndef QX_DEMOLISTITEM_H
#define QX_DEMOLISTITEM_H


#ifndef QT_H
#include "q3listview.h"
#endif
#include <Q3ListViewItem>

#include <hxdemogui/HxDemoObject.h>
#include <hxdemogui/HxDemoGUIWinDLLApi.h>
#include <hxdemogui/HxDemoAttributes.h>


class QxDemoListView;


class HXDEMOGUI_API QxDemoListItem : public Q3ListViewItem
{
  friend class QxDemoListView;

  public:

    /// Constructor used by QxDemoDialog for QxDemoListView
    QxDemoListItem (Q3ListViewItem * parent, 
                    const HxDemoObject &,
                    Q3ListViewItem * after = 0);

    /// Destructor
    ~QxDemoListItem (void) {}

    /// Default constructor
    QxDemoListItem (Q3ListView * parent = 0) : 
    	Q3ListViewItem(parent),
    	_numInvisibleChildren(0),
        _visibilityFlag(true) {}

    /// Copy constructor
    QxDemoListItem (const QxDemoListItem & other, 
                    Q3ListViewItem * parent = 0,
                    Q3ListViewItem * after = 0) ;

    /// Assignment operator for QxDemoListItem
    QxDemoListItem & operator=(const QxDemoListItem & other);

    /// methods for requesting demo attributes
    const HxDemoAttributes & attributes (void) const { return _demoAttributes; }
    const char * description (void) const { return _description; }
    const char * responsible (void) const { return _responsible; }
    const char * directory (void) const { return _directory; }
    const char * scriptFile (void) const { return _scriptFile; }
    const char * demoFile (void) const { return _demoFile; }
    const char * iconFile (void) const { return (_iconFile.length() > 0 ? (const char *)_iconFile : NULL); }
          bool   isDemo (void) const { return _validDemo; }
          bool   isStatic (void) const { return _staticStepSequence; }

    void displayInfo (const QPoint & pos);

    /// indicates if this item is visible or not
    bool isVisiblityFlagSet() const;

    /** sets the visibility flag; called by decrementVisibleChildren() 
        and incrementVisibleChildren(); only a flag: no impact on the 
        real visibility of the item */
    void setVisiblityFlag(bool b);

    /// get the number of invisible children
    int getNumInvisibleChildren() const;

  protected:

    void activate (void);

    /// decrement the number of visible children
    void decrementVisibleChildren(void);

    /// increment the number of visible children
    void incrementVisibleChildren(void);

  private:

    QString  _demoFile;
    HxDemoAttributes _demoAttributes;
    QString  _description;
    QString  _responsible;
    QString  _directory;
    QString  _scriptFile;
    QString  _iconFile;
    bool     _validDemo;
    bool     _staticStepSequence;
    int      _numInvisibleChildren;
    bool     _visibilityFlag;
};


class HXDEMOGUI_API QxDemoStepItem : public Q3ListViewItem
{
  friend class QxDemoListView;

  public:

    /// Constructor used by QxDemoDialog for QxDemoListView
    QxDemoStepItem (Q3ListViewItem * parent, 
                    const HxDemoObject::DemoStep &,
                    Q3ListViewItem * after = 0);

    /// Destructor
    ~QxDemoStepItem (void) {}

    /// Default constructor
    QxDemoStepItem (Q3ListViewItem * parent = 0) : Q3ListViewItem(parent) {}

    /// Copy constructor
    QxDemoStepItem (const QxDemoStepItem & other, 
                    Q3ListViewItem * parent = 0,
                    Q3ListViewItem * after = 0);

    /// Assignment operator for QxDemoListItem
    QxDemoStepItem & operator=(const QxDemoStepItem & other);

    /// methods for requesting demo attributes
    const char * command (void) const { return _command; }
    const char * jump (void) const { return _jump; }
    const char * description (void) const { return _description; }
    const char * iconFile (void) const { return (_iconFile.length() > 0 ? (const char *)_iconFile : NULL); }
    const int number (void) const { return _number; }

    void displayInfo (const QPoint & pos);

  protected:

    void activate (void);

  private:

    int _number;
    QString  _command;
    QString  _jump;
    QString  _description;
    QString  _iconFile;
};


#endif


/// @}
