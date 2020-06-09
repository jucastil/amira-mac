/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SOQTWRAPPER_H
#define SOQTWRAPPER_H
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtWalkViewer.h>
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtWrapper
//
//  The Class is derived from a QWidget and include an Open Inventor Viewer
//  in it. The primary goal of this class is to be used in the Qt Designer
//  program as a plugin.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Creates a QWidget that encapsulates an Open Inventor viewer.
 * 
 * @ingroup Qt
 * 
 * @DESCRIPTION
 * This class creates a QWidget that encapsulates an Open Inventor viewer. This 
 * viewer can either be an SoQtRenderArea or one of the following viewers: 
 * SoQtExaminerViewer,
 * SoQtWalkViewer, SoQtFlyViewer, or SoQtPlaneViewer. The primary purpose
 * of this class is to be used in the Qt Designer
 * program as a plugin.
 * 
 * It also includes a small scene graph
 * that will be unref'd automatically at first setSceneGraph(). This scene graph is only
 * used in the Qt Designer plugin.
 *
 * @SEE_ALSO
 *    SoQtRenderArea,
 *    SoQtExaminerViewer,
 *    SoQtWalkViewer,
 *    SoQtFlyViewer,
 *    SoQtPlaneViewer
 * 
 * 
 */ 

class INVENTORQT_API SoQtWrapper : public QWidget
{
  Q_OBJECT

public:
  /** Viewer Types enumeration. */
  enum ViewerType {
    /**
     *  Creates a render area in the widget.
     */
    RENDER_AREA, 
    /**
     *  Creates an Examiner Viewer in the widget.
     */
    EXAMINER, 
    /**
     *  Creates a Walk Viewer in the widget.
     */
    WALK,
    /**
     *  Creates a Fly Viewer in the widget.
     */
    FLY,
    /**
     *  Creates a Plane Viewer in the widget.
     */
    PLANE
  };

  /**
   * Constructor which specifies the viewer type. If nothing
   * is specified, it creates an examiner viewer.
   */
  SoQtWrapper( QWidget* parent = 0, const char* name = 0, ViewerType type = SoQtWrapper::EXAMINER);

  /**
   * Gets the type of viewer that will be created in the widget.
   */
  ViewerType getViewerType() const { return viewerType; };

  /**
   * Gets a pointer to the created viewer. Depending on the view type,
   * this pointer can either be an SoQtRenderArea, an SoQtExaminerViewer,
   * an SoQtWalkViewer, an SoQtFlyViewer, or an SoQtPlaneViewer.
   */
  SoQtRenderArea * getViewer() const {return viewer;};

  /**
   * Returns whether the viewer decoration is on or off.
   */
  bool isDecoration() const;

public Q_SLOTS:
  /**
   * Shows/hides the viewer decoration (default on).
   */
  void setDecoration(bool on);

protected:
  ViewerType viewerType; 
private:
  // Add a default scene
  // This scene will be unref'd automatically at first setSceneGraph()
  SoSeparator* putTestSceneGraph(SoQtRenderArea *examiner);

  SoQtRenderArea *viewer;
};

#endif
