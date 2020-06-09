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
#ifndef VS_OVERLAY_CONTOUR_H
#define VS_OVERLAY_CONTOUR_H

#include "Vs.h"

#include "VsHandable.h"
#include "VsOverlay.h"
#include "VsOverlayElement.h"

#include <mclib/McColor.h>
#include <mclib/McMat3f.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2i.h>
#include <mclib/McBox2i.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include "McViewVolume.h"


/** \if UNDOCUMENTED An ellipse has a horizontal and vertical radius 
    and a center. As a Overlayment feature the line strip knows about
    its units.

    (The class is for internal use only and will not be exported. Therefore it
     does not hide any implementation detail.)
  */
class VSVOLREN_API VsOverlayContour : public VsOverlayElement
{
    ////////////////////////////////////////
    // override VsOverlayElement
    ////////////////////////////////////////    
public:
    virtual VsOverlayElement* clone() const;
    virtual void init(const McVec3f& pos, const VsCamera* camera, const McVec2i& windowSize, bool grab);
    virtual bool handleStartGrabbingEvent(const VsOverlay::OverlayEvent* event);
    virtual void grab(const VsOverlay::OverlayEvent* event);
    virtual bool picked(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    virtual int pickedPoint(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    virtual bool pickedLabel(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    virtual McDArray<McVec3f> * getVertices();
protected:
    virtual void getAlignment(int& horizontal, int& vertical) const;
    virtual McVec3f textAnchorPoint() const;
    virtual void computeRenderElements( VsViewState & inState );
    virtual void computeTextPosition(VsViewState & st);


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////  
private:

    VsOverlayContour( const VsOverlayContour & );

public:

    void getVertices( McDArray<McDArray<McVec3f> > & outVertices );
    void setVertices( const McDArray<McDArray<McVec3f> > & inVertices );
    
    void setRenderMode(int mode) {mRenderMode = mode;};
    int renderMode() {return mRenderMode;};

    void setInterpolatedContour(bool set);
    bool isInterpolatedContour();

    void setStructureIdx(int structIdx);
    int  structureIdx();
    
    void setContourIdx(int contourIdx);
    int  contourIdx();

    void showLabel(bool set);

    void setTextPosition(const McVec3f &textPosition);
    McVec3f textPosition();

    void disablePicking();
    void setVisible(bool set);
    
    void centerLabel(bool set);
    bool labelCentered();

    void alwaysRaster();
    ///
    VsOverlayContour (class VsOverlay* context);


    // 9 handle points, i.e. idx in [0, 8]
    McVec3f handlePoint(int idx) const;



public:
    McVec3f mCenter;
    McMat3f mOrientation; // has unit length
    float   mRadiusX;
    float   mRadiusY;
    bool mFreehandMode;

private:
    McVec3f mFixedCorner;
    bool mInterpolated;
    int mStructureIdx;
    int mContourIdx;
    McDArray< McDArray<McVec3f> > mVerts; 
    McDArray< McVec3f > mFreehandLoop;
    bool mShowLabel;
    bool mPick;
    bool mVisible;
    bool mLabelMoved;
    // alwyas draw raster image for 3d rendering
    bool mAlwaysRaster;
    // draw points or lines
    int mRenderMode;
};

/// \endif

#endif // VS_OVERLAY_CONTOUR_H


/// @}
