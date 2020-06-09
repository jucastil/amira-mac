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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_OBLIQUE_SLICE_H
#define HX_OBLIQUE_SLICE_H

#include <mclib/McPrimType.h>

#include <Inventor/SbLinear.h>

#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/SoTexturedSlice.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HistogramProviderModuleIface.h>

#include <hxfield/HxScalarField3.h>
#include <hxfield/HxUniformColorField3.h>

#include <hxfield/HxPortMultiChannel.h>

#include "HxLatticeWinDLLApi.h"
#include "HxContrastInterface.h"

class SoShapeKit;
class SoTexture2;
class HxMultiSlice;
class SoAction;

/// Displays an arbitrary slice in a scalar field.

class HXLATTICE_API HxObliqueSlice : public HxArbitraryCut, public HxContrastInterface<HxObliqueSlice>
{
    HX_HEADER(HxObliqueSlice);

    class HistogramProvider : public HistogramProviderModuleIface {
      public:
        HistogramProvider(HxObliqueSlice* o);

        virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
        virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
      private:
        HxObliqueSlice* mObliqueSlice;
    };

  public:

    /// Constructor.
    HxObliqueSlice();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// extracts the slice and adds it to the object pool.
    virtual void createImage(const char* name =0);

    /// 0=histogram equalization, 1=colormap mode
    HxPortMultiMenu portMappingType;
    /// Index of portMappingType. Needed for Amira version < 5.4 script compatibility @see parse()
    int             legacyPortMappingTypeIndex;

    /// Connection to colormap.
    HxPortColormap portColormap;
    /// Global/local range. Needed for Amira version < 5.4 script compatibility @see parse()
    bool legacyPortColormapLocalRangeEnabled;

    /// Parameter used for histogram equalization.
    HxPortIntTextN portContrastLimit;

    /// 0=resolution, 1=interpol uniform fields, 2=high texture quality
    HxPortGeneric portMoreOptions;

    /// Sampling Resolution if resolution type is user-defined.
    HxPortIntTextN portResolution;

    /// How to use transparency (currently colorfield only)
    HxPortRadioBox portTransparency;

    /// How multiple slices are combined, 0=add, 1=multiply.
    HxPortMultiMenu portCombineMethod;

    /// Enable or disable channels of a multi-channel field.
    HxPortMultiChannel portMultiChannel;

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    void updateMultiSlice(HxMultiSlice*);

    ///
    void removeMultiSlice(HxMultiSlice*);

    /// Returns size of texture image.
    const SbVec2s& getTextureSize() { return size; }

    enum SamplingMode
    {
        RESOLUTION
    ,   INTERPOL_DATA
    ,   INTERPOL_TEXTURE
    ,   SQUARE_TEXELS_ON_ORTHO_PLANES
    ,   LOW_RES
    };

    /// set the resolution of level to s1 x s2
    McString setResolution(int level, int s1, int s2);

    /**
     * Returns extracted scalar data (can be NULL) 
     */
    virtual float* getScalarData() { return scalar; }

  protected:

    virtual ~HxObliqueSlice();

    //handle projection activation
    virtual void projectionActivated();

    //handle projection deactivation
    virtual void projectionDeactivated();

    HxField3          * field;
    SoSeparator       * mSeparator;
    SoTexturedSlice   * mSlice;
    int                 alphaThreshold;
    unsigned int        isLabelLat:1;
    unsigned int        isMultiChannel:1;
    int                 m_sliceOrientation;

    McDArray<HxMultiSlice*>
                        otherSlices;

    SbVec3f             mOrig;  ///> center of slice
    SbVec3f             muVec;  ///> 1st basis vector
    SbVec3f             mvVec;  ///> 2nd basis vector

    /// Size of texture image (128x128 on default, 256x256 in high res mode).
    SbVec2s size;

    /// stores resolutions for all levels.
    McDArray<SbVec2s> sizeTable;

    /// This is only used in doOrtho() which is disabled currently.
    SbVec2s factor;

    /// Here the resampled field values are stored.
    float* scalar;

    /// This is true if a color field is processed.
    bool rgbaSlice;

    /// This is @c mc_int32 in case of color fields, @c mc_float otherwise.
    McPrimType sliceDataType;

    virtual void doGeneric();  /// Currently we always use dogeneric() because

    /// Operate filtering on extract data. Does nothing by default.
    virtual void doFiltering() {}

    void computeSize();
    void extractSlice();
    void computeTexture();
    /// alpha=0 means skip alpha, alpha=1 binary alpha,alpha=2 take alpha,
    void setTexture( int nc, int alpha=0);

    void savePorts(FILE *fp);

    HxUniformColorField3* createColoredData(SoTexturedSlice* slice);

    /// To store the max supported texture size once for all.
    static int m_maxTextureSize;

    /// To know if portResolution max value is initialized.
    bool m_portResolutionMaxIsInitialized;

    /// To update portResolution min/max.
    void updatePortResolutionMinMax();

    /// The callback called by OIV during a traversal.
    static void oivTraversalCB(void* userData, SoAction* action);

  private:
    HistogramProvider mHistogramProvider;
};

#endif // HX_OBLIQUE_SLICE_H

/// @}
