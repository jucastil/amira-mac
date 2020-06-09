/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFUINT32WIDGET_H
#define DvMFUINT32WIDGET_H

#include <qvariant.h>
#include <IvTune/plugins/Editors/MFW/DvMFLineWidget.h>

class SoField;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFUInt32Widget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFUInt32Widget : public DvMFLineWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFUInt32Widget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
               		 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFUInt32Widget(const char *fieldName, DvFieldEditorCommandManager *,  
                	 QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFUInt32Widget();

protected:
  virtual bool checkField(SoField *);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFUINT32WIDGET_H

