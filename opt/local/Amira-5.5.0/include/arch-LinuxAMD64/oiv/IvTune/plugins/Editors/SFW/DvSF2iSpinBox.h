/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSF2ISPINBOX_H
#define DvSF2ISPINBOX_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QLabel;
class QSpinBox;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSF2iSpinBox
//
//  Base class for widgets which edit a single-value field 
//  containing a two-dimensional vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSF2iSpinBox class implements a widget which edit a two-dimensional vector.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is a base class for widgets which represent single-value fields 
 *  that contains a two-dimensional vector. It gives some 
 *  extra convenience methods that allow type checking or label naming. Components of vector 
 *  are displayed in spin boxes.
 *
 * @SEE_ALSO
 *  DvMFieldWidget.
 * 
 * 
 */ 


class DEMOVIEWER_API DvSF2iSpinBox : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
  DvSF2iSpinBox(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                const char* name = 0, 
                Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSF2iSpinBox( const char *fieldName, DvFieldEditorCommandManager * manager, 
             		 QWidget* parent = 0, const char* name = 0, 
                 Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSF2iSpinBox();
    
  /** 
   * Spin box which edit the second component of vector.
   */
  QSpinBox* m_yBox;

  /** 
   * Spin box which edit the first component of vector.
   */
  QSpinBox* m_xBox;
  
  /** 
   * Label which display the name of the second component.
   */
  QLabel* m_yLabel;

  /** 
   * Label which display the name of the first component.
   */
  QLabel* m_xLabel;

  /**
   * Set label names. Those are names of components of two-dimensional vector.
   */
  void setNameLabels(QString * nameLabels);
protected:

  /**
   * Set type of data to check it.
   */
  void setLimits(int typeId);

private:
  // Initialize this widget.
  void initClass();

  // Build widgets which represent a component of the vector.
  void buildComponent(QSpinBox *&box, QLabel *&label);
};

#endif // DvSF2ISPINBOX_H

