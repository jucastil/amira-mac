/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FILE_
#define  _SO_FILE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFilePathString.h>

class SoSensor;
class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFile
//
//  This node represents a subgraph that was read from a
//  named input file. When a file node is written out, just the field
//  containing the name of the file is written. (No children are
//  written out.) When one is encountered during reading, reading
//  continues from the named file, and all children found in the file
//  are added as hidden children of this node.
//
//  Whenever the name of the input file changes
//  (name.setValue("foo.iv")), the old children are removed and the
//  contents of the new file is read in.  The file node remembers
//  what directory the last file was read from, and will read the new
//  file from the same directory after checking the standard list of
//  directories (see the static methods on SoInput), assuming the
//  field isn't set to an absolute path name.
//
//////////////////////////////////////////////////////////////////////////////

class SoGroup;

/**
 * Node that reads children from a named file.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This node represents a subgraph that was read from a named input file. When an
 *   SoFile node is written out, just the field containing the name of the file is
 *   written; no children are written out. When an SoFile is encountered during
 *   reading, reading continues from the named file, and all nodes read from the file
 *   are added as hidden children of the file node.
 *   
 *   Whenever the #name field changes, any existing children are removed and the
 *   contents of the new file is read in. The file node remembers what directory the
 *   last file was read from and will read the new file from the same directory after
 *   checking the standard list of directories (see SoInput), assuming the field
 *   isn't set to an absolute path name.
 *   
 *   The children of an SoFile node are hidden; there is no way of accessing or
 *   editing them. If you wish to edit the contents of an SoFile node, you can modify
 *   the contents of the named file and then "touch" the #name field (see
 *   SoField). Alternatively, you can use the copyChildren() method to get an
 *   editable copy of the file node's children. Note that this does not affect the
 *   original file on disk, however.
 * 
 * @FILE_FORMAT_DEFAULT
 *    File {
 *    @TABLE_FILE_FORMAT
 *       @TR name   @TD "<Undefined file>"
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction @BR
 *        Traverses its children just as SoGroup does.
 * 
 *    SoRayPickAction @BR
 *        Traverses its hidden children, but, if intersections are found, generates paths
 *        that end at the SoFile node.
 * 
 *    SoWriteAction @BR
 *        Writes just the #name field and no children.
 * 
 * 
 * @SEE_ALSO
 *    SoInput,
 *    SoPath
 * 
 * 
 */ 

class INVENTOR_API SoFile : public SoNode {

  SO_NODE_HEADER(SoFile);

 public:
  // Fields
  /**
   * Name of file from which to read children.
   */
  SoSFFilePathString name;

  /**
   * Creates a file node with default settings.
   */
  SoFile();

  /**
   * Returns a new SoGroup containing copies of all of the file node's children.
   */
  SoGroup *copyChildren() const;

  /**
   * If flag is TRUE, the search action will traverse hidden children.
   */
  static void setSearchOK(SbBool flag);

  /**
   * Queries whether the search action will traverse the hidden
   * children.
   */
  static SbBool getSearchOK() { return m_searchOK; };

 SoEXTENDER public:
  // Traversal methods for all the actions:
  virtual void doAction(SoAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void search(SoSearchAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getMatrix(SoGetMatrixAction *action);
  virtual void handleEvent(SoHandleEventAction *action);
  virtual void pick(SoPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  
  // Returns pointer to children
  virtual SoChildList *getChildren() const;
  
  // Copies the contents of the given node into this instance.
  // This copies without re-reading the file.
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);
  
 protected:
  // Reads stuff into instance of SoFile. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  virtual ~SoFile();

  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return (SoNotificationInfo*)(&m_notificationInfo); }

 private:
  SoChildList* children;

  void nameChangedCallback(SoInput *upIn = NULL);
  
  // These keep the image and filename fields in sync.
  SoFieldSensor *nameChangedSensor;
  static void nameChangedCB(void *, SoSensor *);
  
  // FALSE on read error.
  SbBool readOK;
  static SbBool m_searchOK;

private:
  SoNode::SoNotificationInfo m_notificationInfo;

};

#endif /* _SO_FILE_ */

