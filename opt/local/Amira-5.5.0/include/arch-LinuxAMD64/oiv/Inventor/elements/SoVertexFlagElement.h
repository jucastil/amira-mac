/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_VERTEX_FLAG_ELEMENT
#define  _SO_VERTEX_FLAG_ELEMENT

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
*   @VSGEXT Stores the current vertex flag.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current vertex flag.
*
*   @SEE_ALSO
*   SoVertexFlag
*/
SoEXTENDER_Documented class INVENTOR_API SoVertexFlagElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoVertexFlagElement);

 public:
  /**
  *
  */
  static void           reInit(SoState *, SoNode *);
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
  *
  */
  static int            getDefault()    {return -1;}

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoVertexFlagElement * getInstance(SoState *state)
    {return getConstElement<SoVertexFlagElement>(state);}

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
  // Initializes the SoVertexFlagElement class
  static void           initClass();
  static void           exitClass();

  // Initializes element
  virtual void  init(SoState *state);

 protected:
  int32_t               numMarked, numUnmarked;
  const int32_t *       marked;
  const int32_t *       unmarked;

  static int32_t markedDefault[1] ;
  static int32_t unmarkedDefault[1] ;

  virtual ~SoVertexFlagElement();

 private:
  void _init();
};

#endif /* _SO_VERTEX_FLAG_ELEMENT */
