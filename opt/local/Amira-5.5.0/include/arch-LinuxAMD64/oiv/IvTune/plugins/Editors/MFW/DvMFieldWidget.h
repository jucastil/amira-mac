/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvMFIELDWIDGET_H
#define DvMFIELDWIDGET_H

#include <QtCore/qglobal.h>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QKeyEvent>
#include <QtGui/QPixmap>
#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/DvFieldEditors.h>

class QLabel;
class QSpinBox;
class QKeyEvent;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;

class DvMFieldTable;
class DvFieldEditorCommandManager;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFieldWidget
//
//  Abstract base class for all multiple-valued field widget.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFieldWidget class implements a widget which edit SoMField classes.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  SoSField implements a widget which edit multiple values from a field.
 *  Each class derived from DvMFieldWidget begins with a DvMF prefix and represents a 
 *  field that contains many values of a particular type. Each has setToField() and 
 *  getFromField() methods that are used to change or access these values. 
 *  In addition, some widget classes have extra convenience methods that allow 
 *  a type checking or label naming.
 *  
 * @SEE_ALSO
 *  DvFieldEditors, DvSFieldWidget.
 */ 

class DEMOVIEWER_API DvMFieldWidget : public DvFieldEditors
{
    Q_OBJECT

public:
  /**
   * Default Constructor.
   */
  DvMFieldWidget( DvFieldEditorCommandManager*, QWidget* parent = 0, const char* name = 0, 
                  Qt::WindowFlags fl = 0 );

  /**
   * Constructor. Set fieldName as text of the widget label.
   */
  
  DvMFieldWidget( const char* fieldName ,DvFieldEditorCommandManager*, 
		              QWidget* parent = 0, const char* name = 0, 
                  Qt::WindowFlags fl = 0 );

   /**
    * Destructor.
    */
  ~DvMFieldWidget();

  inline void setRefresh( bool refresh ) { m_setRefresh = refresh; }

  inline bool isRefresh() { return m_setRefresh; }


  
  /**
   * Table flags 
   */
  static const int m_colorTableFlag;

  /**
   * This spin box allows a direct access to a field in the table.
   */
  QSpinBox*		          m_accessBox;

  /**
   * This button is used to move up a field in the table.
   */
  DvButton*	        m_upButton;

  /**
   * This button is used to move down a field in the table.
   */
  DvButton*	        m_downButton;

  /**
   * Default push button.
   */
  DvButton*	        m_defaultButton;

  /**
   * Ignore push button.
   */
  DvButton*	        m_ignoreButton;

  /**
   * Used to delete a field in the table.
   */
  DvButton*	        m_deleteButton;

  /**
   * Used to add a field in the table.
   */
  DvButton*        	m_addButton;
  
  /**
   * Frame which contains the field label.
   */  
  QFrame*                m_labelFrame;
    
  /**
   * Label which displays the name of the represented field.
   */
  QLabel*			          m_label;

  /**
   * Table which contains values of the field.
   */
  DvMFieldTable*			  m_table;

  virtual QString getFieldValue( int row, int col ) const;
  void setField( SoField* field ) ;
  virtual void refresh() ;
  
  /// Methods for command manager

  virtual void swapRows( int index1, int index2 );
  virtual void swapColumns( int col1, int col2 );
  virtual void set1Value( int vec, int dim = -1, QString value = QString::null );
  virtual void setValue( int, const void* ){};

  virtual void applyChanges(){}

  virtual int getTextFlags();

  SoField* m_field;

protected:

  /**
   * Constructor.
   */
  DvMFieldWidget( const char* fieldName, int tableFlag,
                 DvFieldEditorCommandManager*, QWidget* parent = 0, const char* name = 0, 
                 Qt::WindowFlags fl = 0 );

  DvMFieldWidget( int tableFlag,
                  DvFieldEditorCommandManager*, QWidget* parent = 0, const char* name = 0, 
                  Qt::WindowFlags fl = 0 );

  // Layout of this widget.
  QGridLayout*  m_globalLayout;

  //Layout of all buttons and the spin box.
  QHBoxLayout*  m_buttonsLayout; 

  //Layout of add and delete buttons
  QHBoxLayout*  m_manageButtonsLayout; 

  //Layout of up and down buttons.
  QHBoxLayout*  m_movementButtonLayout;

  //Layout of ignore and default buttons.
  QHBoxLayout*  m_editionButtonLayout;

  //Spacer between the label frame and the edition area.
  QSpacerItem* m_labelTableSpacer;

  //Spacer between add and delete buttons and the spin box.
  QSpacerItem* m_manageAccessSpacer;

  //Spacer between up and down buttons and the spin box.
  QSpacerItem* m_accessMoveSpacer;

  DvFieldEditorCommandManager* m_commandManager;

  virtual bool checkField( SoField* ){ return false; }

protected Q_SLOTS:
  
  /** 
   * Name sub-widget. 
   */
  virtual void languageChange();

  /**
   * Trigger off a command when ignore button is pressed.
   */
  void ignoreButtonStateChanged();

  virtual void setDefaultFieldValue();

private:
  // Images upon buttons.
  QPixmap m_deleteImage; 
  QPixmap m_addImage; 
	QPixmap m_upImage;  
  QPixmap m_downImage; 
  QPixmap m_defaultImage; 
  QPixmap m_ignoreImage;

  bool m_setRefresh;

	//function called by constructors
	void initClass();
};


#endif // DvMFIELDWIDGET_H

