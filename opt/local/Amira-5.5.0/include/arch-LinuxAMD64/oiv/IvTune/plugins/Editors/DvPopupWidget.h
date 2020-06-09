/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOPOPUPWIDGET_H
#define SOPOPUPWIDGET_H

#include <QtGui/QFrame>
#include <QtGui/QPixmap>
#include <QtGui/QLineEdit>
#include <QtCore/QVariant>

#include <IvTune/plugins/Editors/SFW/DvSFLineWidget.h>

class QPushButton;

class DEMOVIEWER_API DvPopupWidget : public DvSFLineWidget
{
    Q_OBJECT

public:
  DvPopupWidget(DvFieldEditorCommandManager * manager, int frameRows, 
		            int frameColumns, QWidget* parent = 0, 
                const char* name = 0, 
                Qt::WFlags fl = 0);
	
	DvPopupWidget( const char *fieldName, DvFieldEditorCommandManager * manager, 
                 int frameRows, int frameColumns,
                 QWidget* parent = 0, const char* name = 0, 
                 Qt::WFlags fl = 0 );

	~DvPopupWidget();
	
protected:
	QPushButton* m_editButton;
	QFrame*	     m_popupFrame;
  QLineEdit**	 m_lineEditArray;
	int					 m_numPopupLine;

	//0 no type, 1 short, 2 int, 3 float, 4 double
	void      setValidator(int typeId);
  void      revertCursorPosition();
  virtual bool edited();

protected Q_SLOTS:
	void			managePopFramePos();
	

private:
	QPixmap			m_editImage;			

	void initClass(int frameRows, int frameColumns);
};

#endif //DVPOPUPWIDGET_H

