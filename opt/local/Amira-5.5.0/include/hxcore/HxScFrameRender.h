/*
*  File      : HxScFrameRender.h
*  Class     : HxScFrameRender
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


#ifndef _HXSCFRAMERENDER_H_
#define _HXSCFRAMERENDER_H_

#include <hxcore/HxFrameRender.h>
#include <hxcore/SoFrameBuffer.h>

class SoMemoryBuffer2D;

class HxScFrameRender: public HxFrameRender {

private :

	SoFrameBuffer	*m_fbo;

	void transferFromMemory(SoMemoryBuffer2D *srcBuf);

protected :

public :

	HxScFrameRender();
	virtual ~HxScFrameRender();

	virtual bool render(QxViewer *viewer, SoMemoryBuffer2D *memoryBuffer);
};

#endif /* _HXSCFRAMERENDER_H_ */
