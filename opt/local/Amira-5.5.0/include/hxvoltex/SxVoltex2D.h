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
#ifndef SX_VOLTEX2D_H
#define SX_VOLTEX2D_H

#include <q3intdict.h>

//#include <hxcore/hxgl.h>
#include <hxvoltex/SxVoltex.h>
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

#include <mclib/McDArray.h>
#include <mclib/McMemArray.h>
#include <mclib/McPrimType.h>

/// Volume rendering module via 2D textures
/**
 *  Module implementing volume rendering via a set of 
 *  two-dimensional textures. These textures are rendered
 *  on three stacks of object-aligned planes which gives the 
 * illusion of a three-dimensional volume. 
 */
class HXVOLTEX_API SxVoltex2D : public SxVoltex 
{

        /// Inventor specific macro
        SO_NODE_HEADER(SxVoltex2D);

public:

        /// Constructor.
        SxVoltex2D();


        /// Destructor
        virtual ~SxVoltex2D();


        /// Initializes the volume.
        /** Copies the volume data  from the input node
         *  Returns 1 if texture is too large.
         */
        int init_volume(unsigned char *data,
                        const mculong orgdim[3], const float delta[3], int nChannels);


        /// Sets the transfer function to the new values
        virtual void set_transfer_function(unsigned char* table, int nDataVar);


        /// Perfoms initialization for Inventor
        static void initClass( void );


        /// Initializes this class
        void init( void );



        /// Gets the currently used extension
        unsigned int get_colortable( void );


        /// Set/unset colortable extension
        void set_colortable( unsigned int i );


private:

        /// List of instances of this node
        /** This list tracks the total number of instances in the object 
         *  pool
         */ 
        static McMemArray<SxVoltex2D*> instanceList;


        /// Used to identify the current viewer
        static int whichViewer;

        /// Used to distinguish between single and multi volume rendering
        enum {RENDER_SELF=0,RENDER_ALL,RENDER_ABORT};

        
        /// Checks whether there are one or more volumes to render
        /** One single volume is easy to render, but two and more
         * volumes can overlap and then we have to sort the texture
         * slices.
         * (: I'm not sure whether this works because the slices
         * are object aligned ?!?)
         */
        int multiRenderCheck(SoGLRenderAction *action);

        /// Loads the shader programs
        int init_shaders( GLuint & outVertName, GLuint & outFragName );

        /// Makes the shader programs active
        void bind_shaders( GLuint inVertName, GLuint inFragName );

        /// Checks visibility
        int isVisible(int viewer);


        /// Render this node
        /* Note: Normally this is rendered into a display list
         * and so only executed once
         */
        void GLRender(SoGLRenderAction *action);


        /// render slice blending equation setup
        void render_slice_setup_blend( void );


        /// setup color
        void render_slice_setup_color( int orientation );


        /// render
        void render_slice_render( int which_slice, SbVec3f v[4], SbVec2f tc[2] );


        /// set vertices
        void render_slice_set_vertices( int orientation,
                                        int & idx0,
                                        int & idx1,
                                        SbVec3f v[4],
                                        float & c,
                                        SbVec3f & offset,
                                        SbVec3f & vs );

        /// texture coords
        void render_slice_set_texture_coordinates( int orientation,
                                                   SbVec2f tc[2],
                                                   int & idx0,
                                                   int & idx1, 
                                                   float & c,
                                                   SbVec3f v[4] );


        /// bind tex
        void render_slice_setup_texture( unsigned int & context,
                                         int & orientation,
                                         int & which_slice );


        /// Render one slice of the texture stack
        void renderSlice(int i, int which, unsigned int context);


        /// Get the texture identifiers for this orientation
        McDArray<GLuint>& getTextureNames( unsigned int context, int orientation );


        /// Helper class to manage textures
        class TexturesCreateStruct 
        {
        public:
            TexturesCreateStruct()
            :   isInitialized       ( 0 )
            ,   shadersInitialized  ( 0 )
            ,   _fragProg           ( 0 )
            ,   _vertProg           ( 0 )
            ,   _tex1dName          ( 0 )
            ,   _tex1dKey           ( 0 )
            {
                for ( int i=3 ; i-- ; )
                {
                    mDirectionPermitted [i] = false;
                    mDirectionRendered  [i] = false;
                    mTexMemPerDim       [i] = 0;
                }
            }

            void preRelease(int ori=-1)
            {
                SxVoltex::mStaticMutex.lock();
                for ( int i=3 ; i-- ; )
                {
                    if ( textureNames[i].size() && (ori<0 || ori==i))
                    {
                        SxVoltex::mTexSizeCurr -= mTexMemPerDim[i];
                        SxVoltex::mOpenGLUsing -= mTexMemPerDim[i] * (mDirectionRendered[i]?2:1);
                        mTexMemPerDim[i] = 0;
                        mDirectionPermitted[i] = false;
                        assert( SxVoltex::mTexSizeCurr>=0 );
                        assert( SxVoltex::mOpenGLUsing>=0 );
                    }
                }
                SxVoltex::mStaticMutex.unlock();
            }

            /// Is this texture already initialized?
            int isInitialized;

            ///
            int shadersInitialized;

            /// Lock for multipipe environments
            QMutex contextMutex;

            /// Fragment program identifier
            GLuint           _fragProg;

            /// Vertex Program identifier
            GLuint           _vertProg;

            /// 1D colormap texture identifier
            GLuint           _tex1dName;

            /// key of the current colormap
            mcuint64         _tex1dKey;

            /// true, if this direction can be rendered
            bool            mDirectionPermitted[3];

            /// true, if this direction was rendered for at least one time
            bool            mDirectionRendered[3];

            /// size of all textures for per direction
            mcint64         mTexMemPerDim[3];

            /// Array of texture identifiers per direction
            McDArray<GLuint> textureNames[3];
        };


        /// Texture managing variable
        Q3IntDict<TexturesCreateStruct> texturesCreated;



        /// This sets the texture for a slice
        /** The previous extracted data is used to specify a texture
         * for the graphics library
         */
        int set_texture( int width, int height,
                         int nDataVar, unsigned char *data);

        /// Initialize textures from the volume
        /*  The name is somewhat misleading: The volume was already
         *  initialized in init_volume, here we initialize our
         *  texture-based volume representation from the regular
         *  sample grid.
         */
        int init_volume_internal(unsigned char *data,
                                 const mculong orgdim[3], const float delta[3], 
                                 int nChannels, unsigned int context);


        /// Load a color table into the graphics library
        /*  This is only used if the color_table, paletted_texture
         *  or fragment_program extension is available
        */
        void loadColorTable(int orienation);


        /// Render two or more volumes in one viewer
        /* This is the complicated path: volumes can overlap, so we have
         * to sort the slices
        */
        void multiVolumeRender(int orientation, int sign, unsigned int context);


        /// Set the interpolation for texture lookup
        void set_interpolation( void );


        /// This is used in the computation of the texture coordinates
        SbVec2f             texCoords[3];


        /// Sample distance in x, y and z
        float dx,dy,dz;


        /// Used for computing a new light position
        float light_idx;


        /// Position of the light source
        GLfloat LightPos[4];


        /// Helper class for sorting slices
        /** This is used in multiVolumeRender for
         * sorting all the slices of all the visible
         * volumes
         */
        class Slice {
        public:

                /// Pointer to instances to distinguish the volumes
                SxVoltex2D * instance;


                /// Index of the slice
                int idx;


                /// Z depth of this slice
                float z;

        };


        /// Compare the slices of all volumes for sorting and rendering them
        static int compareSlices(const void *s1, const void *s2);

        /// texture unit which processes the transfer function texture (0 if disabled GL_TEXTURE0 or GL_TEXTURE1)
        int unit1D;
        /// texture unit which processes the 2d slice texture (GL_TEXTURE0 or GL_TEXTURE1)
        int unit2D;
};


#endif

/// @}
