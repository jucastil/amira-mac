/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ON_OFF_
#define  _SO_ON_OFF_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
 * Engine that functions as an on/off switch.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine has three triggers as input and two Boolean values as output. The
 *   #isOn output is a switch that can be turned #on or #off by
 *   triggering the corresponding input. You can toggle the value by triggering the
 *   #toggle input. By default #isOn is FALSE. The #isOff output
 *   value is the inverse of #isOn
 * 
 * @FILE_FORMAT_DEFAULT
 *    OnOff {
 *    @TABLE_FILE_FORMAT
 *       @TR on       @TD 
 *       @TR off      @TD 
 *       @TR toggle   @TD 
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoOnOff : public SoEngine {

  SO_ENGINE_HEADER(SoOnOff);
    
 public:

  /**
   * Turn the isOn switch on. 
   */
  SoSFTrigger on;
  /**
   * Turn the isOn switch off. 
   */
  SoSFTrigger off;
  /**
   * Toggle the switch value. 
   */
  SoSFTrigger toggle;
    
  /**
   * ( SoSFBool )  Switch value.
   */
  SoEngineOutput isOn;
  /**
   * ( SoSFBool )  The inverse of isOn.
   */
  SoEngineOutput isOff;
    
  /**
   * Constructor.
   */
  SoOnOff();
    
 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:
  virtual void        inputChanged(SoField *whichInput);

  // Destructor
  ~SoOnOff();
 private:


  // Evaluation method
  virtual void evaluate();

  SbBool      state;
};

#endif  /* _SO_ON_OFF_ */

