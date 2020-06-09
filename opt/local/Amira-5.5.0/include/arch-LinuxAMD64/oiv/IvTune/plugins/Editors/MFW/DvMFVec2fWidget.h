/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFVEC2FWIDGET_H
#define DvMFVEC2FWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFVec2fWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of two-dimensional vectors.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFVec2fWidget class implements a widget which edit two-dimensional vectors.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains any number of two-dimensional vectors. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvMF2Box.
 * 
 * 
 */

class DEMOVIEWER_API DvMFVec2fWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFVec2fWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFVec2fWidget(const char *fieldName, DvFieldEditorCommandManager *, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFVec2fWidget();

  int getTextFlags();

  QString  getFieldValue(int row, int col) const;
	void swapRows(int index1, int index2);
  void swapColumns( int , int ){}
  void set1Value(int vec, int dim = -1, QString value = QString::null);

protected:
  bool checkField(SoField *);

protected:
  float getSingleFieldValue (int vec, int index) const;
  void setSingleFieldValue (float val, int vec, int index);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFVEC2FWIDGET_H

