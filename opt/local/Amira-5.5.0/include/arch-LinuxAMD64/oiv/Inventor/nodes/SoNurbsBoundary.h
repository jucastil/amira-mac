/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_NURBS_BOUNDARY_
#define _SO_NURBS_BOUNDARY_

#include <Inventor/nodes/SoNode.h>
/** 
 * @VSGEXT Node that defines a boundary shared by several NURBS profile.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a boundary shared by several NURBS profiles.
 *   It allows the creation of a set of NURBS patches with a common boundary
 *   that is tessellated without cracks.
 *
 *   This node is used in the field SoNurbsProfile::boundary .
 *   Surfaces which have profiles with the same boundary (i.e., the
 *   same SoNurbsBoundary node) will be joined.
 * 
 * @FILE_FORMAT_DEFAULT
 *    SoNurbsBoundary {
 *    @TABLE_FILE_FORMAT  
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoNurbsSurface,
 *    SoNurbsGroup,
 *    SoNurbsProfile,
 *    SoNurbsProperty
 * 
 * 
 */ 

class INVENTOR_API SoNurbsBoundary : public SoNode
{
  SO_NODE_HEADER(SoNurbsBoundary);

 public:
 /**
  * Constructor.
  */
  SoNurbsBoundary();

SoEXTENDER public:
  /** define render action behavior */
   virtual void GLRender(SoGLRenderAction *) {}

   /** define render callback action behavior */
   virtual void callback(SoCallbackAction *) {}

   /** default action behavior */
   virtual void doAction(SoAction *) {}
   
SoINTERNAL public:
  /** register class in database */
  static void initClass();

  /** unregister class in database */
  static void exitClass();

  /** return interanl ID */
  inline int getID()
  { return m_ID; }

  /** set interanl ID */
  inline void setID(int id)
  { m_ID = id; }

protected:
   /** Destructor. */
   virtual ~SoNurbsBoundary();

private:
  /** internal ID */
  int m_ID;

};

#endif
