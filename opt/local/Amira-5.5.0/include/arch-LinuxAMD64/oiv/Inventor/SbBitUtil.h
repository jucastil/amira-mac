/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_BIT_UTIL_H_
#define _SB_BIT_UTIL_H_

#include <Inventor/SbBasic.h>

#ifndef HIDDEN_FROM_DOC

/**
 * @VSGEXT Class for manipulating bit masks.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   Provides simple mask and bit field manipulation functions.
 *
 *   Bit 0 is the low order or "right-most" bit of the mask.
 *
 * [OIV-WRAPPER-NO-WRAP]
 */

class SbBitUtil
{
SoINTERNAL public:
  /**
   * Returns the number of bits set to 1 in a mask.
   */
  static int getNumBits(const unsigned long Mask);

  /**
   * Returns the position of the bit set to 1 in a mask.
   * Expects a single bit to be set.  If more than one
   * bit is set returns index of highest bit set to 1.
   */
  static int getOffsetBit(const unsigned long Mask);

  /**
   * Returns a mask with the bit at position bitOffset set to 1.
   */
  static unsigned long buildMask(const int bitOffset);

  /**
   * Returns the position of the highest bit set to 1 in a mask.
   */
  static int getHeavierBit(const unsigned long Mask);

};

inline int
SbBitUtil::getNumBits(const unsigned long Mask)
{
  int numBits = 0;
  for (unsigned long i = Mask; i != 0; numBits += (i & 1), i >>= 1) ;

  return numBits;
}

inline int
SbBitUtil::getOffsetBit(const unsigned long Mask)
{
  int indice;
  unsigned long mask = Mask;
  for (indice = -1; mask; indice++, mask >>=1) ;

  return indice;
}

inline unsigned long
SbBitUtil::buildMask(const int bitOffset)
{
  return (1 << bitOffset);
}

inline int
SbBitUtil::getHeavierBit (const unsigned long Mask)
{
  unsigned long heavier = ((unsigned long)1) << ((sizeof(unsigned long) * 8) - 1);
  int i;
  for (i = (sizeof(unsigned long) * 8) - 1;
       (heavier) && !(heavier & Mask); heavier >>= 1, i--) ;

  return i;
}

#endif // HIDDEN_FROM_DOC

#endif //_SB_BIT_UTIL_H_
