/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXTAXISEDITOR_H_
#define _POXTAXISEDITOR_H_

#include <MeshViz/PoMeshVizW.h>
#include <Inventor/SbLinear.h>
#include <Inventor/Xt/SoXtComponent.h>

#include <Inventor/dialog/PoXtDialog.h>

class SoCallbackList;
class PoAxis;
class SoSensor;
class SoNodeSensor;
struct menuColumn;


/**
 * @DTEXT  Abstract class for axes editors.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtAxisEditor
: public SoXtComponent
{

 public:

   /**
    * [OIV-WRAPPER NAME{AxisEditorCB}]
    */
  typedef void PoXtAxisEditorCB (void * userData, PoAxis * data);

  enum TextAxisMask
  {
    NO_TEXT_MASK               = 0x00000000,

    GRAD_VISIBILITY            = 0x00000001,
    GRAD_POSITION              = 0x00000002,
    GRAD_PATH                  = 0x00000004,
    GRAD_FONT_NAME             = 0x00000008,
    GRAD_FONT_SIZE             = 0x00000010,
    GRAD_DIST_AXIS             = 0x00000020,
    GRAD_ADD_STRING_VISIBILITY = 0x00000040,
    GRAD_ADD_STRING            = 0x00000080,
    GRAD                       = GRAD_VISIBILITY | GRAD_POSITION
    | GRAD_PATH | GRAD_FONT_NAME | GRAD_FONT_SIZE
    | GRAD_DIST_AXIS | GRAD_ADD_STRING_VISIBILITY
    /**
     *  Family mask.
     */
    | GRAD_ADD_STRING, 
    /**
     *  GRAD is a family mask, thus:
     */
                                                  
    /**
     *  GRAD = GRAD_VISIBILITY | ... | GRAD_ADD_STRING
     */
                                                  

    TITLE_VISIBILITY           = 0x00000100,
    TITLE_POSITION             = 0x00000200,
    TITLE_PATH                 = 0x00000400,
    TITLE_FONT_NAME            = 0x00000800,
    TITLE_FONT_SIZE            = 0x00001000,
    TITLE_DIST_AXIS            = 0x00002000,
    TITLE_STRING               = 0x00004000,
    TITLE                      = TITLE_VISIBILITY | TITLE_POSITION | TITLE_PATH
    | TITLE_FONT_NAME | TITLE_FONT_SIZE | TITLE_DIST_AXIS
    /**
     *  Family mask.
     */
    | TITLE_STRING, 

    REVERSE_FLAG               = 0x00008000,

    MISC_TEXT_ATTR             = 0x00010000,

    ALL_TEXT_MASK = GRAD | TITLE | REVERSE_FLAG | MISC_TEXT_ATTR
  } ;



  enum GeomAxisMask
  {
    NO_GEOM_MASK                = 0x00000000,
    
    MARGIN_TYPE                = 0x00000001,
    MARGIN_START               = 0x00000002,
    MARGIN_END                 = 0x00000004,
    MARGIN                     = MARGIN_TYPE | 
    MARGIN_START | 
    /**
     *  Family mask.
     */
    MARGIN_END,  

    GRID_VISIBILITY             = 0x00000008,
    GRID_LENGTH_GRAD_SIDE       = 0x00000010,
    GRID_LENGTH_GRAD_OTHER_SIDE = 0x00000020,
    GRID                        = GRID_VISIBILITY | 
    GRID_LENGTH_GRAD_SIDE |
    /**
     *  Family mask.
     */
    GRID_LENGTH_GRAD_OTHER_SIDE,  

    ARROW_VISIBILITY            = 0x00000040,
    ARROW_HEIGHT                = 0x00000080,
    ARROW_LENGTH                = 0x00000100,
    ARROW                       = ARROW_VISIBILITY | 
    ARROW_HEIGHT | 
    /**
     *  Family mask.
     */
    ARROW_LENGTH,  

    TICK_VISIBILITY             = 0x00000200,
    TICK_POSITION               = 0x00000400,
    TICK_MAIN_LENGTH            = 0x00000800,
    TICK_SUB_LENGTH             = 0x00001000,
    TICK_SUB_DEF                = 0x00002000,
    TICK_NUM_OR_PERIOD          = 0x00004000,
    TICK_FIRST_GRAD             = 0x00008000,
    TICK_LAST_GRAD              = 0x00010000,
    TICK_ALL                    = TICK_VISIBILITY | 
    TICK_POSITION | 
    TICK_MAIN_LENGTH |
    TICK_SUB_LENGTH | 
    TICK_SUB_DEF | 
    TICK_NUM_OR_PERIOD |
    TICK_FIRST_GRAD | 
    /**
     *  Family mask.                          
     */
    TICK_LAST_GRAD,  
    
    ALL_GEOM_MASK                = MARGIN | GRID | ARROW | TICK_ALL
  } ;



  enum Presentation
  {
    TOGGLE_FOLD,
    TOGGLE_UNFOLD,
    LABEL_UNFOLD 
  } ;



  /**
   *  Type of update.
   */
  enum UpdateFrequency
  {
    /**
     *  Updates the attached object at each modification.
     */
    CONTINUOUS,  
    /**
     *  Updates the attached object when hitting the accept button.
     */
    AFTER_ACCEPT 
  } ;

 public:

  /**
   * Attach the editor to an axis node.
   */
  virtual void attach (PoAxis * axis);

  /**
   * Detach the editor from an axis node.
   */
  void detach ();

  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool isAttached () const;

  /**
   * Addscallbacks which are called on axis changes. (See the method 
   * setUpdateFrequency to define the moment when the callbacks are called).
   * [OIV-WRAPPER EVENT_NAME{AxisChanged}]
   */
  void addAxisChangedCallback (PoXtAxisEditorCB * func, void * userData);

  /**
   * Removes the callbacks called on axis changes. 
   * [OIV-WRAPPER EVENT_NAME{AxisChanged}]
   */
  void removeAxisChangedCallback (PoXtAxisEditorCB * func, void * userData);

  /**
   * Sets the presentation of the editor. (type = TOGGLE_FOLD by default).
   */
  virtual void setPresentation (Presentation type);

  /**
   * Gets the presentation of the editor.
   */
  Presentation getPresentation () const;

  /**
   * Sets the update frequency. (By default freq = CONTINUOUS).
   */
  void setUpdateFrequency (UpdateFrequency freq);

  /**
   * Gets the update frequency. 
   */
  UpdateFrequency getUpdateFrequency () const;

  /**
   * Sets editing filters defining which text axis attributes will be displayed in 
   * the editor. (By default inclusionMask = ALL_TEXT_MASK and 
   * exclusionMask = NO_TEXT_MASK).
   */
  void setTextAxisFilter (unsigned long inclusionMask,
                          unsigned long exclusionMask);

  /**
   * Gets editing filters defining which text axis attributes will be displayed in 
   * the editor. 
   */
  void getTextAxisFilter (unsigned long & inclusionMask,
                          unsigned long & exclusionMask) const;

  /**
   * Sets editing filters defining which geometry axis attributes will be 
   * displayed in the editor. (By default inclusionMask = ALL_GEOM_MASK and 
   * exclusionMask = NO_GEOM_MASK)
   */
  void setGeomAxisFilter (unsigned long inclusionMask,
                          unsigned long exclusionMask);

  /**
   * Gets editing filters defining which geometry axis attributes will be 
   * displayed in the editor. 
   */
  void getGeomAxisFilter (unsigned long & inclusionMask,
                          unsigned long & exclusionMask) const;

  virtual void show ();
  virtual void hide ();

  
 protected:
  PoXtAxisEditor (SoWidget Parent = NULL,
                  const char * name = NULL,
                  SbBool buildInsideParent = TRUE);

  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setAxisFilter();

  virtual ~PoXtAxisEditor ();
  
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  void updateXtElements ();

  virtual void copyAxisFields(PoAxis * dest, PoAxis * source);
  virtual void updateAxisFromXtElements ();
  
  virtual int getMenuItems();

  // Attribute
  PoAxis * _axis;
  PoAxis * _attachedAxis;
  PoXtDialog * _dialog;
  SoNodeSensor * _sensor;

  Presentation    _presentation;

  menuColumn * _menu;
  int          _menuItems;
  SoCallbackList * _callbackList;

 private:
  UpdateFrequency _frequency;
  int _classMenusNb;
  unsigned long   _incTextMask;
  unsigned long   _excTextMask;
  unsigned long   _incGeomMask;
  unsigned long   _excGeomMask;

  SbBool _isTextSet;
  SbBool _isGeomSet;

  void activate ();
  void deactivate ();


  // Callbacks for PoXtDialog
  static void acceptCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
  static void elementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
  static void visibilityChangeCB (void *, SbBool visible);
  static void sensorCB (void *, SoSensor *);
};


#endif // _POXTAXISEDITOR_H_

