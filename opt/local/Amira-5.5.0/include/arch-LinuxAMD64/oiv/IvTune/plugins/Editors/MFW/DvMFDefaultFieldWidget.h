/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFDEFAULTFIELDWIDGET_H
#define DvMFDEFAULTFIELDWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class SoField;
class SbString;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFDefaultFieldWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvMFDefaultFieldWidget : public DvMFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFDefaultFieldWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
                      	 const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
	DvMFDefaultFieldWidget(const char *fieldName, DvFieldEditorCommandManager *,  
		                     QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFDefaultFieldWidget();

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

#endif //DvMFDEFAULTFIELDWIDGET_H

