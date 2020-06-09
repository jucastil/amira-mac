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
#ifndef _VS_VIEW_STATE_
#define _VS_VIEW_STATE_

#include "Vs.h"

#include <mclib/McVec3f.h>
#include <mclib/McMat4f.h>

class VsCamera;
class McVec2i;

/** \if UNDOCUMENTED A class to save part of the rendering state.
    This one saves the model and projection matrix and the viewport to 
    provide a mapping between world and screen coordinates.
    Note that for valid transfomation with the methods 
    mapWorldToScreen/mapScreenToWorld you need to save the current rendering
    state with the help of save().

    Embodyments for specific rendering APIs (e.g. OpenGL or DirectX) need to
    implement save/restore. In the implementation of the case class
    save and restore are no-ops.

    The class is for internal use only and will not be exported. Therefore it
    does not hide any implementation detail.

    TODO: However, to create external VsViewState objects, the functions 
    newVsViewState and deleteVsViewState currently can be used. Moreover, the
    utility function mapWorldToScreen is exported.
    These should be removed in future.
  */

class VsViewState;
extern VSVOLREN_API VsViewState* newVsViewState   (VsCamera* camera, const McVec2i &windowSize);
extern VSVOLREN_API VsViewState* newVsViewState   (const McMat4f& model, const McMat4f& proj, const McVec2i& windowSize);
extern VSVOLREN_API         void deleteVsViewState(VsViewState* viewstate);
extern VSVOLREN_API      McVec3f mapWorldToScreen (VsViewState* viewstate, const McVec3f& world);


class VSVOLREN_API VsViewState
{
public:

    ///
    VsViewState(){};
    ///
    VsViewState(VsCamera* camera, const McVec2i &windowSize);
    ///
    virtual ~VsViewState(){};


public:
   
    /** Save the actual rendering state. This method MUST NOT be called without
        a valid rendering context!! */
    virtual void save(){};

    /** Restore the rendering state to the saved state. This method MUST NOT be
        called without a valid rendering context!! */
    virtual void restore(){};
            
    /// set matricies
    void set(const McMat4f& inModel, const McMat4f& inProj);

    /// set viewport
    void setViewPort( int * inViewPort );

    /// get viewPort
    int * viewPort();

    /// Return world coordinates @c world mapped to the screen coordinates. 
    McVec3f mapWorldToScreen(const McVec3f& world) const;

    /// Return screen coordinates @c screen mapped to world coordinates.
    McVec3f mapScreenToWorld(const McVec3f& screen) const;

    /** Calculates the world coordinate vector at @c pos that shifts in 
        screen coordinates one pixel in x direction. */
    McVec3f screenX(const McVec3f& pos) const;

    /** Calculates the world coordinate vector at @c pos that shifts in 
        screen coordinates one pixel in y direction. */
    McVec3f screenY(const McVec3f& pos) const;

public:

    /// The viewport
    int     mViewPort[4];
    /// The model view matrix.
    McMat4f mModel;
    /// The projection matrix.
    McMat4f mProj;
    /// The combined modelview projection matrix.
    McMat4f mProjMatrix;
    /// The inverse of the modelview projection matrix.
    McMat4f mInvProjMatrix;
};

/// \endif

#endif

/// @}
