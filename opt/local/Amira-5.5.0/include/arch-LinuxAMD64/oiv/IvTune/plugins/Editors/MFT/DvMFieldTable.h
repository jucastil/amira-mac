/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : Tristan Mehamli (Jul 2010)
**=======================================================================*/
#ifndef DVMFIELDTABLE_H
#define DVMFIELDTABLE_H

#include <QtGui/QTableWidget>
#include <QtGui/QKeyEvent>
#include <QtGui/QItemDelegate>

#include <IvTune/plugins/DvLibName.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class QWidget;
class QLineEdit;
class QTableWidgetItem;
class DvMFieldWidget;
class DvFieldEditorCommandManager;
class DvMFieldTableItemDelegate;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvMFieldTable
//
//  Class that implements a table.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * The DvMFTable class implements a table with custom behaviour.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is derived from QTableWidget which implements a table. We use this class
 *  to allow user to interact with keyboard. 
 *  @OL
 *    @LI Shift is used to select several rows when it is kept pressed. 
 *    @LI DEL allow user to delete the selected row. 
 *    @LI "+" is used to add a row.
 *    @Li "-" is used to delete a row (same behaviour than DEL).
 *  @ol
 *  
 * @SEE_ALSO
 *  DvMFieldWidget.
 * 
 * 
 */ 

class DEMOVIEWER_API DvMFieldTable :public QTableWidget
{
  Q_OBJECT

public:
  /**
   * Constructor.
   */
  DvMFieldTable( DvFieldEditorCommandManager* commandManager = NULL, 
                 DvMFieldWidget* parent = 0, const char* name = 0 );

  /**
   * Destructor.
   */
  virtual ~DvMFieldTable();

 /**
  * Types of cell.
  */
  enum MFTableTypeCell
  {
    /** No type */
    NoType, 
    /** Short */
    ShortCell, 
    /** Unsigned short */
    UShortCell, 
    /** Integer */
    IntCell, 
    /** Unsigned integer */
    UIntCell, 
    /** Long */
    LongCell, 
    /** Unsigned long */
    ULongCell, 
    /** Float */
    FloatCell, 
    /** Double */
    DoubleCell 
  };

 /**
  * Sets the range for double editors.
  */
  void setDoubleEditorRange( double min, double max );

 /*
  * Sets the range for integer editors.
  */
  void setIntEditorRange( int min, int max );

 /*
  * Bounds values if true
  */
  void setBoundedValue( bool bounded );

 /*
  * Sets the type of cell.
  */
  void setCellType( MFTableTypeCell type );

public Q_SLOTS:
 /*
  * Removes the row from the table.
  */
  void setNumRows( int row );

  /**
   * Moves up a row in the table. 
   */
	void swapUpRow();

  /**
   * Moves down a row in the table. 
   */
	void swapDownRow();

  /**
   * Deletes a row in the table. 
   */
	virtual void deleteRow();

  /**
   * Adds a row in the table.
   */
	virtual void addRow();

  /**
   * Shows a row in the table. It is called by the spin box.
   */
	void showTableRow( int );

 /*
  * Swaps row1 with row2.
  */
  virtual void swapRows( int row1, int row2 );

protected:
  //Event received when a key is pressed.
  virtual void keyPressEvent( QKeyEvent* e );

  //Event received when a key is released.
  virtual void keyReleaseEvent( QKeyEvent* e );

  // Parent widget.
  DvMFieldWidget* m_parentWidget;

  // Command manager.
  DvFieldEditorCommandManager* m_commandManager;

 /**
  * Delegate for table items.
  */
  DvMFieldTableItemDelegate* m_itemDelegate;

protected Q_SLOTS:
  virtual void editorDestroyed( QObject* editor );

private:
  /*
   * Intializes the class.
   */
  void initClass();

  // flag used to know if the shift key is pressed.
  bool m_multiSelectionState;
};

/**
 * The DvMFieldTableItemDelegate class implements a QItemDelegate with custom behaviour.
 *
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *  This class is derived from QItemDelegate to customize the edition of the table cells. 
 *  
 * @SEE_ALSO
 *  DvMFieldWidget.
 */

class DvMFieldTableItemDelegate : public QItemDelegate
 {
 public:
 /*
  * Defines the cell type.
  */
  enum MFTableTypeCell
  {
    /** Default **/
    NoType, 
    /** Short **/
    ShortCell, 
    /** Unsigned Short **/
    UShortCell,
    /** Integer **/
    IntCell,
    /** Unsigned Integer **/
    UIntCell,
    /** Long **/
    LongCell, 
    /** Unsigned Long **/
    ULongCell, 
    /** Float **/
    FloatCell, 
    /** Double **/
    DoubleCell 
  };

  /*
   * Constructor.
   */
   DvMFieldTableItemDelegate( DvFieldEditorCommandManager* commandManager = NULL, DvMFieldWidget* editorWidget = NULL,
                              QObject* parent = 0 );

   virtual ~DvMFieldTableItemDelegate() {}

  /*
   * Returns the widget used to change data from the model.
   */
   virtual QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option,
                                  const QModelIndex& index ) const;

  /*
   * Provides the widget with data to manipulate.
   */
   virtual void setEditorData( QWidget* editor, const QModelIndex& index ) const;

  /*
   * Ensures that the editor is displayed correctly with respect to the item view.
   */
   virtual void setModelData( QWidget* editor, QAbstractItemModel* model,
                              const QModelIndex& index ) const;

  /*
   * Returns updated data to the model.
   */
   virtual void updateEditorGeometry( QWidget* editor,
                                      const QStyleOptionViewItem& option, const QModelIndex& index ) const;

  /*
   * Sets the cell type.
   */
   void setCellType( int type );

  /*
   * Sets the range for double editors.
   */
   void setDoubleEditorRange( double min, double max );

  /*
   * Sets the range for int editors.
   */
   void setIntEditorRange( int min, int max );

  /*
   * Bounds the editors values if true.
   */
   void setBoundedValue( bool bounded );

  /*
   * Renders the delegate using the given painter and style option for the item specified by index.
   */
   virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;

 protected:
  /*
   * Sets the validator which will check type of text being edited.
   */
   virtual void setValidator( QLineEdit* lineEdit ) const;

  /*
   * Pointer to the editor's parent widget.
   */
   DvMFieldWidget* m_editorParentWidget;

  /*
   * Pointer to the command manager.
   */
   DvFieldEditorCommandManager* m_commandManager;

 private:
   MFTableTypeCell m_typeCell;

   int m_maxInt;
   int m_minInt;
   double m_maxDouble;
   double m_minDouble;
   bool m_isBounded;
 };

#endif // SOMFIELDTABLE_H

