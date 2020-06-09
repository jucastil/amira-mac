/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
** Modified by : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_UNKNOWN_NODE_
#define  _SO_UNKNOWN_NODE_

#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSubNode.h>

class SoSFNode;
class SoMFString;
class SoChildList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoUnknownNode
//
//  The Unknown Node! This node is created during file reading when a
//  node is read that is unrecognized by Inventor and a DSO cannot be found
//  for it.  Note that even though it is derived from SoGroup, we lie
//  and tell SoType that it is derived from SoNode.  This, along with
//  the fact that users are not shipped this header file (so they
//  can't call SoGroup methods directly), has the effect of making the
//  normally public children hidden.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoUnknownNode : public SoGroup {

    SO_NODE_HEADER(SoUnknownNode);

  public:
    // Constructor
    SoUnknownNode();

  SoEXTENDER public:
    virtual void	write(SoWriteAction *action);

  SoINTERNAL public:
    static void		initClass();
    static void		exitClass();
    void                setClassName(const SbString& name);

  protected:
    // Reads field type information, fields, and children.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    // Override search so we don't search alternateRep
    virtual void	search(SoSearchAction *action);

    // Returns file format name
    virtual const char* getFileFormatName() const;

    // Recursively adds this node and all nodes under it to the copy
    // dictionary. Returns the copy of this node.
    virtual SoNode *	addToCopyDict() const;

    // Copies the contents of the given node into this instance
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  private:
    // Used during reading to create an alternateRep from an isA
    // specification.
    void		createFromIsA(SoMFString *isA);

    // Per-instance field data
    SoFieldData		*instanceFieldData;

    // Real class name
    SbString className;

    // List of hidden children.
    SoChildList*		hiddenChildren;
  
    // Destructor
    virtual ~SoUnknownNode();

    // Will be true if read in with children
    SbBool hasChildren;
};

#endif /* _SO_UNKNOWN_NODE_ */
