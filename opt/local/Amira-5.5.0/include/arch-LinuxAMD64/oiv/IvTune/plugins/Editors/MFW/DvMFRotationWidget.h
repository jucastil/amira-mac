/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFROTATIONWIDGET_H
#define DvMFROTATIONWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;
class SbName;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFRotationWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing any number of SbRotations.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFRotationWidget class implements a widget which edit SbRotations.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains any number of SbRotations. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvMF4fBox.
 * 
 * 
 */

class DEMOVIEWER_API DvMFRotationWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFRotationWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
                  	 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
  DvMFRotationWidget(const char *fieldName, DvFieldEditorCommandManager *,
		                 QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvMFRotationWidget();

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

#endif //DvMFROTATIONWIDGET_H

