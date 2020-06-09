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
#ifndef _VS_HEAD_UP_DISPLAY_
#define _VS_HEAD_UP_DISPLAY_


#include "Vs.h"

#include "VsNode.h"
#include "VsMemoryData.h"

#include <mclib/McVec2i.h>
#include <mclib/McVec4f.h>


/** This class is used to draw some additional information as an overlay onto
    the scene. The additional information can consist of a single pixmap image
    and up to eight text segments positioned at the main locations (top, button, 
    left, right, upper left/right, lower left/right).
*/

////////////////////////////////////////////////////////////////////////////////
class  VSVOLREN_API VsHeadUpDisplay : public VsNode
{
    VS_DECL_INTERFACE        ( VsHeadUpDisplay )
    VS_DECL_INTERFACE_IMPL   ( VsHeadUpDisplay )
//    VS_DECL_INTERFACE_FACTORY( VsHeadUpDisplay )
//    VS_DECL_INTERFACE_RELAY  ( VsHeadUpDisplay )

public:

    /** Identifies the main positions on the screen.
    */
    enum Placement
    { 
        /// North-West
        UpperLeft   = 0,
        /// South-West
        LowerLeft   = 1,
        /// North-East
        UpperRight  = 2,
        /// South-East
        LowerRight  = 3,
        /// North
        Top         = 4,
        /// West
        Left        = 5,
        /// South
        Bottom      = 6,
        /// East
        Right       = 7
    };

    /** Append a new line of text to the text at the specified position. 
        A newline is automatically added.
        \param  inLine
                Line of text to append.
        \param  inPlace
                Target text segment the text line is appended to.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT appendLine( const char * inLine, Placement inPlace = UpperLeft );

    /** Set a new image. The VsHeadUpDisplay supports only a single image. 
        The image replaces an old image regardless of the placement. 
        The node keeps a reference to the VsMemoryData object. So if the data or dimension
        of the VsMemoryData object changes the image rendered on the screen changes too.
        \param  inImage
                Image data that is going to be displayed. If \c inImage has
                a z-dimension larger than 1, always the first z-slice is used 
                for display.
                If zero, no image is displayed.
        \param  inPlace
                Target image location. 
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setImage( VsMemoryData * inImage, Placement inPlace = LowerLeft );
    
    /** Get current image.
        \return 
                Handle to the current image. May be an empty handle.
    */
    McHandle<VsMemoryData> image();

#ifndef HIDDEN_FROM_DOC
    /** This method is not used outside of VsHeadUpDisplay -> move to private

        Get the anchor pixel-position of the image set by setImage().
        \param  inWinSize
                Size of the viewer in pixels.
        \param  outAnchorPos
                Anchor pixel-position of the image.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT imageAnchor( const McVec2i & inWinSize, McVec2i & outAnchorPos ) const;
#endif

    /** Clear text elements at the specified position.
        \param  inPlace
                Target text segment that gets cleared. 
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT clearText( Placement inPlace );

    /** Clear image. Since VsHeadUpDisplay supports only a single image,
        there is no need to specify a location here.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT clearImage();

    /** Clear all. This includes the text elements at all possible locations
        as well as an assigned image.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT clear();

    /** Get the shadow color for the displayed text.
        \return 
                Color of the text shadow.
    */
    McVec4f  shadowColor() const;
                
    /** Set the shadow color for the displayed text. Default is black.
        \param  inColor 
                New color for text shadow.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setShadowColor( const McVec4f & inColor );

    /** Get the color used for the displayed overlay text.
        \return 
                Color of overlay text.
    */
    McVec4f  color() const;

    /** Set the color used for the displayed overlay test. Default is white.
        \param  inColor
                New text color.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setColor( const McVec4f & inColor );

    /** Renders the object.
    */
    virtual VsRenderResult render();

    /** Frees render resources.
    */
    virtual VSRESULT cleanup();

    /** Helper method for internal use only.
    */
    virtual void * extension( int , void * );
};


#endif

/// @}
