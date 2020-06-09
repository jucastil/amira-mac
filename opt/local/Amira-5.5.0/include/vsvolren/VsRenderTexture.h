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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_RENDER_TEXTURE_H
#define VS_RENDER_TEXTURE_H

#include "VsVolrenAPI.h"

#include <mcgl/mcgl.h>
#include "VsHandable.h"

class VSVOLREN_API VsRenderTexture : public VsHandable {
	private:
		///  we want no copies of the render texture
		VsRenderTexture&  operator = (const VsRenderTexture& other) { return *this; }
		VsRenderTexture(const VsRenderTexture& other) {}
       
	protected:
		GLuint mTexID;      // result texture Id
		GLuint mFbo;        // offscreen render buffer (fbo) Id
        GLint  mSavedFbo;   // previous attached render buffer (fbo) Id
        GLuint mDepth;      // depth render buffer Id
		GLuint mWidth;      // the render buffer's width
		GLuint mHeight;     // the render buffer's height
private:
        /// use a depth buffer
        bool mUseDepthBuffer;

	public:
        /** Creates a offscreen render buffer of size \c w and \c h with internal  
            texture format \c format. If \c useDepthTexture is true a depth render buffer of the 
            same size will be created.

            \param w                render buffers width
            \param h                render buffers height
            \param format           internal texture format
            \param useDepthBuffer   if true a depth buffer will be created in addition to
                                    the offscreen render buffer
            
        */
		VsRenderTexture(GLuint w, GLuint h, GLuint format, bool useDepthBuffer = true);
		~VsRenderTexture();
        
        /// get buffer width 
        unsigned int width()  { return mWidth;  }
        
        /// get buffer height
        unsigned int height() { return mHeight; }

        /// attach render texture as render target instaed of framebuffer
        void attach();

        /// release render texture and reattach framebuffer as render target 
		void detach();

        /// bind render texture   
		void bind();

        /// unbind render texture  
        void unbind();
        
        /// check framebuffer object's status
        void checkFramebufferStatus();
};

#endif

/// @}
