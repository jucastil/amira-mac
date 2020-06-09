/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFCOLORWIDGET_H
#define DvSFCOLORWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QToolButton;
class SbString;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFColorWidget
//
//  Base class for widgets which edit a single-value field
//  containing a RGB color stored as three floats.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFColorWidget class implements a widget editor of RGB color.
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields
 *  that contains a RGB color stored as three floats.
 *  The table contains four columns. One box display the current color of a row, and
 *  three others cells contain the component of the color. If user clicks on the box,
 *  it launchs a convivial color dialog (QColorDialog). It gives so two ways so as to edit color.
 *  It gives also some extra convenience methods that allow values or the color of the box
 *  to be changed immediately according to the value of the other editing way.
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 *
 *
 */

class DEMOVIEWER_API DvSFColorWidget : public DvSFieldWidget
{
    Q_OBJECT

public:

  /**
   * Default constructor.
   */
  DvSFColorWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0,
              		const char* name = 0, Qt::WFlags fl = 0 );

    /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFColorWidget(const char *fieldName, DvFieldEditorCommandManager * manager,
                  QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFColorWidget();

  QPushButton *		m_colorDisp;
	QLineEdit *			m_rEdit;
	QLineEdit *			m_gEdit;
	QLineEdit *			m_bEdit;
	QLabel *			m_rLabel;
	QLabel *			m_gLabel;
	QLabel *			m_bLabel;

  /**
   * Set values contained in the table to the field.
   */
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */
  void refresh();

protected:
	float m_rValue;
	float m_gValue;
	float m_bValue;
	void displayColor();

  bool edited();

protected Q_SLOTS:
	void changeRValue(const QString & str);
	void changeGValue(const QString & str);
	void changeBValue(const QString & str);
	void getColorEditor();

private:
	void initClass();
  void buildComponent(QLineEdit *&line, QLabel *&label);
};

#endif //DvSFCOLORWIDGET_H

