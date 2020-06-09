/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_BASE_
#define  _SO_BASE_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/misc/SoAuditorList.h>
#include <Inventor/misc/SoRefCounter.h>
#include <Inventor/SbString.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/threads/SbThreadSpinlock.h>

class SoBaseList;
class SoInput;
class SoNode;
class SoNotList;
class SoOutput;
class SoPath;
class SoVRMLPROTODef;
class SoVRMLEXTERNPROTODef;
class SoVRMLISRef;

#if defined(_DEBUG)
class SbPList;
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBase
//
//  Base class for most important SO classes. All subclasses of this
//  class may be read and written, in the form:
//      NameOfClass {
//          <stuff inside>
//      }
//  where NameOfClass is the thing returned by getFileName(). For example,
//  the "FileName" of the SoPath class is "Path".
//
//////////////////////////////////////////////////////////////////////////////


#ifdef OIV_NET_DOC
/**
* Base class for all nodes, paths, and engines.
*
* @ingroup General
*
* @DESCRIPTION
*   Abstract base class for Open Inventor node, path, and engine classes. This class
*   handles reference counting, notification, and naming.
*
*   Instances should be referenced when
*   they will be used outside of the routine in which they were initialized. (A
*   typical example of this is maintaining a reference to the root of a graph.)
*
* @SEE_ALSO
*    SoFieldContainer,
*    SoNode,
*    SoPath,
*    SoEngine,
*    SoDB
*
*
*/
#else
/**
* Base class for all nodes, paths, and engines.
*
* @ingroup General
*
* @DESCRIPTION
*   Abstract base class for Open Inventor node, path, and engine classes. This class
*   handles reference counting, notification, and naming.
*
*   Instances should be referenced when
*   they will be used outside of the routine in which they were initialized. (A
*   typical example of this is maintaining a pointer to the root of a graph.)
*
* @SEE_ALSO
*    SoFieldContainer,
*    SoNode,
*    SoPath,
*    SoEngine,
*    SoDB
*
*
*/
#endif //OIV_NET_DOC

class INVENTOR_API SoBase: public SoRefCounter, public SoTypedObject {
 public:

  /**
   * Marks an instance as modified, simulating a change to it. This will notify
   * auditors (parent nodes, connected engines, and so on) of a change to this object
   * and cause attached sensors to be triggered.
   */
  void                        touch()         { startNotify(); }

  /**
   * Returns type identifier for this class.
   */
  static SoType               getClassTypeId();

  /**
   * Returns the name of an instance. If the instance has not been named, an empty
   * string is returned. Objects that are named can be looked up using the
   * getByName() methods of SoNode, SoEngine, or SoPath.
   */
  virtual SbName              getName() const;

#ifdef OIV_NET_DOC
  /**
  * Sets the name of an instance. Object names are preserved when objects are
  * written to or read from files. Object names must not begin with a digit, and
  * must not contain spaces or control characters, periods, single or double quote
  * characters, backslashes, curly braces, or the plus character. This method will replace any bad
  * characters in the name with underscore characters, and will print out an error
  * message if the application is using the Open Inventor debugging library.
  *
  * The same name may be assigned to more than one instance.
  *
  * Avoid using names that begin with "OIV_". Such names may be used internally.
  *
  * Nodes may be queried by name using the SoNode::GetByName methods.
  * Node names may also be used with SoSearchAction.
  * [OIVNET-WRAPPER-CUSTOM-CODE]
  */

#else
  /**
  * Sets the name of an instance. Object names are preserved when objects are
  * written to or read from files. Object names must not begin with a digit, and
  * must not contain spaces or control characters, periods, single or double quote
  * characters, backslashes, curly braces, or the plus character. The
  * isBaseNameChar() and isBaseNameStartChar() methods of SbName can
  * be used to validate names input by users. This method will replace any bad
  * characters in the name with underscore characters, and will print out an error
  * message if the application is using the Open Inventor debugging library.
  *
  * The same name may be assigned to more than one instance.
  *
  * Avoid using names that begin with "OIV_". Such names may be used internally.
  *
  * Nodes may be queried by name using the SoNode::getByName static methods.
  * Node names may also be used with SoSearchAction.
  * [OIVNET-WRAPPER-CUSTOM-CODE]
  */

#endif //OIV_NET_DOC
  virtual void                setName(const SbName &name);

  /**
   * Sets this to be a ScaleViz synchronizable object.
   * By default all objects are synchronizable.
   */
  inline void setSynchronizable( const bool b );

  /**
   * Gets the ScaleViz synchronizable state of this object.
   */
  inline bool isSynchronizable() const ;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the definition for the prototype node @B protoName @b.
  */

#else
  /**
  * Returns a pointer to the definition for the prototype node @B protoName @b.
  */

#endif //OIV_NET_DOC
  static SoVRMLPROTODef *       getPROTO(const SbName &name) ;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the definition for the externproto node
  * @B externprotoName@b.
  */

#else
  /**
  * Returns a pointer to the definition for the externproto node
  * @B externprotoName@b.
  */

#endif //OIV_NET_DOC
  static SoVRMLEXTERNPROTODef * getEXTERNPROTO(const SbName &name) ;

 protected:

  // Constructor is protected - this is an abstract class
  SoBase();

  // Virtual destructor so that subclasses are deleted properly
  virtual ~SoBase();

  // Actually deletes an instance. Allows subclasses to do other
  // stuff before the deletion if necessary.
  virtual void                destroy();

  // Returns current write counter
  static uint32_t     getCurrentWriteCounter();

  // Returns TRUE if the instance has multiple write references
  SbBool                      hasMultipleWriteRefs() const
    { return writeStuff.multWriteRef; }

  // Unknown nodes and engines write a different name for themselves
  // than their typeId; this virtual method lets them do that (by
  // default the typeId name is returned)
  virtual const char* getFileFormatName() const;

  // This set of enums is used when reading and writing the base.
  // Each enum represents a different bit in a bit field
  // which will be written.
  enum BaseFlags {
    IS_ENGINE        = 1,
    IS_GROUP         = 2
  };

  // Reads stuff into instance of subclass. Return FALSE on error.
  // If reading binary file format, the flags specify whether the
  // object was written as an engine or a group; unknown nodes and
  // groups need this information to read themselves in properly.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags) = 0;

 SoINTERNAL public:

  // Setup type information
  static void initClass();
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  static SbBool addToISDict(SoVRMLISRef *isRef, SoNode *node);
  static SbBool addToDEFDict(const SbName &name, SoBase *base);
  static SbBool addToPROTODict(const SbName &name, SoBase *base);
  static SbBool addToEXTERNPROTODict(const SbName &name, SoBase *base);
  static SoBase* findReferenceInProto(const SbName &name) ;
  static SoBase* findPROTO(const SbName &name) ;
  static SoBase* findEXTERNPROTO(const SbName &name) ;

  static void resetWriteCounter();

  // Increments the current write counter at the start of a write operation
  static void incrementCurrentWriteCounter();

  // Decrements the current write counter after a write operation,
  // in some rare cases
  static void decrementCurrentWriteCounter();

  // Initiates notification from an instance. The default method
  // does nothing, because some classes (path, sensor) never
  // initiate notification. This is used by touch().
  virtual void startNotify();

  // Propagates modification notification through an instance. The
  // default method here does not create and add a new record. It
  // merely propagates the current record list to all auditors. This
  // method may be used by subclasses to do the propagation after
  // modifying the list appropriately.
  virtual void notify(SoNotList *list);

  // Adds/removes an auditor to/from list
  void addAuditor(void *auditor, SoNotRec::Type type);
  void removeAuditor(void *auditor, SoNotRec::Type type);

  // Returns auditor list-- used by SoField and SoEngineOutput to
  // trace forward connections
  const SoAuditorList &getAuditors() const { return auditors; }

  // Internal methods used to maintain the global name dictionary
  static void addName(SoBase *, const char *);
  static void removeName(SoBase *, const char *);

  // Helper routines used to get stuff out of nameDict
  static SoBase *getNamedBase(const SbName &, const SoType&);
  static int getNamedBases(const SbName &, SoBaseList &, const SoType&);

  // Set the net name of an instance.
  virtual void setNetName( const SbName &netName);

  // Get the net name of an instance.
  virtual SbName getNetName() const;

  // Compute automatically the net name of the instance.
  virtual void generateNetName();

  // Sets this a ScaleViz synchronized object.
  inline void setSynchronized( const bool b );

  // Gets the ScaleViz synchronized state of this object.
  inline bool isSynchronized() const;

  /**
   * Writes a header (name, open brace) or footer (close brace) to
   * file defined by SoOutput. writeHeader returns TRUE if no
   * further writing is necessary for an instance.
   * isEngine/isGroup are exactly what they sound like, and must be
   * passed in so that unknown nodes/engines can be correctly
   * created when reading the binary file format.
   */
  SbBool writeHeader(SoOutput* , SbBool , SbBool ) const;
  void writeFooter(SoOutput* ) const;

  virtual bool isGroup() { return false; }

  // Reads one instance of some subclass of SoBase. Returns pointer
  // to read-in instance in base, or NULL on EOF. Returns FALSE on
  // error. The last parameter is a subclass type to match. If
  // the returned base is not of this type, it is an error. A type
  // of SoBase::getClassTypeId() will match any base.
  static SbBool read(SoInput *in, SoBase *&base, const SoType &expectedType);

  // Adds a reference to the instance when writing. isFromField
  // indicates whether the reference is from a field-to-field
  // connection.
  virtual void addWriteReference(SoOutput *out, SbBool isFromField = FALSE);

  // Returns TRUE if the instance should be written, based on the
  // write-reference info already accumulated
  SbBool shouldWrite();

  // This defaults to "+" and is used when naming nodes that are DEF's and USE'd.
  // The ivdowngrade converter needs to set it to other than "+" since that was
  // an illegal character for Inventor V1.0 names.
  static void setInstancePrefix(const SbString &c);

  static SbBool topLevel;
  static int readingEXTERNPROTO;
  static SoVRMLPROTODef *protoDefSave;
  static SbDict *EXTERNPROTODict;

  static SoVRMLPROTODef * getActualProtoDef() {return SoBase::protoDefSave;}
//  static SbDict        *PROTODict;

  static int readingPROTO;

  // This dictionary stores SoVRMLPROTODef's keyed by name
  static SbPList       *PROTOStack;
  static SbDict        *PROTODictionary;
  static int            PROTODepth;
  static void                            pushCurPROTODict(SbDict *dict) ;
  static SbDict *                        popCurPROTODict() ;

  // This dictionary stores SoVRMLPROTODef's keyed by name
  static SbPList       *EXTERNPROTOStack;
  static int            EXTERNPROTODepth;
  static void                            pushCurEXTERNPROTODict(SbDict *dict);
  static SbDict *                        popCurEXTERNPROTODict();

  // This dictionary stores the field to PROTO interface connections
  static SbPList       *ISStack;
  static SbDict        *ISDict;
  static int            ISDepth;
  static void                            pushCurISDict(SbDict *dict) ;
  static SbDict *                        popCurISDict() ;

  // This dictionary stores the DEF  names for each PROTO
  static SbPList       *DEFStack;
  static SbDict        *DEFDictionary;
  static int            DEFDepth;
  static void                            pushCurDEFDict(SbDict *dict) ;
  static SbDict *                        popCurDEFDict() ;
  static SbPList       *ROUTEList;
  static SbPList       *EXPORTList;
  static SbPList       *IMPORTList;
  static SbPList       *METAList;
  static SbPList       *COMPONENTList;

    // These are all packed into one word to save space
  struct WriteStuff {
    // This contains the value of the counter the last time the
    // instance was written.
    unsigned int writeCounter : 26;

    // This is TRUE if the object is named.
    unsigned int hasName : 1;
    unsigned int hasNetName : 1;

    // This is TRUE if more than one reference is made to the
    // instance for writing, meaning that we need to DEF it
    unsigned int multWriteRef : 1;

    // This is TRUE if the instance was referenced via a
    // field-to-field connection, which is not a "real" reference
    unsigned int writeRefFromField : 1;

    // This is TRUE if the instance was already synchronized
    // through ScaleViz
    unsigned int isSynchronized : 1;

    // This is TRUE if the instance can be synchronized
    // through ScaleViz
    unsigned int isSynchronizable : 1;

  };

  WriteStuff  writeStuff;

#if defined(_DEBUG)
  SbPList* m_dbCheckPoint;
#endif

 private:

  static SoType classTypeId;

#if defined(sun)
  static SbString instancePrefix;
#else
  static SbString instancePrefix;
#endif

  struct MTstruct
  {
    // This is incremented once per write operation. It is used to
    // determine which instances to write.
    uint32_t currentWriteCounter;
  };

  // List of auditors: objects to pass notification to
  SoAuditorList auditors;

  // These are used internally by writeHeader()
  void writeDef(SoOutput *, int) const;
  void writeRef(SoOutput *, int) const;
  void writeAnnotation(SoOutput *) const;
  void writeAnnotation1(SoOutput *) const;

  // These are all used internally by read()
  static SbBool readROUTEInstance(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readEXPORTInstance(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readIMPORTInstance(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readMETA(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readCOMPONENT(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readPROTO(SoInput *in, SbName &className, SoBase *&base);
  static SbBool protoRead(SoInput *in, SoBase *&base, SoType expectedType, SoVRMLPROTODef *protoDef);
  static SoBase* createPROTOInstance(SoVRMLPROTODef *protoDef);
  static SoBase* createEXTERNPROTOInstance( SoVRMLEXTERNPROTODef *externprotoDef);

  static SbBool readReference(SoInput *in, SoBase *&base);
  static SbBool readBase(SoInput *in, SbName &className, SoBase *&base);
  static SbBool readBaseInstance( SoInput *in,
                                  const SbName &className, const SbName &refName,
                                  const SbName &netName, SoBase *&base );
  static SoBase* createInstance(SoInput *in, SbName className, unsigned short ioFlags);

  static void flushInput(SoInput *in);
  static SbBool readPROFILEName(SoInput *in,SbName &className, SoBase *&base);
  // This dictionary stores SbPLists keyed by name (the SbPLists
  // contain SoBases-- a BaseList isn't used because we don't want
  // the items on the list to be reference counted, otherwise they
  // will never get deleted).
  static SbDict *nameObjDict;

  // And this dictionary maps the other way, from an SoBase * to a
  // name.
  static SbDict *objNameDict;

  static SbThreadMutex s_classMutex;
};

/**
 * [OIV-WRAPPER-NO-WRAP]
 */
class INVENTOR_API SoBaseInitializer
{
public:
  SoBaseInitializer(SoBase*);
  ~SoBaseInitializer();
  static inline bool isActive()
  {
    s_activeMutex.lock();
    bool ret =  m_active;
    s_activeMutex.unlock();
    return ret;
  }
private:
  SoBase* m_base;
  bool m_sync;
  bool m_prevActive;
  static bool m_active;
  static SbThreadSpinlock s_activeMutex;
};


void
SoBase::setSynchronizable( const bool b )
{
  writeStuff.isSynchronizable = b;
}

bool
SoBase::isSynchronizable() const
{
  return writeStuff.isSynchronizable;
}

void
SoBase::setSynchronized( const bool b )
{
  writeStuff.isSynchronized = b;
}

bool
SoBase::isSynchronized() const
{
  return writeStuff.isSynchronized;
}

#endif /* _SO_BASE_ */

