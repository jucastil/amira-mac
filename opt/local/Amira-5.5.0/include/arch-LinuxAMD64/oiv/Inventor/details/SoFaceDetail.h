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
** Modified by : Martial Bonaventure (Nov 2010)
**=======================================================================*/


#ifndef _SO_FACE_DETAIL_
#define _SO_FACE_DETAIL_

#include <Inventor/details/SoPointDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFaceDetail
//
//  Detail information about vertex-based shapes made of faces. It
//  adds indices of various items that vary among faces and vertices.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of faces.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a face in a vertex-based
 *   shape made of faces. The information includes the number of points in the face,
 *   the points forming the vertices of the face, and the index of the face within
 *   the shape.
 *   
 *   Note that when an SoFaceDetail is returned from picking (in an SoPickedPoint), it
 *   will contain details for all points defining the face that was intersected.
 *   However, when an SoFaceDetail is created for a triangle produced during
 *   primitive generation (in an SoPrimitiveVertex), it will contain details for only
 *   the three vertices of the triangle.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoFaceDetail : public SoDetail {

  SO_DETAIL_HEADER(SoFaceDetail);

 public:
  /**
   * Constructor.
   */
  SoFaceDetail();
  /**
   * Destructor.
   */
  virtual ~SoFaceDetail();

  /**
   * Returns the number of points in the face.
   */
  int32_t                     getNumPoints() const    { return numPoints; }

  /**
   * Returns information about the point forming the i'th vertex of the face,
   * represented as an SoPointDetail.
   */
  const SoPointDetail *       getPoint(int i) const   { return &point[i]; }

  /**
   * Returns the index of the face within the shape.
   */
  int32_t                     getFaceIndex() const    { return faceIndex; }

  /**
   * Returns the index of the part containing the face within the shape.
   */
  int32_t                     getPartIndex() const    { return partIndex; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail *          copy() const;

 SoEXTENDER public:
  // Sets the number of points in the face and allocates room for the points
  void                        setNumPoints(int32_t num);

  // Copies a point detail from the given detail
  void                        setPoint(int32_t index, const SoPointDetail *pd);

  // Sets the face index and part index
  void                        setFaceIndex(int32_t i) { faceIndex = i; }
  void                        setPartIndex(int32_t i) { partIndex = i; }

  // Return a pointer to the point details.
  SoPointDetail *             getPoints()             { return &point[0]; }

#if !defined(IV_STRICT) && !defined(__NUTC__)
  void    setNumPoints(long num)                              // System long
    { setNumPoints ((int32_t) num); }
  void    setPoint(long index, const SoPointDetail *pd)       // System long
    { setPoint ((int32_t) index, pd); }
  void    setFaceIndex(long i)                                // System long
    { setFaceIndex ((int32_t) i); }
  void    setPartIndex(long i)                                // System long
    { setPartIndex ((int32_t) i); }
#endif

 SoINTERNAL public:
  SoFaceDetail(const SoFaceDetail& faceDetail);
  SoFaceDetail& operator=(const SoFaceDetail& faceDetail);

  static void                 initClass();
  static void                 exitClass();

 private:
  SoPointDetail               *point;
  int32_t                     numPoints;
  int32_t                     faceIndex, partIndex;

};

#endif /* _SO_FACE_DETAIL_ */

