/*
*  File      : SoFrameGrabber.h
*  Class     : SoFrameGrabber
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


#ifndef _HXFRAMEGRABBER_H_
#define _HXFRAMEGRABBER_H_

#include <mclib/McTypedObject.h>
#include <hxcore/HxAmiraWinDLLApi.h>

#include <Inventor/SbLinear.h>
#include <Inventor/SbViewportRegion.h>

class HxFrameRender;
class SoMemoryBuffer2D;

class HXCORE_API HxFrameGrabber: public McTypedObject {

	MC_ABSTRACT_HEADER(HxFrameGrabber);

private :

protected :

	bool m_colorTexture;
	bool m_depthTexture;

	unsigned int m_viewport[4];

public :

	HxFrameGrabber();
	virtual ~HxFrameGrabber();

	/**
	* Describe size of depth component
	*/
	typedef enum {
		// 16bits unsigned short buffer
		DEPTH_16,
		// 32 bits float buffer 
		DEPTH_32
	} DepthComponent;

	/**
	 * Returns the render associated to the grabber
	 */
	virtual HxFrameRender * getFrameRender() = 0;

	/**
	* Define the size of the region we have to grab 
	*/
	void setViewport(const SbVec2s &size);
	void setViewport(const SbViewportRegion &viewport); 
	virtual void setViewport(unsigned int width, unsigned int height);
	
	/**
	* all rendering action done between the ::begin and ::end call will be saved 
	* in the frame grabber, as long as no context change occured.
	*/
	virtual void begin() = 0;
	virtual void end() = 0;

	/**
	 *
	 */
	virtual void render() = 0;

	/**
	* specify if color or depth have to be mapped to texture or not
	*/
	void setRenderToTexture(bool color=false, bool depth=false);

	/**
	* specify the depth mode (16 or 32 bits we want to use
	*/
	void setDepthMode(const DepthComponent depthMode) {};

	/**
	* return the color data of the specified region in a memory buffer
	*/
	virtual int getColorBuffer(SoMemoryBuffer2D *buffer);
	virtual int getColorBuffer(SoMemoryBuffer2D *buffer,int offset_x,int offset_y,int width,int height) = 0;

	/**
	* return the depth  data of the specified region in a memory buffer
	*/
	virtual int getDepthBuffer(SoMemoryBuffer2D *buffer);
	virtual int getDepthBuffer(SoMemoryBuffer2D *buffer,const int offset_x,const int offset_y,const int width,const int height) { return -1; };
};

#endif /* _HXFRAMEGRABBER_H_ */
