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

/// @addtogroup hxvoltex hxvoltex
/// @{
#ifndef VT_VOLTEX_H
#define VT_VOLTEX_H

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbBox.h>

#include <q3intdict.h>

#include <mclib/McCutBoxPlane.h>
#include <mclib/McDArray.h>
#include <mclib/McMemArray.h>
#include <mclib/McPrimType.h>

#include <hxvoltex/SxVoltex.h>


/// Volume rendering module via a 3D texture
/**
*  Module implementing volume rendering via a set of
*  two-dimensional textures. These textures are placed
*  on a stack of planes aligned to the viewing plane.
*/

class SxVoltex3D : public SxVoltex {

    /// Inventor specific macro
    SO_NODE_HEADER(SxVoltex3D);

public:

    /// Constructor.
    SxVoltex3D();

    /// ???
    SoSFInt32 doBricking;

    /// Number of semi-transparent planes to be displayed.
    SoSFInt32 planes;


    /** Function to set up your 3D texture
    \return TRUE if successful, else FALSE.
    */
    bool set3DTexture(int width, int height, int depth,
        int nDataVar, unsigned char *data);

    /// Required by Open Inventor, initializes type
    static void initClass();

    /// amount of texture memory in Byte
    static int textureMem;

protected:


    /// ???
    int init_volume(unsigned char *data, const mculong orgdim[3],
        const float delta[3], int NDataVar);


    /// ???
    void init_volume_no_brick( void );


    /// ???
    int init_volume_brick( int texelSize );


    /// ???
    void initialize_brick( int i,
        int & slices_done,
        int & last_brick,
        int & slices_per_brick );


    /// ???
    bool init_volume_internal_brick( unsigned int & context,
        const mculong orgdim[3],
        unsigned char* & brickbuf,
        unsigned char* data );


    /// ???
    bool init_volume_internal_no_brick( unsigned int & context,
        const mculong orgdim[3],
        unsigned char* & brickbuf,
        unsigned char* data );


    /// Set volume. Returns 1 if error occurs.
    int init_volume_internal(unsigned char *data,
        const mculong orgdim[3], const float delta[3], int NDataVar,
        unsigned int context);



    /// ???
    static McMemArray<SxVoltex3D*> instanceList;


    /// ???
    static int whichViewer;


    /// ???
    enum {RENDER_SELF=0,RENDER_ALL,RENDER_ABORT};



    /// ???
    int multiRenderCheck(SoGLRenderAction *action);

    static int multiRenderCheckCount;
    static int numInstancesInThisPass;
    static SoGLRenderAction* lastRenderAction ;
    static int lastRenderCount;

    /// ???
    int isVisible(int viewer);



    /// ???
    McDArray<int> pt_order;



    /// ???
    void loadColorTable( unsigned int inContextId );



    /// ???
    void loadBrickTexture(int brick,unsigned int contextId);



    /// ???
    void prepareRenderBricks( SbVec3f & light, unsigned int inContext );



    /// ???
    //        void sortBricks(const SbMatrix& modelView,McDArray<int>& order, SbVec3f& light);
    void sortBricks( SoState* state, const SbMatrix & matModelView, const SbMatrix & matProjection, McDArray<int> & order, SbVec3f & light ) ;



    /// ???
    unsigned char* phongColorTable;


    /// Per context data
    struct ContextInfo
    {
        ContextInfo()
        :   mFragProg   ( 0 )
        ,   mVertProg   ( 0 )
        ,   mTexture1d  ( 0 )
        {
        }

        /// ???
        int     mIsInitialized;
        int     mShadersInitialized;

        /// Fragment program identifier
        GLuint  mFragProg;

        /// Vertex Program identifier
        GLuint  mVertProg;

        // id of the 1d texture
        GLuint  mTexture1d;

        /// mutex for serialized access to this structure
        QMutex  mMutex;
    };

    /// per-context info
    Q3IntDict<ContextInfo> mContextInfo;


    /// per brick data structure
    struct BrickInfo
    {
        /// get texture name by context
        GLuint & getTextureName(unsigned int contextId) ;

        // 3d texture names one for ech context-ID
        Q3IntDict<GLuint> textureNames;

        /// Texture dimensions of this brick. These are always a power of two.
        GLint dims[3];

        /// ???
        int firstZSlice;

        /// ???
        SbVec3f textureScale; // texture coordinates will first be scaled

        /// ???
        SbVec3f textureOffset; // and then biased.

        /// ???
        SbVec3f center; // center of brick in world coordinates,
                        // but relative to position of VtVoltex !

        /// Size of brick in world coordinates (width, height, depth).
        SbVec3f size;

        /// ???
        BrickInfo() : textureScale(1,1,1), textureOffset(0,0,0)
        {
            // nix
        }
    };


    /// ???
    void freeBrick( BrickInfo & brick );


    /// ???
    McDArray<BrickInfo> bricks;


    /// ???
    virtual ~SxVoltex3D();


    /// Render volume
    void GLRender(SoGLRenderAction *action);


    /// ???
    void render_brick_slices( long int k,
        int nv,
        long int num_slices,
        SbVec3f cutPoints[12] );

    /// ???
    void render_brick_volume( int nv,
        SbVec3f cutPoints[12],
        SbVec3f & boxMin,
        BrickInfo & brick );


    /// ???
    void renderBrick(int i, int which, unsigned int contextId,SbVec3f& light,int loadColorTableAfterTexture = 0);


    /// ???
    void render_slices( long int num_slices,
        float delta,
        int whichSlice,
        SbVec3f & planeCenter,
        SbVec3f & planeNormal,
        McCutBoxPlane & mcbp,
        SbVec3f cutPoints[12],
        SbVec3f & boxMin,
        BrickInfo & brick );


    /** clip input box against the attached ROI-box (if any)
    \return TRUE if the resulting box is non-empty, else FALSE.
    */
    bool clip_sub_volume( SbVec3f & boxMinClipped,
        SbVec3f & boxMaxClipped );


    /// ???
    void set_blending( void );


    /// ???
    int cutPlane(SbVec3f normal,SbVec3f center,
        SbVec3f& bMin, SbVec3f& bMax,
        SbVec3f* vertices);


    /// ???
    void sortVertices(SbVec3f* c, SbVec3f& origin,int n);


    /// ???
    static int getTextureMemory();


private:

    void bricksSortedOrtho( const McVec3f & normal, McDArray<int> & outResult );
    void bricksSortedPerspective( const McVec3f & viewPoint, McDArray<int> & outResult );
    bool isVisibleXOrtho( int i, const McVec3f & normal );
    bool isVisibleYOrtho( int j, const McVec3f & normal );
    bool isVisibleZOrtho( int k, const McVec3f & normal );
    bool isVisibleX( int i, const McVec3f & viewPoint );
    bool isVisibleY( int i, const McVec3f & viewPoint );
    bool isVisibleZ( int i, const McVec3f & viewPoint );


    /// ???
    void multiVolumeRender(unsigned int contextId);


    /// Loads the shader programs
    void init_shaders( GLuint & outVertName, GLuint & outFragName );

    /// Makes the shader programs active
    void bind_shaders( GLuint inVertName, GLuint inFragName );

    /// clears shader programs
    void clear_shaders( GLuint inVertName, GLuint inFragName );


    /// ???
    void set_interpolation( void );


    /// basis vectors in the plane(s)
    SbVec3f puVec;


    /// ???
    SbVec3f pvVec;

    /** The original dimensions of the volume. In contrast to dims[0] and
    dims[1] these numbers are not enlarged to the next power of two. */
    mculong origdims[3];

    /// ???
    static int globalNumber;

    /// Store the total video memory amount.
    int m_videoMemoryAmount;
};

#endif

/// @}
