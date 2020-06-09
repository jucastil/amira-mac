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


#ifndef  _SO_FIELD_
#define  _SO_FIELD_

#include <Inventor/SbString.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/misc/SoNotification.h>
#include <Inventor/misc/SoAuditorList.h>
#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/sensors/SoDataSensor.h>
#include <Inventor/misc/SoMemoryObject.h>

class SoEngineOutput;
class SoVRMLInterpOutput;
struct SoFieldConnectionInfo;
class SoFieldContainer;
struct SoFieldAuditorInfo;
class SoFieldConverter;
class SoFieldList;
class SoInput;
class SoMemoryObject;
class SoNotList;
class SoOutput;

#ifndef HIDDEN_FROM_DOC
// If the field is connected or there are any FieldSensors attached to
// this field, flags.hasAuditors will be TRUE, and this structure is
// used to contain the extra information needed.  Done this way to
// save space in the common case.
/**
 * [OIV-WRAPPER-NO-WRAP]
 */
struct SoFieldAuditorInfo {
  SoFieldContainer *container;
  
  // List of auditors: objects to pass notification to.
  SoAuditorList auditors;
  // The "connection" field points to either an engine output,
  // a VRMLInterpolator output, or
  // another field:
  union {
    SoEngineOutput *engineOutput;
    SoField *field;
    SoVRMLInterpOutput *interpOutput;
  } connection;
};

// If the field has a connections from other fields, there is a
// SoFieldConnectionInfo structure for each connection and the index
// of the last connection that touched this field is in the variable
// lastTouched. The variable numConnected containes the number of connections
// to this field. If multiple connections are allowed, this is also the
// next connection index.
/**
 * [OIV-WRAPPER-NO-WRAP]
 */
struct SoFieldConnectionInfo {
  // The "connection" field points to either an engine output,
  // a VRMLInterpolator output, or
  // another field:
  void* indexToField;
  union {
    SoEngineOutput *engineOutput;
    SoField *field;
    SoVRMLInterpOutput *interpOutput;
  } connection;
  struct {
    unsigned int converted      : 1; // Connection required converter
    unsigned int fromEngine     : 1; // Connection is from engine
    unsigned int fromVRMLInterp : 1; // Connection is from
    // VRMLInterpolator
  } flags;
};
#endif // HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoField
//
//  Base class for all kinds of fields.  SoField maintains the state
//  (ignored, modified, default, ...) of the field.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base class for all fields.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoField is the abstract base class for all fields. Fields are the data elements
 *   contained within nodes and are the input values for engines. Each node or engine
 *   class specifies a set of fields and associates a name with each. These names
 *   define the semantics of the field (e.g., the SoCube node contains three float
 *   fields named width, height, and depth). Field classes provide the access methods
 *   that indirectly allow editing and querying of data within nodes.
 *   
 *   There are two abstract subclasses of SoField: SoSField is the base class for all
 *   single-valued field classes and SoMField is the base class for all
 *   multiple-valued fields, which contain dynamic arrays of values. Subclasses of
 *   SoSField have an SoSF prefix, and subclasses of SoMField have an SoMF prefix.
 *   See the reference pages for SoSField and SoMField for additional methods.
 *   
 *   Fields are typically constructed only within node or engine instances; if you
 *   need a field that is not part of a node or engine, you can create a
 *   @B GlobalField @b; see the methods on SoDB for creating global fields.
 *   
 *   Fields can be connected either directly to another field, or can be connected to
 *   the output of an engine. The value of a field with a connection will change when
 *   the thing it is connected to changes. For example, consider a field "A" that is
 *   connected from "B" (by @B A->connectFrom(B) @b). When B's value is changed, A's
 *   value will also change. Note that A and B may have different values, even if
 *   they are connected: if A's value is set after B's value, A's value will be
 *   different from B's until B's value is set.
 *   
 *   A field can be connected to several other fields, but can be connected from only
 *   one source.
 *   
 *   It is possible (and often useful) to create loops of field connections (for
 *   example, A connected from B and B connected from A). If there are loops, then
 *   the rule is that the last setValue() done overrides any connections in to
 *   that value. You can think of setting the value of a field as immediately
 *   propagating that value forward into all the fields it is connected to, with the
 *   propagation stopping at the place where the original setValue() occurred
 *   if there is a connection loop. (Actually, a more efficient mechanism than this
 *   is used, but the semantics are the same.)
 *   
 *   If you try to connect two fields of differing types, Open Inventor will
 *   automatically try to insert a field converter engine between them to convert
 *   values from one type into the other. Open Inventor has most reasonable
 *   conversions built-in (multiple-valued field to single-valued and vice versa,
 *   anything to SoSFString, anything to SoSFTrigger, float/short/unsigned
 *   short/int32_t/uint32_t/etc numeric conversions, etc). You can add field
 *   converters using SoDB's extender method addConverter(); see the SoDB.h
 *   header file for details. You can also find out if a converter is available with
 *   the SoDB::getConverter() method.
 *   
 *   Fields each define their own file format for reading and being written to files,
 *   but all fields follow the same conventions:
 *   
 *   Fields in a node or engine are written as the name of the field followed by the
 *   field's value; fields are not written if they have not been modified since they
 *   were created (if they have their default value).
 *   
 *   The ignored flag is written as a "~" character after the field's value (if the
 *   field's value is its default value, just the "~" is written).
 *   
 *   Field connections are written as an "=" followed by the container of the field or
 *   engine output that the field is connected to, followed by a "." and the name of
 *   the field or engine output. For example:
 *   
 *   <PRE>
 *    DEF node1 Transform translation 1 1 1 
 *    DEF node2 Scale scaleFactor 1 1 1 = USE node1.translation 
 *   </PRE>
 *   Global fields are written as part of an internal SoFieldContainer class
 *   called @B GlobalField @b, which writes out an SoSFName field named @B type @b
 *   whose value is the type of the global field, followed by a field of that type
 *   whose name is the name of the global field. For example, a global uint32_t field
 *   called "FrameCounter" whose value is 494 would be written as:
 *   
 *   <PRE>
 *    GlobalField{
 *    type SoSFUInt32
 *    FrameCounter 494
 *    }
 *   </PRE>
 *    
 * 
 * @SEE_ALSO
 *    SoSField,
 *    SoMField,
 *    SoNode,
 *    SoDB
 * 
 * 
 */ 

class INVENTOR_API SoField: public SoTypedObject {

 public:
  
  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoField();
#endif // HIDDEN_FROM_DOC
  
  /**
   * Sets the ignore flag for this field. When a field's ignore flag is set to
   * TRUE, the field is not used during traversal for rendering and other actions.
   * This flag enables you to ignore certain fields in a node and to use others. For
   * example, to ignore the specular color in a material node so the value is
   * inherited from the previous material. Some fields are not inherited and are thus
   * not affected by the Ignore flag. 
   * 
   * Examples of fields that are not inherited are the fields of shape nodes,
   * light-source nodes, some groups, and cameras, as well as the fields in the
   * SoEnvironment node. If you set the Ignore flag for a field whose values are not
   * inherited, Open Inventor simply uses the field's default values.
   * 
   * The default value for this flag is FALSE.
   */
  void setIgnored(SbBool ig);
  /**
   * Gets the ignore flag for this field.
   */
  SbBool isIgnored() const      { return flags.ignored; }

  /**
   * Gets the state of default flag of the field. This flag will be TRUE for any
   * field whose value is not modified after construction and will be FALSE for those
   * that have changed (each node or engine determines what the default values for
   * its fields are). Note: the state of this flag should not be set explicitly from
   * within applications.
   */
  SbBool isDefault() const      { return flags.hasDefault; }

  /**
   * Return the type identifier for this field class.
   */
  static SoType getClassTypeId();

  /**
   * Field connections may be enabled and disabled. Disabling a field's connection is
   * almost exactly like disconnecting it; the only difference is that you can later
   * re-enable the connection by calling enableConnection()(@B TRUE @b). Note
   * that disconnecting an engine output can cause the engine's reference count to be
   * decremented and the engine to be deleted, but disabling the connection does not
   * decrement its reference count.
   * 
   * Re-enabling a connection will cause the value of the field to be changed to the
   * engine output or field to which it is connected.
   * 
   * A field's connection-enabled status is maintained even if the field is
   * disconnected or reconnected. By default, connections are enabled.
   */
  void enableConnection(SbBool flag);

  /**
   * Returns FALSE if connections to this field are disabled. Note that this may
   * return FALSE even if the field is not connected to anything.
   */
  SbBool isConnectionEnabled() const
    { return flags.connectionEnabled; }

  /**
   * Connects this field from an engine output. If the field was
   * connected to something before, it will be automatically disconnected (a field
   * may have only one connection writing into it at a time). Unless connections to
   * the field are disabled (see enableConnection()), the field's value will
   * be set to the value of the thing it is connected to.
   */
  SbBool connectFrom(SoEngineOutput *engineOutput);

  /**
   * Connects this field to another field. If the field was
   * connected to something before, it will be automatically disconnected (a field
   * may have only one connection writing into it at a time). Unless connections to
   * the field are disabled (see enableConnection()), the field's value will
   * be set to the value of the thing it is connected to.
   */
  SbBool connectFrom(SoField *field);

  /**
   * Connects this field from an interpOutput. If the field was
   * connected to something before, it will be automatically disconnected (a field
   * may have only one connection writing into it at a time). Unless connections to
   * the field are disabled (see enableConnection()), the field's value will
   * be set to the value of the thing it is connected to.
   */
  SbBool connectFrom(SoVRMLInterpOutput *interpOutput);

  /**
   * Appends this field to the list of connections from another engineOutput.
   * Previous connections remain unchanged. Unless connections to
   * the field are disabled, the field value will be set to that of the 
   * engineOutput that was last touched. 
   */
  SbBool appendConnection(SoEngineOutput *engineOutput);

  /**
   * Appends this field to the list of connections from another field.
   * Previous connections remain unchanged. Unless connections to
   * the field are disabled, the field value will be set to that of the field
   * that was last touched. 
   */
  SbBool appendConnection(SoField *field);

  /**
   * Appends this field to the list of connections from another
   * interpOutput. Previous connections remain unchanged. Unless connections to
   * the field are disabled, the field value will be set to that of the 
   * interpOutput that was last touched. 
   */
  SbBool appendConnection(SoVRMLInterpOutput *interpOutput);

  /**
   * Disconnect the field from the requested engineOutput. All
   * other connections remain.
   */
  void disconnect(SoEngineOutput *engineOutput);

  /**
   * Disconnect the field from the requested field. All
   * other connections remain.
   */
  void disconnect(SoField *field);

  /**
   * Disconnect the field from the requested interpOutput. All
   * other connections remain.
   */
  void disconnect(SoVRMLInterpOutput *interpOutput);

  /**
   * Returns the number of connections to this field.
   */
  int getNumConnections() const
  {
    if (indexToConnectInfo)
      return indexToConnectInfo->getLength(); 
    return 0;
  }

  /**
   * Returns a list of the connections to this field.
   */
  int getConnections(SoFieldList &list) ;

  /**
   * Disconnect the field from whatever it was connected to. This does nothing if the
   * field was not connected.
   */
  void disconnect();

  /**
   * Returns TRUE if the field is connected to anything.
   */
  SbBool isConnected() const { return flags.connected; }

  /**
   * Returns TRUE if the field is connected to a VRML interpOutput.
   */
  SbBool isConnectedFromVRMLInterp() const;

  /**
   * Returns TRUE if the field is connected to an engine's output.
   */
  SbBool isConnectedFromEngine() const;

  /**
   * Returns TRUE if the field is connected to another field.
   */
  SbBool isConnectedFromField() const;

  // Returns the engine or field the output field is connected to.
  // Returns FALSE if there is no connection of the appropriate type.

  /**
   * Returns TRUE if this field is being written into by an engine, and returns the
   * engine output it is connected to in engineOutput. Returns FALSE and does not
   * modify engineOutput if it is not connected to an engine.
   */
  SbBool getConnectedEngine(SoEngineOutput *&engineOutput) const;

  /**
   * Returns TRUE if this field is being written into by another field, and returns
   * the field it is connected to in writingField. Returns FALSE and does not modify
   * writingField if it is not connected to a field.
   */
  SbBool getConnectedField(SoField *&writingField) const;

  /**
   * Returns the VRMLInterpolator output field is connected to. Returns FALSE if
   * there is no connection of the appropriate type.
   */
  SbBool getConnectedVRMLInterp(SoVRMLInterpOutput *&interpOutput) const;

#ifdef OIV_NET_DOC
  /**
  * Adds references to all of the fields that this field is writing into (either
  * fields in nodes, global fields or engine inputs) to the given field list, and
  * returns the number of forward connections.
  */

#else
  /**
  * Adds pointers to all of the fields that this field is writing into (either
  * fields in nodes, global fields or engine inputs) to the given field list, and
  * returns the number of forward connections.
  */

#endif //OIV_NET_DOC
  int getForwardConnections(SoFieldList &list) const;

#ifdef OIV_NET_DOC
  /**
  * Returns the object that contains this field. The type of the object will be
  * either SoNode, SoEngine, or will be a global field container (note that the
  * global field container class is internal to Open Inventor; see the methods for
  * creating and accessing global fields on SoDB).
  *  
  */

#else
  /**
  * Returns the object that contains this field. The type of the object will be
  * either SoNode, SoEngine, or will be a global field container (note that the
  * global field container class is internal to Open Inventor; see the methods for
  * creating and accessing global fields on SoDB). For example:
  * 
  * <PRE> 
  *  SoFieldContainer *f = field->getContainer();
  *  if (f->isOfType(SoNode::getClassTypeId())) { 
  *    ... do something ...
  *  } else if (f->isOfType(SoEngine::getClassTypeId())){
  *    ... do something else ...
  *  } else {
  *    ... it must be a global field. We can figure out its name, but that is about it:
  *    const SbName &globalFieldName = f->getName();
  *  }
  *  </PRE>
  *  
  */

#endif //OIV_NET_DOC
  SoFieldContainer *getContainer() const;

  /**
   * Sets the field to the given value, which is an ASCII string in the Open Inventor
   * file format. Each field subclass defines its own file format; see their
   * reference pages for information on their file format. The string should contain
   * only the field's value, @B not @b the field's name (e.g., "1.0", @B not @b
   * "width 1.0"). This method returns TRUE if the string is valid, FALSE if it is
   * not.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool set(const char *valueString);

  /**
   * Sets the field to the given value, which is an ASCII string in the Open Inventor
   * file format. Each field subclass defines its own file format; see their
   * reference pages for information on their file format. The string should contain
   * only the field's value, @B not @b the field's name (e.g., "1.0", @B not @b
   * "width 1.0"). This method returns TRUE if the string is valid, FALSE if it is
   * not.
   */
  SbBool set( const SbString& valueString );


  /**
   * Returns the value of the field in the Open Inventor file format, even if the
   * field has its default value.
   */
  void get(SbString &valueString);

  /**
   * Simulates a change to the field, causing attached sensors to fire, connected
   * fields and engines to be marked as needing evaluation, and so forth. Calling
   * touch() on an instance of a derived field class is equivalent to calling
   * @B setValue(getValue()) @b using the derived class's methods, except that the
   * field's isDefault() status remains unchanged.
   */
  virtual void touch();

  /**
   * Return TRUE if this field is of the same type and has the same value as
   * f.
   */
  int operator ==(const SoField &f) const
  { return isSame(f); }
  /**
   * Return FALSE if this field is of the same type and has the same value as
   * f.
   */
  int operator !=(const SoField &f) const
  { return ! isSame(f); }

 SoEXTENDER protected:
  // Constuctor:
  SoField();
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  // Initialize ALL Inventor node classes
  static void initClasses();
  static void exitClasses();
  
  // Sets value of field from the Inventor data file format
  // information in the value string.  Returns TRUE if successful,
  // FALSE otherwise. This is used in SoVRMLPROTOInstance to set the
  // fields value that is an SFNode. It is necessary for the SoInput created to 
  // know that this is a VRML2 file so it will know a PROTO if it it is the 
  // default field
  SbBool setVRML(const char *valueString);
  
  
  // Sets default flag
  void setDefault(SbBool def) { flags.hasDefault = def; }
  
  // Initiates or propagates notification through container
  virtual void startNotify();
  virtual void notify(SoNotList *list);
  
  // Sets the containing node.  This also calls enableNotify(TRUE)
  // and setDefault(TRUE).
  void setContainer(SoFieldContainer *cont);
  
  // Returns TRUE if the field really needs to be written out.
  // Fields with default values that aren't ignored and
  // aren't connected to anything will return FALSE.
  SbBool                shouldWrite() const;
  
  // Adds/removes an auditor to/from list
  void addAuditor(void *auditor, SoNotRec::Type type);
  void removeAuditor(void *auditor, SoNotRec::Type type);
  
  // Indicates whether notification will propagate as the result of
  // setting the field value. Engines turn this off when writing
  // results into fields, since notification has already propagated.
  SbBool enableNotify(SbBool flag);
  SbBool isNotifyEnabled() const
    { return flags.notifyEnabled; }
  
  // Indicates to a field that a change has been made involving a
  // connection from it (as source) to another field. Passed the
  // number of things being connected to the field; the number will
  // be negative when things are disconnected.
  // The default method does nothing.
  virtual void connectionStatusChanged(int numConnections);
  
  // If this returns TRUE, it means we're in the middle of doing a
  // setValue()+valueChanged() and values from an upstream
  // connection shouldn't write into this field.
  SbBool isReadOnly() const { return flags.readOnly; }
  
  // Returns TRUE if the given field is of the same type and has the
  // same value(s) as this. Subclasses must define this as well as
  // an == operator.
  virtual SbBool isSame(const SoField &f) const = 0;
  
  // Copies the value from one field to another, assuming same subclass
  virtual void copyFrom(const SoField &f) = 0;
  
  // After a field value has been copied using copyFrom(),
  // this is called to allow fields to update the copy. This is used
  // by node, engine, and path fields to make sure instances are
  // handled properly. The default implementation does nothing.
  virtual void fixCopy(SbBool copyConnections);
  
  // This returns TRUE if this field contains a reference to a node
  // or engine that is copied during a copy operation (i.e., it is
  // "inside"). The default method just checks if the field is
  // connected to such a node or engine. Subclasses may contain
  // other tests, such as those that contain pointers to nodes or
  // engines.
  virtual SbBool referencesCopy() const;
  
  // Copies connection from one field to another. Assumes fields are
  // the same subclass and that this field is connected.
  void copyConnection(const SoField *fromField);
  
  // Reads value of field (with given name) from file as defined by
  // SoInput. This does the work common to all fields, then calls
  // other read methods to do the rest.
  virtual SbBool read(SoInput *in, const SbName &name);
  
  // Writes field (with given name) to file as defined by SoOutput
  virtual void write(SoOutput *out, const SbName &name) const;
  
  // Counts write-references on field to prepare for writing
  virtual void countWriteRefs(SoOutput *out) const;
  
  // Evaluates the field from whatever it's connected to. If
  // there's no connection or we don't need to evaluate, this does
  // nothing. This has to be const because it's used by getValue
  // methods.
  void evaluate() const
    { if (flags.dirty) evaluateConnection(); }
  
  // This is used to set the fieldType member of the flags structure
  void setFieldType( int flagValue)
    { flags.fieldType = flagValue; };
  
  // This is used to get the fieldType member of the flags structure
  int getFieldType()
    { return flags.fieldType; };
  
  // Get the dirty flag so that the actions know to evaluate the events
  SbBool getDirty() 
    { return flags.dirty; };
  
  void setDirty(SbBool value) 
    { flags.dirty = value; };
  
  // Connects the field to the given output of an engine or to
  // another field. Returns FALSE if the connection could not be made.
  SbBool connectFrom(SoEngineOutput *engineOutput, SbBool notDefault);
  
  SbBool connectFrom(SoField *field, SbBool notDefault);
  
  // Connects the field to the given output of an VRMLInterpolator.
  // Returns FALSE if the connection could not be ade.
  SbBool connectFrom(SoVRMLInterpOutput *interpOutput, SbBool notDefault);

  // Connects the field to the given output of an engine or to
  // another field. Returns FALSE if the connection could not be made.
  SbBool connectFrom(SoEngineOutput *engineOutput,
                     SbBool notDefault, SbBool append);
  
  SbBool connectFrom(SoField *field, SbBool notDefault, SbBool append);
  
  // Connects the field to the given output of an VRMLInterpolator.
  // Returns FALSE if the connection could not be made.
  SbBool connectFrom(SoVRMLInterpOutput *interpOutput,
                     SbBool notDefault, SbBool append);
  
  // Changed to support FanIn for VRML2 but used by Inventor also.
  
  // Appends the field to the given output of an engine or to
  // another field. Returns FALSE if the connection could not be made.
  // An overloaded function to allow the appendConnection to not do
  // the notify if setting up a ROUTE-TO connection.
  SbBool appendConnection(SoEngineOutput *engineOutput,
                          SbBool notDefault);
  
  SbBool appendConnection(SoField *field, SbBool notDefault);
  
  // Connects the field to the given output of an VRMLInterpolator.
  // Returns FALSE if the connection could not be made.
  // An overloaded function to allow the appendConnection to not do
  // the notify if setting up a ROUTE-TO connection.
  SbBool appendConnection(SoVRMLInterpOutput *interpOutput,
                          SbBool notDefault);
  
  virtual bool isEnabledMemObj() { return false; }
  virtual SoMemoryObject* getMemObj() { return NULL; }
  virtual void setMemObj( SoMemoryObject* ) { }
  virtual size_t getValueSize() const { return 0; }

#if defined(_DEBUG)
  SbPList* m_dbCheckPoint;
#endif

 protected:
  // Called by an instance to indicate that a value has changed. If
  // resetDefault is TRUE, this turns off default flag. Initiates
  // notification, if necessary.
  void valueChangedBasic(SbBool resetDefault = TRUE);
  
  // Evaluates the field or engine the field is connected to,
  // storing the result in the field. This is const because it is
  // called by evaluate().
  virtual void evaluateConnection() const;
  
  // Reads value(s) of field
  virtual SbBool readValue(SoInput *in) = 0;
  
  // Reads connection.
  virtual SbBool readConnection(SoInput *in);
  
  // Writes value(s) of field
  virtual void writeValue(SoOutput *out) const = 0;
  
  // Writes field connection
  virtual void writeConnection(SoOutput *out) const;

  // These are used by SoField::get()/SoMField::get1()
  // to hold the returned field string
  static SbThreadMutex s_classMutex;
  struct MTstruct
  {
    char *fieldBuf;
    size_t fieldBufSize;
  };
  // This is used to reallocate the string buffer used by SoField::get()
  static void *reallocFieldBuf(void *ptr, size_t newSize);

 private:
  static SoType classTypeId;

  // The "flags" field contains several bit flags:
  struct Flags {
    unsigned int hasDefault     : 1; // Field is set to default value
    unsigned int ignored : 1; // Field value is to be ignored
    unsigned int connected : 1; // Field connected from something
    unsigned int converted : 1; // Connection required converter
    unsigned int fromEngine : 1; // Connection is from engine
    unsigned int connectionEnabled : 1; // Connection is enabled
    unsigned int notifyEnabled : 1; // Notification is enabled
    unsigned int hasAuditors : 1; // Connected, or FieldSensor
    unsigned int isEngineModifying : 1; // Engine evaluating
    unsigned int readOnly : 1; // Must not write into this field
    unsigned int dirty : 1; // Field was notified and needs evaluation
    unsigned int fromVRMLInterp : 1; // Connection is from VRMLInterpolator
    unsigned int fieldType : 3; // Specifies field type for VRML2 nodes.
    // 0 = hidden field         0 0 0
    // 1 = eventIn              0 0 1
    // 2 = eventOut             0 1 0
    // 3 = field and eventIn    0 1 1
    // 4 = internal field       0 0 1
    // 5 = exposedField         1 0 1
    // 6 = private field        1 1 0 // Useful for IvTune, fields which are not displayed
  };
  Flags flags;

  // If no other auditors, the container for this field is stored
  // directly here.  If the field has other auditors (flags.hasAuditors)
  // then the connection information and the container are
  // stored in an opaque SoFieldAuditorInfo structure.  This is
  // done to save space in the common case.
  union {
    /** [OIV-WRAPPER-NO-WRAP] */
    SoFieldContainer *container;
    /** [OIV-WRAPPER-NO-WRAP] */
    SoFieldAuditorInfo *auditorInfo;
  };
  
  SbPList *indexToConnectInfo;
  
  // Creates auditorInfo structure, if necessary:
  void createAuditorInfo();
  
  // Creates connectionInfo strucuture, if necessary:
  SoFieldConnectionInfo* createConnectionInfo(void* fromWhere);

  // return index of the connection info that have the indexToField member equal to fromWhere
  // -1 if not found
  int findConnectionInfo(void* fromWhere) const ;
  
  // Creates a converter engine to convert from the given field
  // type to the type of this field. Returns NULL on error.
  SoFieldConverter *createConverter(const SoType &fromFieldType) const;
  
  // Really disconnects field from whatever it's connected to
  void          reallyDisconnect();
  
  // Returns pointer to field converter, if fields was connected
  // through one
  SoFieldConverter *getConverter() const;
  
  // Looks up what field connection is from (container and field/output name)
  void getConnectionInfo(SoFieldContainer *&, SbName &) const;
  
  friend class SoEngineOutput;
  friend class SoVRMLInterpOutput;
};

// for compatibility we include also this 2 headers
// that were previously implemented here
#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoMField.h>

#endif /* _SO_FIELD_ */
