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


#ifndef  _SO_SF_TRIGGER_
#define  _SO_SF_TRIGGER_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFTrigger subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field used to trigger engines or connection networks.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This class can be used to start or to synchronize a network of field
 *   connections. It is the "null" field - a field with no values. It is typically
 *   used as the "start button" for engines that change over time.
 *   
 *   Triggers can be connected from any other type of field, and will notify any
 *   engines or nodes they are part of (or any other triggers they are connected to)
 *   whenever the value of the field is set (even if it is set to its current value)
 *   or the field is touch()'ed.
 *   
 *   Since they have no value, SoSFTriggers are not written to file. A node or engine
 *   containing an SoSFTrigger field will write only the field's name.
 * 
 * @SEE_ALSO
 *    SoSFBool,
 *    SoMFBool
 * 
 * 
 */ 

class INVENTOR_API SoSFTrigger : public SoSField {

  // Use standard field stuff
  SO_SFIELD_REQUIRED_HEADER(SoSFTrigger);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFTrigger);

 public:
  /**
   * Starts the notification process; this is equivalent to calling touch().
   */
  void                setValue()              { touch(); }

  /**
   * Forces any connected engines or fields to evaluate themselves.
   */
  void                getValue() const        { }

  // Start notification.
  virtual void        touch();

  /**
   * All trigger fields are equal. This method always returns TRUE.
   */
  int                 operator ==(const SoSFTrigger &t) const;
  /**
   * All trigger fields are equal. This method always returns FALSE.
   */
  int                 operator !=(const SoSFTrigger &t) const;

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

  // Notification can flow through a trigger, but can't start at a
  // trigger.  The only way to start notification at a trigger is to
  // call touch().
  virtual void        startNotify();

  // Override notify to always evaluate (after passing on
  // notification) to clear upstream dirty bits
  virtual void        notify(SoNotList *list);

 private:
  // Reading and writing. These are no-ops.
  virtual SbBool      readValue(SoInput *in);
  virtual void        writeValue(SoOutput *out) const;

};

#endif /* _SO_SF_TRIGGER_ */

