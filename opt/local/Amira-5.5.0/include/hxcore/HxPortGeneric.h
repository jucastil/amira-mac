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
#ifndef HX_PORT_GENERIC_H
#define HX_PORT_GENERIC_H

#include <mclib/McColor.h>

#include <hxcore/HxPort.h>

class McColor;
class QxLineEdit;
class QCheckBox;
class QRadioButton;
class QComboBox;
class QPushButton;
class QLabel;
class QxChooseColorButton;
class QStackedWidget;

#define ITEM_FLOAT_TEXT     0
#define ITEM_CHECK_BOX      1
#define ITEM_RADIO_GROUP    2
#define ITEM_COMBO_BOX      3
#define ITEM_PUSH_BUTTON    4
#define ITEM_LABEL          5   
#define ITEM_COLOR          6   
#define ITEM_TEXT           7


////////////////////////////////////////////////////////////////////////////////
struct HXCORE_API HxPortGenericItem
{
    int     id;
    int     type;
    int     newFlag;
    int     sensitivity;
    bool    mVisible;

    // the widgets are put as to QStackedWidgets as widget index 0
    // index i is a dummy widget which gets active if setVisible(false) is called
    // this prevents layout changes on visibility changes
    McDArray< QxGuardedPtr<QStackedWidget> >
            mWidgets;

    HxPortGenericItem()
    :   id          ( -1 )
    ,   type        ( -1 )
    ,   newFlag     ( 0 )
    ,   sensitivity ( 1 )
    ,   mVisible    ( true )
    {
    }

    virtual ~HxPortGenericItem() {}

    //Initialize item from reference item
    virtual void initFrom( HxPortGenericItem* item ){}

    void setVisible( bool inFlag );
    void setSensitivity( bool inFlag );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1) = 0;

    void cleanup();

    void addWidget( HxPort * inBasePort, QWidget * inWidget, QxPortLayout * ioLayout, int pos=-1);
};

struct HXCORE_API HxPortGenericText : public HxPortGenericItem
{
  int nColumns:16;
  McString value;
  QxGuardedPtr<QxLineEdit> lineEdit;

  virtual void initFrom( HxPortGenericItem* item );

  virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};

struct HXCORE_API HxPortGenericFloatText : public HxPortGenericText
{
  float value;
  McString format;

  virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);

  virtual void initFrom( HxPortGenericItem* item );

  /// Sets new text format in FloatText items
  void setFormat(const McString &newFormat);
};


struct HXCORE_API HxPortGenericCheckBox : public HxPortGenericItem
{
    int                     value;
    McString                label;
    QxGuardedPtr<QCheckBox> checkBox;

    virtual void initFrom( HxPortGenericItem* item );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};


struct HXCORE_API HxPortGenericRadioGroup : public HxPortGenericItem
{
    int                                    value;
    McDArray<McString>                     labels;
    McDArray< QxGuardedPtr<QRadioButton> > buttons;
    unsigned int                           buttonSensitivity;

    virtual void initFrom( HxPortGenericItem* item );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};


struct HXCORE_API HxPortGenericComboBox : public HxPortGenericItem
{
    int                     value;
    McDArray<McString>      labels;
    QxGuardedPtr<QComboBox> comboBox;
    
    virtual void initFrom( HxPortGenericItem* item );
    void updateItems();
    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);

};


struct HXCORE_API HxPortGenericPushButton : public HxPortGenericItem
{
    McString                   label;
    QxGuardedPtr<QPushButton> button;

    virtual void initFrom( HxPortGenericItem* item );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};


struct HXCORE_API HxPortGenericLabel : public HxPortGenericItem
{
    McString             label;
    QxGuardedPtr<QLabel> qlabel;

    virtual void initFrom( HxPortGenericItem* item );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};


struct HXCORE_API HxPortGenericColor : public HxPortGenericItem
{
    McColor                           color;
    QxGuardedPtr<QxChooseColorButton> qbutton;
    
    virtual void initFrom( HxPortGenericItem* item );

    virtual void widgetCreate( HxPort * inBasePort, QxPortLayout * ioLayout, int pos=-1);
};




////////////////////////////////////////////////////////////////////////////////

/** Generic Amira port. This port can be customized by inserting several
    different predefined user interface components. The design goal of
    this class was ease-of-use. Thus flexibility is limited. If you want
    to create a port with custom GUI components you should derive directly
    from HxPort and use Qt components.
*/

class HXCORE_API HxPortGeneric : public HxPort {

  MC_ABSTRACT_HEADER(HxPortGeneric);

  public:
    /// Constructor for objects.
    HxPortGeneric(HxObject* object, const char* name);

    /// Constructor for editors.
    HxPortGeneric(HxEditor* editor, const char* name);
  
    /// Destructor.
    virtual ~HxPortGeneric();

    /** Inserts a simple text label.
        In order to set the text field to e.g. "New string", use 
        setValue(id,"New string"). In order to query the value 
        of the text field, use getStringValue(id, value). nColumns specifies 
        the width of the field. index specifies the position where the 
        text field should be inserted. If this is -1 the text field is 
        appended after all other elements.*/
    void insertText(int id, int nColumns, int index=-1);

    /** Inserts an integer text field. In order to set the text field to
        e.g. 27, use setValue(id,27). In order to query the value of the
        text field, use getValue(id). nColumns specifies the width of
        the text field. index specifies the position where the text field
        should be inserted. If this is -1 the text field is appended after
        all other elements. */
    void insertIntText(int id, int nColumns, int index=-1);

    /** Inserts a floating point text field. In order to set the field to
        e.g. 5.5, use setValue(id,5.5). In order to query the value of the
        field, use getFloatValue(id). format specifies the format of the
        field in printf syntax. nColumns specifies the width of the field.
        index specifies the position where the text field should be inserted.
        If this is -1 the text field is appended after all other elements. */
    void insertFloatText(int id, const char* format, int nColumns, int index=-1);

    /** Inserts a check box with a label. In order to set the check box
        use setValue(id,value). In order to query the value of the check
        box use getValue(id). */
    void insertCheckBox(int id, const char* label, int index=-1);
   
    /** Inserts a group of n radio buttons. The button labels are specified
        via the pointer array @c labels. In order to set for example the
        second radio button (and unset all others) use setValue(id,1). In
        order to query which radio button is checked use getValue(id). */
    void insertRadioGroup(int id, int n, const char** labels, int index=-1);

    /** Inserts a combo box with n entries. The entries' labels are
        specified via the pointer array @c labels. In order to select for
        example entry 2 use setValue(id,2). In order to query which entry
        is selected use getValue(id). */
    void insertComboBox(int id, int n, const char** labels, int index=-1);

    /** Inserts a simple push button. label specifies the label of the
        button. In order to simulate a button press event use
        setValue(id,1). In order to check if the button has been pressed
        use the method isItemNew(id). */
    void insertPushButton(int id, const char* label, int index=-1);

    /** Inserts a color button. The button can be used to specify an RGB 
        color. Pushing the button opens the color dialog, In order to set
        the color use the method setColor(int id, const McColor& color).
        In order to query the color use getColor(int id, McColor& color). */
    void insertColorButton(int id, int index=-1);

    /** Inserts a simple label. The label text can be changed by invoking
        setValue(id,"new textstring"). Calling setValue(id,floatval) resp.
        setValue(id,intval) changes the label text through the appropriate
        printf formats (%g, %d). */
    void insertLabel(int id, const char* label, int index=-1);

    /// Sets the value of the specified element.
    void setValue(int id, int value);

    /** Sets the value of a float text field. The method can also be used
        to set the value of other elements. In this case the argument is
        rounded to the next integer value or formatted via printf in case of
        a label. */
    void setValue(int id, float value);

    /** Set method with string argument. If the specified element is a
        combo box or a radio group the first combo box entry or the first
        radio button with a label equal to value is selected. This methods
        can be used to change label texts.  For other elements the string
        value is converted to a number. */
    void setValue(int id, const char* value);

    /** Sets the color of a color button. The element specified by id must
        be a color button, otherwise nothing happens. */
    void setColor(int id, const McColor& color);

    /// Get value of integer-type elements.
    int getValue(int id);

    /// Get value of a float text field.
    float getFloatValue(int id);

    /** Get value as a string. If the specified element is a combo box or
        a radio group the label of the selected combo box entry or of the
        selected radio button is returned. */
    void getStringValue(int id, McString& result);

    /** Returns the color of a color button. The element specified by id must
        be a color button, otherwise the result is undefined. */
    void getColor(int id, McColor& color);

    /** Sets the sensitivity of an element. If an element is insensitive it
        is grayed out and accepts no user input. On default, all new elements
        are sensitive. */
    void setSensitivity(int id, int value);

    /// Returns the sensitivity of an element.
    int getSensitivity(int id) const;

    /** Sets the sensitivity of a button in a radio group box. */
    void setSensitivity(int id, int whichButton, int value);

    /// Returns the sensitivity of a button in a radio group box.
    int getSensitivity(int id, int whichButton) const;

    /** Sets the visibility of an element.On default, all new elements
        are visible. */
    using HxPort::setVisible;
    void setVisible( int inId, bool inFlag );

    /// Returns the visibilty of an element.
    int visible( int inId ) const;

    /// Deletes the specified elements.
    void deleteItem(int id);

    /** Check if specified element is new. While the standard method
        HxPort::isNew() returns true is any element has been modified
        the method allows you to detect which element was modified. */
    bool isItemNew(int id);

    /// Returns the number of elements
    int getNum();

    /// Overloaded untouch method also untouches all items.
    virtual void untouch( bool untouchConnectedPorts = true );

    /// Tcl command interface of port.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    HxPortGenericItem* findItem(int id) const;

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  protected:
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    virtual void destroyWidget();

    McDArray<HxPortGenericItem*> items;
    QxGuardedPtr<QxPortLayout> itemsLayout;
};

#endif

/// @}
