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

/// @addtogroup hxcolormapeditor hxcolormapeditor
/// @{
#ifndef QX_HISTOGRAM_EDITOR_H
#define QX_HISTOGRAM_EDITOR_H

#include <hxcolormapeditor/HxColormapEditorWinDLLApi.h>
#include <mclib/McDArray.h>

#include <QFrame>
#include <QResizeEvent>

class HxData;
class PzPlot;
class PzAxis;
class PzCurve;
class PzMarkerline;
class QxMultiSlider;
class HxColormap;

class HXCOLORMAPEDITOR_API QxHistogramEditor : public QFrame
{
    Q_OBJECT
public:
    QxHistogramEditor(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~QxHistogramEditor();

    /// Set the data used to build the histogram
    void setInputData(const HxData * data, int numbins = 256);
    
    float getDataMin() const { return m_dataMin; }
    float getDataMax() const { return m_dataMax; }

    /// Number of bins of histogram
    int getNumBins() const { return m_bins.size(); }

    const McDArray<int> & getBins() const { return m_bins; }

    /// Set the colormap used to colorize the histogram
    void setColorMap(const HxColormap * cmap);

    /// Set colormap coordinate range
    void setColorRange(float min, float max);

    float getMinRange() const { return m_minRange; }
    float getMaxRange() const { return m_maxRange; }

    /// Return the plot background colour
    const QColor & getBackgroundColor() const{ return m_backgroundColor; }
public slots:
    void setAxisType(const QString & type);    // "Linear" / "Log"
    void setAxisScaling(const QString & type); // "Auto" / "Fixed"
    void setCurveType(const QString & type);   // "Histogram" / "Curve" / "Impulse"

    /// Sets the plot background colour
    void setBackgroundColor(const QColor & col);
    
signals:
    void colorRangeChanged(float min, float max);

protected slots:
    void cursorMoved(int index);
    void updateHistogram();
    void updateCursors();
    
private:
    void updateColormap();
    /// transform plot world coordinate to device coordinate
    int xwc2dc(float x);

    /// converts the x-value from device to plot world coordinates
    float xdc2wc(int x);

	float m_minRange, m_maxRange;
    float m_dataMin, m_dataMax;
    McDArray<int> m_bins;

    const HxColormap * m_p_colormap;

    PzPlot * m_p_plot;
    PzAxis * m_p_axis;
    PzCurve* m_p_curve;

    PzMarkerline * m_p_minMarker, * m_p_midMarker, * m_p_maxMarker;

    QColor m_backgroundColor;

    bool m_autoScaling;
    bool m_useAlpha;

    QxMultiSlider * m_p_slider;
};

#endif

/// @}
