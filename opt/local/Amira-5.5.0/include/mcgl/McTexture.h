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

/// @addtogroup mcgl mcgl
/// @{
#ifndef __MC_TEXTURE_H__
#define __MC_TEXTURE_H__

/** 
    This class is a wrapper around OpenGL textures. 
    It creates a copy of the data in the create function. 
    In the bindTexture function, an OpenGL texture is created for each context.
    */

class MCGL_API McTexture
{
public:
    McTexture();
    ~McTexture();

    /// Create a RGBA byte 1D texture
    /// The pixels are copied. This function can be called from any thread
    /// The size represents the number of elements. Each element is represented by 4 bytes
    void create1D(const GLvoid *pixels, int size);

    void destroy();

    bool isCreated() const {return (mPixels != 0);}

    /// This function must be called in the render function
    bool bindTexture(unsigned int context = 1);

private:
    /**************************************************************************/
    class McTextureBase
    {
        public:

        McTextureBase();
        ~McTextureBase();
        friend class McTexture;
        protected:

        void createRGBAbyte(GLenum target, GLvoid *pixels, int size, unsigned int context);
        void bindTexture();

        GLuint mId;
        unsigned int mContext;
        bool bIsCreated;
        GLenum mTarget;

    };
    /**************************************************************************/
    void createPixels(const GLvoid *pixels, int size);
    void deletePixels();
    void deleteTextures();

    McDArray<McTexture::McTextureBase* > mTextures;
    GLenum mTarget;
    unsigned char *mPixels;
    int mSize;    
    bool mNewTexture;
};

#endif // __MC_TEXTURE_H__


/// @}
