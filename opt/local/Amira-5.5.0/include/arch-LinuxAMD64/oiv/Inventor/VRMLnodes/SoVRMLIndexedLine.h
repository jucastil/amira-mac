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


#ifndef  _SO_VRMLINDEXED_LINE_
#define  _SO_VRMLINDEXED_LINE_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/VRMLnodes/SoVRMLVertexLine.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIndexedLine
//
//  Abstract indexed shape node class. All nodes derived from this
//  (such as SoVRMLIndexedFaceSet and SoVRMLIndexedLineSet) are shapes
//  that are constructed from vertices defined by indexing into the
//  current coordinates. The coordinate indices are stored in the
//  coordIndex field, which is used by all subclasses.
//
//  One rule is used: all coordinate indices less than 0 may be used
//  for special purposes, such as to denote the end of a face or
//  polyline. This means that all indices < 0 can be ignored safely
//  when looking at vertices.
//
//  Depending on the current material, normal, and texture coordinate
//  binding values, materials, normals, and texture coordinates may be
//  accessed in order or may be indexed using the colorIndex,
//  normalIndex, and textureCoordIndex fields.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for the SoVRMLIndexedLineSet node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node is an abstract base class for the SoVRMLIndexedLineSet node.
 *
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived 
 *   class for the format and default values.
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord
 *       @TR   SoMFInt32  @TD   set_colorIndex
 *       @TR   SoMFInt32  @TD   set_coordIndex
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLIndexedLine : public SoVRMLVertexLine {

  SO_NODE_ABSTRACT_HEADER(SoVRMLIndexedLine);

 public:
  /**
   * Indices of the coordinates that the indexed line set uses as its vertices. The
   * coordinates connect to form the lines.
   * 
   */
  SoMFInt32           coordIndex;
  /**
   * The indices of the colors to use for the lines or vertices depending on the
   * value of the @B colorPerVertex @b field. If NULL, the colors are applied to
   * each line of the SoVRMLIndexedLineSet in order.
   * 
   */
  SoMFInt32           colorIndex;

 SoEXTENDER public:
  // This handles bounding box computation for all shapes derived
  // from this class. It sets the bounding box to contain all
  // vertices of the shape, assuming that the shape uses the
  // coordinates indexed by all non-negative values in the
  // coordIndex field. It also sets the center to the average of the
  // vertices' coordinates.
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Constructor - makes this abstract
  SoVRMLIndexedLine();

  // Returns TRUE if texture coordinates should be indexed
  //static SbBool     areTexCoordsIndexed(SoAction *action);

  // Starting at a given index in the coordIndex array, figure out
  // how many vertices there are before either the end of the array
  // or the next 'border' index
  int getNumVerts(int startCoord);

  // Setup for fast rendering.  This should be called by subclasses,
  // which can then use the textureI/colorI/normalI arrays (which
  // will either point to one of the coordIndex arrays, or to a
  // consective array of integers.  This must be called AFTER the
  // vpCache has been filled in.
  void                setupIndices(int numFaces);

  // These must not be called unless setupIndices has been called first:
  //const int32_t *   getNormalIndices()
  //{ return (normalI ? normalI : consecutiveIndices); }
  const int32_t *     getColorIndices()
    { return (colorI ? colorI : consecutiveIndices); }
  //const int32_t *   getTexCoordIndices()
  //{ return (texCoordI ? texCoordI : consecutiveIndices); }

  // Returns the SoNormalBindingElement normalBinding enum based on
  // the normal field and normalPerVertex field.

  // Keep indices up to date if things change
  virtual void        notify(SoNotList *list);

  virtual ~SoVRMLIndexedLine();

 private:
  // Internal routines used to allocate sequential indices so the
  // same rendering loops can be used for indexed or non-indexed
  // cases:
  void        allocateSequential(int howMany);
  int32_t*    allocateSequentialWithHoles();

  // These are filled in by the setupIndices routine:
  //const int32_t     *texCoordI;
  const int32_t       *colorI;
  //const int32_t     *normalI;
  static int32_t      *consecutiveIndices;
  static int  numConsecutiveIndicesAllocated;

  unsigned char materialBinding;
  //unsigned char normalBinding;
  //unsigned char texCoordBinding;
};

#endif /* _SO_VRMLINDEXED_LINE_ */

