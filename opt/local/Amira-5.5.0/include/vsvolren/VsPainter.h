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
#ifndef VS_PAINTER_H
#define VS_PAINTER_H

#include "Vs.h"
#include "VsImpl.h"
#include "VsViewState.h"
#include "VsHandable.h"

#include <mclib/McVec2i.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McDArray.h>

#include <mcgl/McGLText.h>


class VSVOLREN_API VsPainter
:   public VsHandable
{
public:
    
    enum 
    {
        LINE_SOLID  = 0
    ,   LINE_DASHED = 1 
    ,   LINE_DOTTED = 2
    };

    VsPainter();
    virtual ~VsPainter();

    virtual bool isGL();

    VsViewState & viewState();


    void setIsOriginAtLowerLeft( bool inFlag );
    bool isOriginAtLowerLeft();

    void setDoDrawFlipped( bool inFlag );
    bool doDrawFlipped();

    /** Draws point with given color
        if shadowColor != 0, draws on top of semitransparent stripe
        if inState is 0, the point is assumed to be in pixel coordinates
        already, else, it is mapped by the modelview and projection
        matrix and the viewport transformation of inSpace. */
    virtual void drawPoint(
        const McVec3f& a
    ,   const McVec4f& color
    ,   int size
    ,   const McVec4f* inShadowColor=0
    ,   VsViewState* inState=0
    );

    /** Draws line with given color
        if shadowColor != 0, draws on top of semitransparent stripe
        if inState is 0, the points are assumed to be in pixel coordinates
        already, else, they are mapped by the modelview and projection
        matrix and the viewport transformation of inSpace. */
    virtual void drawLine (
        const McVec3f& a
    ,   const McVec3f& b
    ,   const McVec4f& color
    ,   int width=1
    ,   int style=LINE_SOLID
    ,   const McVec4f* inShadowColor=0
    ,   bool inRoundToInt=false
    ,   VsViewState* inState=0 
    );

    virtual void drawLineStrip(
        McVec3f* verts
    ,   int vertsNum
    ,   const McVec4f& color
    ,   int width=1
    ,   int style=LINE_SOLID
    ,   const McVec4f* inShadowColor=0
    ,   VsViewState* inState=0
    );

    virtual void drawPolygon(
        McVec3f       * inVerts
    ,   int             inVertsNum
    ,   McVec4f const & inFillColor
    )
    {
    }

    virtual void drawShutterHole(
        McVec3f       * inVerts
    ,   int             inVertsNum
    ,   const McVec3f & inCenter
    ,   float           inExtrusion
    ,   McVec4f const & inFillColor
    )
    {
    }

    /** Draw angle for last two segments and display text
        if inState is 0, the points are assumed to be in pixel coordinates
        already, else, they are mapped by the modelview and projection
        matrix and the viewport transformation of inSpace. */
    virtual void drawAngle(
        const McDArray<McVec3f>& points
    ,   const McVec4f& color
    ,   int width=1
    ,   VsViewState * inState=0
    );

    /// enables scissoring.
    virtual void enableScissoring(
        int left
    ,   int top
    ,   int width
    ,   int height
    ,   int renderMask = VS_EX_RENDER_RASTERIMAGE
    );

    /// disables scissoring
    virtual void disableScissoring(
        int renderMask = VS_EX_RENDER_RASTERIMAGE
    );


    /**
        inImageOriginIsLL:  
            If set to TRUE, the first pixel of the data section of inImage
            should be displayed at the lower left corner of the destination
            rectangle. This is the OpenGL style of storing images.
            In case of using QT QImages, this has to be set to FALSE since
            the first pixel of QImage is at the upper left side.
    */
    virtual void drawImage(
        McVec2i      & inDstPos
    ,   McVec2i      & inDstSize
    ,   McVec2i      & inSrcPos
    ,   McVec2i      & inSrcSize
    ,   VsMemoryData * inImage
    ,   bool           inImageOriginIsLL
    );


    /** Draws an array of raw pixel data to the designated position
        on the screen. The position is given by the lower left
        \c inLowerLeft and upper right \c inUpperRight corner which
        are both given in object space (i.e. they will be transformed
        by the current model view matrix).
        With the parameter \c inFlipY one can account for the different
        data definitions (y running either top-to-bottom or bottom-to-top).
        Setting \c inFlipY to true will just flip the data.
        A scale and bias can be specified which are then applied while
        drawing the pixel data. If \c inScale or \c inBias is 0, no
        mapping will be performed. \c inLinearFilter specifies whether
        scaling the image should be done with linear or nearest neighbor
        filtering.

        Since remapping the data is a quite costly operation, we provide
        a way of pre-map the data (see createMappedPixels()). The latter
        will create a copy of the original data in a more hardware friendly
        format, supposed to render faster.

        Note that certain restrictions in the supported pixel format for this
        method may apply. However, pre-mapped images generated by 
        createMappedPixels() are always supposed to work.
    */
    virtual void drawPixels(
        const McVec3f & inLowerLeft
    ,   const McVec3f & inUpperRight
    ,   VsMemoryData  * inImage
    ,   bool            inFlipY = false
    ,   float         * inScale = 0
    ,   float         * inBias = 0
    ,   bool          * inLinearFilter = 0
    );


    /** Create pre-mapped pixel data from a given input image. (see drawPixels()).
        The input data is transformed into a more hardware-friendly format supposed
        to render faster. During the conversion the raw data can be flipped about 
        the y-axis on the fly accounting for different data definition models
        (y running top-to-bottom or bottom-to-top). Additionally a scale and bias
        can be applied to each pixel during the conversion.
        */
    virtual VsMemoryData * createMappedPixels(
        VsMemoryData * inData
    ,   bool           inFlipY = false
    ,   float        * inScale = 0
    ,   float        * inBias = 0
    );


    virtual void drawText_(
        McVec3f const & inAnchor
    ,   char    const * inTextUTF8
    ,   McVec4f const & inColor
    ,   McGLText::Alignment inHAlignment
    ,   McGLText::Alignment inVAlignment
    ,   VsViewState   * inState = 0
    ,   McVec4f const * inBackroundColor = 0
    ,   int             inFontPointSize  = 0
    ,   bool            inFontBold       = false
    ,   bool            inFontItalic     = false
    ,   char const    * inFontFamily     = 0
    ,   bool            inDryRun         = false
    ,   McVec2i       * outSize          = 0
    )
    {
    }


    /// Clears a rectangular box of the render area
    virtual void clear(
        McVec4f const & inColor
    ,   McVec2i       * inDstPos  = 0
    ,   McVec2i       * inDstSize = 0
    );


    static VsPainter & painterToRender();
    static void setPainterToRender( VsPainter * inPainter );

    static VsPainter & painterToStream();
    static void setPainterToStream( VsPainter * inPainter );



    ////////////////////////////////////////
    // convenience methods
    ////////////////////////////////////////

    void fillRect(
        float const     inX
    ,   float const     inY
    ,   float const     inWidth
    ,   float const     inHeight
    ,   McVec4f const & inColor
    );


protected:

    VsViewState mViewState;

    bool        mIsOriginAtLowerLeft;
    bool        mDoDrawFlipped;
};

#endif

/// @}
