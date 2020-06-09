/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFVEC4FWIDGET_H
#define DvSFVEC4FWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSF4fBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFVec4fWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a four-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFPlaneWidget class implements a widget which edit four-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a four-dimensional vector. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvSF4fBox.
 * 
 * 
 */
class DEMOVIEWER_API DvSFVec4fWidget : public DvSF4fBox
{

public:
  /**
   * Default constructor.
   */
  DvSFVec4fWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );
	
  /**
   * Constructor.
   */
  DvSFVec4fWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFVec4fWidget();

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFVEC4FWIDGET_H

