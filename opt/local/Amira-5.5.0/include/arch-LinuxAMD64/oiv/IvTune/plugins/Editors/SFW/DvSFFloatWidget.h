/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFFLOATWIDGET_H
#define DvSFFLOATWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class DvRealSlider;
class DvRangeComponent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFFloatWidget
//
//////////////////////////////////////////////////////////////////////////////

class DEMOVIEWER_API DvSFFloatWidget : public DvSFieldWidget
{

public:

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFFloatWidget(const char *fieldName, DvRangeComponent &rangeSet, 
                  DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                  const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFFloatWidget();

  DvRealSlider * m_sliderEdit;

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

#endif //DvSFFLOATWIDGET_H

