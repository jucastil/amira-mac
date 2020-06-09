/*
*  File      : HxScFrameGrabber.h
*  Class     : HxScFrameGrabber
*  
*  Author(s) : Jerome Lague
*  Date      : 8/6/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXSCFRAMEGRABBER_H_
#define _HXSCFRAMEGRABBER_H_

#include <hxcore/HxFrameGrabber.h>

class SoFrameBuffer;

class HXCORE_API HxScFrameGrabber: public HxFrameGrabber {

	MC_ABSTRACT_HEADER(HxFrameGrabber);

private :

	bool m_isInitialized;

	SoFrameBuffer *m_fbo;

protected :

public :

	HxScFrameGrabber();
	virtual ~HxScFrameGrabber();

	virtual HxFrameRender * getFrameRender();

	virtual void begin();
	virtual void end();

	virtual void render();

	virtual int getColorBuffer(SoMemoryBuffer2D *buffer,int offset_x,int offset_y,int width,int height);

	/**
	* return the texture ID attached to the color buffer, this texture ID
	* is valid only in the context used for frame grabbing
	*/
	int getColorTextureID();
	int getColorTextureFormat();
	int getColorTextureTarget();
};

#endif /* _HXSCFRAMEGRABBER_H_ */
