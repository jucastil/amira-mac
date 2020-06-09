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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_GL_VIEW_STATES
#define HX_GL_VIEW_STATES

#include <hxmeasure/HxMeasureWinDLLApi.h>

#include <Inventor/SbLinear.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>
#include <mclib/McMat4f.h>

#include <hxcore/hxgl.h>

/** A class to save part of the openGL rendering state.
This one saves the model and projection matrix and the viewport to 
provide a mapping between world and screen coordinates.
*/
class HXMEASURE_API HxGLViewState {
public:
    ///
    HxGLViewState ();
    ///
    ~HxGLViewState ();

    /// save the actual GL state. 
    void save ();
    /// restore GL to the saved state.
    void restore ();
    
    bool saved() {  return mAlreadySaved;  }
	
    /** map the worldcoordinates w to the screencoordinates s 
    (including z buffer value).
    */
    void mapWorldToScreen (const McVec3f& w, McVec3f& s) const;
    /** return w mapped to the screen. 
    */
    McVec3f mapWorldToScreen (const McVec3f& w) const {
        McVec3f sc;
        mapWorldToScreen (w, sc);
        return sc;
    };

    /** map screen to world coordinates.
    */
    void mapScreenToWorld (const McVec3f& screen, McVec3f& world) const;
    /** return screen mapped to world coordinates.
    */
    McVec3f mapScreenToWorld (const McVec3f& sc) const {
        McVec3f w;
        mapScreenToWorld (sc, w);
        return w;
    };

    /** calculates the length of a vector in world coordinates at pos that 
    shifts in screen coordinates by one pixel.
    */
    float getScreenUnit (McVec3f& pos) const {
        McVec3f scPos;
        mapWorldToScreen (pos, scPos);
        scPos[0] += 1.0;
        McVec3f tmp;
        mapScreenToWorld (scPos, tmp);
        return (tmp - pos).length ();
    };
    /** calculates the world coordinate vector at pos that shifts in 
    screen coordinates one pixel in x direction.
    */
    McVec3f getScreenX (McVec3f& pos) const {
        McVec3f scPos;
        mapWorldToScreen (pos, scPos);
        scPos[0] += 1.0;
        McVec3f tmp;
        mapScreenToWorld (scPos, tmp);
        return (tmp - pos);
    };
    /** calculates the world coordinate vector at pos that shifts in 
    screen coordinates one pixel in y direction.
    */
    McVec3f getScreenY (McVec3f& pos) const {
        McVec3f scPos;
        mapWorldToScreen (pos, scPos);
        scPos[1] += 1.0;
        McVec3f tmp;
        mapScreenToWorld (scPos, tmp);
        return (tmp - pos);
    };
    /** calculates the world coordinate vector at pos that shifts in 
    screen coordinates one 'pixel' in z direction.
    Means away from the camera.
    */
    McVec3f getScreenZ (McVec3f& pos) const {
        McVec3f scPos;
        mapWorldToScreen (pos, scPos);
        // move towards 0 means towards the camera 
        scPos[2] -= scPos[2] * 0.1;
        McVec3f tmp;
        mapScreenToWorld (scPos, tmp);
        tmp -= pos;
        tmp.normalize ();
        tmp *= -getScreenUnit (pos);
        return tmp;
    }

    McVec3f shiftScreenZ(McVec3f& pos, float multFactor = 10.0f) const {
        McVec3f scPos, scPos2;
        mapWorldToScreen (pos, scPos);
        // move towards 0 means towards the camera 
        scPos[2] -= scPos[2] * 0.1;
        McVec3f tmp;
        mapScreenToWorld (scPos, tmp);
        tmp -= pos;
        tmp.normalize ();
        tmp *= -multFactor*getScreenUnit (pos);

        // The point was not clipped before the offset was added.
        // Check that it is still not clipped afterwards.
        // If necessary, reduce the offset.
        if (scPos[2]>0) {
            mapWorldToScreen (pos-tmp, scPos2);
            while (scPos2[2]<0) {
                tmp *= 0.2f;
                mapWorldToScreen (pos-tmp, scPos2);
            }
        }
        return pos-tmp;
    }

    McVec3f mapScreenToDevice (const McVec3f& pos) const {
        return McVec3f(pos[0]*viewPort[2],pos[1]*viewPort[3],0.f);
    }

    McVec2f getViewportSize() const { return McVec2f(viewPort[2],viewPort[3]); }

    private:
        bool mAlreadySaved;
        ///
        GLint viewPort[4];
        ///
        float model[4][4];
        ///
        float proj[4][4];
        ///
        McMat4f projMatrix;
        ///
        McMat4f invProjMatrix;
};

/** A class to save part of the OpenGL rendering state.
This one saves the frame buffer and the depth buffer. 
Only the frame buffer will be restored due to problems
with different GL implementations.
*/
class HXMEASURE_API HxGLBufferState
{
public:
    /// Constructor.
    HxGLBufferState();

    /// Destructor.
    ~HxGLBufferState();

    /** Saves the frame buffer and the depth buffer in main memory.
    When this method is called an OpenGL context should have
    been set using wglMakeCurrent() or glXMakeCurrent(). */
    void save ();

    /** Restores the framebuffer, but not the depth buffer.
    When this method is called an OpenGL context should have
    been set using wglMakeCurrent() or glXMakeCurrent(). */
    void restore ();

    /// get zbuffer at screen pos. 
    float getZBuffer (const McVec2f& screen);

    /// get zbuffer at screen pos. 
    float getZBuffer (const SbVec2s& screen) {
        return getZBuffer (McVec2f (screen[0], screen[1]));
    };

    // get the whole zBuffer
    float * getZBuffer() {return zBuffer; };

private:
    ///
    int viewPort[4];
    ///
    float* zBuffer;
    //
    unsigned char* rgbaBuffer;
    ///
    float depthRange[2];
};

/** A class to save part of the openGL rendering state.
This one saves the state of the first 8 lights of GL.
8 lights is the minimum that a GL implementation has to
provide and is thought to be sufficient.
*/
class HXMEASURE_API HxGLLightState {
    public:
        /// save the lights.
        void save ();
        /// restore the lights.
        void restore ();
     
    private:
        class Light {
            public:
                Light () {
                    enabled      = false;
                    spotExp      = 0.f;
                    spotCutoff   = 0.f;
                    constAtt     = 0.f;
                    linAtt       = 0.f;
                    quadAtt      = 0.f;
					
                    for (int i=0; i<4;++i) 
                        ambient[i]  = diffuse[i]  = specular[i]  = position[i]  = 0.f;
                    
                    spotDir[0]  = spotDir[1]  = spotDir[2]  = 0.f;

                };
                Light (int no);
                void restore (int no);
            private:
                GLboolean enabled;
                float ambient[4];
                float diffuse[4];
                float specular[4];
                float position[4];
                float spotDir[3];
                float spotExp;
                float spotCutoff;
                float constAtt;
                float linAtt;
                float quadAtt;
        };

    Light li[8];
};

#endif

/// @}
