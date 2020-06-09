/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFUSHORTWIDGET_H
#define DvMFUSHORTWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFLineWidget.h>

class SoField;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFUShortWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFUShortWidget : public DvMFLineWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFUShortWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
               		 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFUShortWidget( const char *fieldName, DvFieldEditorCommandManager *,  
                		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFUShortWidget();

protected:
  virtual bool checkField(SoField *);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFUSHORTWIDGET_H

