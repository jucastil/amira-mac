/*
*  File      : HxFrameRender.h
*  Class     : HxFrameRender
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


#ifndef _HXFRAMERENDER_H_
#define _HXFRAMERENDER_H_

#include <Inventor/SbViewportRegion.h> 
#include <mcgl/mcgl.h>

class QxViewer;
class SoMemoryBuffer2D;

class HxFrameRender {

protected :

	bool	m_isInitialized;
	bool	m_isAvailable;

	GLuint	m_userViewport[4];

	// Helper for debugging purpose
	int checkGlError(const char *msg);

	// Draw the given texture to the viewport
	void mapTextureToViewport(	GLuint texID, GLenum texTarget,
								GLuint off_x, GLuint off_y,
								GLuint width, GLuint height );

public :

	HxFrameRender();
	virtual ~HxFrameRender();

	virtual bool isAvailable() { return m_isAvailable; }

	virtual void setViewport(const SbVec2s size);
	virtual void setViewport(GLuint width, GLuint height);
	virtual void setViewport(const SbViewportRegion viewport);

	virtual bool render(QxViewer *viewer, SoMemoryBuffer2D *memoryBuffer) = 0;
};

#endif /* _HXFRAMERENDER_H_ */
