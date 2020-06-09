/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFIMAGEWIDGET_H
#define DvSFIMAGEWIDGET_H

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QPushButton;
class SbString;
class SoField;
class DvSFImageLabel;
class QPixmap;
class QLabel;
class QMouseEvent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFImageWidget
//
//////////////////////////////////////////////////////////////////////////////


class DEMOVIEWER_API DvSFImageWidget : public DvSFieldWidget
{

public:

  /**
   * Default constructor.
   */
    DvSFImageWidget(DvFieldEditorCommandManager * manager, QWidget* parent = 0, 
              		  const char* name = 0, Qt::WindowFlags fl = 0 );

    /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
	DvSFImageWidget(const char *fieldName, DvFieldEditorCommandManager * manager, 
                  QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );

  /**
   * Destructor.
   */
	~DvSFImageWidget();

  DvSFImageLabel *		m_imageBox;

  /**
   * Set values contained in the table to the field.
   */ 
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */ 
  void refresh();

  static void getPixmapFromField(SoField * field, QPixmap &);


private:
  void initClass();

  QPixmap * m_buttonImage;

  QIcon * m_iconImage;

  static uchar * copyBuffer(const uchar *, int size);
};

class DvSFImageLabel : public QLabel
{

public:

  /**
   * Default constructor.
   */
    DvSFImageLabel( int width, int height, QWidget * parent, const char * name = 0 );

  /**
   * Destructor.
   */
	~DvSFImageLabel();

  void setPixmap ( const QPixmap &);

protected:
  void mouseMoveEvent ( QMouseEvent * e );

private:
  QLabel * m_pixmapFrame;
};

#endif //DvSFIMAGEWIDGET_H

