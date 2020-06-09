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
#ifndef _VS_BOUNDING_BOX_H_
#define _VS_BOUNDING_BOX_H_

#include "Vs.h"

#include "VsNode.h"

class VsCropRegion;


// VS_RELAY_CLASS VsBoundingBox VsNodeRelay
/** Displays a bounding box.

    This class displays the bounding box of a 3D image volume
    represented by a VsData object. In addition, a crop region
    can be set via setCropRegion(). In this case the cropped
    bounding box will be displayed.
*/
class VSVOLREN_API VsBoundingBox : public VsNode
{
    VS_DECL_INTERFACE        ( VsBoundingBox )
    VS_DECL_INTERFACE_IMPL   ( VsBoundingBox )
    VS_DECL_INTERFACE_FACTORY( VsBoundingBox )
    VS_DECL_INTERFACE_RELAY  ( VsBoundingBox )

public:

    /** Notification flags. See VsObject::TouchFlag for details. */
    enum TouchFlag
    {
        /// Set if a new input volume was set or the input volume was changed.
        NEW_DATA        = 1<<1
        /// Set if a new crop region was set or the crop region was changed.
    ,   NEW_CROPREGION  = 1<<6
        /// Set if visibility changed.
    ,   NEW_VISIBILITY  = 1<<7
    };


    /** 
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // VS_LOCAL_GET

    /** 
    */
    virtual VsRenderResult render();

    /** 
    */
    virtual VSRESULT cleanup();

    /** Sets the bounding box to be displayed.
        \param  inBox
                The bounding box to be displayed.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setBoundingBox( const McBox3f & inBox ); // VS_RELAY

    /** Sets a new crop region. If a crop region is active only the
        parts of the box inside the crop region will be
        shown. In order to disable cropping you should call this
        method with a zero pointer. The crop region object will not
        be copied but a handle to the object will be stored. When
        the crop region is modified, this object will be automatically
        touched. 
        \param  inCropRegion
                The new crop region object. If zero, drawing of crop regions is disabled.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setCropRegion( VsCropRegion * inCropRegion, unsigned int inIndex = 0 ); // VS_RELAY

    /** Returns the current crop region object. 
        \return 
                The current crop region or zero.
    */
    VsCropRegion * cropRegion( unsigned int inIndex = 0 ) const; // VS_LOCAL_GET


    /**
    */
    VSRESULT setBoundingBoxVisible( bool inFlag ); // VS_RELAY

    /**
    */
    bool boundingBoxVisible(); // VS_LOCAL_GET

    /**
    */
    VSRESULT setRegionVisible( bool inFlag, unsigned int inIndex = 0 ); // VS_RELAY

    /**
    */
    bool regionVisible( unsigned int inIndex = 0 ); // VS_LOCAL_GET
    

    
protected:

    /** This node actually observes the crop region object set with setCropRegion().
        \param  inObject 
                The observed object that has changed. If zero, method does nothing.
        \param  inMask
                The bitmask that has been used for the touch on the observed object.
                Refer to VsObject::TouchFlag or corresponding enum types of derived
                classes for the semantics of particular flags.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );
};


#endif


/// @}
