/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFBOX3SWIDGET_H
#define DvSFBOX3SWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/DvPopupWidget.h>

class DEMOVIEWER_API DvSFBox3sWidget : public DvPopupWidget
{

public:
  DvSFBox3sWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );
	
  DvSFBox3sWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

	~DvSFBox3sWidget();

	/**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFBOX3SWIDGET_H

