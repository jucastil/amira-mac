/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_ISOVALUES_LIST_
#define  _PB_ISOVALUES_LIST_

#include <MeshViz/graph/PbBase.h>

/**
 * @DTEXT  Class to define a list of isovalues.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define a list of isovalues. An isovalue list is a list 
 *    of floating-point values sorted by increasing order. By default the isovalue 
 *    list is regular and contains ten values. The minimum value equals 1, the 
 *    maximum value equals 10, and the difference between two consecutive values 
 *    is constant (1 in this case).
 * 
 */
class MESHVIZ_API PbIsovaluesList : public PbBase {


 public:

  /**
   * Default constructor.
   */
  PbIsovaluesList() ;

  /**
   * Copy constructor.
   */
  PbIsovaluesList(const PbIsovaluesList &isovalList) ;

  /**
   * Constructor of a regular list of numValues isovalues.
   */
  PbIsovaluesList(float min, float max, int numValues) ;

  /**
   * Destructor.
   */
  ~PbIsovaluesList() ;

  /**
   * Assignment operator.
   */
  PbIsovaluesList& operator=(const PbIsovaluesList &isovalList) ;

  /**
   * Equality comparison operator.
   */
  int operator==(const PbIsovaluesList &isoList) ;

  /**
   * Inequality comparison operator.
   */
  int operator!=(const PbIsovaluesList &isoList)
  { return !(*this == isoList) ; }

  /**
   * Creates an irregular isovalue list with numValues values.
   */
  void setIrregularIsoList(int numValues, const float *values) ;

  /**
   * Creates a regular isovalue list with numValues values. The isovalue list is 
   * computed homogeneous through the min and the max of values, so the 
   * difference between two values is constant. numFloats is the size of values.
   */
  void setRegularIsoList(int numFloats, const float *values, int numValues) ;

  /**
   * Creates a new regular isovalue list, but the current number of isovalues is kept.
   * The isovalue list is computed homogeneous through the min and the max of values, 
   * so the difference between two values is constant. numFloats is the size of values.
   */
  void setRegularIsoList(int numFloats, const float *values) ;

  /**
   * Creates a regular isovalue list with numValues values. The isovalue list is 
   * computed from a firstValue and the difference between values (step).
   */
  void setRegularIsoList(int numValues, float firstValue, float step) ;

  /**
   * Creates a regular isovalue list with numValues values. The isovalues are
   * between min and max.
   */
  void setRegularIsoList(float min, float max, int numValues) ;

  /**
   * Creates a new regular isovalue list, but the current number of isovalues is kept.
   * The isovalues are between min and max.
   */
  void setRegularIsoList(float min, float max) ;

  /**
   * Creates a regular isovalue list with numValues values. The isovalues are
   * between the min and max of the previous isovalue list.
   */
  void setRegularIsoList(int numValues) ;

  /**
   * Returns information about the isovalue list.
   * [OIV-WRAPPER-RETURN-TYPE NAME{values},ARRAY{numValues}]
   * [OIVJAVA-WRAPPER-ARG NO_WRAP,OUT,OUT,OUT,OUT]
   * [OIVJAVA-WRAPPER PACK{IsoList}]
   */
  const float *getIsoList(int &numValues, float &min, float &max, float &step,
                          SbBool &isRegularIsoList) const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:

  void isoListDependsOnRep(SbBool flag)
    { m_isDependOnRep = flag ; }
  // Enables the isovalue list to be made depending on a representation (the 
  // isovalue list is computed by a representation). Be careful, all representations 
  // cannot compute a list of isovalues (For the moment, only mesh representations 
  // are able to compute an isovalue list from mesh limit). By default, the isovalue 
  // list does not depend on a representation.
  
  SbBool isIsoListDependsOnRep() const
    { return m_isDependOnRep ; }
  // Returns TRUE, if the isovalue list depends on a representation, otherwise 
  // FALSE.

  float getLowerIsovalue(float value) const ;
  float getUpperIsovalue(float value) const ;
  int   getIndex(float value) const ;

 private:
  // Used by constructor per copy and affectation operator
  void copy(const PbIsovaluesList &isovalList, SbBool isConstructorPerCopy) ;

  // Used to debug
  void print() ;

  // Allow to allocate isovalues list
  void allocIsovalList() ;

  // Compute a homogeneous isovalues list from min, max and 
  // number of values desired
  void homogIsovalList(float min, float max, int numValues) ;
  
  float  m_minValue, m_maxValue, *m_isovalList, m_stepIsoValues,
    m_deltaIsoMin ; // not used for the moment
  int    m_numIsoValues, m_numAllocValues ;
  SbBool m_isRegularIsovalList, m_isDependOnRep ;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_ISOVALUES_LIST_ */



