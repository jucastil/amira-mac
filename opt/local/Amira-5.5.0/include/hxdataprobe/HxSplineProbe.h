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

/// @addtogroup hxdataprobe hxdataprobe
/// @{
#ifndef HX_SPLINE_PROBE
#define HX_SPLINE_PROBE

#include <hxdataprobe/HxDataProbe.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortFloatTextN.h>

class PzPlotGroup;
class PzCurve;
class PzAxis;
class PzPlot;
class PzPlotArea;

class HxLineSet;

#define NO_INTERPOLATION -1
#define LINEAR_INTERPOL 0
#define SPLINE_INTERPOL 1

///
class HXDATAPROBE_API HxSplineProbe : public HxDataProbe {

  HX_HEADER(HxSplineProbe);

  public:
    ///
    HxSplineProbe(const int numPoints = 4, const bool changeable = true);

    ///
    HxPortRadioBox portSampleOrDist;

    ///
    HxPortIntSlider portSamplesSlider;

    ///
    HxPortFloatSlider portDistSlider;

    ///
    HxPortToggleList portAverage;

    /// select averaging mode (0 - mean, 1 - maximum, 2 - minimum)
    HxPortRadioBox portAverageOptions;

    ///
    HxPortFloatSlider portRadius;

    ///
    HxPortFloatSlider portLongitudWidth;

    ///
    HxPortButtonList portPlotWinButton;

    ///
    HxPortFloatTextN portOffset;
    
    ///
    virtual void update();

    ///
    virtual void compute();

    ///
    void info();

    ///
    void setOrder(int order);

    ///
    int getOrder() { return splineOrder; }

    ///
    void setInterpolMode(int mode);

    ///
    int getInterpolMode() { return interpolMode; }

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0);

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

    /** Reimplemented for internal reasons. The method shows or hides
        the plot window. Afterwards, it calls HxModule::setViewerMask(). */
    virtual void setViewerMask(int mask, int master=0xffff);

    ///
    void savePorts(FILE* fp);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /**
     *  Remain probe results displayed in the probe plot window
     *  after this class has been deleted.
     */
    static void remainProbeResultDisplayed(bool remainDisplayed);

    /**
     *  Remove all remaining probe results from the probe plot window
     */
    static void clearRemainingDisplayedResults();

    /**
     *  Delete or not the plot window which represent the probing result when
     *  last probing module is deleted.
     *  If true (the default), this window will be deleted (and so invisible) when
     *  last HxSplineProbe is deleted.
     *  Otherwise, this window remains active. It allow to always have the probe plot window
     *  at the same location (screen, position) and size even if all probing module have been
     *  removed and the probe plot window has been closed.
     */
    static void deleteSplineProbePlotWinOnLastModuleDelete(bool deleteOnLastProbeModuleClose);

    /**
     *  Create the line set which represent all the sample points.
     *  This HxLineSet module will automatically be added to the pool.
     */
    HxLineSet* createLineSet ();

    /**
     *  Set if this module must plot probe samples in the plot window. 
     *  Useful if you use this class just to display a spline. True by deafult.
     */
    void plotProbeSamples(bool plotThem);

    const McString & getCurveName(int i) const { return curveNames[i]; }

    void renderLines(bool state);
  protected:

    virtual ~HxSplineProbe();

    virtual void showLine(SoSeparator* sep);

    /// List of sample points
    McDArray<SbVec3f *> sampleNormals;

    McDArray<SbVec3f *> m_controlPoints;

    int                 interpolMode, splineOrder;

    enum AverageOption {
        AO_AVG,  // average
        AO_MAX,  // maximum
        AO_MIN   // minimum
    };

    // p1 and p2 are pointers to arrays of size 6.
    // Type refers to the number of components in p1 and p2.
    // Returns -1 if p1 is smaller than p2
    // Returns  0 if p1 equals p2
    // Returns +1 if p1 is larger than p2
    int comparePoints(const float *p1, const float *p2, int type);

    float    distSamples;
    McDArray<float> samplePoints;
    McDArray<int>   sampledIndex;
    int      startingPoint;
    float    zoomedLength;
    bool     useDist, useAdaptive;
    bool     m_renderLines;

    int numCurves;
    McString curveNames[6];
    
    float    plotXRange, plotYRange;
    float    plotXMin, plotXMax;
    bool     newprobing;
    bool     m_plotSamples;

    static bool s_remainProbeResultsDisplayed;
    static bool s_deleteSplineProbePlotWin;

    int continousSampleLocs();

    int adaptiveSampleLocs();

    int discreteSampleLocs();

    int fromDisplayedSplineSampleLocs();

    int getSamples();

    void renderControlPoints(bool show = true);

    void computeCurveControlPoints(McDArray<SbVec3f*>& controlPoints) const;
    void computeCurve();

    void tesselateSpline(const McDArray<SbVec3f *>& splineToTesselateControlPoints,
                         McDArray<SbVec3f>& tesselatedSplinePoints) const;

    void computeFeedbackControlPointsAppendMode(McDArray<SbVec3f*>& feedbcakControlPoints, const SbVec3f& feedback3DPos) const;
    void computeFeedbackControlPointsModifyMode(McDArray<SbVec3f*>& feedbcakControlPoints, const SbVec3f& feedback3DPos) const;
    virtual void renderFeedback(const SbVec3f& pos3D);

    void computeLength();

    virtual void checkPlotWin();

    /** In inherited class, set your PzCurve values when this virtual method is called.*/
    virtual int setExtraCurvesValues() {return 0;}

    /**
     *  update the visibility of ports @c portSampleOrDist, @c portSamplesSlider and @c portDistSlider
     */
    virtual void updateCustomizeSamplingPortsVisibility(bool showThem);
    
  private:

    void commonInit();

    int computeSampleLocs();

    static int storeVals(float *to, float *from, SbVec3f norm, int type,
                         int vcomp, int skip);

    static void plotUpdateCallback(PzPlot* plot, void* userData);

    McHandle<SoSeparator> line;
    SoCoordinate3* coords;
    SoLineSet* lineset;
};

#endif // HX_SPLINE_PROBE

/// @}
