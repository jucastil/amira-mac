/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFBOOLWIDGET_H
#define DvSFBOOLWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QCheckBox;
class SbString;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFBoolWidget
//
//  Base class for widgets which edit a single-value field 
//  containing a Boolean value.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFBoolWidget class implements a widget editor of a Boolean value.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains a Boolean value. Table items are check boxes.
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvSFBoolWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
    DvSFBoolWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		  const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFBoolWidget( const char *fieldName, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFBoolWidget();

    QCheckBox *		m_box;

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();


private:
  void initClass();
};

#endif //DvSFBOOLWIDGET_H

