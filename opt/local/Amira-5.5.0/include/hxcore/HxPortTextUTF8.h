#ifndef HX_PORT_TEXT_UTF8
#define HX_PORT_TEXT_UTF8

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxPortText.h>

class HxObject;
class HxEditor;

/**
 * This class defines a specific HxPortText with UTF8 management.
 * For the moment, the only limitation is when setting UTF8 values
 * via the console since this last manages QString with Latin1 encoding.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
 */

class HXCORE_API HxPortTextUTF8 : public HxPortText
{
    MC_ABSTRACT_HEADER( HxPortTextUTF8 );

public :

    /** 
     * Constructors.
     */
    HxPortTextUTF8(HxObject* object, const char* name);
    HxPortTextUTF8(HxEditor* editor, const char* name);

    /**
     * Destructor.
     */
    virtual ~HxPortTextUTF8();

    /**
     * To get the unicode representation of the current text.
     */
    const wchar_t* getUnicodeValue();


protected:

    /** 
     * To store the unicode value.
     */
    wchar_t* m_unicodeValue;

    /** 
     * Inherited from HxPortText.
     */
    virtual void guiCallback();
    virtual void setLineEditText(const char* str);

    /** 
     * To update the stored unicode value.
     * Called when value is changed.
     */
    void updateUnicodeValue();

};

#endif // HX_PORT_TEXT_UTF8
