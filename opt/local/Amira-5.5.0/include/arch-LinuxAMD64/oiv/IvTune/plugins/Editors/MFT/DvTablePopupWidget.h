/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DVTABLEPOPUPWIDGET_H
#define DVTABLEPOPUPWIDGET_H

#include <QtGui/QLineEdit>

#include <IvTune/plugins/Editors/MFW/DvMFieldWidget.h>

class QPushButton;
class DvTablePopupLineEdit;
class QFrame;
class QPixmap;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvTablePopupWidget
//
//  Base class for widgets which edits a multiple-value field 
//  containing any number of huge data like matrices.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvTablePopup class implements a widget which edit huge data.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is a base class for widgets which represent multiple-value fields 
 *  that contains any number of huge or heavy data like matrices. These piece of data 
 *  are displayed in a frame apart from the widget. One frame can be displayed at once. 
 *  In this case frame are popup widgets.
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvMFLineWidget.
 * 
 * 
 */

class DEMOVIEWER_API DvTablePopupWidget : public DvMFieldWidget
{
    Q_OBJECT

	friend class DvTablePopupLineEdit;

public:
  /**
   * Default constructor.
   */
  DvTablePopupWidget(DvFieldEditorCommandManager *manager,
                     int frameRows, int frameColumns, QWidget* parent = 0, 
		                 const char* name = 0, 
                     Qt::WindowFlags fl = 0);
	
  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvTablePopupWidget( const char *fieldName, 
                      DvFieldEditorCommandManager *manager, int frameRows, int frameColumns,
                      QWidget* parent = 0, const char* name = 0, 
                      Qt::WindowFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvTablePopupWidget();
	
protected:
  /** 
   * Edition button.
   */
	QPushButton *		          m_editButton;

  /**
   * Frame that display huge data.
   */
	QFrame		*		            m_popupFrame;

  /**
   * Array of edition lines which are on the frame 
   * and represent components of the piece of data we want to edit.
   */
	DvTablePopupLineEdit	**	m_lineEditArray;

  /**
   * Number of components.
   */
	int             					m_numPopupLine;
	
	/**
   * Check type of text edited on frame.
   */
	void setValidator(int typeId);

  /**
   * This method moves the frame at the right place (left of editor).
   */
  void			managePopFramePos();

  /**
   * Update text in edition lines.
   */
  void      updatePopupLines(int row = -1);

  /**
   * Display correctly text in edition lines so user could see the beginning.
   */
  void      revertCursorPosition();

  virtual QString getPopupValue(int rowToEdit, int index);

protected Q_SLOTS:
  /**
   * Launch the frame on elected row.
   */
	void      setEditFrame();

private:
  // Image upon button.
	QPixmap			m_editImage;
  
  // Initialize this widget.
	void initClass(int frameRows, int frameColumns);
};

////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvTablePopupLineEdit
//
//    DvTablePopupLineEdit implements a one-line text editor.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * DvTablePopupLineEdit class implements a one-line text editor.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *    This class is derived from QLineEdit in order to introduce a new behaviour.
 *  When text changes, text displayed in the table changes accordingly.
 *
 * @SEE_ALSO
 *  DvMFieldWidget, DvMFLineWidget.
 * 
 * 
 */

class DEMOVIEWER_API DvTablePopupLineEdit : public QLineEdit
{
	Q_OBJECT
public:
  /**
   * Constructor.
   */
	DvTablePopupLineEdit(int index, DvTablePopupWidget *	mainWidget, 
		QWidget * parent, const char * name = 0 );

public Q_SLOTS:
  /**
   * This slot warns SoTablePopupWidget when text changes.
   */
	void setCurrentValue(const QString &);

private:
  // DvTablePopupWidget
	DvTablePopupWidget *	m_mainWidget;
};

#endif //DVTABLEPOPUPWIDGET_H

