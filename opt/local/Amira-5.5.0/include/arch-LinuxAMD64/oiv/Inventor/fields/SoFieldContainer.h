/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FIELD_CONTAINER_
#define  _SO_FIELD_CONTAINER_

#include <Inventor/fields/SoSubFieldContainer.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/STL/set>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFieldContainer
//
//  Base class for engines and nodes.  This takes care of keeping
//  track of the fields in a node, or the input fields of an engine;
//  reading them, writing them, copying them, etc.
//
//////////////////////////////////////////////////////////////////////////////

class SbDict;
class SoFieldData;
class SoFieldList;
class SoField;


/**
 * Abstract base class for objects that contain fields.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoFieldContainer is the abstract base class for engines and nodes. It contains
 *   methods for finding out what fields an object has, controlling notification, and
 *   for dealing with all of the fields of an object at once.
 *   
 *   The fields of an engine are its inputs. Note that even though an engine's output
 *   corresponds to a specific type of field, an engine output is not a field.
 * 
 * @SEE_ALSO
 *    SoSField,
 *    SoMField,
 *    SoNode,
 *    SoDB
 * 
 * 
 */ 

class INVENTOR_API SoFieldContainer : public SoBase {

 public:

  /**
   * Returns the type of this class.
   */
  static SoType getClassTypeId();

  /**
   * Sets all fields in this object to their default values.
   */
  void setToDefaults();

  /**
   * Returns TRUE if all of the object's fields have their default values. This will
   * return TRUE even if a field's isDefault() method returns FALSE - for
   * example, if a field's default value is 0.0 and you @B setValue(0.0) @b that
   * field, the default flag will be set to FALSE (because it would be too slow to
   * compare the field against its default value every time @B setValue @b is
   * called). However, hasDefaultValues() would return TRUE in this case.
   */
  SbBool hasDefaultValues() const;

  /**
   * Returns TRUE if this object's fields are exactly equal to fc's fields. If fc is
   * not exactly same type as this object, FALSE is returned.
   */
  SbBool fieldsAreEqual(const SoFieldContainer *fc) const;

  /**
   * Copies the contents of fc's fields into this object's fields. fc must be the
   * same type as this object. If copyConnections is TRUE, then if any of fc's fields
   * are connected then this object's fields will also be connected to the same
   * source.
   */
  void copyFieldValues(const SoFieldContainer *fc,
                       SbBool copyConnections = FALSE);

#ifdef OIV_NET_DOC
  /**
  * Sets one or more fields in this object to the values specified in the given
  * string, which should be a string in the Open Inventor file format. true is
  * returned if the string was valid Open Inventor file format. 
  *
  * @UNICODE_WARNING
  */

#else
  /**
  * Sets one or more fields in this object to the values specified in the given
  * string, which should be a string in the Open Inventor file format. TRUE is
  * returned if the string was valid Open Inventor file format. For example, you
  * could set the fields of an SoCube by doing:
  * 
  * <PRE> 
  *  SoCube *cube = ....
  *  cube->set("width 1.0 height 2.0 depth 3.2");
  *  </PRE>
  *  
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC
  SoNONUNICODE SbBool set(const char *fieldDataString)
    { return set(fieldDataString, NULL); }


#ifdef OIV_NET_DOC
  /**
  * Sets one or more fields in this object to the values specified in the given
  * string, which should be a string in the Open Inventor file format. true is
  * returned if the string was valid Open Inventor file format. 
  */

#else
  /**
  * Sets one or more fields in this object to the values specified in the given
  * string, which should be a string in the Open Inventor file format. TRUE is
  * returned if the string was valid Open Inventor file format. For example, you
  * could set the fields of an SoCube by doing:
  * 
  * <PRE> 
  *  SoCube *cube = ....
  *  cube->set("width 1.0 height 2.0 depth 3.2");
  *  </PRE>
  *  
  */

#endif //OIV_NET_DOC
  SbBool set(const SbString& fieldDataString)
    { return set(fieldDataString, NULL); }

  /**
   * Returns the values of the fields of this object in the Open Inventor ASCII file
   * format in the given string. Fields whose isDefault() bit is set will not
   * be part of the string. You can use the SoField::get() method to get a
   * field's value as a string even if has its default value.
   */
  void get(SbString &fieldDataString)
    { get(fieldDataString, NULL); }

#ifdef OIV_NET_DOC
  /**
  * Appends references to all of this object's fields to resultList, and returns the
  * number of fields appended. The field names can be determined by passing the field 
  * references to the getFieldName() method
  * (see below).
  */

#else
  /**
  * Appends pointers to all of this object's fields to resultList, and returns the
  * number of fields appended. The types of the fields can be determined using
  * SoField::isOfType() and SoField::getTypeId(), and their names can be
  * determined by passing the field pointers to the getFieldName() method
  * (see below).
  */

#endif //OIV_NET_DOC
  virtual int getFields(SoFieldList &list) const;

  /**
   * Returns a list of fields, including the eventIn's and eventOut's
   */
  virtual int getAllFields(SoFieldList &list) const;
  // Added this method to allow the eventIns and eventOuts to be returned
  // along with the fields

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the field of this object whose name is fieldName. Returns
  * NULL if there is no field with the given name.
  */

#else
  /**
  * Returns a pointer to the field of this object whose name is fieldName. Returns
  * NULL if there is no field with the given name.
  */

#endif //OIV_NET_DOC
  virtual SoField *getField(const SbName &fieldName) const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the eventIn with the given name. If no such eventIn exists,
  * NULL is returned.
  */

#else
  /**
  * Returns a pointer to the eventIn with the given name. If no such eventIn exists,
  * NULL is returned.
  */

#endif //OIV_NET_DOC
  virtual SoField *getEventIn(const SbName &fieldName) const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the eventOut with the given name. If no such eventOut
  * exists, NULL is returned.
  */

#else
  /**
  * Returns a pointer to the eventOut with the given name. If no such eventOut
  * exists, NULL is returned.
  */

#endif //OIV_NET_DOC
  virtual SoField *getEventOut(const SbName &fieldName) const;

  /**
   * Returns the name of the given field in the fieldName argument.
   * Returns FALSE if field is not a member of this object.
   */
  SbBool getFieldName(const SoField *field, SbName &fieldName) const;

  /**
   * Notification at this Field Container is enabled (if flag == TRUE) or disabled
   * (if flag == FALSE). The returned Boolean value indicates whether notification
   * was enabled immediately prior to applying this method.
   */
  SbBool enableNotify(SbBool flag)
    { SbBool e = notifyEnabled; notifyEnabled = flag; return e; }

  /**
   * Notification is the process of telling interested objects that this object has
   * changed. Notification is needed to make engines and sensors function, is used to
   * keep SoPaths up to date when the scene graph's topology changes, and is also
   * used to invalidate rendering or bounding box caches.
   * 
   * Notification is normally enabled, but can be disabled on a node by node (or
   * engine by engine) basis. If you are making extensive changes to a large part of
   * the scene graph then disabling notification can increase performance, at the
   * expense of increased responsibility for making sure that any interested engines,
   * sensors or paths are kept up to date.
   * 
   * For example, if you will be making a lot of changes to a small part of your scene
   * graph and you know that there are no engines or sensors attached to nodes in
   * that part of the scene graph, you might disable notification on the nodes you
   * are changing, modify them, re-enable notification, and then touch() one of the
   * nodes to cause a redraw.
   * 
   * However, you should profile your application and make sure that notification is
   * taking a significant amount of time before going to the trouble of manually
   * controlling notification.
   */
  SbBool isNotifyEnabled() const
    { return notifyEnabled; }

  /**
   * Sets user application data. You can use this to add your own data
   * (physical properties, inventory tracking numbers, etc.) to a node.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  virtual void setUserData(void *data)
    { m_userData = data; }

  /**
   * Gets user application data.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void *getUserData(void) const
    { return m_userData; }

 SoINTERNAL public:
  
  // Setup type information
  static void initClass();
  static void exitClass();

  // This is used by the PROTOInstance to get the copy dictionary
  SbPList *getCopyDictionary()
    { return copyDictList; }
  
  // Versions of set() and get() that take SoInput or SoOutput from
  // which to inherit reference dictionary.
  SoNONUNICODE SbBool set(const char *fieldDataString, SoInput *dictIn);
  SbBool set(const SbString& fieldDataString, SoInput *dictIn);
  void get(SbString &fieldDataString, SoOutput *dictOut);
  
  // Propagates modification notification through an instance.
  virtual void notify(SoNotList *);

  // Manages dependencies between field (and member), update the container according to a change
  virtual void fieldHasChanged( SoField * ) { } 
  
  // Initiates notification from an instance.
  virtual void startNotify();

  // Returns whether the about to be set field value is a valid one for
  // This container
  virtual SbBool validateNewFieldValue(SoField *pField, void *newValue);
  
  // Adds a reference to the instance when writing. isFromField
  // indicates whether the reference is from a field-to-field
  // connection.
  virtual void addWriteReference(SoOutput *out, SbBool isFromField = FALSE);
  
  // Writes instance to SoOutput. (Used only for last stage of writing)
  virtual void writeInstance(SoOutput *out);
  
  // Returns whether or not instance is considered 'built-in' to the
  // library. Used during writing.
  virtual SbBool getIsBuiltIn() const { return FALSE; }
  
  // Returns an SoFieldData structure for the node. Objects with no
  // fields should return NULL, which is what the default method does.
  virtual const SoFieldData *getFieldData() const;
  
  // During a copy operation, copies of nodes and engines are
  // stored in a dictionary, keyed by the original node or engine
  // pointer, so that copies can be re-used. These methods
  // operate on that dictionary.
  
  // Initializes a new copy dictionary
  static void initCopyDict();
  
  // Adds an instance to the dictionary
  static void addCopy(const SoFieldContainer *orig,
                      const SoFieldContainer *copy);
  
  // If a copy of the given instance is in the dictionary, this
  // returns it. Otherwise, it returns NULL. The copy is not changed
  // in any way.
  static SoFieldContainer *checkCopy(const SoFieldContainer *orig);
  
  // If a copy of the given instance is not in the dictionary, this
  // returns NULL. Otherwise, this copies the contents of the
  // original into the copy (if not already done) and returns a
  // pointer to the copy.
  static SoFieldContainer *findCopy(const SoFieldContainer *orig,
                                    SbBool copyConnections);
  
  // Cleans up the dictionary when done. 
  static void copyDone();
  
  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);
  
  // During a copy operation, this copies an instance that is
  // encountered through a field connection. The default
  // implementation just returns the original pointer - no copy is
  // done. Subclasses such as nodes and engines handle this
  // differently.
  virtual SoFieldContainer *copyThroughConnection() const;
  
  // return all fieldContainer in parent path that satify the condition 
  // defined by the given searchFieldContainerFunc function
  typedef bool searchFieldContainerFunc(const SoFieldContainer *fc);
  static void searchParents(SoFieldContainer* node, searchFieldContainerFunc *func, std::set<SoFieldContainer*>& fclist);

 protected:
  
  // Is the subclass a built-in Inventor subclass or an extender subclass?
  // This is used to determine whether to read/write field type information.
  // MFO SbBool isBuiltIn;
  
  // Default constructor
  SoFieldContainer();

  // WARNING : Copy constructor should never be called.
  // WARNING : Implemented here only to add a debug message to derived class.
  SoFieldContainer(const SoFieldContainer&);

  // Destructor
  virtual ~SoFieldContainer();
  
  // Reads stuff into instance. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  static const SoFieldData** getFieldDataPtr() { return NULL; }

 private:
  
  // This pointer can be used by user to add informations in all nodes he use.
  // The user must allocate and deallocate this pointer.
  // Use it with setUserData and getUserData.
  void *m_userData;
  
  SbBool notifyEnabled; // Whether notification is enabled
  
  static SoType classTypeId;
  
  // This holds a list of SbDict instances used during copy
  // operations. It is a list to allow recursive copying.
  static SbPList *copyDictList;
  
  // These are used by SoFieldContainer::get() to hold
  // the returned field string
  static char *fieldBuf;
  static size_t fieldBufSize;
  
  // And this callback is used to unref() all instances in the
  // copyDict when copyDone() is called
  static void unrefCopy(uintptr_t key, void *instPtr);
  
  // This is used to reallocate the string buffer used by
  // SoFieldContainer::get()
  static void *reallocFieldBuf(void *ptr, size_t newSize);

private:
  // These 2 pointers allow to keep a linked list of all SoFieldContainer
  // created to be able to resync them in case of cluster Connection/disconnction.
  // they are fully managed by the SoFieldContainerExt class.
  SoFieldContainer *cacheNext;
  SoFieldContainer *cachePrev;
  friend class SoFieldContainerExt;

};

#endif  /* _SO_FIELD_CONTAINER_ */
