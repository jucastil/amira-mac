/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXTLEGENDEDITOR_H_
#define _POXTLEGENDEDITOR_H_

#include <MeshViz/PoMeshVizW.h>
#include <Inventor/SbLinear.h>
#include <Inventor/Xt/SoXtComponent.h>

#include <MeshViz/PbBasic.h>

#include <Inventor/dialog/PoXtDialog.h>

class SoCallbackList;
class PoLegend;
class SoSensor;
class SoNodeSensor;
struct menuColumn;


/**
 * @DTEXT  Abstract class for all legend editors.
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtLegendEditor
: public SoXtComponent
{

 public:

  /** 
   * [OIV-WRAPPER NAME{LegendEditorCB}] 
   */
  typedef void PoXtLegendEditorCB (void * userData, PoLegend * data);

  enum LegendMask
  {
    NO_LEGEND_MASK               = 0x00000000,

    TITLE_VISIBILITY             = 0x00000001,
    TITLE_POSITION               = 0x00000002,
    TITLE_PATH                   = 0x00000004,
    TITLE_FONT_NAME              = 0x00000008,
    TITLE_FONT_SIZE              = 0x00000010,
    TITLE_STRING                 = 0x00000020,
    TITLE = TITLE_STRING | TITLE_FONT_SIZE | TITLE_FONT_NAME | TITLE_PATH
    /**
     *  Family mask
     */
    | TITLE_POSITION | TITLE_VISIBILITY, 

    VALUE_VISIBILITY             = 0x00000040,
    VALUE_POSITION               = 0x00000080,
    VALUE_FONT_NAME              = 0x00000100,
    VALUE_ADD_STRING_VISIBILITY  = 0x00000200,
    VALUE_ADD_STRING             = 0x00000400,
    VALUE = VALUE_ADD_STRING | VALUE_ADD_STRING_VISIBILITY | VALUE_FONT_NAME
    /**
     *  Family mask
     */
    | VALUE_POSITION | VALUE_VISIBILITY, 

    MARGIN_TYPE                  = 0x00000800,
    MARGIN_LEFT                  = 0x00001000,
    MARGIN_RIGHT                 = 0x00002000,
    MARGIN_BOTTOM                = 0x00004000,
    MARGIN_TOP                   = 0x00008000,
    MARGIN = MARGIN_TOP | MARGIN_BOTTOM | MARGIN_RIGHT 
    /**
     *  Family mask
     */
    | MARGIN_LEFT | MARGIN_TYPE,  

    INCREMENT_TYPE               = 0x00010000,
    NUM_COLUMNS                  = 0x00020000,
    BOX_RATIO                    = 0x00040000,
    MISC_TEXT_ATTR               = 0x00080000,
    /**
     *  Family mask
     */
    MISC = INCREMENT_TYPE | NUM_COLUMNS | BOX_RATIO | MISC_TEXT_ATTR, 
    
    ALL_LEGEND_MASK = TITLE | VALUE | MARGIN | MISC
  } ;


  enum Presentation
  {
    TOGGLE_FOLD,
    TOGGLE_UNFOLD,
    LABEL_UNFOLD 
  } ;


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
   * Attach the editor to a legend node.
   */
  virtual void attach (PoLegend * legend);

  /**
   * Detach the editor from a legend node.
   */
  void detach ();

  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool isAttached () const;

  /**
   * Adds callbacks which are called on legend changes. (See the method 
   * setUpdateFrequency to define the moment when the callbacks are called).
   * [OIV-WRAPPER EVENT_NAME{LegendChanged}]
   */
  void addLegendChangedCallback (PoXtLegendEditorCB * func, void * userData);

  /**
   * Removes the callbacks called on legend changes. 
   * [OIV-WRAPPER EVENT_NAME{LegendChanged}]
   */
  void removeLegendChangedCallback (PoXtLegendEditorCB * func, void * userData);

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
   * Sets editing filters defining which legend attributes will be displayed in the 
   * editor. (By default inclusionMask = ALL_LEGEND_MASK and 
   * exclusionMask = NO_LEGEND_MASK).
   */
  void setLegendFilter (unsigned long inclusionMask,
                        unsigned long exclusionMask);

  /**
   * Gets editing filters defining which legend attributes will be displayed in the 
   * editor.
   */
  void getLegendFilter (unsigned long & inclusionMask,
                        unsigned long & exclusionMask) const;

  virtual void show ();
  virtual void hide ();
  

  /*----------------------------------------------------------------------------*/


 PoINTERNAL protected:

  PoXtLegendEditor (SoWidget Parent = NULL,
                    const char * name = NULL,
                    SbBool buildInsideParent = TRUE);

  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setFilter();

  virtual ~PoXtLegendEditor ();
  
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  void updateXtElements ();

  virtual void copyLegendFields(PoLegend * dest, PoLegend * source);
  virtual void updateLegendFromXtElements ();
  
  virtual int getMenuItems();

  // Attribute
  PoLegend * _legend;
  PoLegend * _attachedLegend;
  PoXtDialog * _dialog;
  SoNodeSensor * _sensor;

  Presentation    _presentation;

  menuColumn * _menu;
  int          _menuItems;
  SoCallbackList * _callbackList;

 private:
  UpdateFrequency _frequency;
  int _classMenusNb;
  unsigned long   _incLegendMask;
  unsigned long   _excLegendMask;

  SbBool _isLegendSet;

  void activate ();
  void deactivate ();


  // Callbacks for PoXtDialog
  static void acceptCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
  static void elementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
  static void visibilityChangeCB (void *, SbBool visible);
  static void sensorCB (void *, SoSensor *);
};


#endif // _POXTLEGENDEDITOR_H_

