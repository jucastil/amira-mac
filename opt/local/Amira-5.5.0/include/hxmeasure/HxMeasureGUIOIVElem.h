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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASURE_GUI_OIV_ELEM
#define HX_MEASURE_GUI_OIV_ELEM

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxmeasure/HxMeasureGUIElem.h>

class SoSwitch;
class SoSeparator;

class HXMEASURE_API HxMeasureGUIOIVElem : public HxMeasureGUIElem
{
public:
    ///
    HxMeasureGUIOIVElem();
    ///
    virtual ~HxMeasureGUIOIVElem ();

    /**
    *  Nothing to do : use OIV.
    */ 
    virtual void redraw (int viewerId) {};

    /**
    *  As shape is added as OIV shape, no need to recompute bbox  
    */
    virtual bool getBBox (McBox3f& box){ return false; }

    /**
    *  OIV shapes support only 3D mode.
    */
    Mode getMode() const { return Mode3D; }

    /**
    *  All OIV shapes must support export.
    */
    inline virtual bool isShapeExportable() const {return true;}

    /**
    *  This method is virtual pure because, all inherited classes must support export.
    */
    virtual HxLineSet* exportShape() = 0;

    /**
    *  By default, OIV shapes doesn't support 2D mode
    *  unless inherited classes implement it.
    */
    inline virtual bool isSupporting2DMode() const { return false;}


    virtual void updateMe();

    virtual void setVisible (bool l);

    virtual void fillTextValue( McString &text );
        
    virtual void fillFloatValue( McString &text );

    virtual void setNoDepthTest (bool t);

protected:

    //Father node containing the gui node (annotation or separator)
    SoSeparator* m_currentFather;

    /// Visible switch
    SoSwitch* m_visibleSwitch;

    /// Main separator
    SoSeparator* m_root;

    /**
    *  Construct OIV SG basis.
    */
    void buildGeom();
};

#endif

/// @}
