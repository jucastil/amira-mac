/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFINT32WIDGET_H
#define DvMFINT32WIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFLineWidget.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFInt32Widget
//
//////////////////////////////////////////////////////////////////////////////

class DEMOVIEWER_API DvMFInt32Widget : public DvMFLineWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFInt32Widget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvMFInt32Widget(const char *fieldName, DvFieldEditorCommandManager *,
		              QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFInt32Widget();

protected:
  bool checkField(SoField *);

private:

  //function called by constructors
  void	initClass();

};

#endif //DvMFINT32WIDGET_H

