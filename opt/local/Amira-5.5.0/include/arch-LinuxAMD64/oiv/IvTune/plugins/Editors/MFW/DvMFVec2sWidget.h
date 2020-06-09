/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFVEC2SWIDGET_H
#define DvMFVEC2SWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFVec2sWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of two-dimensional vectors.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFVec2sWidget class implements a widget which edit two-dimensional vectors.
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

class DEMOVIEWER_API DvMFVec2sWidget : public DvMFieldWidget
{
 
public:
  /**
   * Default constructor.
   */
  DvMFVec2sWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                  const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFVec2sWidget(const char *fieldName, DvFieldEditorCommandManager * manager,
              		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFVec2sWidget();

  int getTextFlags();

  QString  getFieldValue(int row, int col) const;
	 void swapRows(int index1, int index2);
  void swapColumns( int , int ){}
  void set1Value(int vec, int dim = -1, QString value = QString::null);

protected:
  bool checkField(SoField *);

protected:
  short getSingleFieldValue (int vec, int index) const;
  void setSingleFieldValue (short val, int vec, int index);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFVEC2SWIDGET_H

