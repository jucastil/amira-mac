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
#ifndef HXSEEDBOXPORTHELPER_H
#define HXSEEDBOXPORTHELPER_H

#include "HxAmiraWinDLLApi.h"

#include "HxPort.h"

#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <mclib/McHandle.h>

#include <QPointer>

class SoTransformBoxDragger;
class SoTabBoxDragger;
class SoDragger;
class SoSFVec3f;

class HxModule;
class McBox3f;

class QWidget;
class QRadioButton;

/**
    Port for selecting an axis aligned 3D box.
 */
class HXCORE_API HxPortBox3D : public HxPort {
public:
    HxPortBox3D(HxObject* parent, const char* name);

    ~HxPortBox3D();

    McBox3f getValue() const;

    void setValue(const McBox3f& box);

    enum InteractionMode {
        XFORMBOX = 0,
        TABBOX = 1,
        NONE = 2
    };

    void setInteractionMode(InteractionMode mode);
    InteractionMode getInteractionMode();

private:
    void createWidget(QWidget* parent);
    void guiCallback();
    int parse(Tcl_Interp *interpreter, int argc, char **argv);
    void getState(McString &state);
    int setState(const McString &state);
    void initFrom(HxPort *refPort);

    void setCurrentDragger();
    void setDragger(int draggerType);
    void setDraggerNode(McHandle<SoDragger> dragger);
    McHandle<SoTransformBoxDragger> createTransformBoxDragger();
    McHandle<SoTabBoxDragger> createTabBoxDragger();

    McBox3f m_box;
    int m_draggerType;

    McHandle<SoDragger> m_dragger;

    SoSFVec3f& translationOfDragger();
    SoSFVec3f& scaleFactorOfDragger();

    void setDraggerBox();
    void getDraggerBox();

    static void draggerFinishCB(void* userData, SoDragger* dragger);
    void draggerInteractionFinish();

    McDArray<QPointer<QRadioButton> > m_radioButtons;

    HxPortBox3D(HxPortBox3D&);
    void operator=(HxPortBox3D&);
};

#endif // HXSEEDBOXPORTHELPER_H

/// @}
