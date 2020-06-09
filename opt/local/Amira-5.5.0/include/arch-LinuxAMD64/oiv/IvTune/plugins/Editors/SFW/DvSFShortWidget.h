/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFSHORTWIDGET_H
#define DvSFSHORTWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class DvIntSlider;
class DvRangeComponent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFShortWidget
//
//////////////////////////////////////////////////////////////////////////////

class DEMOVIEWER_API DvSFShortWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSFShortWidget(DvRangeComponent &rangeSet, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFShortWidget( const char *fieldName, DvRangeComponent &rangeSet, DvFieldEditorCommandManager * manager, 
                   QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFShortWidget();

  DvIntSlider * m_sliderEdit;

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

#endif //DvSFSHORTWIDGET_H

