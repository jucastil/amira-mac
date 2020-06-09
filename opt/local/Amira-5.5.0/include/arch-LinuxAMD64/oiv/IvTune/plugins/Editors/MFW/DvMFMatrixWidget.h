/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFMATRIXWIDGET_H
#define DvMFMATRIXWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFT/DvTablePopupWidget.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFMatrixWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of 4x4 matrices.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFNodeWidget class implements a widget which edit 4x4 matrices.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains any number of 4x4 matrices. Matrices are displayed in a frame apart 
 *  from this widget.
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvTablePopupWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvMFMatrixWidget : public DvTablePopupWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFMatrixWidget(DvFieldEditorCommandManager *manager, QWidget* parent = 0, 
                   const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvMFMatrixWidget( const char *fieldName, DvFieldEditorCommandManager *manager, 
                    QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvMFMatrixWidget();

  int getTextFlags();

  QString  getFieldValue(int row, int col) const;
	void swapRows(int index1, int index2);
  void swapColumns( int , int ){}
  void set1Value(int vec, int dim = -1, QString value = QString::null);

protected:
  bool checkField(SoField *);

  QString getPopupValue(int rowToEdit, int index);
};

#endif //DvMFMATRIXWIDGET_H

