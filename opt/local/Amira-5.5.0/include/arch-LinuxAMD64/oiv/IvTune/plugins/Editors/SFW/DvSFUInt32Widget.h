/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFUINT32WIDGET_H
#define DvSFUINT32WIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class DvUIntSlider;
class DvRangeComponent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFUInt32Widget
//
//////////////////////////////////////////////////////////////////////////////

class DEMOVIEWER_API DvSFUInt32Widget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSFUInt32Widget(DvRangeComponent &rangeSet, DvFieldEditorCommandManager * manager, 
                   QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFUInt32Widget( const char *fieldName, DvRangeComponent &rangeSet, DvFieldEditorCommandManager * manager, 
                    QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFUInt32Widget();

  DvUIntSlider * m_sliderEdit;

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

#endif //DvSFUINT32WIDGET_H
