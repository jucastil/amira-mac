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
#ifndef QX_ATTRIBUTESLISTVIEW_H
#define QX_ATTRIBUTESLISTVIEW_H


#ifndef QT_H
#include "q3listview.h"
#endif

#include <hxdemogui/HxDemoGUIWinDLLApi.h>

class QxAttributesListItem;

/** ListView containing the permitted attributes, which the user could
    select to filter the available demos */
class HXDEMOGUI_API QxAttributesListView : public Q3ListView
{

    Q_OBJECT

  public:

    /// standard constructor
    QxAttributesListView(QWidget *parent = 0, const char *name = 0) :
        Q3ListView(parent, name){}

    /// destructor
    ~QxAttributesListView(void){}

    /** method called from a QxAttributesListItem to signalize a 
        changed checkbox state */
    void stateChanged(void){
        emit(checkBoxChanged());
    }

  signals:
    
    /** this signal is emitted, if one of the QxAttributesListItems
        changes it's state */
    void checkBoxChanged(void);

};

#endif

/// @}
