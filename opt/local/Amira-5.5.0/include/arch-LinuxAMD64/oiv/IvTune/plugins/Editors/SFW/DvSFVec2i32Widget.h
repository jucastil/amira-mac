/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFVEC2I32WIDGET_H
#define DvSFVEC2I32WIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSF2iSpinBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFVec2i32Widget
//
//  Base class for widgets which edit a single-value field 
//  containing a two-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFVec2i32Widget class implements a widget which edit two-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a two-dimensional vector. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvSF2Box.
 * 
 * 
 */
class DEMOVIEWER_API DvSFVec2i32Widget : public DvSF2iSpinBox
{

public:
  /**
   * Default constructor.
   */
  DvSFVec2i32Widget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
                		const char* name = 0, 
                    Qt::WFlags fl = 0);

  /**
   * Constructor.
   */
	DvSFVec2i32Widget(const char *fieldName, DvFieldEditorCommandManager *, 
                		QWidget* parent = 0, const char* name = 0, 
                    Qt::WFlags fl = 0);

  /**
   * Destructor.
   */
	~DvSFVec2i32Widget();

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFVEC2I32WIDGET_H

