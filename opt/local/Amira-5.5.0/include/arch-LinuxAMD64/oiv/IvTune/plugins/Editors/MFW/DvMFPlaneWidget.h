/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFPLANEWIDGET_H
#define DvMFPLANEWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;
class SbName;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFPlaneWidget
//
//  Base class for widgets which edit a multiple-value field 
//  containing several plane equations.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFPlaneWidget class implements a widget which edit plane equations.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents multiple-value fields 
 *  that contains several plane equations. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget.
 * 
 * 
 */

class DEMOVIEWER_API DvMFPlaneWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFPlaneWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
  DvMFPlaneWidget(const char *fieldName, DvFieldEditorCommandManager *,
		              QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destuctor.
   */
	~DvMFPlaneWidget();

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

#endif //DvMFPLANEWIDGET_H

