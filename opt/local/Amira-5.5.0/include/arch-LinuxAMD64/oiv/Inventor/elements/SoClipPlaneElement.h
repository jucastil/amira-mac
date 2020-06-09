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


#ifndef  _SO_CLIP_PLANE_ELEMENT
#define  _SO_CLIP_PLANE_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

/**
*   Stores the current set of clipping planes, specified
*   as SbPlanes.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current set of clipping planes, specified
*   as SbPlanes.
* 
*   When a plane is added, this element gets the current model matrix
*   from the state and stores it in the instance. This allows the
*   get() method to return the clip plane in object space (the plane
*   as originally defined) or world space (after being transformed by
*   the model matrix).
* 
*   @SEE_ALSO
*   SoClipPlane, SoOrthoSlice
*/

SoEXTENDER_Documented class INVENTOR_API SoClipPlaneElement : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(SoClipPlaneElement);

 public:
    /**
    *  Adds a clip plane to the current set in the state.
    */
    static void         add(SoState *state, SoNode *node,
                          const SbPlane &plane);

    /**
    *  Overrides push() method to copy values from next instance in the stack.
    */
    virtual void        push(SoState *state);

    /**
    *  Overrides pop() method to free up planes that were added.
    */
    virtual void        pop(SoState *state, const SoElement *prevTopElement);

    /**
    *  Returns the top (current) instance of the element in the state.
    */
    static const SoClipPlaneElement * getInstance(SoState *state);

    /**
    *  Returns the number of planes in an instance.
    */
    int                 getNum() const;

    /**
    *  Returns the indexed plane an element as an SbPlane. The plane
    *  can be returned in object or world space.
    */
    const SbPlane &     get(int index, SbBool inWorldSpace = TRUE) const;

    /**
    *  Prints element (for debugging).
    */
    virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoClipPlaneElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbPList             planes;         // List of plane structures
  int                 startIndex;     // Index of 1st plane created
  // in this instance

  // Adds the clipping plane to an instance. Takes the new plane and
  // the current model matrix
  virtual void        addToElt(const SbPlane &plane,
                               const SbMatrix &modelMatrix);

  virtual ~SoClipPlaneElement();
};

#endif /* _SO_CLIP_PLANE_ELEMENT */
