/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHBASEREPRESENTATION_
#define  _MO_MESHBASEREPRESENTATION_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/misc/SoChildList.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MxNodeSensor;

/**
 * @DTEXT  Abstract base class for all MeshViz Interface representation nodes.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *    Abstract base class for all MeshViz Interface representation nodes. 
 *
 * 
 */

class MESHIVIZDM_API MoMeshBaseRepresentation : public MoActionNode {

  SO_NODE_HEADER(MoMeshBaseRepresentation) ;

 public:

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  virtual bool isSynchronizingContentOnly() { return TRUE; }

 SoEXTENDER public:
  virtual void write(SoWriteAction *action);
  virtual void doAction(SoAction *action);

 protected:
  MoMeshBaseRepresentation() ;
  virtual ~MoMeshBaseRepresentation() ;  

  // The separator containing the generated scene graph
  SoSeparator *m_group;

  SoNode * getChild(int index) const ;
  virtual SoChildList *getChildren() const {return m_childList; }

  virtual void clear();

  // indicates if any fields has been modified (linked to a node sensor)
  bool isModified() const;

private:
  // Necessary for having its children traversed. Must be private to hide them.
  // Implements a hidden list of children
  SoChildList *m_childList;

  // Internal mechanism used to detect that the node has changed.
  MxNodeSensor* m_nodeSensor;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHBASEREPRESENTATION_ */



