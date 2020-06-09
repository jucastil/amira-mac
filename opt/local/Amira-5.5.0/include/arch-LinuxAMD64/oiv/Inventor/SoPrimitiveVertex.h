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


#ifndef _SO_PRIMITIVE_VERTEX_
#define _SO_PRIMITIVE_VERTEX_

#include <Inventor/SbLinear.h>

class SoDetail;
class SoPointDetail;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPrimitiveVertex
//
//  An SoPrimitiveVertex represents a vertex of a primitive (triangle,
//  line segment, point) that is being generated via the
//  SoCallbackAction.
//
//  An SoPrimitiveVertex contains an object-space point, normal,
//  texture coordinates, material index, and a pointer to an instance
//  of some SoDetail subclass. This detail may contain more
//  information about the vertex, or may be a NULL pointer if there is
//  no such info.
//
//  Instances of SoPrimitiveVertex are typically created on the stack
//  by shape classes while they are generating primitives. Anyone who
//  wants to save them as return values from SoCallbackAction should
//  probably make copies of them.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Represents a vertex of a generated primitive.
* 
* @ingroup General
* 
* @DESCRIPTION
*   An SoPrimitiveVertex represents a vertex of a primitive (triangle, line segment,
*   or point) that is being generated by an SoCallbackAction. It contains an
*   object-space point, normal, texture coordinates, material index, and a reference
*   to an instance of an SoDetail subclass. This detail may contain more information
*   about the vertex, or may be a NULL reference if there is no such info.
*   
*   Instances of SoPrimitiveVertex are typically created on the stack by shape
*   classes while they are generating primitives. Anyone who wants to save them as
*   return values from SoCallbackAction should probably make copies of them.
* 
* 
*/ 
#else
/**
* Represents a vertex of a generated primitive.
* 
* @ingroup General
* 
* @DESCRIPTION
*   An SoPrimitiveVertex represents a vertex of a primitive (triangle, line segment,
*   or point) that is being generated by an SoCallbackAction. It contains an
*   object-space point, normal, texture coordinates, material index, and a pointer
*   to an instance of an SoDetail subclass. This detail may contain more information
*   about the vertex, or may be a NULL pointer if there is no such info.
*   
*   Instances of SoPrimitiveVertex are typically created on the stack by shape
*   classes while they are generating primitives. Anyone who wants to save them as
*   return values from SoCallbackAction should probably make copies of them.
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoPrimitiveVertex {

 public:
  /**
   * Default constructor.
   */
  SoPrimitiveVertex();
#ifdef OIV_NET_DOC
  /**
  * Constructor. Note that copying a primitive vertex copies the
  * detail reference, and not the detail itself.
  */

#else
  /**
  * Constructor. Note that copying a primitive vertex copies the
  * detail pointer, and not the detail itself.
  */

#endif //OIV_NET_DOC
  SoPrimitiveVertex(const SoPrimitiveVertex &pv);

  /**
   * Destructor.
   */
  ~SoPrimitiveVertex();

  /**
   * Returns the surface point in object space.
   */
  const SbVec3f &     getPoint() const                { return point; }
  /**
   * Returns the normal in object space.
   */
  const SbVec3f &     getNormal() const               { return normal; }
  /**
   * Returns the texture coordinates in object space.
   */
  const SbVec4f &     getTextureCoords() const        { return texCoords; }

  /**
   * Returns the index into the current set of materials of the material active at
   * the vertex.
   */
  int                 getMaterialIndex() const    { return materialIndex; }

  /**
  * Returns the point detail giving more information about the vertex. Note that
  * the return value is NULL if there is no more info.
  */
  const SoPointDetail *    getPointDetail() const               { return m_pointDetail; }

  /**
  * Returns the detail giving more information about the vertex. Note that the
  * return value is NULL if there is no more info.
  */
  const SoDetail *    getDetail() const               { return detail; }

#ifdef OIV_NET_DOC
  /**
  * Copies the given vertex. Note that just the reference to the detail is copied, and
  * not the detail itself.
  */
#else
  /**
  * Copies the given vertex. Note that just the pointer to the detail is copied, and
  * not the detail itself.
  */
#endif //OIV_NET_DOC
  SoPrimitiveVertex & operator =(const SoPrimitiveVertex &pv);

 SoEXTENDER public:

  // These methods are typically called by shape classes during
  // primtiive generation

  // These set the object space point, normal, and texture coordinates:
  void                setPoint(const SbVec3f &pt)       { point     = pt; }
  void                setNormal(const SbVec3f &norm)    { normal    = norm; }
  void                setTextureCoords(const SbVec4f &t){ texCoords = t; }

  // Sets the material index. The index is set to 0 during construction.
  void                setMaterialIndex(int index)  { materialIndex = index; }

  // Sets the detail corresponding to the vertex. The pointer may be
  // NULL, although it is set to NULL during construction.
  void                setDetail(SoDetail *d)            { detail = d; }

  // Sets the point detail corresponding to the vertex. The pointer may be NULL.
  void                setPointDetail(SoPointDetail *p)            { m_pointDetail= p; }

 private:
  SbVec3f             point;          // Object-space point
  SbVec3f             normal;         // Object-space normal
  SbVec4f             texCoords;      // Object-space texture coordinates
  int                 materialIndex;  // Material index
  SoDetail*           detail;        // Extra detail info
  SoPointDetail*      m_pointDetail;  //Point detail info       

};

#endif /* _SO_PRIMITIVE_VERTEX_ */

