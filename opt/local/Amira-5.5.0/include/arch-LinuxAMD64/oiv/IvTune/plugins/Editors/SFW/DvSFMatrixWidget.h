/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFMATRIXWIDGET_H
#define DvSFMATRIXWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/DvPopupWidget.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFMatrixWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a 4x4 matrix.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFMatrixWidget class implements a widget which edit 4x4 matrix.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a 4x4 matrix. Matrix is displayed in a frame apart 
 *  from this widget.
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvTablePopupWidget.
 * 
 * 
 */ 
class DEMOVIEWER_API DvSFMatrixWidget : public DvPopupWidget
{

public:
  /**
   * Default constructor.
   */
  DvSFMatrixWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
                	 const char* name = 0, Qt::WFlags fl = 0 );

    /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFMatrixWidget( const char *fieldName, DvFieldEditorCommandManager *, 
                    QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvSFMatrixWidget();

/**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFMATRIXWIDGET_H

