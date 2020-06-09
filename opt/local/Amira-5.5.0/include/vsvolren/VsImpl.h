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
#ifndef _VS_IMPL_H
#define _VS_IMPL_H

#include "Vs.h"

#include <mclibthreaded/McMutex.h>
#include <mclib/McHandle.h>
#include <mclib/McVec4f.h>
#include <mclib/McVec3f.h>
#include <mclib/McPlane.h>

class McBox3f;
class McMat4f;

#include "VsTechnique2.h"


#define VS_VOLREN_MODULE_ID     13   

////////////////////////////////////////
// common helper
////////////////////////////////////////

// memory management
#define VS_SAFE_DIV(a,b)          ((b)?((a)/(b)):(0))
#define VS_SAFE_FREE(p)           do{ if(p) { ::free((void*)p);   (p)=0; } }while(0)
#define VS_SAFE_DELETE(p)         do{ if(p) { delete (p);         (p)=0; } }while(0)
#define VS_SAFE_DELETE_ARR(p)     do{ if(p) { delete [] (p);      (p)=0; } }while(0)
#define VS_SAFE_FCLOSE(p)         do{ if(p) { ::fclose((FILE*)p); (p)=0; } }while(0)

// relations
#define VS_MAX(x,y)               (((x)<(y))?(y):(x))
#define VS_MIN(x,y)               (((x)<(y))?(x):(y))
#define VS_MAX3(x,y,z)            (((x)<(y))?(VS_MAX(y,z)):(VS_MAX(x,z)))
#define VS_MIN3(x,y,z)            (((x)<(y))?(VS_MIN(x,z)):(VS_MIN(y,z)))
#define VS_MAX2_INDEX(x,y)        ( ((x)>(y)) ? 0 : 1 )
#define VS_MAX3_INDEX(x,y,z)      ( ((x)>(y)) ? ((x)>(z)?0:2) : ((y)>(z)?1:2) )
#define VS_MIN3_INDEX(x,y,z)      ( ((x)<(y)) ? ((x)<(z)?0:2) : ((y)<(z)?1:2) )

// ranges
#define VS_ISIN(x,min,max)        ( (x)>=(min) && (x)<=(max) )
#define VS_CLAMP(x,min,max)       ( ((x)<(min)) ? (min) : ( (x)>(max)?(max):(x) ) )
#define VS_CLAMPSAFE(x,min,max)   ( ((min)>(max)) ? (VS_CLAMP(x,max,min)) : (VS_CLAMP(x,min,max)) )

// DirectX
#define VS_SAFE_RELEASE(p)        do{ if(p) { (p)->Release(); (p)=0; } }while(0)


// real number stuff
#define VS_REALEPSILON            (0.000001)

#define VS_NEARZERO_EPS(x,e)      ((x)<(e) && (x)>-(e))
#define VS_GREATER_EPS(x,y,e)     ((x)-(e)>(y))
#define VS_SMALLER_EPS(x,y,e)     ((x)+(e)<(y))
#define VS_NEAREQUAL_EPS(x,y,e)   (!VS_GREATER_EPS(x,y,e) && !VS_SMALLER_EPS(x,y,e))

#define VS_NEARZERO(x)            VS_NEARZERO_EPS   ((x),    (VS_REALEPSILON))
#define VS_GREATER(x,y)           VS_GREATER_EPS    ((x),(y),(VS_REALEPSILON))
#define VS_SMALLER(x,y)           VS_SMALLER_EPS    ((x),(y),(VS_REALEPSILON))
#define VS_NEAREQUAL(x,y)         VS_NEAREQUAL_EPS  ((x),(y),(VS_REALEPSILON))


/// swap 
template <class T>
void VS_SWAP(T & a, T & b)
{
    T tmp = a;
    a = b;
    b = tmp;
}


/// malloc with alignment semantics. for example, with align=16, aligns on 16 bytes boundaries
/// (e.g., for SSE code). memory acquired in this way should free the memory using vsAlignedFree()
inline void* vsAlignedMalloc(size_t size, size_t align)
{
#ifdef HX_OS_WIN
    return _aligned_malloc(size, align);
#elif HX_OS_LINUX
    void * vresorted   = 0;
    if (posix_memalign(&vresorted, align, size) == 0)
        return vresorted;
    else
        return 0;
#elif HX_OS_MACX
#warning "platform maybe not supported"
	return malloc(size);
#endif
}


/// frees aligned memory allocated by vsAlignedMalloc()
inline void vsAlignedFree(void* dta)
{
#ifdef HX_OS_WIN
    _aligned_free(dta);
#else
    free(dta);
#endif
}

////////////////////////////////////////
// 
////////////////////////////////////////

VSVOLREN_API int vsSetRootDir( const char * inDir );

VSVOLREN_API const char * vsRootDir();

/// plays a short tick sound for acoustic error tracing
VSVOLREN_API void vsDbgTick();
VSVOLREN_API bool vsDbgCheckHeap();

char * VsDecryptData( unsigned char * data, unsigned int length );

VSVOLREN_API VSRESULT vsSaveBMP ( char * Buffer, int width, int height, int bytesPerPixel, char * bmpfile );

void vsNotify( const McResult & inResult, void * inUserData );

bool vsIsNormalScalar( double inNumber );

bool vsIsNormalMatrix( McMat4f const & inMatrix );

VSVOLREN_API unsigned long vsCurrentThreadId();


////////////////////////////////////////
// multithreading
////////////////////////////////////////

VSVOLREN_API mcint64 vsAtomicIncrement( mcint64 & ioNumber );


////////////////////////////////////////
// 
////////////////////////////////////////

/** Clip polygon by plane. 
    Those parts of the polygon will remain, that lie in the
    positive half space with respect to the normal direction
    of the plane.

    \param  inPlane
            the plane, where the polygon should be clipped
    \param  inVertsSrcNum
            number of input verticies
    \param  inSrcV
            array of input vertex coords
    \param  inSrcT
            array of input texture coords
    \param  outVertsDstNum
            number of output verticies generated
    \param  outDstV
            array of output vertex coords
    \param  outDstT 
            array of output texture coords
*/
template <class V, class T>
void clipPolygonByPlane( McVec4f & inPlane, unsigned int inVertsSrcNum, const V * inSrcV, const T * inSrcT, unsigned int & outVertsDstNum, V * outDstV, T * outDstT );


/** Clip polygon by plane. 
    Those parts of the polygon will remain, that lie in the
    positive half space with respect to the normal direction
    of the plane.

    \param  inPlane
            the plane, where the polygon should be clipped
    \param  inVertsSrcNum
            number of input verticies
    \param  inSrcV
            array of input vertex coords
    \param  outVertsDstNum
            number of output verticies generated
    \param  outDstV
            array of output vertex coords
*/
void vsClipPolygonByPlane( McVec4f & inPlane, unsigned int inVertsSrcNum, McVec3f * inSrcV, unsigned int & outVertsDstNum, McVec3f * outDstV );


/** Clip polygon by a bounding box. 
    Those parts of the polygon will remain, that lie inside the
    bonding box.

    \param  inBoundingBox
            the box, where the polygon should be clipped
    \param  inVertsSrcNum
            number of input verticies
    \param  inSrcT
            array of input texture coords
    \param  outVertsDstNum
            number of output verticies generated
    \param  outDstV
            array of output vertex coords
    \param  outDstT 
            array of output texture coords
*/
template <class V, class T>
void clipPolygonByBoundingBox(McBox3f & inBoundingBox, unsigned int inVertsSrcNum, const V * inSrcV, const T * inSrcT, 
                              unsigned int & outVertsDstNum, V * outDstV, T * outDstT );


VSVOLREN_API VSRESULT intersect3Planes( McPlane const * inPlane0, McPlane const * inPlane1, McPlane const * inPlane2, McVec3f * outPos, float inEPS = 0.0f );


/*  transforms all corners of the \c inBBox and returns the bounding box of the 
    transformed points. */
VSVOLREN_API McBox3f transformBBox( const McBox3f& inBBox, const McMat4f& inMatrix );


/*  Split set of lines by a plane. 
    Just cut all input lines by the given plane. Return remaining line segments.

    \param  inPlane
            the plane
    \param  inSrcV
            array of input vertex coords two per line
    \param  outDstV
            array of output vertex coords
*/
template <class V>
void vsCutLinesByPlane( McVec4f & inPlane, const McDArray<V> & inSrcV, McDArray<V> & outDstV, float inEPS = 0.0f );

// explicit template instantiation
void vsCutLinesByPlaneV3( McVec4f & inPlane, const McDArray<McVec3f> & inSrcV, McDArray<McVec3f> & outDstV, float inEPS = 0.0f );


VSVOLREN_API void vsClipSOPTransform ( 
    McDArray< McDArray< McPlane > > const & inClipSOP
,   McDArray< McDArray< McPlane > >       & outClipSOP 
,   McMat4f                         const & inTrans
);

VSVOLREN_API void vsClipSOPTransformInv ( 
    McDArray< McDArray< McPlane > > const & inClipSOP
,   McDArray< McDArray< McPlane > >       & outClipSOP
,   McMat4f                         const & inTransInv
);

VSVOLREN_API bool vsClipSOPIsInside ( 
    McDArray< McDArray< McPlane > > const & inClipSOP
,   McVec3f                         const & inPos 
,   float                                   inEpsilon = 0.0f
);


////////////////////////////////////////
// 
////////////////////////////////////////
/*  This is a convenient class that locks a mutex
    at creation and unlocks it at destruction. Use this as local 
    variable that gets destroyed when program execution leaves 
    the scope it belongs to.
*/
class VsLocker
{
public:

    /*  Constructor. The given mutex gets instantly locked.
        \param  inMutex
                The mutex that is going to be locked. If zero no locking operations are performed.
    */
    VsLocker( McMutex * inMutex )
    :   mMutex ( inMutex )
    {
        if (mMutex)
            mMutex->lock(); 
    }

    /** Destructor. The locked mutex gets unlocked.
    */
    ~VsLocker() 
    { 
        if (mMutex)
            mMutex->unlock();
    }

protected:

    McMutex * mMutex;
};

// macro for convenient creating local VsLocker instances
#define VS_LOCKER(M) VsLocker _locker_(M);


////////////////////////////////////////
// Utility functions for OpenGL shaders 
////////////////////////////////////////

/** Create an appropriate VsTechnique2 object.
    Depending on the underlying hardware this may create either a GLSL shader
    object or an ARB shader object.
    This method should only be called if the target rendring context is 
    set as the current context.
*/
VSRESULT techniqueCreate( Vs::TechniqueAPI & outAPI, char * inTechName, McHandle<VsTechnique2> & outTechnique, bool fragmentOnly = false );


////////////////////////////////////////////////////////////////////////////////
// undocumented API
////////////////////////////////////////////////////////////////////////////////

// Returns whether a node supports overlay rendering.
// If only overlay vector graphics changed there was no need to render the full 
// scene and to transfer the whole image. Instead only a small update, assembled 
// by this method, was sent as vector information.
// While this functionality has been removed with the WAN client, this setting is
// still used to determine whether things on the WAN server must be rerendered, or
// the client can render the scene alone without requesting new image data. Probably
// in future this mechanism should be made more explicit. 
#define VS_EX_SUPPORTS_OVERLAY_RENDERING 12

/* Enables / disables decoration of a VsSlice without touching the according touch flags. */
#define VS_EX_SETDECORATION 20

struct VsExtensionUInt
{
    unsigned int mUInt;
};

/* Enums for the render-mode mask that control the kind of data to render. */
enum VsExRenderMask
{
    VS_EX_RENDER_RASTERIMAGE  = 1<<0
,   VS_EX_RENDER_OVERLAY      = 1<<1
,   VS_EX_SCOUTS_AS_RASTER    = 1<<2
,   VS_EX_RENDER_ALL          = 0xffffffff
};


/*  Some nodes within vsvolren may require two calls to the render method. One before
    any volume is beeing rendered and one after the rendered volume. One such example
    is VsSurfRen. Thus for such nodes the rendering is supplemented by two callback
    functions VsNode::extension(VS_EX_PRE_RENDER) and VsNode::extension(VS_EX_POST_RENDER).
    Call the pre-render callback before any volume is beeing rendered. Or before any
    any rendering takes place at all and the post-render callback after the volume or
    after all other nodes have been traversed. Each callback will return a VsRenderResult.
*/
#define VS_EX_PRE_RENDER 40

#define VS_EX_POST_RENDER 50

/*  Accepted by VsNode.
    Before rendering of a scene, set this to TRUE. 
    If a node renders something non-gray, is should set this to FALSE. 
    If the frame is fully rendered one can ask then if the image is grayscaled only or not.
*/
#define VS_EX_RENDERISGRAYSCALE     60  // inData is zero(FALSE) or nonzero(TRUE)
#define VS_EX_RENDERISGRAYSCALE_GET 61  // returns zero(FALSE) or nonzero(TRUE)

/*  VsSlice renders the bound in its frame-color(0) or the alternate color(1).
*/
#define VS_EX_SLICEBOUNDCOLORINDEX  70

/*  An external parameter bundle can be set with VsVolume, that 'hides' the internal bundle.
    (Used in conjunction with label data)
*/
#define VS_EX_SETPARAMETERS 80

/*  An interface for accessing the asynchronous reader thread of a VsVolume.
*/
#define VS_EX_ASYNCREADER 90
#define VS_EX_READPENDINGDATA 91

////////////////////////////////////////////////////////////////////////////////
// Error generation
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNCTION__
#define __FUNCTION__ ""
#endif

///
VSVOLREN_API void vsError( Vs::ResultCode inCode, const char * inFileName, unsigned int inLine, const char * inFunction, const char * inDate, const char * inTime, const char * inData );

/// macro that sets an McResult as last error
#define VS_ERROR(CODE) vsError( (CODE), __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__, 0 )

/// macro that sets an McResult as last error
#define VS_ERROR2(CODE,DATA) vsError( (CODE), __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__, (DATA) )

/// macro that sets an McResult as last error and returns VS_FAILED
#define VS_FAIL(CODE) do{ vsError( (CODE), __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__, 0 ); return VS_FAILED; }while(0)

/// macro that sets an McResult as last error and returns VS_FAILED
#define VS_FAIL2(CODE,DATA) do{ vsError( (CODE), __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__, (DATA) ); return VS_FAILED; }while(0)


////////////////////////////////////////////////////////////////////////////////
// OpenGL helper
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
void vsglBlendEquation( unsigned int mode );
void vsglBlendEquationSeparate( unsigned int modeRGB, unsigned int modeA );
void vsglBlendFuncSeparate( unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha );

#endif

/// @}
