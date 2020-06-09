/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFIELDWIDGET_H
#define DvSFIELDWIDGET_H

#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtCore/QVariant>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QSpacerItem;
class DvFieldEditorCommandManager;
class DvSlider;

#include <IvTune/plugins/Editors/DvFieldEditors.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFieldWidget
//
//  Abstract base class for all single-value field widget.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFieldWidget class implements a widget which edit SoSField classes.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  DvSField implements a widget which edit a single value from a field.
 *  Each class derived from DvSFieldWidget begins with a DvSF prefix and represents a 
 *  field that contains one value of a particular type. Each has setToField() and 
 *  getFromField() methods that are used to change or access this value. 
 *  In addition, some widget classes have extra convenience methods that allow 
 *  a type checking or label naming.
 *  
 * @SEE_ALSO
 *  DvFieldEditors, DvMFieldWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvSFieldWidget : public DvFieldEditors
{
    Q_OBJECT

    friend class DvSlider;

public:
  /**
   * Default Constructor.
   */
  DvSFieldWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
                 const char* name = 0, Qt::WindowFlags fl = 0 );
	
  /**
   * Constructor. Set fieldName as text of the widget label.
   */
  DvSFieldWidget(const char* fieldName, DvFieldEditorCommandManager * manager, 
		             QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSFieldWidget();

  enum SFFrameType { NoPreFrame, IvTuneRealSlide, IvTuneInt32Slide, IvTuneUInt32Slide,
                     IvTuneShortSlide, IvTuneUShortSlide, IvTuneIntSlide };
  /**
   * Label which displays the name of the represented field.
   */
  QLabel*			  m_label;

  /**
   * Default button.
   */
  DvButton*	m_defaultButton;

  /**
   * Ignore button.
   */
  DvButton*	m_ignoreButton;

  void setField(SoField * field) ;
  virtual void refresh() ;

  void setRefresh (bool){}

  virtual void applyChanges();

  void swapRows(int index1, int index2);
  void swapColumns( int col1, int col2);
  void set1Value(int vec, int dim = -1, QString value = QString::null);
  void setValue(int , const void * ){};

protected:

  /**
   * Constructor used when we have already a frame (e.g. DvSlider )
   * without fieldname
   */
  DvSFieldWidget( SFFrameType type, DvFieldEditorCommandManager * manager,
		              QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );


  /**
   * Constructor used when we have already a frame (e.g. DvSlider )
   */
  DvSFieldWidget( const char* fieldName, SFFrameType type, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );

	SoField *	m_field;
  DvFieldEditorCommandManager * m_commandManager;

  // Frame which will contains specific edition components.
  QFrame *              m_editionFrame;

  // Layout of the widget.
  QHBoxLayout *         m_frameLayout;
  QHBoxLayout *         m_buttonLayout;
  QHBoxLayout *         m_editLayout;
  QHBoxLayout *         m_editionAreaLayout;

  // Spacer between the label and the edition area (m_editionAreaLayout).
  QSpacerItem *         m_labelEditSpacer;
  // Spacer between the edition frame and buttons.
  QSpacerItem *         m_editButtonSpacer;

  virtual bool edited() ;

protected Q_SLOTS:

  /** 
   * Name sub-widget. 
   */
  virtual void languageChange();
  virtual void setCommandValue();

  void setFocusLeaveEvent();

  /**
   * Trigger off a command when ignore button is pressed.
   */
  void ignoreButtonStateChanged();

  virtual void setDefaultFieldValue();

private:
  // images. upon buttons.
  QPixmap			m_defaultImage;		
  QPixmap			m_ignoreImage;
	
  // Initialize all components of this widget. Called by constructors.
	void initClass();
};

#endif // DvSFIELDWIDGET_H

