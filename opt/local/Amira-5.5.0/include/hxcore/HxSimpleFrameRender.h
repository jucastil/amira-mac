/*
*  File      : HxSimpleFrameRender.h
*  Class     : HxSimpleFrameRender
*  
*  Author(s) : Jerome Lague
*  Date      : 7/17/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXSIMPLEFRAMERENDER_H_
#define _HXSIMPLEFRAMERENDER_H_

#include <hxcore/HxFrameRender.h>

class HxSimpleFrameRender: public HxFrameRender {

public :

	HxSimpleFrameRender();
	virtual ~HxSimpleFrameRender();

	virtual bool render(QxViewer *viewer, SoMemoryBuffer2D *memoryBuffer);
};

#endif /* _HXSIMPLEFRAMERENDER_H_ */
