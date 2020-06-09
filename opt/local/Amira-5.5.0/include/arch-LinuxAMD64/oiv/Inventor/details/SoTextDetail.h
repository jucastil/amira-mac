/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thaddeus Beier (MMM yyyy)
** Modified by : Dave Immel (MMM yyyy)
** Modified by : Howard Look (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_TEXT_DETAIL_
#define _SO_TEXT_DETAIL_

#include <Inventor/SbBox.h>
#include <Inventor/details/SoSubDetail.h>
#include <Inventor/nodes/SoText3.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextDetail
//
//  Detail about a shape representing text.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about a text node.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a point on a text shape (SoText2 or
 *   SoText3). It contains the part of the text, string, and character that were hit
 *   or generated.
 * 
 * @SEE_ALSO
 *    SoText2,
 *    SoText3,
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex
 * 
 * 
 */ 

class INVENTOR_API SoTextDetail : public SoDetail {

  SO_DETAIL_HEADER(SoTextDetail);

 public:
  /**
   * Constructor.
   */
  SoTextDetail();
  /**
   * Destructor.
   */
  virtual ~SoTextDetail();

  /**
   * Returns the index of the relevant string within a multiple-value @B string @b
   * field of a text node.
   */
  int32_t             getStringIndex() const          { return stringIndex; }

  /**
   * Returns the index of the relevant character within the string. For example, if
   * the character of detail was the "u" within "Splurmph", the character index would
   * be 3.
   */
  int32_t             getCharacterIndex() const       { return charIndex; }

  /**
   * For SoText3, this returns which part was picked or generated.
   */
  SoText3::Part       getPart() const         { return part; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail *  copy() const;

 SoEXTENDER public:
  // For Text3, this sets which part is picked:
  void                setPart(SoText3::Part p)        { part = p; }

  // These set the string and character indices:
  void                setStringIndex(int32_t i)               { stringIndex = i; }
  void                setCharacterIndex(int32_t i)    { charIndex = i; }

#if !defined(IV_STRICT) && !defined(__NUTC__)
  void    setStringIndex(long i)                              // System long
    { setStringIndex((int32_t) i); }
  void    setCharacterIndex(long i)                           // System long
    { setCharacterIndex((int32_t) i); }
#endif

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 private:
  int32_t             stringIndex, charIndex;
  SoText3::Part       part;

};

#endif /* _SO_TEXT_DETAIL_ */

