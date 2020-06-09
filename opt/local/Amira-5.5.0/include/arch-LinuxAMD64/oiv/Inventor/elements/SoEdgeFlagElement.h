/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_EDGE_FLAG_ELEMENT
#define  _SO_EDGE_FLAG_ELEMENT

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
* @VSGEXT Stores the edge flag values.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the edge flag values.
*   @SEE_ALSO
*   SoEdgeFlag
*/

SoEXTENDER_Documented class INVENTOR_API SoEdgeFlagElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoEdgeFlagElement);

 public:
/**
*  Sets the current flags in the state as marked.
*/
  static void           setMarked(SoState *state, SoNode *node,
                                  int32_t numFlags, const int32_t *flags);

  /**
  *  Sets the current flags in the state as unmarked.
  */
  static void           setUnmarked(SoState *state, SoNode *node,
                                    int32_t numFlags, const int32_t *flags);

  /**
  *  Returns the default values.
  */
  static int            getDefault()    {return -1;}

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoEdgeFlagElement * getInstance(SoState *state)
    {return getConstElement<SoEdgeFlagElement>(state);}

  /**
  *  Returns the number of marked flags in an instance.
  */
  int32_t               getNumMarked() const            { return numMarked; }
  /**
  *  Returns the number of unmarked flags in an instance.
  */
  int32_t               getNumUnmarked() const          { return numUnmarked; }

  /**
   * Returns the marked flags.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumMarked()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumMarked()}]
   */
  const int32_t *       getMarked() const               { return marked; }
  /**
   * Returns the unmarked flags.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumUnmarked()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumUnmarked()}]
   */
  const int32_t *       getUnmarked() const             { return unmarked; }

  /**
  *  Prints element (for debugging).
  */
  virtual void  print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoEdgeFlagElement class
  static void           initClass();
  static void           exitClass();

  // Initializes element
  virtual void  init(SoState *state);
  static void           reInit(SoState *, SoNode *);

 protected:
  int32_t               numMarked, numUnmarked;
  const int32_t *       marked;
  const int32_t *       unmarked;

  static int32_t markedDefault[1] ;
  static int32_t unmarkedDefault[1] ;

  virtual ~SoEdgeFlagElement();

 private:
  void _init();
};

#endif /* _SO_EDGE_FLAG_ELEMENT */
