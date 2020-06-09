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
#ifndef _VS_CROP_REGION_H_
#define _VS_CROP_REGION_H_

#include "VsVolrenAPI.h"

#include "VsObject.h"
#include "VsRelay.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <mclib/McMat4f.h>
#include <mclib/McDArray.h>
#include <mclib/McPlane.h>
#include <mclib/McColor.h>
#include <mclib/McBox3f.h>

class VsData;
class VsCamera;

// VS_RELAY_CLASS VsCropRegion VsObjectRelay


/** Base class of all crop region classes.
    A crop region is used to restrict the rendered parts of the volume image.
    It is, for instance, considered by the VsVolren volume rendering node.

    This is an abstract class interface. Derived classes need to provide
    at least a method inside().
*/
class VSVOLREN_API VsCropRegion : public VsObject
{
    VS_DECL_INTERFACE        ( VsCropRegion )
    VS_DECL_INTERFACE_IMPL   ( VsCropRegion )
    VS_DECL_INTERFACE_FACTORY( VsCropRegion )
    VS_DECL_INTERFACE_RELAY  ( VsCropRegion )

public:
    
    //////////////////////////////////////////////////////////////
    /// Notifications flags. See VsObject::TouchFlag for details.
    //////////////////////////////////////////////////////////////
    enum TouchFlag
    {
        NEW_MOUSE_RELEASED = 1<<1 /// Mouse button released after modifying the crop region
    };

    ////////////////////////////////////////
    // override VsObject
    ////////////////////////////////////////
        
    virtual VSRESULT observedObjectRemoved( VsObject * inObject ); // VS_FORBIDDEN_ON_SERVER
    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    /** Decides if the crop region contains a given point.
        \param  inPos
                Position that is tested for enclosure.
        \param  inEpsilon
                Threshold for points inside the crop region.
                If the distance of a point is less than this value it is considered
                to be inside.
        \return 
                \c True if position is inside, \c False if it is outside of the region
                the crop region encloses.
    */
    bool inside( const McVec3f & inPos, float inEpsilon = 0.0f ) const; // VS_LOCAL_GET

    /** TODO: add documentation
    */
    bool insideUnlocked( const McVec3f & inPos, float inEpsilon = 0.0f ) const; // VS_LOCAL_GET

    /**
     Set a data object for the crop region in order to enable the inside out calculation 
     for the integer coordinates.

     \param [in] data The data object of the crop region.
    */
    VSRESULT setTransformationVoxelToWorld( VsData * inData ); // VS_RELAY

    /** Decides if the crop region contains a given point. This version is intended to be 
        used in screen coordinated for fast scan converters. 

        \param  inPos
                Position that is tested for enclosure.
        \return 
                \c True if position is inside, \c False if it is outside of the region
                the crop region encloses.
    */
    bool inside( const McVec3i & inPos, float inEpsilon = 0.0f ) const; // VS_LOCAL_GET


    /** TODO: add documentation
    */
    bool insideUnlocked( const McVec3i & inPos, float inEpsilon = 0.0f ) const; // VS_LOCAL_GET

    /** TODO: add documentation
    */
    VSRESULT transformationLocalToObject( McMat4f & outTransformation ) const; // VS_LOCAL_GET

    /** TODO add documentation
    */
    VSRESULT setTransformationLocalToObject( const McMat4f & inTransformation ); // VS_RELAY


    /** TODO: add documentation
    */
    VSRESULT transformationObjectToWorld( McMat4f & outTransformation ) const;  // VS_LOCAL_GET

    /** TODO add documentation
    */
    VSRESULT setTransformationObjectToWorld( const McMat4f & inTransformation ); // VS_RELAY


    /** TODO add documentation
    */
    VsCamera * camera() const;

    /** TODO add documentation
    */
    VSRESULT setCamera( const VsCamera * inCamera );


    /** TODO add documentation
    */
    VSRESULT planeSOP( McDArray< McDArray<McPlane> > & outSOP ) const; // VS_LOCAL_GET

    /** Retrieve PlaneSOP in object coordinates.
        Raw planes transformed by the transformation set by setTransformationLocalToObject().
    */
    VSRESULT planeSOPTransformed( McDArray< McDArray<McPlane> > & outSOP ) const; // VS_LOCAL_GET

    /** TODO add documentation
    */
    VSRESULT setPlaneSOP( const McDArray< McDArray<McPlane> > & inSOP ); // VS_RELAY

    /** TODO add documentation
    */
    VSRESULT planeTransformed( McPlane & outPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ) const; // VS_LOCAL_GET

    /** TODO add documentation
    */
    VSRESULT setPlaneTransformed( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ); // VS_RELAY

    /** TODO add documentation
    */
    VSRESULT plane( McPlane & outPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ) const; // VS_LOCAL_GET

    /** TODO add documentation
    */
    virtual VSRESULT setPlane( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ); // VS_RELAY

    /// This is the color that is used for those parts of the crop region that
    /// are inside the bounding box.
    McColor  color() const; // VS_LOCAL_GET
    VSRESULT setColor( const McColor & inColor ); // VS_RELAY

    /// This is the color that is used for those parts of the crop region that
    /// are outside the bounding box.
    McColor  color2() const; // VS_LOCAL_GET
    VSRESULT setColor2( const McColor & inColor ); // VS_RELAY


    /* Returns the bounding box of the remaining parts of the ingoing box after being clipped.
       To archieve that the remaining polyhedrons are computed and their edge points added to the resulting box.
       Before an edge point is added, it is transformed by the given transformation.
    */
    McBox3f boundingBoxOfBoxClip( McBox3f const & inBoxObject, McMat4f const & inObjectToResultBoxSpace );
};


#endif

/// @}
