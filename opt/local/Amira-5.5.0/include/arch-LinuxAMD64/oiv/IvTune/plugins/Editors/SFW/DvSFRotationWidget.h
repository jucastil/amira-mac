/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFROTATIONWIDGET_H
#define DvSFROTATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QFocusEvent>

#include <IvTune/plugins/Editors/SFW/DvSF4fBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFRotationWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a SbRotation.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFRotationWidget class implements a widget which edit SbRotation.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a SbRotation. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvSF4fBox.
 * 
 * 
 */

class DEMOVIEWER_API DvSFRotationWidget : public DvSF4fBox
{

public:
  /**
   * Default constructor.
   */
  DvSFRotationWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                  	 const char* name = 0, Qt::WFlags fl = 0 );

     /**
   * Constructor.
   */
	DvSFRotationWidget( const char *fieldName, DvFieldEditorCommandManager * manager, 
                      QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvSFRotationWidget();

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();

protected:
  virtual void focusOutEvent ( QFocusEvent * event);
};

#endif //DvSFROTATIONWIDGET_H

