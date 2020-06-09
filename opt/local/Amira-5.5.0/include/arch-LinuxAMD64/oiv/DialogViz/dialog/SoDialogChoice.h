/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_CHOICE_
#define  _SO_DIALOG_CHOICE_

#include <DialogViz/dialog/SoDialogComponent.h>
#include <Inventor/fields/SoMFString.h>

class SoDialogChoiceAuditor;

/**
 * @VSGEXT Abstract class for a multiple choice node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node specifies the properties for SoDialogRadioButtons and SoDialogComboBox
 *   nodes.
 *
 * @SEE_ALSO
 *   SoDialogComboBox,
 *   SoDialogRadioButtons
 *
 */

class DIALOGVIZ_API SoDialogChoice : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogChoice);

 public:

  /**
   * List of strings appearing in the component. @B items@b is empty by default.
   */
  SoMFString  items;

  /**
   * Selected choice. Default value is zero, the first item in @B items@b.
   */
  SoSFInt32   selectedItem;

  /**
   * Adds a dialogChoiceAuditor to the current Choice component.
   */
  void addAuditor(SoDialogChoiceAuditor* auditor);

  /**
   * Removes the specified choiceAuditor from the auditor list.
   */
  void removeAuditor(SoDialogChoiceAuditor* auditor);

  /**
   * Convenient method for adding a new item.
   */
   void addItem(SbString newItem);

  /**
   * Convenient method for inserting a new item.
   */
   void insertItem(int index, SbString newItem);

  /**
   * Convenient method for removing a new item.
   */
   void removeItem(int index);

/*==============================================================================*/
SoINTERNAL public:
  virtual SoWidget getLabelWidget();
  static  void   initClass();
  static  void   exitClass();
  virtual void   updateFromSensor(SoSensor* sensor);
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();

  void applyDlgCptAuditor();

 protected:
  int m_numItems;

  SoDialogChoice();
  virtual ~SoDialogChoice();

  // reflex function when fields change
  virtual void changeEnable() {};
  virtual void changeWidgetEnable(SbBool ) {};
  virtual void changeItems() {};
  virtual void changeLabel();
  virtual void changeLabelAlignment() {};
  virtual void changeLabelVisibility() {};
  virtual void changeSelectedItem() {};
  void fixItemsNumber();

  /* === FIELDS DECLARATION === */
  FIELD_SENSOR(items);
  FIELD_SENSOR(selectedItem);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

protected:
  SoText3 *choiceLabel;
  SoTranslation* choiceLabelTranslation;
  int m_initItem;
  int m_prevNumItems;
  int m_prevSelectedItem;
  SbBool m_needUpdate;

  virtual void change3DSelectedItem() {};
  virtual void change3DItems() {};

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_CHOICE_
