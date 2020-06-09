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

/// @addtogroup hxlines hxlines
/// @{
#ifndef HXCURVEEDITOR_H
#define HXCURVEEDITOR_H

#include <hxcore/HxEditor.h>
#include <hxcore/HxPort3DPointList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>

#include <Inventor/nodes/SoSeparator.h>

#include <hxlines/HxLinesWinDLLApi.h>
#include "HxCurve.h"

class SoCoordinate3;
class SoLineSet;
class SoVertexProperty;
class QxCurveEditorNotifier;

class HXLINES_API HxCurveEditor : public HxEditor {

    HX_HEADER(HxCurveEditor);

public:

    HxCurveEditor();

    ~HxCurveEditor();

    /// port sets degree of BSpline, if curve is a spline.
    HxPortIntSlider portDegree;

    /// number of sample points per curve
    HxPortIntSlider portNumSamples;

    /// define curve by approximation or interpolation
    HxPortMultiMenu portMode;

    /// edit mode
    HxPortRadioBox portEditMode;

    /// point editing modes
    typedef  enum  {Append = 0, Modify, Insert, numEditModes} editMode;

    /// List of 3D-Ports
    HxPort3DPointList* controlPortsList;

    /// scaling of the point glyphs
    HxPortFloatSlider portPointScale;

    /// display mode of geometry
    HxPortToggleList portDisplayMode;

    /// display modes
    typedef  enum  {Points = 0, Lines, Curve, numDisplayModes} displayMode;

    /// Resets Curve
    HxPortButtonList portReset;

    /// GUI update and computation
    void update();

protected:

    // DATA
    HxCurve * mCurve;
    McDArray< McVec3f > mPoints;
    McHandle< SoSeparator > mLines;
    SoCoordinate3 * mLineCoords;
    SoLineSet * mLineset;
    McHandle< SoSeparator > mFeedbackSep;
    SoLineSet* mFeedbackLine;
    SoVertexProperty* mFeedbackLineVP;

    /// mode: true=create a new curve, false=modify points
    bool mInterpolationMode;

    /// constructor code
    void commonInit();

    /// rebuild the geometry
    void updateGeometry();

    /// add a new point to curve
    void addPoint(const SbVec3f &point); 

    virtual void startEditing(HxData *);
    virtual void stopEditing();
    
    // adjust the curve's degree according to the number of points
    // returns the new degree of the curve
    int modifyDegree(int degree);

    // enable preview of interactive curve edition (control point displacement or insertion)
    void setFeedbackVisible(bool visible);

    // callback called by notifier when preview should be refreshed.
    void feedbackPointChanged(const SbVec3f& pos3D);

    // callback called by notifier when cursor goes out of curve range and preview should be hidden.
    void feedbackPointOutOfRange();

    // callback called by notifier when curve data is deselected inside object and preview should be hidden.
    void objectDeselected(HxObject* object);

private:

    McBitfield  displayState;

    QxCurveEditorNotifier * mNotifier;

    friend class QxCurveEditorNotifier;
};

#endif

/// @}