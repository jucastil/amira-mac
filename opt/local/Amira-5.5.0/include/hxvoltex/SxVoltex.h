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
#ifndef SX_VOLTEX_H
#define SX_VOLTEX_H

#include <qthread.h>
#include <QMutex>

#include <mcgl/mcgl.h>

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <mclib/McMemArray.h>
#include <mclib/McPrimType.h>

///
#if !defined(_WIN32)
#define __stdcall
#endif

#include "HxVoltexWinDLLApi.h"

class HxVoltex;

/// Base class for 2D and 3D direct volume rendering nodes
class HXVOLTEX_API SxVoltex : public SoShape {

        /// Inventor specific macro
        SO_NODE_HEADER(SxVoltex);

public:
        /// Constructor.
        SxVoltex();

        /// World coordinates of node 0,0,0
        SoSFVec3f position;


        /// Base opacity of slices.
        SoSFFloat alphaScale;


        /// Do maximum intensity projection ?
        SoSFBool mip;

        /// ???
        SoSFInt32 useSubVolume;

        /// Set volume. Returns 1 in case of error.
        virtual int init_volume(unsigned char *data,
                                const mculong n[3], const float delta[3], 
                                int nChannels);



        /// Perfoms initialization for Inventor
        static void initClass();


        /// Instead of showing the volume, display the slices used
        int showSlices;


        /// Used to distinguish between the different OpenGL extensions
        enum 
        { 
            VOLTEX_NO_EXTENSION                     = 0,
            VOLTEX_SGI_TEXTURE_COLOR_TABLE          = 1,
            VOLTEX_EXT_PALETTED_TEXTURE             = 2,
            VOLTEX_NV_VERTEX_AND_FRAGMENT_PROGRAM   = 3,
            VOLTEX_ARB_VERTEX_AND_FRAGMENT_PROGRAM  = 4,
            VOLTEX_ATI_FRAGMENT_SHADER              = 5
        };

private:
        /// Variable to control use of OpenGL extensions
        unsigned int render_extension;

        /// the OpenGL capabilities need to be detected if an OpenGL context is active. Until this detection this flag remains false.
        bool render_extension_detected;

public:
        /// Finds the best extension for colortables
        static unsigned int best_extension( void );


        /// Sets the type of OpenGL extension used
        void set_render_extension( unsigned int ext );


        /// Gets the actual OpenGL extension used
        unsigned int get_render_extension( void );

        /// returns true if the render extension was already detected
        bool get_render_extension_detected( void );

        /// Reinitializes the node and OpenGL state
        virtual void init_shaders( void );


        /// amount of texture memory in Byte
        static int textureMem;

    
        /// Sets the transfer function
        virtual void set_transfer_function(unsigned char* table, int nDataVar);


        /// Variable controlling the verbosity of output messages
        static int verbose;


        /// Pointer to this node, used by child nodes
        HxVoltex* hxvoltex; 


        /// Variable controlling the use of multi volume rendering capabilities
        static int doMultiVolumeRendering;


        /// ???
        SbBox3f subVolumeBox;


        /// Is a color table supported on that platform
        bool hasColorTable( void );


        /// Do we use the color table now
        bool use_color_table( void );


        /// Set/unset preferred colortable extension
        virtual void set_colortable( unsigned int i );

protected:

        /// Used to distinguish vertex from fragment programns
        enum { VERTEX_PROGRAM = 0, FRAGMENT_PROGRAM = 1 }; 


        /// Node specific mutex for multi-pipe configurations
        QMutex instanceMutex;

        /// Load a vertex/fragment program
        void load_program( const McString & name, const unsigned int program_type );

        /// Distinguish between voltex modules
        enum { VOLTEX_2D, VOLTEX_3D };

        /// Initialize fragment shaders for pseudo-shading (Nvidia version)
        void init_shaders_nv( int which_voltex, GLuint & outVertName, GLuint & outFragName );
        void bind_shaders_nv( GLuint inVertName, GLuint inFragName );
        void clear_shaders_nv( GLuint inVertName, GLuint inFragName );

        /// Initialize fragment shaders for pseudo-shading (ARB fragment programs).
        void init_shaders_arb( int which_voltex, GLuint & outVertName, GLuint & outFragName );
        void bind_shaders_arb( GLuint inVertName, GLuint inFragName );
        void clear_shaders_arb( GLuint inVertName, GLuint inFragName );

        void init_shaders_ati( int which_voltex, GLuint & outVertName, GLuint & outFragName );
        void bind_shaders_ati( GLuint inVertName, GLuint inFragName );
        void clear_shaders_ati( GLuint inVertName, GLuint inFragName );

        /// Small helper function to check OpenGL errors
        int check_error( int line, char * file );

        /// Vertex program string representation
        McString vertex_program_text;

        /// Fragment program string representation
        McString fragment_program_text;

        /// Pointer to the volume data
        unsigned char* volumeData;

        /// Dimension of volume in x, y and z direction
        mculong volumeDims[3];

        /// ???
        float volumeDelta[3];

        /// Number of channels in the volume
        int volumeNChannels;

        /// Is the node already initialized with the volume data?
        int initialized;

        /// Distinguishes between the different color table extensions
        GLenum mGLTextureColorTableEnum;

        void detectTextureColorTableEnum();

        /// Do we use texture colortables?
        static int textureColorTableEnabled;
    
        /// ???
        SbVec3f center;

        /// ???
        SbBox3f box;

        /// ???
        void getDiagonal();

        /// ???
        float diagonal,diagonal2;

        /// ??? (should be per thread in the future)
        float pt_lastModelViewGL[16];

        /// ??? (should be per thread in the future)
        SbVec3f pt_light;

        /* these should be per thread in the future */
        SbMatrix pt_modelView;

        /// The transfer function    
        McDArray<unsigned char> transferFunc[3];

        /// key of the currently used transfer function - gets increased on every CT change
        mcuint64    transferFuncKey;

        /// Dimensions in world coordinates
        float height, width, depth;


        /// Number of texture components
        int          nDataVar;


        /// Dimenstion in x, y and z
        mculong dims[3];


        /// ???
        virtual void generatePrimitives(SoAction *action);
    

        /// ???
        virtual void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);
    

        /// Destructor
        virtual ~SxVoltex();
 

        /// Main render function
        void GLRender(SoGLRenderAction *action);
    

        /// ???
        static int getTextureMemory();

public:

        static int      mInstanceCount; // number of current instances
        static mcint64  mOpenGLAlloc;   // we assume that OpenGL has allocated this amount of bytes
        static mcint64  mOpenGLUsing;   // we assume that it actually uses this anmount of memory from that chunk
        static mcint64  mTexSizeCurr;   // we've allocated this amount of bytes for textures
        static QMutex   mStaticMutex;   // lock before access to the statics


        /// Return val's next power of two.
        static int find2Bigger(int val);

        /// ???
        static int find2Smaller(int val);

private:
        /// Render two or more volumes
        /** This is complicated by the fact that
         *  to or more volumes can overlap each
         * other
         */ 
        void multiVolumeRender(int orientation, int sign);


        /// Is the color table currently used?
        bool color_table_used;

};

/// test if the given amount of memory is currently allocable
bool hxvoltex_hasMemory( mcint64 inSize, bool inForceLinear = false );

/// check if there is a valid corrent OpenGL context
bool hxvoltex_hasGLContext();

#endif

/// @}
