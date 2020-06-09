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
#ifndef HX_DATA_PROBE
#define HX_DATA_PROBE

#include <hxdataprobe/HxDataprobeWinDLLApi.h>

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <Inventor/nodes/SoSeparator.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPort3DPointList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>

#include <hxfield/HxLoc3Tetra.h>
#include <hxfield/HxScalarField3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxVectorField3.h>
#include <hxfield/HxComplexVectorField3.h>

class SoShapeKit;
class SoSeparator;
class SoCoordinate3;
class SoLineSet;
class SoVertexProperty;
class QxDataProbeNotifier;

///
class HXDATAPROBE_API HxDataProbe : public HxModule {

  HX_HEADER(HxDataProbe);
  
  public:
    ///
    HxDataProbe(const int probenum = 1, const bool changeable = true);

    /// Reset orientation of lines (axial, coronal, sagittal).
    HxPortButtonList portReset;

    /// Dragger options (0=immediate, 1=orthogonal, 2=customize sampling, 3=follow slice).
    HxPortToggleList portOptions;

    /// List of 3D-Ports
    HxPort3DPointList* controlPortsList;

    /// Size of probe location (sphere)
    HxPortFloatSlider portPointSize;

    ///
    HxPortRadioBox portVectorComp;

    //slice number if attached like a slice
    HxPortIntSlider portSliceNumber;

    ///
    virtual void compute();

    ///
    virtual void update();

    ///
    void shift(const SbVec3f& trans);

    ///
    void shift(const float transX, const float transY, const float transZ);

    ///
    void transform(const SbMatrix& mat);

    ///
    void setPoint(int ip, float x, float y, float z);

    ///
    void setPoint(int ip, SbVec3f p);

    ///
    void setPoint(float x, float y, float z);

    ///
    void setPoint(SbVec3f p);

    /// number of sample points
    int getNumSamplePoints (void) {return(sampleLocs.size());}

    /// returns the coordinates of a specific sample point (one of them which have been used to display the curve in the plot window )
    SbVec3f *getSamplePoint (int ip) {return(sampleLocs[ip]);}

    /// returns the dimension of the samples values
    int nDataVar();

    /// returns the sampled value(s) of a specific sample point
    float* getSampledValue(int ip = 0);

    /// returns the number of control points 
    int getNumPoints() { return controlPortsList->getNumPoints(); }

    ///
    void getPoint(int ip, float &x, float &y, float &z);

    ///
    SbVec3f getPoint(int ip);

    ///
    void getPoint(float &x, float &y, float &z);

    ///
    SbVec3f getPoint();

    ///
    float getLength() { return theLength; }

    ///
    void setImmediate(int state = 1);

    ///
    void setOrtho(int state = 1);

    /**
     *  If @c customizeSampling is true, user will be
     *  able to tune the sample curve which will be used
     *  to display the probe result in the plot window.
     *  Otherwise, the displayed curve (in the 3D viewer)
     *  will be used to compute the sample curve .
     */
    void setCustomizeSampling(bool customizeSampling);

    ///
    virtual void renderProbe(bool show = true);

    /// appends a point at the end of the point list
    int appendPoint(SbVec3f point);

    /// appends a point at the end of the point list
    int appendPoint(float x, float y, float z);

    /// inserts a point after point <em> n</em>
    int insertPoint(int n, SbVec3f point);

    /// inserts a point after point <em> n</em>
    int insertPoint(int n, float x, float y, float z);

    /// removes point <em> n</em>
    int removePoint(int n);
    
    /// Writes a command sequence initializing the ports to fp.
    virtual void savePorts(FILE* fp);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    QxDataProbeNotifier* const mNotifier;

    /// Get the probe name m_myName
    const char* getName() const;

    /// Set the probe name m_myName
    void setName(const McString & name);

  protected:

    virtual ~HxDataProbe();

    void commonInit();

    virtual void showLine(SoSeparator* sep);

    virtual void hideLine(SoSeparator* sep);

    void computeLength();

    int getMaterial(HxField3* field, int cellndx = -1);

    // Returns orientation according to port reset
    int getOrientation();

    /**
     *  Render the interactive feedback.
     *  It does nothing by default. Inherited classes have to implement
     *  this method and display the geometry thanks to @c m_feedbackLineVP
     *  and @c m_feedbackLineVP.
     *  The inherited class will also have to declare that it can manage
     *  interactive feedback by calling :
     *  @code
     *  controlPortsList->enableInteractiveLineFeedbackOption(true);
     *  @endcode
     */
    virtual void renderFeedback(const SbVec3f& pos3D) {};

    /**
     *  Automatically hide the feedback by calling :
     *  @code
     *  m_feedbackLine->numVertices.setValue(0);
     *  @endcode
     */
    virtual void hideFeedbackLine();

    virtual void deselect();

    /**
     *  No sampling port here.
     */
    virtual void updateCustomizeSamplingPortsVisibility(bool showThem) {};

    // connected field
    HxRegScalarField3* m_regField;

    //Last orientation chosen with portReset
    int m_orientation;

    HxField3* field;
    HxTetraGrid* grid;
    McHandle<SoSeparator> theLines;

    /**@name Feedback OIV nodes*/
    //@{
    /// Feedback root
    McHandle<SoSeparator> m_feedbackLineSep;
    /// Feedback vertex property
    SoVertexProperty* m_feedbackLineVP;
    /// Feedback line representation
    SoLineSet* m_feedbackLine;
    //@}

    /// List of curve points
    McDArray<SbVec3f> curvePoints;

    /// List of sample points
    McDArray<SbVec3f*> sampleLocs;

    McDArray<char*> materialNames;

    McDArray<float> sampledValues;

    McString            myName;

    int                 currMaterial;
    int                 typeOfField, vComp, inGrid;
    int                 resample, newcurve;

    float               theMin, theMax;
    float               theLength;

    float               xMin, xMax, yMin, yMax, zMin, zMax;

    bool                m_customizeSampling;

  private:

    // Probe name (might be different from probe label)
    McString m_myName;

    void newData(HxSpatialData *data);

    void feedbackPointChanged(const SbVec3f& pos3D);
    void feedbackPointOutOfRange();

    friend class QxDataProbeNotifier;

    // 1 == PointProbe, 2 == LineProbe, >=3 == SplineProbe
    int probeNum;
    int changeNumPoints;
    int useOrthoLine;

    McHandle<SoSeparator> line;
    SoCoordinate3* coords;
    SoLineSet* lineset;
};

#endif // HX_DATA_PROBE

/// @}
