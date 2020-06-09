/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFLINEWIDGET_H
#define DvSFLINEWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFLineWidget
//
//  Base class for widgets which edit a single-value field.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFLineWidget class implements a widget editor for simple value.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains one value. It means this class display only string value 
 *  contained in the field. It is so the default widget for SoSField.
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 * 
 * 
 */
class DEMOVIEWER_API DvSFLineWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSFLineWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              	 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFLineWidget( const char *fieldName, DvFieldEditorCommandManager * manager, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFLineWidget();

	QLineEdit *			m_lineEdit;
	
  /**
   * Set values contained in the table to the field.
   */ 
  virtual void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  virtual void refresh();
  
protected:
  bool edited();
};

#endif //DvSFLINEWIDGET_H

