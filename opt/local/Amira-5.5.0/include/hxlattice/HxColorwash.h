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
#ifndef HX_COLORWASH
#define HX_COLORWASH


#include <mclib/McBitfield.h>

#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxScalarField3.h>
#include <hxlattice/HxOrthoSlice.h>

#include <hxlattice/HxLatticeWinDLLApi.h>

struct Face;
struct Vertex2;

/// This class modifies the texture of an OrthoSlice module.
class HXLATTICE_API HxColorwash : public HxOverlayModule {

  HX_HEADER(HxColorwash);

  class HistogramProvider : public HistogramProviderModuleIface {
      public:
        HistogramProvider(HxColorwash* owner);

        virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
        virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
      private:
        HxColorwash* mOwner;
    };

  public:
    /// Constructor.
    HxColorwash();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    // This method is called by an OrthoSlice module.
    virtual void colorwash(unsigned char* data, int size[3],
        int factor[2], mculong dim[2]);

    /// The colormap to be used.
    HxPortColormap portColormap;

    /// Menu for choice of fusion method
    HxPortMultiMenu portMethod;

    /// Percentage of first modality for mixing the pixel values
    HxPortFloatSlider portMixFactor;

    /// Checkerboard width of magic lens
    HxPortIntSlider portLenseWidth;

    /// Overlay range
    HxPortFloatTextN portRange1;

    HxPortFloatSlider portLabelBlendingAlpha;
    HxPortToggleList portLabelBlendingOptions;

    /// Returns portModule as primary port
    virtual int autoConnect(HxObject* primary);
  protected:

    virtual ~HxColorwash();

    enum { cw_multiply=0, cw_add=1, cw_weightedSum=2, cw_magicLense=3, cw_overlay=4,
           cw_alphaBlending=5, cw_luminanceBlending=6, cw_labelBlending=7, cw_none=8  };

    enum LabelBlendingOptions {LabelBlendingColorExterior=0, LabelBlendingUseColormap=1};

    McHandle<HxOrthoSliceBase> orthoSlice;
    McHandle<HxScalarField3> field;
    McHandle<HxColormap> colormap;

    mculong nValuesPerSlice;
    float*  extractedSlice;

    McBitfield validValues;

    unsigned char*  texData;
    int size[3];
    mculong dim[2];
    int nearestNeighbor;

    void extractSliceGeneric(int factor[2]);
    void combineSlices();

    void multiplyPixel();
    void addPixel();
    void mixPixel();
    void magicLense();
    void overlay();
    void alphaBlending();
    void luminanceBlending();
    void labelBlending();

    void extractSliceTetra(int factor[2]);
    void polyScan(const Face& p);
    void scanline(int y, Vertex2& l, Vertex2& r);

  private:
    HistogramProvider mHistogramProvider;
};

#endif

/// @}
