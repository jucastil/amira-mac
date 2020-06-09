/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH1D_HINTS_
#define  _PO_MESH1D_HINTS_

#include <Inventor/fields/SoSFEnum.h>

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Node that provides hints about the mesh 1D.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This nodes defines the current hints for the current mesh 1D 
 *    (PoIrregularMesh1D or PoRegularMesh1D).
 *    All subsequent representations (heriting from PoChart) use these hints
 *    for their computation.
 *    The first hint supplied is geomInterpretation which defines how the 
 *    geometry of the current mesh 1D is interpreted. For instance choosing
 *    SMOOTH as interpretation, means that all subsequent representations will
 *    interpret the geometry of the current mesh 1D as smoothed (by a cubic spline)
 *    points (A cubic spline is computed from the current mesh 1D geometry passing all
 *    points, and this spline is used by the subsequent repres).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMesh1DHints {
 *    @TABLE_FILE_FORMAT
 *       @TR geomInterpretation @TD AS_IS
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoMesh1DHints : public PoNode {
  
  SO_NODE_HEADER(PoMesh1DHints) ;
  

 public:

  /**
   *  Interpretation Type.
   */
  enum GeomInterpretation {
    /**
     *  The geometry of the current mesh 1D is "as is" interpreted.
     */
    AS_IS,      
    /**
     *  The geometry of the current mesh 1D is smoothed by a cubic
     */
    SMOOTH,     
    /**
     *  spline.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    STAIRS_X,   
    /**
     *  X stair passing through all points.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    STAIRS_Y,   
    /**
     *  Y stair passing through all points.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    HISTO_X,    
    /**
     *  X stair no necessarily passing through all points.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    HISTO_Y,    
    /**
     *  Y stair no necessarily passing through all points.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    STAIRS_2X,  
    /**
     *  double X stair passing through all points.
     */
                
    /**
     *  The geometry of the current mesh 1D is interpreted as a
     */
    STAIRS_2Y   
    /**
     *  double Y stair passing through all points.
     */
                
  } ;



  /* Fields */



  SoSFEnum  geomInterpretation ;

  /**
   * Constructor.
   */
  PoMesh1DHints() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoMesh1DHints() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH1D_HINTS_  */

