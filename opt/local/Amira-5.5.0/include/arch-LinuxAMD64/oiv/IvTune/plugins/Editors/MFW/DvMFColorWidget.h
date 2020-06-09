/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFCOLORWIDGET_H
#define DvMFCOLORWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/MFW/DvMFVec3fWidget.h>

class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFColorWidget
//
//
//////////////////////////////////////////////////////////////////////////////

class DEMOVIEWER_API DvMFColorWidget : public DvMFVec3fWidget
{

public:
  /**
   * Default constructor.
   */
  DvMFColorWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvMFColorWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
               		QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvMFColorWidget();

  void setValue(int vec,const void * data);

protected:
  bool checkField(SoField *);

  void setSingleFieldValue (float val, int vec, int index);

private:
  //function called by constructors
	void initClass();


};

#endif //DvMFCOLORWIDGET_H

