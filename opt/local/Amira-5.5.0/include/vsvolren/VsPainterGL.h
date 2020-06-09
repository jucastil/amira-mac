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
#ifndef VS_PAINTER_GL_H
#define VS_PAINTER_GL_H

#include "VsPainter.h"

#include <mclib/McVec4f.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>


class VSVOLREN_API VsPainterGL
:   public VsPainter
{
public:

    virtual bool isGL();

    /// Draws point with given color
    /// if shadowColor != 0, draws on top of semitransparent stripe
    /// if inState is 0, the point is assumed to be in pixel coordinates
    /// already, else, it is mapped by the modelview and projection
    /// matrix and the viewport transformation of inSpace.
    virtual void drawPoint(
        const McVec3f& a
    ,   const McVec4f& color
    ,   int size
    ,   const McVec4f* inShadowColor=0
    ,   VsViewState* inState=0
    );

    /// Draws line with given color
    /// if shadowColor != 0, draws on top of semitransparent stripe
    /// if inState is 0, the points are assumed to be in pixel coordinates
    /// already, else, they are mapped by the modelview and projection
    /// matrix and the viewport transformation of inSpace.
    virtual void drawLine (
        const McVec3f& a
    ,   const McVec3f& b
    ,   const McVec4f& color
    ,   int width
    ,   int style=LINE_SOLID
    ,   const McVec4f* inShadowColor=0
    ,   bool inRoundToInt=false
    ,   VsViewState* inState=0 
    );

    virtual void drawLineStrip(
        McVec3f* verts
    ,   int vertsNum
    ,   const McVec4f& color
    ,   int width
    ,   int style=LINE_SOLID
    ,   const McVec4f* inShadowColor=0
    ,   VsViewState* inState=0
    );

    virtual void drawShutterHole(
        McVec3f       * inVerts
    ,   int             inVertsNum
    ,   const McVec3f & inCenter
    ,   float           inExtrusion
    ,   McVec4f const & inFillColor
    );

    /// Draw angle for last two segments and display text
    /// if inState is 0, the points are assumed to be in pixel coordinates
    /// already, else, they are mapped by the modelview and projection
    /// matrix and the viewport transformation of inSpace.
    virtual void drawAngle(
        const McDArray<McVec3f>& points
    ,   const McVec4f& color
    ,   int width
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


    virtual void drawImage(
        McVec2i      & inPos
    ,   McVec2i      & inSize
    ,   McVec2i      & inROIPos
    ,   McVec2i      & inROISize
    ,   VsMemoryData * inImage
    ,   bool           inImageOriginIsLL
    );


    virtual VsMemoryData * createMappedPixels(
        VsMemoryData * inData
    ,   bool           inFlipY = false
    ,   float        * inScale = 0
    ,   float        * inBias = 0
    );


    virtual void drawPixels(
        const McVec3f & inLowerLeft
    ,   const McVec3f & inUpperRight
    ,   VsMemoryData  * inImage
    ,   bool            inFlipY = false
    ,   float         * inScale = 0
    ,   float         * inBias = 0
    ,   bool          * inLinearFilter = false
    );


    virtual void drawText_(
        McVec3f const & inAnchor
    ,   char    const * inTextUTF8
    ,   McVec4f const & inColor
    ,   McGLText::Alignment inHAlignment
    ,   McGLText::Alignment inVAlignment
    ,   VsViewState   * inState
    ,   McVec4f const * inBackroundColor
    ,   int             inFontPointSize
    ,   bool            inFontBold
    ,   bool            inFontItalic
    ,   char const    * inFontFamily
    ,   bool            inDryRun
    ,   McVec2i       * outSize
    );


    virtual void clear(
        McVec4f const & inColor
    ,   McVec2i       * inDstPos  = 0
    ,   McVec2i       * inDstSize = 0
    );
};

#endif


/// @}
