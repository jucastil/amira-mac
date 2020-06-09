/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBIJTOI_H
#define _MBIJTOI_H

/**
* @DTEXT Simple adaptor that transforms a pair of indices (i,j) into a single index.
* 
* @ingroup MeshIViz_Implement
* 
* @DESCRIPTION Transforms matrix(N,M) indices into a single index. 
*/
class MbIjToI 
{
public:
  /** 
  * Constructor 
  * @param numCellI number of cells on the first axis of the input matrix.
  */
  MbIjToI(size_t numCellI)
  {
    m_numI = numCellI;
  }

  /** 
  * Computes the index associated with the pair (i,j) 
  */
  size_t getI(size_t i, size_t j) const
  {
    return j*m_numI + i;
  }

protected:
  size_t m_numI;

};

#endif
