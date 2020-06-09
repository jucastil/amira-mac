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
#ifndef HX_PORT_3DPOINT_LIST_H
#define HX_PORT_3DPOINT_LIST_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McHandle.h>
#include <hxcore/HxCoordSystem.h>
#include <hxcore/HxPort.h>
#include <hxcore/SoCrosshair3Dragger.h>
#include <hxcore/SoCrosshairDraggerInterface.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/SbColor.h>

class QLineEdit;
class QPushButton;
class QSpinBox;
class QAction;
class QxActionNotifier;

class SoEventCallback;
class SoCrosshair3Dragger;
class QxPort3DPointListNotifier;

/** This port defines a list of points in 3D space. The point
    coordinates can be edited via a text field or by using a 3D
    dragger.

    The number of points managed by this port may be changed using
    @c setNumPoints(). Points may be interactively added or removed
    by the user if the minimal and maximal numbers of points are
    specified as optional arguments of setNumPoints(). On default,
    no dynamic range is used, i.e., the number of points is fixed.
    The minimal number of points may be any number >= 0.

    In order to use this port first a bounding box has to be defined.
    Otherwise, the points and the 3D dragger will not be visible. The
    coordinates of any point will always be clipped to lie inside the
    bounding box.
    See the  @htmlonly <a href= ../usersguide/HxPort3DPointList.html> usersguide </A> @endhtmlonly
    for a detailed view of the port's GUI.

    BE CARREFUL: Unlike any other ports, this class cannot be instantiated as a class member
    which isn't a pointer.
    Indeed, within the destructor of this class, a call to the HxBase owner of this port is done:
    @code
    theObject->hideGeom(pointListSep);
    theObject->hideGeom(dragger);
    @endcode
    This implies that if this class hasn't been created as a pointer, after that @c theObject has
    been destroyed, the destructor of this class is automatically called and tries to work on the
    previously deleted @c theObject object!
    */
class HXCORE_API HxPort3DPointList : public HxPort {
    MC_ABSTRACT_HEADER(HxPort3DPointList);

public:

    /// this port has three operation modes
    typedef enum {MODIFY, APPEND, INSERT} EditMode;

    /// Constructor for objects. Default dragger is of type @c SoCrosshair3Dragger.
    HxPort3DPointList(HxObject* o, const char *name, int numPoints=1, SoCrosshairDraggerInterface* dragger=NULL);

    /// Constructor for editors. Default dragger is of type @c SoCrosshair3Dragger.
    HxPort3DPointList(HxEditor* e, const char *name, int numPoints=1, SoCrosshairDraggerInterface* dragger=NULL);

    /// Destructor.
    ~HxPort3DPointList();

    /// Returns the number of points
    int getNumPoints() const { return points.size(); }

    /** Sets the number of points. If minNum and maxNum are specified
        and if minNum < maxNum, points can be interactively added or
        removed by the user via appropriate entries in the option
        buttons popup menu. If minNum >= 0 and maxNum < 0 creation
        and removal of points is allowed, but no upper limit for the
        number of points is assumed. */
    void setNumPoints(int numPoints, int minNum=-1, int maxNum=-1);

    /// Get coordinates of n-th point.
    SbVec3f getValue(int n) const;

    /// Get coordinates of current point if number of points is > 0.
    SbVec3f getValue() const { return getValue(current); }

    /// Get index of current point.
    int getCurrent() const {return current;}

    /**
     *  Select the point which user will control/view/modify
     */
    void selectPoint(int n);

    /** Set coordinates of n-th point. If @c doUpdate is set the Inventor
        geometry is updated. */
    void setValue(int n, SbVec3f v, int doUpdate=1);

    /** Set coordinates of current point if number of points is > 0.
        If @c doUpdate is set the Inventor geometry is updated. */
    void setValue(SbVec3f v, int doUpdate=1);

    /// Get coordinates of n-th point in internal coordinate system.
    SbVec3d getCoord(int n) const;

    /** Set coordinates of n-th point in internal coordinate system. 
        If @c doUpdate is set the Inventor geometry is updated. */
    void setCoord(int n, const SbVec3d& v, int doUpdate=1);

    /// Set the bounding box of the dragger.
    void setBoundingBox(float xmin, float xmax, float ymin,
                        float ymax, float zmin, float zmax);

    /// Set the bounding box of the dragger.
    void setBoundingBox(float bb[6]);

    /// Get the bounding box of the dragger.
    void getBoundingBox(float bb[6]) const;

    /** Sets the output format of the coordinate text fields. The format has
        to specified in printf syntax. Initially it is set to "%.5g", which
        means that at most 5 significant digits are printed. */
    void setFormat(const char* format, bool doUpdateInterface = false);

    /// Returns the printf format string of the coordinate text fields.
    const char* getFormat() const { return format; }

    /// In immediate mode the owner module is fired during dragging.
    void setImmediate(int value=1) { immediate=value; }

    /// Check if port is in immediate mode (see above).
    int getImmediate() const { return immediate; }

    /** Sets orthogonal mode. Using the dragger you can only move one point,
        the current point, at a time. In <tt>orthogonal mode</tt> all other points
        are moved in sync. */
    void setOrtho(int value=1) { ortho=value; }

    /// Check if port is in orthogonal mode (see above).
    int getOrtho() const { return ortho; }

    /** Appends point at the end of the list unless the maximal
        number of points specified in setNumPoints() is reached.
        Returns index of new point, -1 if no point has been added. */
    int appendPoint(SbVec3f point);

    /// Appends point with default coordinates.
    int appendPoint();

    /** Inserts point before point n unless the maximal number
        of points specified in setNumPoints() is reached. Returns
        index of new point, -1 if no point has been added. */
    int insertPoint(int insertBefore, SbVec3f point);

    /** Inserts point with default coordinates. Returns
        index of new point, -1 if no point has been added. */
    int insertPoint(int insertBefore);

    /** Removes point n unless the minimal number of points specified
        in setNumPoints() is reached. If the point couldn't be removed
        0 is returned. Othwerwise 1 is returned. */
    int removePoint(int n);

    /// Shows the dragger (or hides it if the argument is 0).
    void showDragger(int show=1);

    /// Hides the dragger.
    void hideDragger() { showDragger(0); }

    SoDragger* getDragger() const { return dragger; }

    /// Shows the point spheres (or hides them if the argument is 0).
    void showPoints(int show=1);

    /// Hides the point spheres.
    void hidePoints() { showPoints(0); }

    /** Sets point size (radius). The point size is automatically adjusted
        if the dragger's bounding box changes. */
    void setPointSize(float radius);

    /// Returns point size (radius).
    float getPointSize() const;

    /** Sets point size scale factor. On default the scale factor is 1.
        If you find that the default size of the points is too small or
        too big you can adjust this factor. */
    void setPointScale(float factor);

    /// Returns point size scale factor.
    float getPointScale() const { return pointSizeFactor; }

    /// Sets a transformation that is to be considered for picking
    void setTransform(const SbMatrix & tMat = SbMatrix::identity()) { xForm = tMat; }

    /// retrieves any given transformation
    SbMatrix getTransform(void) const { return xForm; }

    /// Command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /// Save current state to file.
    virtual void saveState(FILE* fp);

    //// get mode
    EditMode getMode() const;

    /// set mode to append or modify
    void setMode(EditMode mode);

    // Is connected to HxCoordSystem.
    void coordSystemChanged();

  /**
   *  Display interactive feedback (false by default).
   */
  void displayInteractiveFeedback(bool displayIt);

  /**
   *  This method must be used if the module which using this class
   *  is able to display interactive feedback.
   *  To display it, the module should connect to @c mNotifier to
   *  receive the necessary signals.
   *  Default is false.
   */
  void enableInteractiveLineFeedbackOption(bool enableIt);

  /**
   *  Check if the interactive feedback is displayed.
   */
  inline bool isDisplayingInteractiveFeedback() const
  {
      return m_isDisplayingInteractiveFeedback;
  }

  /** Connection point for Qt signals and slots.
   */
  QxPort3DPointListNotifier* const mNotifier;

  /**
  *  Copy values from refPort and update GUI.
  *  
  */
  virtual void initFrom( HxPort* refPort );


  /// Show or hide options button.
  void showOptionButton(bool enable);

  /// Check if slider has an edit button.
  bool hasOptionButton() const { return m_showOptionButton; }

  protected:
    struct HXCORE_API Point {
        Point();
        void initFrom( const Point* ref );

        SbVec3f pos;
        McHandle<SoSeparator> geom;
    };

    /// existing points are modified or new points added
    EditMode mode;

    McDArray<Point> points;

    int current;
    int minNumPoints;
    int maxNumPoints;
    float pointSizeFactor;
    float xmin, xmax, ymin, ymax, zmin, zmax;
    SbColor pointColor;
    SbColor highlightColor;
    SbMatrix  xForm;

    //Indicates if option button must be shown ( true by default)
    bool m_showOptionButton;

    unsigned int showDraggerFlag:1;
    unsigned int showPointsFlag:1;
    unsigned int immediate:1;
    unsigned int ortho:1;
    unsigned int bboxSet:1;
    unsigned int pickCallbackRegistered:1;
    unsigned int isMoving:1;

    McString format;
    QxGuardedPtr<QSpinBox> spinBox;
    QxGuardedPtr<QLineEdit> text[3];
    QxGuardedPtr<QPushButton> button;

    QxGuardedPtr<QxActionNotifier> actionNotifier;
    QxGuardedPtr<QAction> showDraggerAction;
    QxGuardedPtr<QAction> showPointsFlagAction;
    QxGuardedPtr<QAction> insertPointAction;
    QxGuardedPtr<QAction> appendPointAction;
    QxGuardedPtr<QAction> removePointAction;
    QxGuardedPtr<QAction> displayInteractiveFeedbackAction;
    QxGuardedPtr<QAction> appendModeAction;
    QxGuardedPtr<QAction> appendModeSeparator;

    McHandle<SoSeparator> pointListSep;
    McHandle<SoSelection> pointSelector;
    McHandle<SoCrosshairDraggerInterface> dragger;

    SoEventCallback* m_eventCB;

    bool m_isDisplayingInteractiveFeedback;
    bool m_supportInteractiveLineFeedbackOption;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);

    void commonInit(int num, SoCrosshairDraggerInterface* dragger);
    void actionTriggered(QAction*);
    void update();
    void updatePointSize();
    void updateInterface();
    void selectPoint(SoPath *selectionPath);
    void translate(int notThis, const SbVec3f& delta);
    void dragStart();
    void dragChanged();
    void dragFinish();
    void setPointColor(int k, SbVec3f color);
    void registerPickCallback();
    void pickCallback(SoEventCallback* node);
    bool canRetrieve3DPoint() const;
    bool get3DPoint(const SoPickedPoint* pickedPoint, SbVec3f& point3D) const;
    const HxSpatialData* getData() const;

    static void dragStartCB(void *userData, SoDragger *dragger);
    static void dragChangedCB(void *userData, SoDragger *dragger);
    static void dragFinishCB(void *userData, SoDragger *dragger);
    static void keyPressedCB(void *userData, SoEventCallback *eventCB);
    static void selPointCallback(void *userData, SoPath *selectionPath);
    static void pickCallbackCB(void *userData, SoEventCallback* node);
    static void trackerEventCB(void *userData, SoEventCallback* node);
    static void controllerEventCB(void *userData, SoEventCallback* node);
    static void location2CB(void *userData, SoEventCallback *m_eventCB);

    friend class QxActionNotifier;
};

#endif

/// @}
