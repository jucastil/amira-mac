/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DVMFCOLORTABLE_H
#define DVMFCOLORTABLE_H

#include <IvTune/plugins/Editors/MFT/DvMFieldTable.h>

class DvMFColorTableItemDelegate;

class DEMOVIEWER_API DvMFColorTable :public DvMFieldTable
{
  Q_OBJECT

public:
  /**
   * Constructor.
   */
  DvMFColorTable( DvFieldEditorCommandManager* commandManager, 
                  DvMFieldWidget* parent = 0, const char * name = 0 );

  /**
   * Destructor.
   */
  virtual ~DvMFColorTable();

protected Q_SLOTS:
  void getColorFromEditor( int row, int col );

};

/**
 * The DvMFColorTableItemDelegate class implements a DvMFieldTableItemDelegate with custom behaviour.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is derived from DvMFieldTableItemDelegate to fit the needs for the edtion of
 *  color table cells. 
 *  
 * @SEE_ALSO
 *  DvMFieldTableItemDelegate
 */

class DvMFColorTableItemDelegate : public DvMFieldTableItemDelegate
{
public:
 /*
  * Constructor.
  */
  DvMFColorTableItemDelegate( DvFieldEditorCommandManager* commandManager = NULL, DvMFieldWidget* editorWidget = NULL,
                              QObject* parent = 0 );

 /*
  * Destructor.
  */
  virtual ~DvMFColorTableItemDelegate() {}

  /*
   * Returns the widget used to change data from the model.
   */
   virtual QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option,
                                  const QModelIndex& index ) const;

  /*
   * Ensures that the editor is displayed correctly with respect to the item view.
   */
   virtual void setModelData( QWidget* editor, QAbstractItemModel* model,
                              const QModelIndex& index ) const;

  /*
   * Renders the delegate using the given painter and style option for the item specified by index.
   */
   virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};

#endif // SOMFCOLORTABLE_H

