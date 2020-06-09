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
#ifndef HX_PORT_DOIT
#define HX_PORT_DOIT

#include <mclib/McDArray.h>
#include <hxcore/HxPortButtonList.h>

/** The "Do it" button. This module is almost exactly the same as HxPortButtonList.
    The primary difference is that all buttons are initialized to have 
	a snap toggle and by default it has only one button.

    Note: Since amira 4.0, the HxPortDoIt port is not by default visible in 
    the control panel of its associated module. Rather, the fact that a module 
    has an HxPortDoIt activates (makes green) the Apply button at the bottom 
    of the Properties Area. Checking the auto-refresh toggle is equivalent 
    to snapping down the red DoIt port snap toggle. To request display of 
    the DoIt port in the module's control panel, open the Edit/Preferences dialog, 
	click on the Layout tab, then check the 'Show "DoIt" buttons' box. 

    Note also that the Apply button corresponds to the first button of 
    the DoIt port. If a DoIt port has multiple buttons, in order to 
    display all of them, you must check the 'Show "DoIt" buttons' box 
    as described above. 
*/
class HXCORE_API HxPortDoIt : public HxPortButtonList {

  MC_ABSTRACT_HEADER(HxPortDoIt);

  public:
    /// Constructor.
    HxPortDoIt(HxObject *object, const char* name, int nButtons=1);
      
    /// Constructor.
    HxPortDoIt(HxEditor *editor, const char* name, int nButtons=1);

    // Send the command.
    void sendCmd() ;

  protected:
    // Called when the gui has been touched.
    virtual void guiCallback();
};

#endif


/// @}
