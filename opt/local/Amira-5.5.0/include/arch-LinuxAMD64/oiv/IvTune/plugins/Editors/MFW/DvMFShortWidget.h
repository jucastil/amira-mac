/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFSHORTWIDGET_H
#define DvMFSHORTWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFLineWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFShortWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFShortWidget : public DvMFLineWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFShortWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFShortWidget(const char *fieldName, DvFieldEditorCommandManager *, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFShortWidget();

protected:
  virtual bool checkField(SoField *);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFSHORTWIDGET_H

