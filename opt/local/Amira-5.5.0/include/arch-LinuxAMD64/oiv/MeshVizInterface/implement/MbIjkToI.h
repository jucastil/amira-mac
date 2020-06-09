/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBIJKTOI_H
#define _MBIJKTOI_H

/**
* @DTEXT Simple adaptor that transforms a triplet of indices (i,j,k) into a single index.
* 
* @ingroup MeshIViz_Implement
* 
* @DESCRIPTION Transforms matrix(N,M,L) indices into a single index. 
*/
class MbIjkToI 
{
public:
  /** 
  * Constructor 
  * @param numCellI number of cells on the first axis of the input matrix.
  * @param numCellJ number of cells on the second axis of the input matrix.
  */
  MbIjkToI(size_t numCellI, size_t numCellJ)
  {
    m_numI = numCellI;
    m_numIxJ = (numCellI)*(numCellJ);
  }

  /** 
  * Computes the index associated with the triplet (i,j,k) 
  */
  size_t getI(size_t i, size_t j, size_t k) const
  {
    return k*m_numIxJ + j*m_numI + i;
  }

protected:
  size_t m_numI;
  size_t m_numIxJ;
};

#endif
