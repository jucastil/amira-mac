#ifndef HX_PORT_FONT_SELECTION
#define HX_PORT_FONT_SELECTION

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                  |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxPort.h>
#include <hxcore/QxGuardedPtr.h>
#include <mclib/McColor.h>

class HxObject;
class QWidget;
class QFont;
class QLabel;
class QPushButton;
class QxChooseColorButton;

/**
 * This class defines a port used to select a font.
 * It provides a preview of the current font, a button
 * used to launch a font selection dialog and another
 * to select the font color.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
 */

class HXCORE_API HxPortFontSelection : public HxPort
{
    MC_ABSTRACT_HEADER( HxPortFontSelection );

public:

    /** 
     * Constructor.
     */
    HxPortFontSelection(HxObject* object, const char* name);

    /** 
     * Destructor.
     */
    virtual ~HxPortFontSelection();

    /** 
     * To know which button has been pressed.
     */
    enum { NEW_FONT = 1, NEW_FONT_COLOR = 2 };

    /** 
     * To get the current font.
     */
    const QFont* getFont() const; 

    /** 
     * To get the current font's name.
     */
    const char* getFontName() const;

    /** 
     * To get the current font's point size.
     */
    int getFontSize() const;

    /** 
     * To know if the current font is bold.
     */
    bool isBoldFont() const;

    /** 
     * To know if the current font is italic.
     */
    bool isItalicFont() const;

    /** 
     * To get the font color.
     */
    const McColor& getFontColor() const;

    /** 
     * To set the current font.
     */
    void setFont(const QFont* font);

    /** 
     * To set the font name.
     */
    void setFontName(const char* fontName);

    /** 
     * To set the font size.
     */
    void setFontSize(int fontSize);

    /** 
     * To set the font's bold flag.
     */
    void setBoldFont(bool isBold);
    
    /**
     * To set the font's italic flag.
     */
    void setItalicFont(bool isItalic);

    /** 
     * To set the font color.
     */
    void setFontColor(const McColor& fontColor);  

    /** 
     * To get a textual representation of the current font.
     */
    const McString getFontDescription() const;


protected:

    /** 
     * The current font.
     */
    QFont* m_font;

    /** 
     * The current font color.
     */
    McColor m_fontColor;

    /** 
     * The label used to display the font name and size.
     */
    QxGuardedPtr<QLabel> m_fontLabel;

    /**
     * The button used to select the current font.
     */
    QxGuardedPtr<QPushButton> m_fontSelectBtn;

    /** 
     * The button used to select the font color.
     */
    QxGuardedPtr<QxChooseColorButton> m_colorBtn;

    /** 
     * Inherited from HxPort.
     */
    virtual void createWidget(QWidget* parent);

    /**
     * Inherited from HxPort.
     */
    virtual void guiCallback();

    /** 
     * Inherited from HxPort.
     */
    virtual void getState(McString& state);

    /**
     * Inherited from HxPort.
     */
    virtual int setState(const McString& state);

    /** 
     * Inherited from HxPort.
     */
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

    /** 
     * Called to update the font label.
     * Font label looks like: <FontName> (<FontSize> pt.)
     * The label's font is the same than the selected one.
     */
    void updateFontLabel();

    /**
     * Called when the font changed.
     */
    void fontChanged();

};

#endif //HX_PORT_FONT_SELECTION
