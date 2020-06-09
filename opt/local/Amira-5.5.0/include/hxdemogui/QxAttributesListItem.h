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
#ifndef QX_ATTRIBUTESLISTITEM_H
#define QX_ATTRIBUTESLISTITEM_H


#ifndef QT_H
#include "q3listview.h"
#endif

#include <hxdemogui/HxDemoGUIWinDLLApi.h>


/** The QxAttributesListItem represents a attribute name or a key. If the state of
    the item changes the stateChanged method of QxAttributesListView is called. */
class HXDEMOGUI_API QxAttributesListItem : public Q3CheckListItem
{

  public:

    /// constructor
    QxAttributesListItem(Q3ListView *parent, 
                         Q3ListViewItem *after, 
                         const QString &text, 
                         Type tt = RadioButtonController) : 
        Q3CheckListItem(parent, after, text, tt) {}


    /// constructor
    QxAttributesListItem(Q3CheckListItem *parent, 
                         Q3ListViewItem *after, 
                         const QString &text, 
                         Type tt = RadioButtonController) :
        Q3CheckListItem(parent, after, text, tt) {}

    /// destructor
    ~QxAttributesListItem(){}

  protected:
    
    /** called if the user clicks on the item and used to signalize QxAttributesListView
        a change in the item's state */
    void activate(){
        ToggleState previousState = state();
        Q3CheckListItem::activate();
        ToggleState currentState = state();
        if( previousState != currentState ){
            previousState = currentState;
            QxAttributesListView *attListView = dynamic_cast<QxAttributesListView *>(listView());
            if( attListView ) attListView->stateChanged();
        }
        
    }

};

#endif

/// @}
