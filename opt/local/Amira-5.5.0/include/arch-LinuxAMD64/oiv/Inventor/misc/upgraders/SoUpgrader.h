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


#ifndef  _SO_UPGRADER_
#define  _SO_UPGRADER_

#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoUpgrader
//
//////////////////////////////////////////////////////////////////////////////

class SbDict;
class INVENTOR_API SoUpgrader : public SoGroup {
  
  SO_NODE_ABSTRACT_HEADER(SoUpgrader);
  
 public:
  // Find out if an upgrader exists for a specific class and a
  // specific version of the file format.
  static SoUpgrader     *getUpgrader(const SbName &className,
                                     float fileFormatVersion);
 protected:
  // Register a converter for a specific class and a specific file
  // format.
  static void           registerUpgrader(const SoType &type,
                                         const SbName &className,
                                         float version);
  static void           unregisterUpgrader(const SbName &className,
                                           float version);
 SoINTERNAL public:
  static void           initClass();
  static void           exitClass();
 
  // Initialize ALL upgraders.
  static void           initClasses();
  static void           exitClasses();
  
  // This is the key method that reads in fields, calls the
  // createNewNode() method (which is responsible for looking at the
  // fields read and setting the appropriate fields in the new
  // node), and then reads in and adds children to the new node if
  // it is derived from SoGroup.
  virtual SbBool        upgrade(SoInput *in, const SbName &refName,
                                SoBase *&result);
  
 protected:
  // This is set to TRUE in the SoUpgrader constructor. A subclass
  // should set this to FALSE in its constructor if its
  // createNewNode() method returns a group node but the node being
  // upgraded is not really a group; it keeps children from being
  // read.
  SbBool                isGroup;
  
  // Subclasses MUST define this...
  virtual SoNode        *createNewNode() = 0;
  
  // Constructor.  Subclass constructors should be protected or
  // private (upgraders are created on demand by SoDB, and should
  // never be created using 'new').
  SoUpgrader();
  
  virtual ~SoUpgrader();
  
 private:
  // The dictionaries associating class names with upgrader types.
  static SbDict *getUpgradeDict(float version);
  static SbDict        *upgradeDictV1;
  static SbDict        *upgradeDictV2;
};

// Macro to initialize upgrader classes.  Pass in the name of the
// upgrader's class.
#define SO_UPGRADER_INIT_CLASS(className) \
  SO__NODE_INIT_CLASS(className, SO__QUOTE(className), SoUpgrader)

#define SO_UPGRADER_EXIT_CLASS(className)                                     \
  SO__NODE_EXIT_CLASS(className)

// Macro to register a converter.  This should be put in the initClass
// method just after SO_UPGRADER_INIT_CLASS.  This also marks the upgrader
// class as internal (upgraders are transient, and should only exist
// while reading an old Inventor file-- you shouldn't be able to just
// create one using SoType::createInstance).  Pass in the name of the
// class being upgraded (e.g. if this is MyV1Upgrader that upgrades
// the MyClass node, you would SO_REGISTER_UPGRADER(MyClass, 1.0)).
#define SO_REGISTER_UPGRADER(oldClassName, version) \
{ \
  classTypeId.makeInternal(); \
  registerUpgrader(classTypeId, SO__QUOTE(oldClassName), version); \
}

#define SO_UNREGISTER_UPGRADER(oldClassName, version) \
  unregisterUpgrader(SO__QUOTE(oldClassName), version)

// Shorthand macro to copy a field value (and flags) from an upgrader
// instance into a real node. The first version can be used if the
// fields have different names; the second assumes they're the same.
#define SO_UPGRADER_COPY_FIELD2(oldName, newName, nodeVar)                    \
{ \
  if (! oldName.isDefault())                                          \
    nodeVar->newName = oldName;                               \
  if (oldName.isIgnored())                                            \
    nodeVar->newName.setIgnored(TRUE);                        \
}

#define SO_UPGRADER_COPY_FIELD(fieldName, nodeVar)                            \
  SO_UPGRADER_COPY_FIELD2(fieldName, fieldName, nodeVar)

// Use this macro instead of calling "new" on the className. 
// This ensures that overridden types are created during an upgrade.
#define SO_UPGRADER_CREATE_NEW(className)                                     \
  ((className *) className::getClassTypeId().createInstance())

#endif /* _SO_UPGRADER_ */
