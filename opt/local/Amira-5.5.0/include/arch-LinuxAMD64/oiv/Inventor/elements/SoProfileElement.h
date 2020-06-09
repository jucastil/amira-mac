/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_PROFILE_ELEMENT
#define  _SO_PROFILE_ELEMENT

#include <Inventor/SoLists.h>
#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

class SoProfile;

/**
*   Stores 2D profiles for NURBS and 3D text.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores 2D profiles for NURBS and 3D text.
* 
*   @SEE_ALSO
*   SoProfile
*/

SoEXTENDER_Documented class INVENTOR_API SoProfileElement : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(SoProfileElement);

 public:

   /** Profile */
  enum Profile {
    /** Start first */
    START_FIRST,
    /** Start new */
    START_NEW,
    /** Add to current */
    ADD_TO_CURRENT
  };

  /**
  *  Add to the current profile list.
  */
  static void         add(SoState *state, SoProfile *profile);

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void        push(SoState *state);

  /**
  *  Returns the current list of profile nodes from the state.
  */
  static const SoNodeList &   get(SoState *state);

  /**
  *  Prints element (for debugging).
  */
   virtual void        print(FILE *fp) const;

 SoINTERNAL public:

  // Initializes the SoCoordinateElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element.
  virtual void        init(SoState *state);

 protected:
  // list of profile nodes
  SoNodeList          profiles;

  virtual ~SoProfileElement();
};

#endif /* _SO_PROFILE_ELEMENT */
