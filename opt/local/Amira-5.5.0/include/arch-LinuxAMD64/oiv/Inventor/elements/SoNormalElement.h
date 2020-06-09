/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NORMAL_ELEMENT
#define  _SO_NORMAL_ELEMENT



#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/errors/SoDebugError.h>

/**
*   Allows read-only access to the top element in the state.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This class allows read-only access to the top element in the state
*   to make accessing several values in it more efficient. Individual
*   values must be accessed through this instance.
*
*   @SEE_ALSO
*   SoNormal, SoVertexProperty, SoVRMLNormal
*/

SoEXTENDER_Documented class INVENTOR_API SoNormalElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoNormalElement);

 public:
  /**
   * Sets the current normals.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(normals != NULL? normals->Length: 0)},ARRAY]
   */
  static void         set(SoState *state, SoNode *node,
                          int32_t numNormals, const SbVec3f *normals);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoNormalElement * getInstance(SoState *state)
    {return getConstElement<SoNormalElement>(state);}

  /**
  *  Returns the number of normal vectors in an instance.
  */
  int32_t             getNum() const          { return numNormals; }

  /**
  *  Returns the indexed normal from an element.
  */
  const SbVec3f &     get(int index) const
    {
#if defined(_DEBUG)
      if (index < 0 || index >= numNormals)
        SoDebugError::post("SoNormalElement::get",
                           "Index (%d) is out of range 0 - %d",
                           index, numNormals - 1);
#endif
      return normals[index];
    }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoNormalElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  int32_t             numNormals;
  const SbVec3f       *normals;

  virtual ~SoNormalElement();

 private:
  // This stores a pointer to the default normal so that we can set
  // "normals" to point to it if no other normal has been set.
  static SbVec3f      *defaultNormal;
};

#endif /* _SO_NORMAL_ELEMENT */
