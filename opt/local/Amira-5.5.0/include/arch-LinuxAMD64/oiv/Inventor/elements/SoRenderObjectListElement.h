/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : SoRenderObjectListElement.cxx
 *   Classes     : SoRenderObjectListElement
 *   Author(s)   : Jerome Hummel
 *   Date        : 4-18-2002
 *==============================================================================
 *
 * Description : Element that stores a renderObjectList for the render
 * list nodes to communicate between each other.
 *
 *============================================================================*/

#ifndef  _SO_RENDER_OBJECT_LIST_ELEMENT_
#define  _SO_RENDER_OBJECT_LIST_ELEMENT_

#include <Inventor/SbBasic.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/elements/SoReplacedElement.h>

class SoRenderObjectList;

/**
*  @VSGEXT Stores the recent render object list.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the most recent render object list (computed by the render list).
*
*   @SEE_ALSO
*   SoOctreeOrdering
*/

SoEXTENDER_Documented class INVENTOR_API SoRenderObjectListElement : public SoReplacedElement
{
  SO_ELEMENT_HEADER(SoRenderObjectListElement);

 public:
  /**
  *  Sets cache in element accessed from state.
  */
  static void set(SoState *state, SoNode *node, SoRenderObjectList *);
  /**
  *  Sets transparent list in state.
  */
  static void setTransparentList(SoState *state, SoNode *node, SoRenderObjectList *);

  /**
  *  Gets list of render objects from state.
  */
  static SoRenderObjectList *getRenderObjectList(SoState *, SoNode *);
  /**
  *  Gets list of transparent objects from state.
  */
  static SoRenderObjectList *getTransparentObjectList(SoState *, SoNode *);

  virtual void push(SoState *);

 SoINTERNAL public:
  // Initializes the SoRenderObjectListElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

  // Returns the top (current) instance of the element in the state
  static const SoRenderObjectListElement *getInstance(SoState *state)
    { return getConstElement<SoRenderObjectListElement>(state); }

 protected:
  virtual ~SoRenderObjectListElement();

 private:
  // Stores pointer to cache
  SoRenderObjectList *renderObjectList;
  SoRenderObjectList *transparentObjectList;
};


#endif /* _SO_RENDER_OBJECT_LIST_ELEMENT_ */
