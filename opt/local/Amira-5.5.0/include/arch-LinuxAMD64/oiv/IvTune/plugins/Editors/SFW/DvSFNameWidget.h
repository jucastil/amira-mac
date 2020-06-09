/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFNAMEWIDGET_H
#define DvSFNAMEWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFNameWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvSFNameWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSFNameWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                   const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFNameWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                   QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFNameWidget();

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

#endif //DvSFNAMEWIDGET_H

