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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_AXIS
#define HX_AXIS

#include <mclib/McString.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortFontSelection.h>
#include <hxcore/HxController.h>
#include <hxcore/HxPortGeneric.h>

/** Displays coordinate frame. If connected to a data object it
    shows the local coordinate frame of the data, otherwise the
    global coordinate frame. */
class HXCORE_API HxAxis : public HxModule {

  HX_HEADER(HxAxis);

  public:
    /// Constructor.
    HxAxis();

    /// Compute method.
    virtual void compute();

    /// Returns 1 if module is connected to a data object
    int isLocal() const { return portData.source() ? 1 : 0; }

    /// Turn on or off individual axes
    HxPortToggleList portAxis;

    /// Options: 0=arrows, 1=text, 2=grid
    HxPortToggleList portOptions;

    enum { ARROWS=0, TEXT=1, GRID=2 };

    /// To set the format of the displayed ticks.
    enum { FLOAT=0, INT=1 };

    /// Thickness of the axes
    HxPortFloatSlider portThickness;

    /// Color of axes, grid, and text.
    HxPortColorList portColor;

    /// Names of axes
    HxPortGeneric portAxisNames;

    /// Axis labels.
    enum AxisLabels
    {
        /// X axis label.
        X_LABEL = 0,
        /// Y axis label.
        Y_LABEL = 1,
        /// Z axis label.
        Z_LABEL = 2
    };

    /// User-defined axis titles.
    enum AxisCustomTitles
    {
        /// User-defined X axis title.
        X_TITLE = 0,
        /// User-defined Y axis title.
        Y_TITLE = 1,
        /// User-defined Z axis title.
        Z_TITLE = 2
    };

    /// To select the font attributes.
    HxPortFontSelection portFont;

    /// Tcl_command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Needed in order to adjust the bounding box.
    virtual void saveUpdate(FILE* fp);

    /** Sets a user-defined bounding box. Once a user.defined bounding
        box has been set this box is used instead of the bounding box
        of the scene or the bounding box of the data set the axis module
        is connected to. The argument @c bb is a pointer to a vector of
        6 floats where the xmin, xmax, ymin, ymax, zmin, and zmax
        coordinates of the bounding box are stored. If @c bb is null
        a user-defined bounding box will be unset again. */
    void setBoundingBox(float* bb);

    /** Returns a pointer to the bounding box vector of the axis module.
        The pointer points to a vector of 6 floats where the xmin, xmax,
        ymin, ymax, zmin, and zmax coordinates of the bounding box are
        stored. Unless a bounding box was set by the user the bounding
        box will be bounding box of the entire scene or the bounding box
        of the data set the axis module is connected to. */
    const float* getBoundingBox() const { return bbox; }

    /** Sets a user-defined ticks bounding box. When local coordinates mode
        is enabled, this box is used to calculate the min/max axis bounds. */
    void setTicksBoundingBox(float* bb);

    /** Returns a pointer to the ticks bounding box */
    const float* getTicksBoundingBox() const { return tbox; }

    /** Sets the flip flag for an axis. If an axis is flipped it points
        from the opposite side of the bounding box into the negative
        coordinate direction. */
    void setFlip(int k, bool value);

    /// Returns true if the specified axis points into negative direction.
    bool getFlip(int k) const { return (flip>>k)&1; }

    /** Enables local coordinates mode. If local coordinates mode is
        enabled the origin of the axes will be labelled with (0,0,0)
        irrespectively of the actual location of the bounding box. */
    void setLocalMode(bool value);

    /// Returns true if local coordinate mode is enabled.
    bool getLocalMode() const { return localMode; }

    /** Sets a user-defined increment between subsequent tick marks.
        If a negative value is specified the increment is computed
        automatically. */
    void setDelta(float value);

    /// Returns the increment between subsequent tick marks.
    float getDelta() const { return delta; }

    /** Sets text label for a specific axis. On default the axes are
        labeled with "x", "y", and "z". */
    void setAxisText(int k, const char* label);

    /// Returns the label of an axis.
    const char* getAxisText(int k) const { return axisText[k]; }

    /// To get the bounding box of the connected data.
    virtual void getDataBoundingBox();

  protected:
    virtual ~HxAxis();

    float bbox[6]; // bounding box
    float tbox[6]; // tick bounding box
    float firstTick[3];
    float delta;
    SbVec3f m_scaleFactor; // The scales used to compute the right number of ticks.
    float thickness;
    int nTicks[3];
    int preferedNumberOfTicks;
    unsigned int format:1; // the format of the displayed ticks.
    unsigned int flip:3;
    unsigned int textStart:3;
    unsigned int keepBox:1; // indicates user-defined box
    unsigned int keepTicksBox:1;
    unsigned int keepDelta:1;
    unsigned int localMode:1;

    McHandle<SoSeparator> root;
    McHandle<SoSeparator> text;
    McHandle<SoFaceSet> faceSet;
    McHandle<SoIndexedLineSet> indexedLineSet;

    McString axisText[3];
    virtual void computeDimensions();
    void clearGeometry();
    void buildText();
    void buildTicks(int k);
    void buildAxis(int k);
    void buildGrid(int k);
    float nice(float x);
    virtual float getDelta(int k) const { return ((flip>>k)&1) ? -delta / m_scaleFactor[k] : delta / m_scaleFactor[k]; }
    virtual float getOrigin(int k) const { return ((flip>>k)&1) ? bbox[2*k+1] : bbox[2*k]; }
};

#endif // HX_AXIS

/// @}
