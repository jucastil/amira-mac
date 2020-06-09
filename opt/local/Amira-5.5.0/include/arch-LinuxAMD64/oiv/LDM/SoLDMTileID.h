/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_TILE_ID_
#define  _SO_LDM_TILE_ID_

#include <Inventor/nodes/SoSubNode.h>

#define LDM_TILE_ID_TYPE int64_t

/**
 * @LDMEXT Tile ID
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * Encapsulates the ID of a tile.
 *
 * @SEE_ALSO
 *
 */

class LDM_API SoLDMTileID {

 public:

  /**
   * Constructor.
   */
  SoLDMTileID()
  {
    m_id = 0 ;
    m_timeStep = 0 ;
  };

  /**
   * Constructor using ID value.
   * setTimeStepToCurTimeStep indicates if the time step is set to the current time step.
   * [OIVJAVA-WRAPPER-ARG IN,IN&JNI_CAST_TO{bool}]
   */
  SoLDMTileID( LDM_TILE_ID_TYPE tileID, bool setTimeStepToCurTimeStep=false )
  {
    m_id = tileID;
    m_timeStep=0;
    if (setTimeStepToCurTimeStep)
      m_timeStep = m_CurrentTimeStep ;
  };

  /**
   * Constructor using ID value and timeStep value
   * [OIVJAVA-WRAPPER-ARG IN,IN&JNI_CAST_TO{unsigned short}]
   */
  SoLDMTileID( LDM_TILE_ID_TYPE tileID, unsigned short timeStep )
  {
    m_id = tileID;
    m_timeStep=timeStep;
  };

  /**
   * Equality comparison operator.
   */
  inline SbBool operator==(const SoLDMTileID&b) const {return (m_id == b.m_id) && (m_timeStep == b.m_timeStep);}
  /**
   * Inequality comparison operator.
   */
  inline SbBool operator!=(const SoLDMTileID&b) const {return (m_id != b.m_id) || (m_timeStep != b.m_timeStep) ;}
  /**
   * Relational (less than or equal to) operator.
   */
  inline SbBool operator<=(const SoLDMTileID&b) const {return m_id <= b.m_id;}

  /**
   * Relational (greater than or equal to) operator.
   */
  inline SbBool operator>=(const SoLDMTileID&b) const {return m_id >= b.m_id;}

  /**
   * Relational (less than) operator.
   */
  inline SbBool operator<(const SoLDMTileID&b) const {return m_id < b.m_id;}

  /**
   * Relational (greater than) operator.
   */
  inline SbBool operator>(const SoLDMTileID&b) const {return m_id > b.m_id;}


  /**
   * Returns the tile ID.
   */
  inline LDM_TILE_ID_TYPE getID() const
  {
    return m_id;
  }

  /**
   * ++ Prefix, increment the tile id (not the time step)
   */
  inline SoLDMTileID &operator++();

  /**
   * Postfix ++, increment the tile id (not the time step)
   */
  inline SoLDMTileID operator++(int);

  /**
   * -- Prefix, increment the tile id (not the time step)
   */
  inline SoLDMTileID &operator--();

  /**
   * Postfix --, increment the tile id (not the time step)
   */
  inline SoLDMTileID operator--(int);

  /**
   * Returns the time step.
   */
  inline unsigned short getTimeStep() const
  {
    return m_timeStep ;
  }

  static void setCurrentTimeStep(unsigned short currentTimeStep) {m_CurrentTimeStep=currentTimeStep;}

SoINTERNAL public:

private:
  LDM_TILE_ID_TYPE m_id;
  unsigned short m_timeStep;

  static unsigned short m_CurrentTimeStep ;

};

/*******************************************************************************/
SoLDMTileID &
SoLDMTileID::operator++()
{
  m_id++;
  return *this;
}

/*******************************************************************************/
SoLDMTileID
SoLDMTileID::operator++(int)
{
  SoLDMTileID tileId = *this;
  ++(*this);

  return tileId;
}

/*******************************************************************************/
SoLDMTileID &
SoLDMTileID::operator--()
{
  m_id--;
  return *this;
}

/*******************************************************************************/
SoLDMTileID
SoLDMTileID::operator--(int)
{
  SoLDMTileID tileId = *this;
  --(*this);

  return tileId;
}

/**
 * Writes the tile to the specified output stream.
 */
inline std::ostream& operator << (std::ostream& os, const SoLDMTileID& tile)
{
  return os << "(" << tile.getID() << ", " << tile.getTimeStep() << ")";
}

#endif // _SO_LDM_TILE_ID_
