/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFSTRINGWIDGET_H
#define DvMFSTRINGWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;
class SbString;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFStringWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFStringWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFStringWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
               		 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFStringWidget(const char *fieldName, DvFieldEditorCommandManager *, 
                	 QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFStringWidget();

  QString  getFieldValue(int row, int col) const;
	void swapRows(int index1, int index2);
  void swapColumns( int , int ){}
  void set1Value(int vec, int dim = -1, QString value = QString::null);

protected:
  bool checkField(SoField *);

protected:
  SbString getSingleFieldValue (int vec, int index) const;
  void setSingleFieldValue (SbString val, int vec, int index);

private:
  //function called by constructors
	void initClass();
};

#endif //DvMFSTRINGWIDGET_H

