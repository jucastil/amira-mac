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
#ifndef HX_3D_WIDGET_H
#define HX_3D_WIDGET_H

#include <QThread>
#include <QObject>
#include <Q3IntDict>
#include <QMutex>
#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>

#include <hxtracking/hxtrackingAPI.h>
#include <hxtracking/HxVREvent.h>

#define GUI_BORDER_WIDTH 0.18
#define EPS_WIDTH 0.008
#define DARK_GREY 0.5
#define MEDIUM_GREY 0.75

class SoNode;
class Hx3DWand;

class HXTRACKING_API Qx3DWidget : public QObject
{
    Q_OBJECT

  public:
    Qx3DWidget(Qx3DWidget* parent);

    ~Qx3DWidget();
    
    Qx3DWidget* parent() const { return parentWidget; }

    bool isVisible() const { return visibleFlag; }

    const SbVec2f& getPosition() const { return position; }

    virtual void setPosition(const SbVec2f& position);

    void setPosition2(float x, float y) { setPosition(SbVec2f(x,y)); }

    const SbVec2f& getSize() const { return size; }

    virtual void setSize(const SbVec2f& size);

    void setSize2(float x, float y) { setSize(SbVec2f(x,y)); }

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    void reparent(Qx3DWidget* newParent);

    virtual void touch();

    static SoNode* getSceneGraph();

    static void handleEventAll(Hx3DWand* wand, HxVREvent* event);

    static McDArray<Qx3DWidget*>& get3DTopLevelWidgets();

    static void scheduleDelete(Qx3DWidget* widget);

    virtual SbVec2f sizeHint();

    virtual void setScale(float scaleFactor);

    static void setScaleAll(float scaleFactor);

  public slots:
    virtual void show();

    virtual void hide();

  protected:
    SbVec2f size;
    SbVec2f position;
    Qx3DWidget* parentWidget;
    unsigned int visibleFlag:1;
    McDArray<Qx3DWidget*> children;

    static void setScale(SbMatrix& M, SbMatrix& MI, float scale);
};

class HXTRACKING_API Hx3DLabel : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DLabel(Qx3DWidget* parent);

    ~Hx3DLabel();

    void setText(const QString& text);

    QString getText() const { return text; }

    void setAutoResize(bool);

    bool isAutoResize() const { return autoResizeFlag; }

    void setForeground(const SbColor&);

    virtual void render(unsigned int cacheId);

    bool isBold() const { return boldFlag; }

    void setBold(bool);

    bool isItalic() const { return italicFlag; }

    void setItalic(bool);

    virtual SbVec2f sizeHint();

    void setAlignment(int);

    virtual void setSize(const SbVec2f& size);

  protected:
    unsigned int autoResizeFlag:1;
    unsigned int boldFlag:1;
    unsigned int italicFlag:1;
    QString text;
    SbColor foreground;
    SbVec2f texCoord;
    int nc,width,height;
    unsigned char* texture;
    int alignFlags;

    struct TexturesCreateStruct {
        int isInitialized;
        QMutex contextMutex;
        unsigned int textureName;
    };

    QMutex instanceMutex;
    Q3IntDict<TexturesCreateStruct> textures;

    void freeTexture();
    virtual void createTexture();
    void checkTexture(unsigned int cache, int internalFormat, int format);

    void renderLabel(const SbVec2f& pos, const SbVec2f& size, unsigned int);
};

class HXTRACKING_API Hx3DButton : public Hx3DLabel
{
    Q_OBJECT

  public:
    Hx3DButton(Qx3DWidget* parent);

    ~Hx3DButton();

    void setBackground(const SbColor&);

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    bool isDown() const { return downFlag; }

    void setDown(bool value) { downFlag=value; }

  signals:
    void pressed();
    void clicked();

  protected:
    SbColor background;
    unsigned int downFlag:1;
    unsigned int highlightFlag:1;
};

class HXTRACKING_API Hx3DToggleButton : public Hx3DButton
{
    Q_OBJECT

  public:
    Hx3DToggleButton(Qx3DWidget* parent);

    ~Hx3DToggleButton();

    bool isSet() const { return setFlag; }

    void set(bool value) { setFlag = value; }

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    void setToggleColor(const SbColor& c) { toggleColor=c; }

    void useBitmap(bool v) { bitmapFlag=v; }

  protected:
    SbColor toggleColor;
    unsigned int setFlag:1;
    unsigned int bitmapFlag:1;
    unsigned int radioFlag:1;
    void renderTogglePart();
    void renderRadioTogglePart();
    virtual void createTexture();
};

class HXTRACKING_API Hx3DRadioButton : public Hx3DToggleButton
{
  public:
    Hx3DRadioButton(Qx3DWidget* parent);
};

class HXTRACKING_API Hx3DSlider : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DSlider(Qx3DWidget* parent);

    ~Hx3DSlider();

    float value() const { return theValue; }

    float minValue() const { return theMin; }

    float maxValue() const { return theMax; }

    bool setMinMax(float min, float max);

    bool setValue(float val);

    void setGap(float width);

    void setTracking(bool v) { trackingFlag=v; }

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    virtual void setSize(const SbVec2f& size);

    virtual void setPosition(const SbVec2f& pos);

  signals:
    void valueChanged();

  protected:
    float theValue;
    float theMin;
    float theMax;
    McString fmt;
    SbColor color;
    Hx3DLabel* label;
    float offset;
    float gap;
    unsigned int highlightFlag:1;
    unsigned int draggingFlag:1;
    unsigned int trackingFlag:1;
};


class HXTRACKING_API Hx3DOptionMenu : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DOptionMenu(Qx3DWidget* parent);

    ~Hx3DOptionMenu();

    int count() const;

    void insertItem(const QString& text, int index=-1);

    void removeItem(int index=-1);

    void clear();

    QString currentText() const;

    QString text(int index) const;

    void changeItem(const QString& text, int index);

    int currentItem() const;

    virtual void setCurrentItem(int index);

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    virtual void setSize(const SbVec2f& size);

    virtual void setPosition(const SbVec2f& pos);

    virtual SbVec2f sizeHint();

  signals:
    void activated(int index);

  protected:
    int current;
    int highlightedItem;
    SbColor color;
    Hx3DLabel* label;
    McDArray<Hx3DLabel*> items;
    unsigned int popupFlag:1;
    unsigned int highlightFlag:1;
};


class HXTRACKING_API Hx3DTextField : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DTextField(Qx3DWidget* parent);

    ~Hx3DTextField();

    QString getText() const { return label->getText(); }

    float getNum() const;

    void setText(const QString& text);

    void setNum(float value);

    void setFormat(const char* f) { format=f; }

    void setMinMax(float a, float b) { minVal=a; maxVal=b; }

    virtual SbVec2f sizeHint();

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    virtual void setSize(const SbVec2f& size);

    virtual void setPosition(const SbVec2f& pos);

  signals:
    void valueChanged();

  protected:
    Hx3DLabel* label;
    unsigned int highlightFlag:1;
    unsigned int slidingFlag:1;
    McString format;
    float minVal, maxVal;
    float lastVal;
    float lastY;
};

class HXTRACKING_API Hx3DPopupMenu : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DPopupMenu(Qx3DWidget* parent);

    ~Hx3DPopupMenu();

    int count() const;

    void insertMenu(const QString& text, Hx3DPopupMenu* menu, int id=-1, int index=-1);

    void insertItem(const QString& text, int id=-1, int index=-1);

    void removeItem(int id);

    void removeItemAt(int index);

    void clear();

    QString text(int id) const;

    QString textAt(int index) const;

    void changeItem(const QString& text, int id);

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    virtual void focusLost();

    void popup(const SbVec2f& pos, int indexAtPoint=0);

  signals:
    void activated(int id);

  protected:
    struct Item {
        int id;
        Hx3DLabel* label;
        Hx3DPopupMenu* menu;
    };

    SbColor color;
    int highlightedItem;
    McDArray<Item> items;
    Hx3DPopupMenu* master;
};

class HXTRACKING_API Hx3DPopupButton : public Hx3DButton
{
    Q_OBJECT

  public:
    Hx3DPopupButton(Qx3DWidget* parent);

    ~Hx3DPopupButton();

    virtual void render(unsigned int cacheId);

    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    Hx3DPopupMenu* popupMenu() const { return thePopupMenu; }

  protected:
    Hx3DPopupMenu* thePopupMenu;
};

class HXTRACKING_API Hx3DColorButton : public Qx3DWidget
{
    Q_OBJECT

  public:
    Hx3DColorButton(Qx3DWidget* parent);

    ~Hx3DColorButton();

    virtual void render(unsigned int cacheId);

    void setColor(float r, float g, float b) {m_color.setValue(r,g,b);}

  protected:
    SbColor m_color;
};

#endif

/// @}
