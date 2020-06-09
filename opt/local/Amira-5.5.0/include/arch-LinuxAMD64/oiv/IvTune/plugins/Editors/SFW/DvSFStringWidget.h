/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFSTRINGWIDGET_H
#define DvSFSTRINGWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFStringWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvSFStringWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSFStringWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                   const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFStringWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                   QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFStringWidget();

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

#endif //DvSFSTRINGWIDGET_H

