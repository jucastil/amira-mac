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


#ifndef _SO_LINE_DETAIL_
#define _SO_LINE_DETAIL_

#include <Inventor/details/SoPointDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLineDetail
//
//  Detail information about vertex-based shapes made of line
//  segments. It adds indices of various items that vary among lines,
//  segments, and vertices.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of line segments.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a line segment in a
 *   vertex-based shape made of line segments. The information includes the points at
 *   the ends of the segment, and the index of the segment within the shape.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoLineDetail : public SoDetail {

  SO_DETAIL_HEADER(SoLineDetail);

 public:
  /**
   * Constructor.
   */
  SoLineDetail();
  /**
   * Destructor.
   */
  virtual ~SoLineDetail();

  /**
   * Returns information about the first of two points forming the end vertices of the
   * line segment, represented as an SoPointDetail.
   */
  const SoPointDetail *       getPoint0() const       { return &point[0]; }
  /**
   * Returns information about the second of two points forming the end vertices of the
   * line segment, represented as an SoPointDetail.
   */
  const SoPointDetail *       getPoint1() const       { return &point[1]; }

  /**
   * Returns the index of the line the segment is part of within a shape, such as the
   * third line within an SoLineSet.
   */
  int32_t                     getLineIndex() const    { return lineIndex; }

  /**
   * Returns the index of the part containing the line segment within the shape.
   * Usually, the part index is the same as the line segment index, such as the fifth
   * segment overall within an SoLineSet.
   */
  int32_t                     getPartIndex() const    { return partIndex; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail *          copy() const;

 SoEXTENDER public:
  // Copies a point detail from the given detail
  void                        setPoint0(const SoPointDetail *pd);
  void                        setPoint1(const SoPointDetail *pd);

  // Sets the line index and part index
  void                        setLineIndex(int32_t i) { lineIndex = i; }
  void                        setPartIndex(int32_t i) { partIndex = i; }

#if !defined(IV_STRICT) && !defined(__NUTC__)
  void    setLineIndex(long i)                                // System long
    { setLineIndex ((int32_t) i); }
  void    setPartIndex(long i)                                // System long
    { setPartIndex ((int32_t) i); }
#endif

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  SoPointDetail               point[2];
  int32_t                     lineIndex, partIndex;

};

#endif /* _SO_LINE_DETAIL_ */

