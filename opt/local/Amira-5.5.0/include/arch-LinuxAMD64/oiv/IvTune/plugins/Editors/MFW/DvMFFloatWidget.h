/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFFLOATWIDGET_H
#define DvMFFLOATWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFLineWidget.h>

class SoField;
class DvRangeComponent;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFFloatWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFFloatWidget : public DvMFLineWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFFloatWidget(DvRangeComponent &rangeSet, 
                  DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFFloatWidget(const char *fieldName, DvRangeComponent &rangeSet, 
                  DvFieldEditorCommandManager *, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFFloatWidget();

protected:
  virtual bool checkField(SoField *);

private:
  //function called by constructors
	void initClass(DvRangeComponent &rangeSet);
};

#endif //DvMFFLOATWIDGET_H

