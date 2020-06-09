/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DVMFVEC4FWIDGET_H
#define DVMFVEC4FWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFVec4fWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of four-dimensional vectors.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFVec4fWidget class implements a widget which edit four-dimensional vectors.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains any number of four-dimensional vectors. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvMF4fBox.
 * 
 * 
 */

class DEMOVIEWER_API DvMFVec4fWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFVec4fWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFVec4fWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFVec4fWidget();

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

#endif //DVMFVEC4FWIDGET_H

