/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMLINE_
#define  _PO_STREAMLINE_

#include <MeshViz/3Ddata/PoBaseStreamLine.h>

/**
 * @DTEXT  Representation of streamlines on a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    This class builds a line for each streamline starting from
 *    PoBaseStreamLine::startPoints.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamLine {
 *    @TABLE_FILE_FORMAT
 *       @TR lineWidth @TD 2.0
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
 * @CATALOG_PARTS_INCLUDE postreamline.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamLine : public PoBaseStreamLine {
  
  SO_KIT_HEADER(PoStreamLine) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamLine) ;
  

 public:

  /**
   * Constructor.
   */
  PoStreamLine();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /* Fields */

  /**
   * Convenience field to set the width line attribute of each streamline drawn.
   * 2.0 by default.
   */
  SoSFFloat lineWidth;
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoStreamLine() ;  
  // Destructor

  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  PiStreamPath *m_streamPath;
  int          m_allocStreamPath;

 private:
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMLINE_ */


