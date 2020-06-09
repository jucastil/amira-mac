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
#ifndef HX_VOLTEX
#define HX_VOLTEX

#include <QObject>

#include <mclib/McHandle.h>
#include <mclib/McPrimType.h>

#include <mcgl/mcgl.h>

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HxColormap256.h>
#include <hxcolor/HistogramProviderModuleIface.h>

#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxUniformScalarField3.h>

#include <hxfield/HxPortMultiChannel.h>

#include "SxVoltex.h"
#include "SxVoltex3D.h"
#include "SxVoltex2D.h"
#include "HxVoltexWinDLLApi.h"

class SoNode;

/// Module for texture-based volume rendering.
class HXVOLTEX_API HxVoltex : public HxModule {

        /// Mclib Typed Object macro
        HX_HEADER(HxVoltex);

        class HistogramProvider : public HistogramProviderModuleIface {
            public:
                HistogramProvider(HxVoltex* owner);

                virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
                virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
            private:
                HxVoltex* mOwner;
        };

public:

        /// Conctructor.
        HxVoltex();


        /// Ports are shown or hidden here.
        virtual void update();

        /// Compute method.
        virtual void compute();

        /// Parse the interpreter commandline and execute commands
        int parse(Tcl_Interp* t, int argc, char **argv);

        /// See HxObject
        void savePorts(FILE* fp);




        /// bool. indicates if there should be an interpolation for voxel value lookup
        unsigned int doInterpolationVOX(){ return mDoInterpolationVOX; }

        /// bool. indicates if there should be an interpolation for color-table lookup
        unsigned int doInterpolationCT(){ return mDoInterpolationCT; }

        /// Input port for region of interest.
        HxConnection        portRoi;

        /// Modes: 0=mip, 1=color table
        HxPortToggleList    portOptions;
        enum { M_MIP=0, M_COLORTABLE=1 };

        /// Range is used only if no colormap is present
        HxPortFloatTextN    portRange;

        /// Texture lookup mode: 0=alpha, 1=luminance-alpha, 2=rgba
        HxPortRadioBox      portLookup;
        enum { M_ALPHA=0, M_LUMINANCE_ALPHA=1, M_RGBA=2 };

        /// Colormap defines transfer function.
        HxPortColormap      portColormap;

        /// Gamma scale for multi-channel data
        HxPortFloatSlider   portGamma;

        /// Overall alpha scale factor (alpha value of slices)
        HxPortFloatSlider   portAlphaScale;

        /// Toggles between 2D and 3D mode.
        HxPortRadioBox      port2D3D;

        /// Number of slices to be used in 3D mode.
        HxPortIntSlider     portSlices;

        /// Input volume is downsampled by these integer factors.
        HxPortIntTextN      portDownsample;

        /// For switching parts of a multi-channel field on or off.
        HxPortMultiChannel  portMultiChannel;

        /// Recompute and load OpenGL texture.
        HxPortDoIt          portAction;

        ///
        HxColormap* getColormap();


protected:

        /// ???
        float f0,r;


        /// dimenstion of the grid in x, y and z direction
        mculong dims[3];


        /// downsampled dimension pf the grid in the x, y and z direction
        mculong ddims[3];


        /// Destructor
        virtual ~HxVoltex();


        /// Pointer to the 3D rendering node
        McHandle<SxVoltex3D> voltex3D;


        /// Pointer to 2D rendering node
        McHandle<SxVoltex2D> voltex2D;


        /// Pointer to the voltex node
        SxVoltex * voltex;


        /// Inventor separator
        McHandle<SoSeparator> separator;


        /// Inventor dragger
        McHandle<SoTabBoxDragger> dragger;


        /// Inventor sensor callback
        static void sensorCallbackCB(void* userData, SoSensor* sensor);


        /// Inventor sensor callback
        void sensorCallback(SoSensor* sensor);


        /// Inventor sensor
        SoNodeSensor* sensor;


        /// Holds the volume data
        unsigned char* voltexBuffer;


        /// Size of the voltex buffer
        /** This can be only 0 or x * y * z * number_of_channels
         */
        mculong        voltexBufferSize;


        /// Have we to hit the Doit button?
        bool volumeUpToDate;


        /// Sets the new transfer function
        void set_transfer_function( void );


        /// Sets the new transfer function
        void set_transfer_function( int i );


        /// Fills the voltex buffer
        void fillVoltexBuffer(void* data,McPrimType pt,const mculong* dims, HxColormap* colormap, int nChannels);


        /// Voltex buffer filling, 2nd incarnation
        void fillVoltexBuffer(void* data,McPrimType pt,const mculong* dims, float min, float max);


        /// Fills the voltex buffer, 3nd incarnation
        void fillVoltexBuffer(HxMultiChannelField3*, const mculong* ddims);

        



private:
        

        ///
        void computeDefaultColormap();

        ///
        void setExtension( );

        /// If colormap is used we update the display faster
        bool fast_update;


        /// Initializes the SxVoltex node
        void init_voltex( void );


        /// Initializes the field and lattice members
        void init_field_and_lattice( void );


        /// Converts data in the right format
        void convert_data( void );


        /// Should we really compute
        bool really_compute( void );


        /// Set to 1, 2, or 4 channels
        /// number of channels in the preprocessed dataset
        /// the original dataset may have a different number of channels
        void set_channels( int & channels );


        /// Update if the user has changed settings
        void update_user_changes( void );


        /// Sets the dimension
        void set_dims( void );



        /// Resampling the volume
        void resample( void* & src_data, McPrimType& pt, void* & temp_mem );


        /// bla
        void fill_buffer( int & num_channels, void* & src_data, McPrimType & pt, void* & temp_mem, unsigned char* & tmp );


        /// bla
        void update_viewer( int byte_range, unsigned char* & tmp, float* delta, int & num_channels );


        /// bla
        void update_transformation( float* delta );


        /// bla
//        void allocate_buffer( int num_channels, void* temp_mem );

        /// allocates a voltex buffer of the required size
        void voltexBufferAllocate( mcuint64 inLength );



        /// bla
        static int verbose;


        ///  remember the input
        HxObject                * object;
        ///  remember the input
        HxUniformScalarField3   * field;
        ///  remember the input
        HxUniformColorField3    * colfield;
        ///  remember the input
        HxMultiChannelField3    * multifield;
		/// tell if we are managing labels
		bool					isLabeledLattice;


        /// bla
        HxLattice3              * lattice;


        /// bla
        int byte_range;


        /// This is the best supported extension
        unsigned int preferred_extension;

        /// bool. indicates if there should be an interpolation for the voxel values
        unsigned int mDoInterpolationVOX;

        /// bool. indicates if there should be an interpolation for color-table lookup
        unsigned int mDoInterpolationCT;


        /// Two-dimensional pre-integrated transfer function
        unsigned char pre_table[256][256][4];

        McHandle<HxColormap256> defaultColormap;

        HistogramProvider mHistogramProvider;
};

#endif

/// @}
