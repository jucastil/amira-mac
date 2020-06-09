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

/// @addtogroup hxvolren hxvolren
/// @{
#ifndef HX_PORT_GENERIC_MATERIAL_H
#define HX_PORT_GENERIC_MATERIAL_H

#include <hxcore/HxPortGeneric.h>

#include <hxcolor/HxColormap.h>
#include <hxcolor/HxPortColormap.h>

#include <mclib/McString.h>

#include "QxChooseTransferFuncButton.h"
#include "hxvolrenAPI.h"

static const int ITEM_TRANSFER_FUNC = 99;


////////////////////////////////////////////////////////////////////////////////
struct HXVOLREN_API HxPortGenericTransferFunc : public HxPortGenericItem
{
    int                                      mValue;
    QPixmap                                  mPixmap;
    McString                                 mLabel;

    QxGuardedPtr<QxChooseTransferFuncButton> mQButton;
    QxGuardedPtr<QLabel>                     mQLabel;

    HxPortGenericTransferFunc()
    :   mValue  ( -1 )
    ,   mPixmap ( 0, 0 )
    {
    }

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1 );
};

struct HXVOLREN_API HxPortVolrenColor : public HxPortGenericItem
{
    McColor                           color;
    QxGuardedPtr<QxChooseColorButton> qbutton;

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1 );
};




////////////////////////////////////////////////////////////////////////////////
class HxPortGenericMaterial : public HxPortGeneric   
{
public:
    
    /// Constructor for objects.
    HxPortGenericMaterial(HxObject* object, const char* name);

    /// Constructor for editors.
    HxPortGenericMaterial(HxEditor* editor, const char* name);
  
    /// Destructor.
    virtual ~HxPortGenericMaterial();

    /// HxPortGenericTransferFunc specific functions
    // set QxChooseTransferFuncButton button pixmap icon to colormap
    void setColorMap(int id, HxPortColormap& portColorMap);

    void setColor(int id, const McColor &color);

    // insert HxPortGenericTransferFunc item
    void insertTransferFuncButton( int inId, const char * inLabel, int inIndex = -1 );

    void insertVolrenColorButton(int id, int index = -1);



    /// overloaded functions from  HxPortGeneric
    int getValue(int id);
    void setValue(int id, int value);

    virtual void guiCallback();
};

#endif // HX_PORT_GENERIC_MATERIAL_H

/// @}
