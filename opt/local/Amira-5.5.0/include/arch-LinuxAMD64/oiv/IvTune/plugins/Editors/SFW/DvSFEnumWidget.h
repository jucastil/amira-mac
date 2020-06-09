/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFENUMWIDGET_H
#define DvSFENUMWIDGET_H

#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QComboBox;
class SbName;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFEnumWidget
//
//  Base class for widgets which edit a single-value field 
//  containing an enumerated type value.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFEnumWidget class implements a widget editor of enumerated type value.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields 
 *  that contains an enumerated type value. Table items are combo boxes.
 *  These boxes use mnemonic names for values defined in nodes which use SoMFEnum.
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvSFEnumWidget : public DvSFieldWidget
{

public:
  /**
   * Default constructor.
   */
  DvSFEnumWidget(DvFieldEditorCommandManager *, QWidget* parent = 0, 
              	 const char* name = 0, Qt::WFlags fl = 0 );

    /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   * @param numValues Number of values.
   * @param enumName Mnemonic names.
   */
	DvSFEnumWidget( const char *fieldName, DvFieldEditorCommandManager *, 
                  int numValue, SbName *enumName ,
		              QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFEnumWidget();

	QComboBox *			m_comboBox;
	
  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();
};

#endif //DvSFENUMWIDGET_H

