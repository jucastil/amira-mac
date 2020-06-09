/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMSURFACE_
#define  _PO_STREAMSURFACE_

#include <MeshViz/3Ddata/PoBaseStreamLine.h>
#include <Inventor/fields/SoMFVec3f.h>

/**
 * @DTEXT  Representation of a surface connecting several streamlines.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to build surfaces which represent stream-surfaces. It connects several 
 *    streamlines to build a stream-surface. The source of each stream-surface is 
 *    a rake for which the middle point is defined by startPoints. numLinesPerRake
 *    streamlines start from each segment. 
 * 
 *    Each surface is made up of numLinesPerRake * N points, where N is the 
 *    smallest point number of all the numLinesPerRake streamline.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamSurface {
 *    @TABLE_FILE_FORMAT
 *       @TR rakeOrientation @TD SbVec3f(1,0,0)
 *       @TR numLinesPerRake @TD 3
 *       @TR rakeLength @TD 1
 *       @TR startPoints @TD SbVec3f(0,0,0)
 *       @TR maxLifetime @TD 0 (i.e. infinite)
 *       @TR maxLength @TD 0 (i.e. infinite)
 *       @TR minSpeed @TD 0 (i.e. infinite)
 *       @TR integrationStepLengthFactor @TD 0.3
 *       @TR integrationMaxStepNumber @TD 0 (i.e. infinite)
 *       @TR integrationDirection @TD FORWARD 
 *       @TR colors @TD (SbColor(1,0,0)
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR valuesIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE postreamsurface.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamSurface : public PoBaseStreamLine {
  
  SO_KIT_HEADER(PoStreamSurface) ;
  
  // Define fields for new parts
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamSurface) ;
  

 public:

  /**
   * Constructor.
   */
  PoStreamSurface();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /* Fields */

  /**
   * Orientation of the rake-sources. SbVec3f(1,0,0) by default.
   */
  SoMFVec3f rakeOrientation;

  /**
   * Number of point sources per rake. For each rake-sources, numLinesPerRake 
   * streamlines are calculated and are connected by a quad mesh to form a stream-
   * surface. 3 by default.
   */
  SoSFInt32 numLinesPerRake;

  /**
   * Length of each rake-source. 1 by default.
   */
  SoSFFloat rakeLength;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoStreamSurface() ;  

  // Methods
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  PiStreamPath *m_streamPath;
  int          m_allocStreamPath;

 private:
  // Sensors
  FieldSensorList m_fieldSensorList ;

  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMSURFACE_ */


