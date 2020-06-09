/*
*  File      : HxDisplayDate.h
*  Class     : HxDisplayDate
*  
*  Author(s) : Jerome Lague
*  Date      : 3/16/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXDISPLAYDATE_H_
#define _HXDISPLAYDATE_H_

class QDateTime;

#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFontSize.h>
#include <hxcore/HxPortToggleList.h>

#include <hxtime/HxDisplayValue.h>

class HXTIME_API HxDisplayDate: public HxDisplayValue {

    HX_HEADER(HxDisplayDate);
public :

    HxPortToggleList portOptions3;
    HxPortFontSize   portPointSize;
    HxPortToggleList portDisplay;
    HxPortGeneric    portDateFormat;
    HxPortGeneric    portTimeFormat;

    HxDisplayDate();

    /// Update method.
    virtual void update();

protected:

    enum { DATE=0, TIME=1 };

    virtual ~HxDisplayDate();

    void buildValueText();

private:

    McString buildDateText(const QDateTime &dateTime);
    McString buildTimeText(const QDateTime &dateTime);
};

#endif /* _HXDISPLAYDATE_H_ */
