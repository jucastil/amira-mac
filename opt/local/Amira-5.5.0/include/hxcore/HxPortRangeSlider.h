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
#ifndef HX_PORT_RANGE_SLIDER
#define HX_PORT_RANGE_SLIDER

#include <sys/types.h>
#include <hxcore/HxPort.h>
#include <mclib/McHistogram.h>

class QWidget;
class QxFullRangeSlider;

/** Represents a bounded floating point number which can be edited
    via a slider. You can also have arrow buttons (setButtons())
    for step-wise editing. Use setIncrement to set the step width.

    Most of the port's options, e.g. the slider limits, step width,
    or the output format, can be set interactively via a popup dialog,
    see the  @htmlonly <a href= ../usersguide/HxPortRangeSlider.html> usersguide </A> @endhtmlonly
    for a detailed view of the port's GUI. */
class HXCORE_API HxPortRangeSlider : public HxPort {
    MC_ABSTRACT_HEADER(HxPortRangeSlider);

  public:
    /// Constructor for objects.
    HxPortRangeSlider(HxObject *obj, const char *name);

    /// Constructor for editors.
    HxPortRangeSlider(HxEditor *editor, const char *name);

    /// Destructor.
    virtual ~HxPortRangeSlider();


    bool setClipValue(float min, float max);

    /// Set port's value.
    void setValue(float l, float h);

    void setHistogram(const McHistogram& histogram);

    /// Returns port's value.
    float getValue(int i) const;

    /// Set slider limits, initially set to 0-1.
    void setMinMax(float min, float max);

    /// Returns minimum allowed value, initially set to 0.
    float getMinValue() const;

    /// Returns maximum allowed value, initially set to 1.
    float getMaxValue() const;

    /// Set increment for arrow buttons, initially set to @f$0.1@f$.
    void setIncrement(float increment);

    /// Get arrow button increment.
    float getIncrement() const { return increment; }

    /// Set output format for text field (printf style).
    void setFormat(const char* str);

    /// Get output format (default is %.g).
    const char* getFormat() const { return format; }

    /// Show or hide arrow buttons.
    void setButtons(int enable);

    /// Check if slider has arrow buttons.
    bool hasButtons() const { return showArrows; }

    /// Set width of slider including text field and optional arrow buttons.
    void setSliderWidth(int width);

    /// Get width of slider in pixels.
    int getSliderWidth() const { return sliderWidth; }

    /// Set text width (number of characters) of the slider's text field.
    void setNumColumns(int nColumns);

    /// Get number of columns (width) of text field.
    int getNumColumns() const { return nColumns; }

    /** Sets tracking flag. If tracking is enabled the owner is fired whenver
        the slider is moved. Otherwise, it is only fired if the mouse button
        is released and the value actually changed. */
    void setTracking(bool tracking);

    /// Returns value of tracking flag.
    bool getTracking() const;

    /** Sets slider in discrete mode. In this mode the slider value is always
        equal to the min value plus an integer multiple of the increment. */
    void setDiscrete(bool value);

    /// Check if slider is in discrete mode.
    bool isDiscrete() const { return discreteFlag; }

    /// Show or hides the subrange buttons.
    void setSubRangeButtons(bool subRange);

    /// Returns true if subrange buttons are visible.
    bool hasSubRangeButtons() const;

    /// set sub range
    void setSubRange(float min, float max);

    /// retrieve sub range min
    float getSubMin();

    /// retrieve sub range max
    float getSubMax();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Saves current state to file.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

	/// friend classes.
	friend class HxTreeViewGUI;
	friend class QxTreeView;

    QxFullRangeSlider* slider;

    /// Enables, disbales the slider widget but not the port itself.
    void setSensitivity(bool inFlag);

    /// 
    bool getSensitivity()const;

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  protected:
    
    McString format;
    unsigned int showArrows:1;
    unsigned int nColumns:8;
    unsigned int sliderWidth:10;
    unsigned int trackingFlag:1;
    unsigned int subRangeFlag:1;
    unsigned int discreteFlag:1;
    float value_l, value_h,minValue,maxValue,increment;
    // variables to cache histogram entries until slider member is initialized
    // and can store them itself
    McHistogram bufferedHistogramEntries; 
    float bufferedClipMin, bufferedClipMax;
    int bufferedSensitivity;

    int   subValueValid;
    float subValueMin;
    float subValueMax;

    void init();
    virtual void guiCallback();
    void popupMenu(int x, int y);
    virtual void createWidget(QWidget* parent);
};

#define HxPortAnimatedRange HxPortRangeSlider

#endif

/// @}
