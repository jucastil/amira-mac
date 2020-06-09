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
#ifndef VS_OVERLAY_IMAGE_H
#define VS_OVERLAY_IMAGE_H

#include "Vs.h"

#include "VsOverlay.h"
#include "VsOverlayElement.h"

#include <mclib/McHandle.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

#include <vsvolren/VsMemoryData.h>


/** \if UNDOCUMENTED An image.

    (The class is for internal use only and will not be exported. Therefore it
     does not hide any implementation detail.)
  */
class VSVOLREN_API VsOverlayImage
:   public VsOverlayElement
{
    VsOverlayImage( const VsOverlayImage & inOther );

public:
    
    //
    VsOverlayImage( VsOverlay * inContext );
   ~VsOverlayImage();


    ////////////////////////////////////////
    // override VsOverlayElement
    ////////////////////////////////////////
private:    
    virtual void render();
    virtual VsOverlayElement * clone() const;
    virtual void init(const McVec3f& pos, const VsCamera* camera, const McVec2i& windowSize, bool grab);
    virtual void grab(const VsOverlay::OverlayEvent* event);
    virtual bool handleStartGrabbingEvent(const VsOverlay::OverlayEvent* event);
    virtual bool picked(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    virtual int pickedPoint(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    virtual McDArray<McVec3f> * getVertices( VsPainter * inPainter = 0 );
protected:
    virtual void getAlignment(int& horizontal, int& vertical) const;
    virtual McVec3f textAnchorPoint() const;
    virtual void computeTextPosition(VsViewState& st);
    virtual void computeRenderElements( VsViewState & inState );


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////
public:

    void setPosition( McVec3f & inCenter );
    
    McVec3f position();

    /** Set a new image.
        The image replaces the old image. 
        The object holds a reference to the VsMemoryData object. So if the data or dimension
        of the VsMemoryData object changes the image rendered on the screen changes too.
        Currently the only supported image format is RGBA8.
        \param [in] inImage
                Image data that is going to be displayed. The first slice is displayed.
                If zero, no image is displayed.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setImage( VsMemoryData * inImage );

    /** Get current image.
        \return 
                Handle to the current image. May be an empty handle.
    */
    McHandle<VsMemoryData> image();

    /** Set first pixel position indicator.
        TRUE indicates that the first pixel of the image data is the lower left pixel.
        FALSE indicates upper left.
    */
    void setImageOriginIsLL( bool inFlag );

    bool imageOriginIsLL();


private:

    McHandle<VsMemoryData>  mImage;
    bool                    mImageIsLL;

    McVec3f                 mCenter;

    McDArray<McVec3f>       mVerts;
};


#endif

/// @}
