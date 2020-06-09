/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFPLANEWIDGET_H
#define DvSFPLANEWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSF4fBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFPlaneWidget
//
//  Base class for widgets which edit a single-value field 
//  containing one plane equation.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFPlaneWidget class implements a widget which edit plane equation.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a plane equation. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvMF4fBox.
 * 
 * 
 */
class DEMOVIEWER_API DvSFPlaneWidget : public DvSF4fBox
{

public:
  /**
   * Default constructor.
   */
  DvSFPlaneWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
	              	const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvSFPlaneWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvSFPlaneWidget();

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFPLANEWIDGET_H

