/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFVEC3FWIDGET_H
#define DvSFVEC3FWIDGET_H

#include <QtGui/QLabel>
#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLabel;
class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFVec3fWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a three-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFVec3fWidget class implements a widget which edit three-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a three-dimensional vector. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 * 
 * 
 */
class DEMOVIEWER_API DvSFVec3fWidget : public DvSFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvSFVec3fWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                  const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
  DvSFVec3fWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
              	  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSFVec3fWidget();
    
  /** 
   * One-line text editor which edit the third component of vector.
   */
  QLineEdit* m_zLine;

  /** 
   * One-line text editor which edit the second component of vector.
   */
  QLineEdit* m_yLine;

  /** 
   * One-line text editor which edit the first component of vector.
   */
  QLineEdit* m_xLine;
    

  /** 
   * Label which display the name of the third component.
   */
  QLabel* m_zLabel;

  /** 
   * Label which display the name of the second component.
   */
  QLabel* m_yLabel;

  /** 
   * Label which display the name of the first component.
   */
  QLabel* m_xLabel;

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();

protected:
  bool edited();

private:
  //function called by constructors
    void initClass();
    void buildComponent(QLineEdit *&line, QLabel *&label);
};

#endif //DvSFVEC3FWIDGET_H

