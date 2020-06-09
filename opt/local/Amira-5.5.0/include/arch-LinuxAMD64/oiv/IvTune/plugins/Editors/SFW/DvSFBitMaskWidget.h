/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DvSFBITMASKWIDGET_H
#define DvSFBITMASKWIDGET_H

#include <QtCore/QVariant>
#include <QVector>

#include <IvTune/plugins/Editors/SFW/DvSFieldWidget.h>

class QCheckBox;
class SbString;
class SoField;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvSFBitMaskWidget
//
//  Base class for widgets which edit a single-value field
//  containing a BitMaskean value.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvSFBitMaskWidget class implements a widget editor of a BitMaskean value.
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *  This class implements a widget which represents single-value fields
 *  that contains a BitMaskean value. Table items are check boxes.
 *
 * @SEE_ALSO
 *  DvSFieldWidget.
 *
 *
 */

class DEMOVIEWER_API DvSFBitMaskWidget : public DvSFieldWidget
{
  Q_OBJECT
public:

  /**
   * Default constructor.
   */
  DvSFBitMaskWidget(SoField* field, DvFieldEditorCommandManager * manager, QWidget* parent = 0,
                    const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Constructor.
   * @param fieldName Name of the field which is represented by this widget.
   */
  DvSFBitMaskWidget(SoField* field,  const char *fieldName, DvFieldEditorCommandManager * manager,
                    QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );

  /**
   * Destructor.
   */
  ~DvSFBitMaskWidget();


  /**
   * Set values contained in the table to the field.
   */
  void applyChanges();

  /**
   * Get and display values contained in the field.
   */
  void refresh();

protected Q_SLOTS:
  virtual void setBitMaskValue();

private:
  void initClass();
  QVector<QCheckBox *> m_boxes;
};

#endif //DvSFBOOLWIDGET_H

