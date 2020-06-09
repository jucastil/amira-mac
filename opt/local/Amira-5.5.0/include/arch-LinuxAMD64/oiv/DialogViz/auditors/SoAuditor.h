/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_AUDITOR_
#define  _SO_AUDITOR_

#include <Inventor/SoTypedObject.h>
#include <DialogViz/auditors/SoSubAuditor.h>

/**
 * @VSGEXT Base class for all auditors.
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   SoAuditor is the base class for auditors in the DialogViz auditor model. An auditor
 *   typically represents a user action, such as a mouse button being pressed or a
 *   keyboard key being released.
 *   
 * @SEE_ALSO
 *   SoDialogAuditor,
 *   SoDialogCheckBoxAuditor,
 *   SoDialogComboBoxAuditor,
 *   SoDialogEditTextAuditor,
 *   SoDialogIntegerSliderAuditor,
 *   SoDialogPushButtonAuditor,
 *   SoDialogRadioButtonsAuditor,
 *   SoDialogRealSliderAuditor,
 *   SoMenuCheckBoxAuditor,
 *   SoMenuFileSelectionAuditor,
 *   SoMenuPushButtonAuditor,
 *   SoMenuRadioButtonsAuditor
 *
 * 
 */ 

class DIALOGVIZ_API SoAuditor: public SoTypedObject {
 public:
  
  /**
   * Returns the type id for this event instance.
   */
  virtual SoType      getTypeId() const;
    
  /**
   * Returns the type id for the SoEvent class.
   */
  static SoType       getClassTypeId();
    
 SoINTERNAL public:
  // Initializes base event class
  static void         initClass();
  static void         exitClass();

  // Initialize ALL Inventor auditor classes
  static void         initClasses();
  static void         exitClasses();
    
 protected:
  /**
   * Constructor.
   */
  SoAuditor();
  /**
   * Destructor.
   */
  virtual ~SoAuditor();

 private:
  static SoType       classTypeId; // base typeId for all auditors
};


#endif /* _SO_AUDITOR_ */

