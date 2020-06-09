/*
*  File      : HxSimpleFrameGrabber.h
*  Class     : HxSimpleFrameGrabber
*  
*  Author(s) : Jerome Lague
*  Date      : 7/11/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXSIMPLEFRAMEGRABBER_H_
#define _HXSIMPLEFRAMEGRABBER_H_

#include <hxcore/HxFrameGrabber.h>

class HxSimpleFrameRender;

class HXCORE_API HxSimpleFrameGrabber: public HxFrameGrabber {

	MC_ABSTRACT_HEADER(HxFrameGrabber);

private :

	bool m_isInitialized;

public :

	HxSimpleFrameGrabber();
	virtual ~HxSimpleFrameGrabber();

	virtual HxFrameRender * getFrameRender();

	virtual void begin();
	virtual void end();

	virtual void render();

	virtual int getColorBuffer(SoMemoryBuffer2D *buffer,int offset_x,int offset_y,int width,int height);
};

#endif /* _HXSIMPLEFRAMEGRABBER_H_ */
