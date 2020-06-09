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
#ifndef VS_PBUFFER_H
#define VS_PBUFFER_H

#include "Vs.h"

#include "VsInterface.h"


#include <mclib/McVec2i.h>

/** This class represents an OpenGL PBuffer. A PBuffer can be used
    as an offscreen render target. The PBuffer can be created on a
    particular device (graphics card). On Linux/X11, the device is
    specified by the display specified via setDisplay(). On Windows,
    the device can be specified by calling setDevice().
*/
class VsPBuffer : public VsInterface
{
    VS_DECL_INTERFACE        ( VsPBuffer )
    VS_DECL_INTERFACE_IMPL   ( VsPBuffer )
//    VS_DECL_INTERFACE_FACTORY( VsPBuffer )

public:
    /** Checks if there is a valid OpenGL PBuffer. The method returns
        false unless the actual OpenGL PBuffer has been created
        by calling create().
        
        \return \c True if a OpenGL PBuffer has been successfully
            created via create(), \c false otherwise. */
    bool isValid() const;

#ifdef HX_HAS_X11
    /** Sets the display on which to create the PBuffer (X11 only).
        This method opens a new connection to the specified X server.
        The connection to the X server will be automatically closed
        again in the destructor. If you want to use an existing
        display connection, use the alternative method below.
        
        \param display The name of the X11 display, e.g. ":0.1".

        \return #VS_OK if the connection to the display could be
            successfully opened, #VS_FAILED otherwise. To get extended
            error information, call Vs::lastError().
    */
    VSRESULT setDisplay(const char* display);

    /** Sets the display on which to create the PBuffer (X11 only).
        Use this method if the connection to the X server has already
        been opened.
        
        \param display Pointer to an existing X11 display of type.
            \c VsVoidHandle is used instead of \c Display* in order
            to avoid the inclusion of X11 header files.

        \param screen Number of screen on which the PBuffer should
            be created.

        \return #VS_OK on success, #VS_FAILED otherwise. To get
            extended error information, call Vs::lastError().
    */
    VSRESULT setDisplay(VsVoidHandle display, int screen);
#endif

#ifdef HX_OS_WIN
    /** Specifies the device on which to create the PBuffer (Windows
        only). In order to create a PBuffer on Windows, a Windows
        device context is required. Usually this device context will
        be taken from the desktop window. By calling setDevice()
        with a non-zero argument, the device context can be created
        on a specific display device. Calling this method makes only
        sense on a multi-GPU system.

        \param device Name of the display device on which to create
             the PBuffer. The names of possible display devices can be
             obtained via the Windows GDI function EnumDisplayDevices().

        \return #VS_OK on success, #VS_FAILED otherwise. To get
            extended error information, call Vs::lastError().
    */
    VSRESULT setDevice(const char* device);
#endif

    /** Set PBuffer attributes such as color or alpha depth. If the
        requested combination of attributes is not supported, #VS_FAILED
        is returned. The method does not actually create a PBuffer or
        change the attributes of an existing one. This can be done by
        calling create().

        \param pixelDepth number of bits of a pixel component. Common
            values are 8, 16, or 32.
        \param numChannels number of pixel components. Common values
            are 1, 2, 3 (RGB buffer), or 4 (RGBA buffer).
        \param hasDepthBuffer if true this indicates that a depth and
            a stencil buffer should be created.
        \param hasFloatComponents if true pixel components should be
            represented as floating point numbers. This requires that
            the pixel depth is either 16 or 32.
        \return #VS_OK on success, #VS_FAILED if the requested
            combination of attributes is not supported.
    */
    VSRESULT setAttributes(int pixelDepth, int numChannels,
                           bool hasDepthBuffer, bool hasFloatComponents);


    /** Set PBuffer attributes in a platform dependent way. On
        Windows wgl attributes as expected by wglChoosePixelFormatARB()
        are expected. */
    VSRESULT setAttributes(const int* attr);

    /** Sets default PBuffer attributes. The method tries to choose
        a 16-bit floating point PBuffer first. If this fails, 
        several other formats are tried until a valid format is found.
        If no valid format can be found the method returns Vs_FAILED.

        \return #VS_OK on success, #VS_FAILED otherwise. To get
            extended error information, call Vs::lastError().
    */
    VSRESULT setDefaultAttributes();

    const int * attributes() const;

	/** Returns true if the buffer has floating point components. */
	bool hasFloatComponents() const;

    /** Creates an OpenGL PBuffer with the specified size. If a
        PBuffer already has been created before, the old buffer
        will be automatically deleted. 
    */
    VSRESULT create(const McVec2i& size);

    /** Returns the size of the OpenGL PBuffer.
    
        \param Size of the OpenGL PBuffer. If the PBuffer
            has not yet been created, McVec2i(0,0) is returned.
    */
    McVec2i size() const;

    /** Create an OpenGL context on top of this pbuffer. If the pbuffer gets re-created
        the returned context-id remains valid as well as the OpenGL objects in it.
        All contexts created by this method share their OpenGL objects.
        The identifier returned by this method is not a regular OpenGL context handle.
        Instead of it is an identifier with which the VsPBuffer class identifies the internal stored context.
    */
    VsVoidHandle createContext(VsVoidHandle contextForSharing=0);

    /** Destroys the specified rendering context. On Windowes this method calls
        wglDeleteContext(). On Linux/X11 it calls glXDestroyContext().

        \param context [in] The OpenGL rendering context to be destroyed.
            On Windows the context should be of type HGLRC. On Linux/X11 it
            should be of type GLXContext.
        \return #VS_OK on success, #VS_FAILED otherwise. To get
            extended error information, call Vs::lastError().
    */
    VSRESULT destroyContext(VsVoidHandle context);

    /** Makes the specified rendering context the current rendering context of the calling
        thread. Internally, the method calls wglMakeCurrent() on Windows and glXMakeCurrent()
        on Linux/X11.

        \param context [in] The OpenGL rendering context that should be set as the
            calling thread's current context. On Windows the context should be of
            type HGLRC. On Linux/X11 it should be of type GLXContext.
        \return #VS_OK on success, #VS_FAILED otherwise. To get
            extended error information, call Vs::lastError().
    */
    VSRESULT makeCurrent(VsVoidHandle context);

    VSRESULT destroy();

    VSRESULT bind(VsVoidHandle context=0);

    VSRESULT unbind();



};

#endif


/// @}
