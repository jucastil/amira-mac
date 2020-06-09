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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef HX_HISTOGRAM_H
#define HX_HISTOGRAM_H

#include <hxcore/HxModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortGeneric.h>
#include <hxsurface/HxSurfaceScalarField.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxTetraData.h>
#include <hxfield/HxHexaData.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxTetraScalarField3.h>
#include <hxfield/HxHexaScalarField3.h>
#include <hxlines/HxLineSetInterface.h>
#include <hxstatistics/HxSpreadSheet.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>

class PzPlot;
class PzAxis;
class PzCurve;
class PzMarkerline;
class HxVolumeDataObject;


/// Computes the histogram and other statistical properties of a data set.

class HXSTATISTICS_API HxHistogram : public HxModule {

  HX_HEADER(HxHistogram);

  public:
    /// Constructor
    HxHistogram();

    /// Compute method
    virtual void compute();

    /// Compute method
    virtual void update();

    /// Input port for region of interest.
    HxConnection portRoi;

    /// label field
    HxConnection portLabels;

    /// Info port displays mean and standard deviation.
    HxPortInfo portInfo;

    /// Info port displays mean and standard deviation within range.
    HxPortInfo portInfo2;

    /** Defines range of histogram (data values are clamped to this),
        resets range to min max of input data. */
    HxPortGeneric portRange;

    /// Number of bins of histogram
    HxPortIntSlider portNumBins;

    /// Histogram options
    HxPortGeneric portHistOptions;

    /// Plot options
    HxPortToggleList portPlotOptions;

    /// Defines threshold and displays the percentage of above values
    HxPortGeneric portThreshold;

    /// Index (0...100) for computing index value.
    HxPortGeneric portIndex;

    /// Material menu.
    HxPortMultiMenu portMaterial;

    /// Menu for selecting a data column of a spreadsheet.
    HxPortMultiMenu portSpreadSheetDataChannel;

    /// Menu for selecting a data channel of a lineset.
    HxPortMultiMenu portLineSetDataChannel;

    /// 0=show or hide plot window
    HxPortDoIt portAction;

    /// Returns the computed histogram.
    const McDArray<int> & getBins();

    /// Returns the computed histogram between requested range.
    const McDArray<int> & getBins( float min, float max );

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0) { if ( !theHistogramPlotWin ) createPlotWindow(); return theHistogramPlotWin; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

    ///
    float doGetThresholdValue() {return thresholdValue;}
    float doGetIndexValue() {return indexValue;}

  protected:

    PzPlot*       theHistogramPlotWin;
    PzAxis*       axis;
    PzCurve*      frequencies;
    PzCurve*      cumulative;
    PzCurve*      rightcumulative;
    PzCurve*      differential;
    PzMarkerline* tindexmarker;
    PzMarkerline* threshmarker;
    int           rangeAlreadySet;

    HxTetraScalarField3* tetraField;
    HxHexaScalarField3* hexaField;
    HxSurfaceField* surfaceField;
    HxRegScalarField3* latticeField;
    HxVolumeDataObject* volumeDataObject;
    HxLineSetInterface* pLineSet;
    HxSpreadSheet* spreadsheet;
    int fieldType;
    bool recompute;

    McDArray<int> count;
    bool histoUpToDate;
    float indexValue;
    float thresholdValue;

    // All values, not restricted to range
    float mean;
    float deviation;
    float rms;

    // Values restricted to range
    float meanRes;
    float devRes;
    float rmsRes;

    // Sub-volume, region-of-interest
    McBox3f subVolumeBox;
    int useSubVolume;

    // Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    // Checks if pos is contained in ROI ?
    inline bool contained(const McVec3f &pos) { return subVolumeBox.contains(pos); }

    virtual void saveState(FILE* fp, const char* dataDir, int saveFlags);

    // Type of the input field
    enum { UNKNOWN_TYPE=-1, SURFACE_TYPE=0, HEXA_TYPE=1, TETRA_TYPE=2, LATTICE_TYPE=3, VOLUME_DATA_OBJECT=4, LINE_TYPE=5, SPREADSHEET_TYPE=6 };

    void savePorts(FILE* fp);

    ~HxHistogram();

    void createPlotWindow();
    void resetPortRange();

    void computeHistogram();

    void computeIndexValue();
    void computeThresholdValue();

    void computeHistogramOfLattice(float min, float max, McDArray<int>& histo,
        mclong& countRes, double& sumRes, double& sum2Res,
        mclong& count, double& sum, double& sum2);

    static void plotUpdated(PzPlot* plotwin, void* userdata);
private:
    /// @{
    /// \warn inheritance for internal use only.

    /// Returns the range of the input data.
    virtual void getRange(float& min, float& max);

    /// fill histogram information
    virtual void computeHistogram(float min, float max, McDArray<int>& histo,
                                  mclong& countRes, double& sumRes, double& sum2Res,
                                  mclong& count, double& sum, double& sum2)
    {
      m_computeHistogramImplemented = false;
    }

    /// Check input type.
    virtual bool checkInput();

    /// @}

    bool m_computeHistogramImplemented;
};

#endif

/// @}
