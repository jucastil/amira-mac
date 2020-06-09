/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFVEC2SWIDGET_H
#define DvSFVEC2SWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSF2iSpinBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFVec2sWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a two-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFVec2sWidget class implements a widget which edit two-dimensional vector.
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
class DEMOVIEWER_API DvSFVec2sWidget : public DvSF2iSpinBox
{

public:
  /**
   * Default constructor.
   */
  DvSFVec2sWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, 
                  Qt::WFlags fl = 0);

  /**
   * Constructor.
   */
	DvSFVec2sWidget(const char *fieldName, DvFieldEditorCommandManager *, 
              		QWidget* parent = 0, const char* name = 0, 
                  Qt::WFlags fl = 0);

  /**
   * Destructor.
   */
	~DvSFVec2sWidget();

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFVEC2SWIDGET_H

