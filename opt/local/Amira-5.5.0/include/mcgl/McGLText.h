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
#ifndef _MC_GL_TEXT_H
#define _MC_GL_TEXT_H

#include "mcglAPI.h"

#ifdef HX_HAS_X11
#include <X11/Xlib.h>
#ifdef CursorShape
    #undef CursorShape
#endif
#endif

//RK doesnt compile on VC8
// struct _XDisplay;
// typedef struct _XDisplay Display;

#if !defined(_WCHAR_T_DEFINED) && !defined(HX_OS_MACX)
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif


class MCGL_API McGLText
{
  public:

    /** Sets a global default size for font rendering. */
    static void setDefaultFontSize(int defaultFontSize);

    /** Returns the global default font size. */
    static int defaultFontSize();

    /** Sets a global default font family for font rendering. */
    static void setDefaultFontFamily(const char* defaultFontFamily);

    /** Returns the global default font family. */
    static const char* defaultFontFamily();

    /** Sets the font to be used in a subsequent glText() call. Supported
        font families are at least helvetica, times, and courier. */
    static void setFont(int pointSize=defaultFontSize(), bool bold=true,
        bool italic=false, const char* family=defaultFontFamily());

    /** Sets the background color of text rendered with glText(). Unless
        an alpha parameter a=0 is used the text will be drawn inside a
        semi-transparent rectangle filled with the background color. */
    static void setBackground(float r=0, float g=0, float b=0, float a=0);

    /** Sets the foreground color of text rendered with glText(). If the
        alpha parameter is not 1 (fully opaque) blending is used. */
    static void setForeground(float r=1, float g=1, float b=1, float a=1);

    enum Alignment { LEFT=-1, CENTER=0, RIGHT=1, BOTTOM=-1, TOP=1 };

    /** Sets the alignment mode for text rendered with glText(). The
        alignment mode determines how the text is positioned relative to
        the raster position specified as an argument of glText(). */
    static void setAlignment(int horizontal=LEFT, int vertical=BOTTOM);

    /** Sets an offset in pixels for rendered with glText(). The text
        will be offset by this amount relative to the raster position
        specified as an argument to glText(). */
    static void setPixelOffset(int x=0, int y=0);

    /** Renders a text using OpenGL. The properties of the rendered text
        can be modified using glTextSetFont(), glTextSetBackground(),
        glTextSetForeground(), and glTextSetAlignment(). The text may
        contain new line characters or '\\n' delimiters. In this case
        multiple lines will be printed. The arguments x, y, and z specify
        the current OpenGL raster position where the text should be
        rendered. */
    static void render(float x, float y, float z, const char* text);
    
    /** Render function for wchar characters.
        Only call if wcharSupported() returns true. */
    static void render(float x, float y, float z, const wchar_t* text);

    /** Same as the render() above, but with 2d raster position. The z
        component of the current raster position will be set to 0. */
    static void render(float x, float y, const char* text) {
        render(x,y,0.f,text);
    }
    
    /** Same as above but for wchar characters.
        Only call if wcharSupported() returns true. */
    static void render(float x, float y, const wchar_t* text) {
        render(x,y,0.f,text);
    }

    /** This method calculates the area that will be covered when
        rendering the specified text using glText(). The method
        returns the number of lines in the text. */
    static int textExtent(const char* text, int& w, int& h);

    /** Same as above but for wchar characters.
        Only call if wcharSupported() returns true. */
    static int textExtent(const wchar_t* text, int& w, int& h);

    /** Obsolete. This method if provided just for compatibility with
        previous versions of Amira. */
    static int fontBase(int pointSize=14);

    /** Delete all cached fonts. */
    static void cleanUp();

    /** Active a cache context. */
    static void setCacheContext(int cacheContext);

    /** Returns the current cache context. */
    static int cacheContext();

#ifdef HX_HAS_X11
    /** Sets the Display which is used for geometric calculation such as textExtent. 
        If the Display is set, it will used for those calculations, else a valid 
        OpenGL context is required to query the display using glXGetCurrentDisplay
        for these functions to work. */
    static void setDisplay(Display*);
    Display* display();
#endif

    /** Returns a list of available point sizes. 
        Mostly important for Linux for this uses fixed-size bitmap fonts.
        The list of available point sizes is returned in the array \c sizes
        for which the method will assume that the user provides allocated
        space for \c maxSizes elements. The number of available point sizes
        is provided as return value.*/
    static int availablePointSizes(int * sizes, int maxSizes, const char* family=defaultFontFamily(), bool bold=true, bool italic=false);

    /** Returns whether wchar is natively supported. (This may depend on
        the plattform and also on the configuration used for building
        the mcgl lib). In case the method does not return true, the result
        of calling wchar parameterized methods is undefined. */
    static bool wcharSupported();
};

#endif


/// @}
