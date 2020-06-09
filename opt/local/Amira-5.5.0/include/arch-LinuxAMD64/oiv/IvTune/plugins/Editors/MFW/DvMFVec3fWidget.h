/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFVEC3FWIDGET_H
#define DvMFVEC3FWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFVec3fWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of three-dimensional vectors.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFVec3fWidget class implements a widget which edit three-dimensional vectors.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains any number of three-dimensional vectors. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget.
 * 
 * 
 */

class DEMOVIEWER_API DvMFVec3fWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFVec3fWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvMFVec3fWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFVec3fWidget();

  int getTextFlags();

  QString  getFieldValue(int row, int col) const;
	void swapRows(int index1, int index2);
  void swapColumns( int , int ){}
  void set1Value(int vec, int dim = -1, QString value = QString::null);

protected:
  virtual bool checkField(SoField *);

protected:
  DvMFVec3fWidget(int tableFlag, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

	DvMFVec3fWidget(const char *fieldName, int tableFlag, DvFieldEditorCommandManager * manager, 
               		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );


  float getSingleFieldValue (int vec, int index) const;
  virtual void setSingleFieldValue (float val, int vec, int index);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFVEC3FWIDGET_H

