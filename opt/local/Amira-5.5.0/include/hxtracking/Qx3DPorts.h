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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_3D_PORTS_H
#define HX_3D_PORTS_H

#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortInfo.h>
#include <hxcolor/HxPortColormap.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortGeneric.h>
#include <hxtracking/Qx3DWidget.h>
#include <hxtracking/hxtrackingAPI.h>

class HXTRACKING_API Hx3DPort : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DPort(Qx3DWidget* parent, HxPort* port);

    ~Hx3DPort();

    HxPort* getPort() const { return port; }

    virtual void render(unsigned int cacheId);
        
    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    void arrange();

  public slots:
    virtual void send();

    virtual void update();

    virtual void destroy(bool ownerToo);

  protected:

    bool isEventHandlingAllowed(HxVREvent* event);

    HxPort* port;
    Hx3DLabel* label;
};

class HXTRACKING_API Hx3DPortButtonList : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortButtonList(Qx3DWidget* parent, HxPortButtonList* port);

    ~Hx3DPortButtonList();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DButton*> buttons;
};

class HXTRACKING_API Hx3DPortToggleList : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortToggleList(Qx3DWidget* parent, HxPortToggleList* port);

    ~Hx3DPortToggleList();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DToggleButton*> buttons;
};

class HXTRACKING_API Hx3DPortRadioBox : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortRadioBox(Qx3DWidget* parent, HxPortRadioBox* port);

    ~Hx3DPortRadioBox();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DRadioButton*> buttons;
};

class HXTRACKING_API Hx3DPortFloatSlider : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortFloatSlider(Qx3DWidget* parent, HxPortFloatSlider* port);

    ~Hx3DPortFloatSlider();

    virtual void update();

    virtual void send();

  protected:
    Hx3DSlider* slider;
};

class HXTRACKING_API Hx3DPortMultiMenu : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortMultiMenu(Qx3DWidget* parent, HxPortMultiMenu* port);

    ~Hx3DPortMultiMenu();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DOptionMenu*> menus;
};

class HXTRACKING_API Hx3DPortOptionMenu : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortOptionMenu(Qx3DWidget* parent, HxPortOptionMenu* port);

    ~Hx3DPortOptionMenu();

    virtual void update();

    virtual void send();

  protected:
    Hx3DOptionMenu* menu;
};

class HXTRACKING_API Hx3DPortFloatTextN : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortFloatTextN(Qx3DWidget* parent, HxPortFloatTextN* port);

    ~Hx3DPortFloatTextN();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DLabel*> labels;
    McDArray<Hx3DTextField*> fields;
};

class HXTRACKING_API Hx3DPortColormap : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortColormap(Qx3DWidget* parent, HxPortColormap* port);

    ~Hx3DPortColormap();

    virtual void update();

    virtual void send();

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

  public slots:
    void changeColormap(int);

  protected:
    Hx3DTextField* minField;
    Hx3DTextField* maxField;
    unsigned int highlightFlag:1;
    Hx3DPopupMenu* popupMenu;
};

class HXTRACKING_API Hx3DPortInfo : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortInfo(Qx3DWidget* parent, HxPortInfo* port);

    ~Hx3DPortInfo();

    virtual void update();
};

class HXTRACKING_API Hx3DPortTime : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortTime(Qx3DWidget* parent, HxPortTime* port);

    ~Hx3DPortTime();

    virtual void update();

    virtual void send();

    void arrange();

  public slots:
    void goStep();
    void goPlay();

  protected:
    Hx3DButton* playBackward;
    Hx3DButton* backward;
    Hx3DSlider* slider;
    Hx3DButton* forward;
    Hx3DButton* playForward;
};

class HXTRACKING_API Hx3DPortButtonMenu : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortButtonMenu(Qx3DWidget* parent, HxPortButtonMenu* port);

    ~Hx3DPortButtonMenu();

    virtual void update();

    virtual void send();

  protected:
    McDArray<Hx3DButton*> buttons;
    McDArray<Hx3DOptionMenu*> menus;
};

class HXTRACKING_API Hx3DPortGeneric : public Hx3DPort
{
    Q_OBJECT

  public:
    Hx3DPortGeneric(Qx3DWidget* parent, HxPortGeneric* port);

    ~Hx3DPortGeneric();

    virtual void update();

    virtual void send();

  protected:
    McDArray<int> types;
    McDArray<Qx3DWidget*> widgets;
};

class HXTRACKING_API Hx3DObject : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DObject(Qx3DWidget* parent, HxObject* object);

    ~Hx3DObject();

    HxObject* getObject() const { return object; }

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    virtual void setScale(float s);

    void arrange();

    void setPosition(const SbMatrix& M);

  public slots:
    void sendViewerMask();
    void update();
    void close();
    void action(int);

  protected:
    static float border;
    HxObject* object;
    Hx3DToggleButton* label;
    Hx3DPopupButton* popupButton;
    McDArray<Hx3DPort*> ports;

    SbMatrix M, MI, refMat;
    unsigned int isMoving:1;
    unsigned int isActive:1;
};

#endif

/// @}
