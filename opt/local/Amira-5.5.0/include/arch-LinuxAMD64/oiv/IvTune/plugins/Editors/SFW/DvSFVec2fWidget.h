/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFVEC2FWIDGET_H
#define DvSFVEC2FWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLabel;
class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFVec2fWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a two-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFVec2fWidget class implements a widget which edit two-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a two-dimensional vector. 
 *
 * @SEE_ALSO
 *  DvSFieldWidget, DvSF2Box.
 * 
 * 
 */
class DEMOVIEWER_API DvSFVec2fWidget : public DvSFieldWidget
{

public:
  /**
   * Default constructor.
   */
    DvSFVec2fWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                    const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   */
  DvSFVec2fWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSFVec2fWidget();
    
  /** 
   * One-line text editor which edit the second component of vector.
   */
  QLineEdit* m_yLine;

  /** 
   * One-line text editor which edit the first component of vector.
   */
  QLineEdit* m_xLine;
  
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

#endif //DvSFVEC2FWIDGET_H

