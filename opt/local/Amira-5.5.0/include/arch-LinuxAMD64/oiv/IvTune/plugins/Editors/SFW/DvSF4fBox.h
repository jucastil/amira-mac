/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSF4FBOX_H
#define DvSF4FBOX_H

#include <QtCore/QVariant>
#include <QLabel>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLabel;
class QLineEdit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSF4fBox
//
//  Base class for widgets which edit a single-value field 
//  containing a four-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSF4fBox class implements a widget which edit a four-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is a base class for widgets which represent single-value fields 
 *  that contains a four-dimensional vector. It gives some 
 *  extra convenience methods that allow type checking or label naming. Components of vector 
 *  are displayed in one-line text editors. 
 *
 * @SEE_ALSO
 *  DvMFieldWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvSF4fBox : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSF4fBox(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
            const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSF4fBox( const char *fieldName, DvFieldEditorCommandManager * manager, 
          	 QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSF4fBox();
    
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
   * One-line text editor which edit the fourth component of vector.
   */
  QLineEdit* m_vLine;
    
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
   * Label which display the name of the fourth component.
   */
  QLabel* m_vLabel;



protected:
  /**
   * Revert the position of cursors in line editors in order 
   * to see the beginning of text.
   */
  void revertCursorPosition();

  /**
   * Set label names. Those are names of components of two-dimensional vector.
   */
  void setNameLabels(QString * nameLabels);

  virtual bool edited();

private:
  // Initialize this widget.
  void initClass();

  // Build widgets which represent a component of the vector.
  void buildComponent(QLineEdit *&line, QLabel *&label);

};

#endif // DvSF4FBOX_H

