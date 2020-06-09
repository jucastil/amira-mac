/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ISOVALUES_LIST_
#define  _PO_ISOVALUES_LIST_

#include <MeshViz/nodes/PoNode.h>
#include <Inventor/fields/SoMFFloat.h>

class PbIsovaluesList ;
class SoFieldSensor   ;

/**
 * @DTEXT  Node to define a list of isovalues.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This node defines the current list of isovalues for all subsequent 
 *    MeshViz representations which use it.
 *    There is no list of isovalues until a PoIsovaluesList node is traversed.
 *    An isovalue list is a list of floating-point values sorted by increasing order. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoIsovaluesList {
 *    @TABLE_FILE_FORMAT
 *       @TR isovaluesList @TD 0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoIsovaluesList : public PoNode {

  SO_NODE_HEADER(PoIsovaluesList) ;
  

 public:

  /* Fields */

  /**
   * Defines the list of isovalues.
   */
  SoMFFloat isovaluesList ;

  /* Methods */

  /**
   * Constructor.
   */
  PoIsovaluesList() ;

  /**
   * Convenience method to create a regular isovalue list with numValues 
   * values. The isovalue list is computed homogeneous through the min and 
   * the max of values, so the difference between two values is constant. 
   * numFloats is the size of values.
   */
  void setRegularIsoList(int numFloats, const float *values, int numValues) ;

  /**
   * Convenience method to create a regular isovalue list with numValues values.
   * The isovalue list is computed from a firstValue and the difference between 
   * values (step).
   */
  void setRegularIsoList(int numValues, float firstValue, float step) ;

  /**
   * Convenience method to create a regular isovalue list with numValues values.
   * The isovalues are between min and max.
   */
  void setRegularIsoList(float min, float max, int numValues) ;

  /**
   * Convenience method which returns information about the isovalue list.
   * [OIV-WRAPPER-RETURN-TYPE NAME{values},ARRAY{numValues}]
   * [OIVJAVA-WRAPPER-ARG NO_WRAP,OUT,OUT,OUT,OUT]
   * [OIVJAVA-WRAPPER PACK{IsoList}]
   */
  const float *getIsoList(int &numValues, float &min, float &max, float &step,
                          SbBool &isRegularIsoList) ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoIsovaluesList() ;

 private:
  static void isoListChangedCB(void *data, SoSensor *) ;
  void updateIsoList() ;

  SbBool          m_isoListChanged ;
  PbIsovaluesList *m_isoList ;
  SoFieldSensor   *m_isoListSensor ;
  
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_ISOVALUES_LIST_  */

