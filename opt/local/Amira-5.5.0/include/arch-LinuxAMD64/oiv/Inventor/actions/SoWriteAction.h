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


#ifndef  _SO_WRITE_ACTION_
#define  _SO_WRITE_ACTION_

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SoOutput.h>

class SoVRMLPROTODef;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWriteAction
//
//  For writing scene graphs to files. There are two stages in this
//  action. First it has to count references to nodes and paths, since
//  multiply-referenced nodes and paths need to have temporary names
//  defined for them. The second stage is writing the stuff out.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Writes a scene graph to a file.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class is used for writing scene graphs in Open Inventor (.iv) format. 
 *   SoWriteAction traverses the scene graph and uses an instance of SoOutput
 *   to write each node. SoOutput methods can be called to specify what file or 
 *   memory buffer to write to. SoOutput supports both ASCII (default) and 
 *   binary formats and provides some convenience functions for opening and 
 *   closing files. See SbFileHelper for more convenience functions.
 *   Since Open Inventor 8.1, SoOutput can write compressed data in the lossless 
 *   Zlib (gzip) format.  Both ASCII and binary format files may be compressed.
 *
 *   X3D / VRML @BR
 *   Open Inventor ASCII format is essentially the same as the VRML97 format
 *   (because the standard was influenced by Open Inventor), which is now
 *   called the "Classic VRML" encoding in the X3D specification (see
 *   www.x3d.org).  The main difference is the file header.  If you need to
 *   write VRML compatible files, you must set the appropriate file header
 *   string using SoOutput's @I setHeaderString@i method. However setting the 
 *   correct header string does not guarantee everything in the file is valid
 *   X3D/VRML.  If you need to convert a scene graph containing Open Inventor
 *   specific nodes to X3D/VRML, use SoToVRML2Action.
 *
 *  @EXAMPLE
 *   An instance of SoOutput is automatically created by SoWriteAction and can be 
 *   queried using the \oivnetdoc GetOutput() \else getOutput() \endoivnetdoc
 *   method.  This is typically the only instance needed. For example:
 *   \oivnetdoc
 *     \code
 *     SoWriteAction writeAction = new SoWriteAction();
 *     writeAction.GetOutput().OpenFile( "output.iv" );
 *     writeAction.GetOutput().SetBinary( true );
 *     writeAction.Apply( scene );
 *     writeAction.GetOutput().CloseFile();
 *     \endcode
 *   \else
 *     \code
 *     SoWriteAction writeAction;
 *     writeAction.getOutput()->openFile( "output.iv" );
 *     writeAction.getOutput()->setBinary( TRUE );
 *     writeAction.apply( scene );
 *     writeAction.getOutput()->closeFile();
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SoOutput
 */ 

class INVENTOR_API SoWriteAction : public SoAction {

  SO_ACTION_HEADER(SoWriteAction);

 public:
  /**
   * Constructor.
   */
  SoWriteAction();

  /**
   * Constructor that takes an SoOutput to use for output.
   */
  SoWriteAction(SoOutput *out);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoWriteAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Returns reference to SoOutput instance in action.
   */
  SoOutput *          getOutput() const               { return output; }

  // Applies action to the graph rooted by a node
  // These methods were added to write out PROTO's and EXTERNPROTO's. The normal
  // write action only writes out referenced PROTO's and EXTERNPROTO's
  // M. Alcala 4/21/98

  /**
   * Write given SoVRMLPROTODef to the current SoOutput.
   */
  void        writePROTO(SoVRMLPROTODef *protoDef);

  /**
   * Write given SoVRMLEXTERNPROTODef to the current SoOutput.
   */
  void        writeEXTERNPROTO(SoVRMLEXTERNPROTODef *externprotoDef);

  /**
   * Write all defined VRMLPROTO to the current SoOutput.
   */
  void        writeAllPROTO();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Continues write action on a graph or path
  void                continueToApply(SoNode *node);
  void                continueToApply(SoPath *path);

 protected:
  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);

  // Override method to return FALSE, since this action applies
  // itself to each path separately, so it doesn't need the extra
  // overhead of compacting the list.
  virtual SbBool      shouldCompactPathLists() const;

 private:
  SoOutput            *output;        // Output info
  SbBool              createdOutput;  // TRUE if output created by action
  SbBool              continuing;     // TRUE only if continueToApply()
  // was used to apply action
  SbBool              doOneStage;     // TRUE if only supposed to do 1 stage
  SbPList             savedLists;     // Path lists saved for later apply
  SbBool              headerDone;

  // Performs traversal on a path list, which is a little tricker
  void                traversePathList(SoNode *node);
  void        writeRoutes();
  void        metaWrite();
  void        componentWrite();
  void        profileWrite();
  void        protoWrite();
};

#endif /* _SO_WRITE_ACTION_ */

