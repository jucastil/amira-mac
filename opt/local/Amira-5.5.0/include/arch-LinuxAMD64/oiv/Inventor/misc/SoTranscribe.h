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


#ifndef  _SO_TRANSCRIBE_
#define  _SO_TRANSCRIBE_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>

class SoGroup;
class SoInput;
class SoNode;
class SoOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTranSender
//
// This stores database changes that are to be transcribed. The
// changes are written to an SoOutput instance allocated and managed
// by the caller.
//
// These database change routines are supported:
//
//   INSERT node [parent n]
//      Creates and adds a node to other database. With 1 argument,
//      the node is added as the last child of the root of the
//      database. With 3 arguments, the node is added as the nth
//      child of the given parent. (The parent may be NULL to
//      indicate the root.) Note that if the inserted node is already
//      in the graph, a link is made from the parent to the existing
//      version of the node. (Therefore, if the new node is different
//      from the old one, any changes are lost.)
//
//   REMOVE parent n
//      Removes nth child from the given parent node. (The parent may
//      be NULL to indicate the root.)
//
//   REPLACE parent n newNode
//      This is exactly equivalent to "REMOVE parent n" followed by
//      "INSERT newNode parent n".
//
//   MODIFY node
//      Updates the field data for the given node to the new
//      contents. Note that this changes only field data; children of
//      groups are not affected, nor is any non-field instance data.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Sends database changes for transcription.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   This class is used for transcribing Open Inventor data. Transcription is the
 *   process of packaging changes to a database and sending them over a "wire" to
 *   another database.
 *   
 *   The SoTranSender class is used on the sending side of transcription. It packages
 *   up changes to an Open Inventor database into a file or memory area defined by an
 *   SoOutput instance. It supports a limited set of changes to a database; each
 *   change is stored as a command in the transcription area. The SoTranReceiver
 *   class can be used at the other end to interpret the transcribed commands.
 * 
 * @SEE_ALSO
 *    SoOutput,
 *    SoTranReceiver
 * 
 * 
 */ 

class INVENTOR_API SoTranSender {
 public:

#ifdef OIV_NET_DOC
	 /**
	 * The constructor takes a reference to an SoOutput instance that determines what the
	 * transcription area is (file or memory).
	 */

#else
	 /**
	 * The constructor takes a pointer to an SoOutput instance that determines what the
	 * transcription area is (file or memory).
	 */

#endif //OIV_NET_DOC
	 SoTranSender(SoOutput *output);

  /**
   * Destructor.
   */
  ~SoTranSender()                             {}

#ifdef OIV_NET_DOC
  /**
  * Returns reference to current SoOutput instance.
  */

#else
  /**
  * Returns pointer to current SoOutput instance.
  */

#endif //OIV_NET_DOC
  SoOutput *          getOutput() const       { return out; }

  /**
   * Adds an INSERT command to the transcription area. The given node will be added
   * as the last child of the root node on the receiving end.
   */
  void                insert(SoNode *node);

  /**
   * Adds an INSERT command to the transcription area. The given node will be added
   * as the <B>n</B>th child of the given parent node on the receiving end. A NULL
   * parent node causes the node to be added to the receiving end's root node.
   */
  void                insert(SoNode *node, SoNode *parent, int n);

  /**
   * Adds a REMOVE command to the transcription area. The <B>n</B>th child of the
   * given (non-NULL) parent node on the receiving end will be removed.
   */
  void                remove(SoNode *parent, int n);

  /**
   * Adds a REPLACE command to the transcription area. The <B>n</B>th child of the
   * given (non-NULL) parent node on the receiving end will be replaced with
   * @B newNode @b.
   */
  void                replace(SoNode *parent, int n, SoNode *newNode);
  /**
   * Adds a MODIFY command to the transcription area. Updates the field data for the
   * given node to the new contents. Note that this changes only field data; children
   * of groups are not affected, nor is any non-field instance data.
   */
  void                modify(SoNode *node);

  /**
   * Prepares an SoTranSender instance for transcription, making sure the
   * transcription area is complete and all packaged to go. This must be called
   * before the transcription can be performed.
   */
  void                prepareToSend();

 private:
  SoOutput            *out;

  // Adding items to send
  void                addBytes(const void *bytes, size_t nBytes);
  void                addCommand(int command);
  void                addInt(int n);
  void                addNode(SoNode *node, SbBool addNames = TRUE);
  void                addNodeNames(const SoNode *root);
  void                addNodeRef(const SoNode *node);
  void                addString(const char *cmdString);

  friend class SoTranReceiver;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTranReceiver
//
// An SoTranReceiver is used on the receiving end to interpret the
// data packaged up by an SoTranSender. It is given a root node that
// is the default place to add incoming nodes. The input for the
// receiver comes from an SoInput.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Interprets database changes for transcription.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   This class is used for transcribing Open Inventor data. Transcription is the
 *   process of packaging changes to a database and sending them over a "wire" to
 *   another database.
 *   
 *   The SoTranReceiver class is used on the receiving side of transcription. It
 *   interprets changes to a Open Inventor database packaged up by an SoTranSender.
 * 
 * @SEE_ALSO
 *    SoInput,
 *    SoTranSender
 * 
 * 
 */ 

class INVENTOR_API SoTranReceiver {

 public:

#ifdef OIV_NET_DOC
	 /**
	 * The constructor takes a reference to an SoGroup instance that is the root node of
	 * the scene graph on the receiving end. All changes to the database are made
	 * relative to this root.
	 */

#else
	 /**
	 * The constructor takes a pointer to an SoGroup instance that is the root node of
	 * the scene graph on the receiving end. All changes to the database are made
	 * relative to this root.
	 */

#endif //OIV_NET_DOC
	 SoTranReceiver(SoGroup *rootNode);

  /**
   * Destructor.
   */
  ~SoTranReceiver();

  /**
   * Interprets the transcription commands found in the given input stream. Returns
   * FALSE on any error. Note: some errors (such as invalid node references) are
   * recoverable, while others (such as syntax errors) are not.
   */
  SbBool      interpret(SoInput *in);

 private:
  SoGroup     *root;
  SbDict      nameToEntryDict;        // Maps node keyname to SoTranDictEntry
  SbDict      nodeToNameDict;         // Maps node pointer to node keyname

  // Interprets one database change command (with given code) from stream.
  // Sets done to TRUE if end command was found. Returns T/F error status.
  SbBool      interpretCommand(int commandCode, SoInput *in, SbBool &done);

  // Gets a node and node names from the input
  SbBool      getNodeAndNames(SoInput *in, SoNode *&node);

  // Gets node from input
  SbBool      getNode(SoInput *in, SoNode *&root);

  // Recursively gets node names and sets up dictionaries.
  SbBool      getNodeNames(SoInput *in, SoNode *root,
                           SbBool lookForNode, SoNode *&oldRoot);

  // Gets reference to a node, looks it up in dictionary, returns
  // node pointer.
  SbBool      getNodeReference(SoInput *in, SoNode *&node);

  // Removes reference to node in dictionaries, recursively.
  void        removeNodeReferences(SoNode *node);

  // Adds an entry to the dictionaries
  void        addEntry(SoNode *node, SbName &name);

  // Deletes (frees up) an entry from the nodeDict
  static void deleteDictEntry(uintptr_t key, void *value);
};

#endif /* _SO_TRANSCRIBE_ */



