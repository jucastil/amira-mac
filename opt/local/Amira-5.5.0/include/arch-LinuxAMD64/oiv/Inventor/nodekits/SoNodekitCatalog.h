/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NODEKIT_CATALOG
#define  _SO_NODEKIT_CATALOG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>
#include <Inventor/SoType.h>

#define SO_CATALOG_NAME_NOT_FOUND -1
#define SO_CATALOG_THIS_PART_NUM   0

#ifndef HIDDEN_FROM_DOC
////////////////////////////////////////////////////////////////////
//
//    Class: SoNodekitCatalogEntry
//
//    an internal class that should be accessed only by an SoNodekitCatalog
//
//
////////////////////////////////////////////////////////////////////
SoINTERNAL class INVENTOR_API SoNodekitCatalogEntry {
 private:
  SbName     name;                // Reference name of this entry 
  SoType     type;                // Type of node allowable for setting
  // this entry. 'type' may be an 
  // abstract node type
  SoType     defaultType;         // Type of node to create if the nodekit
  // is asked to build this part itself.
  // May not be an abstract node type.
  SbBool     nullByDefault;       // If FALSE, then this part is 
  // created within the constructor.
  // Otherwise, it isn't.
  SbBool     leafPart;            // Is this entry a leaf node in the 
  // nodekit's structure?
  SbName     parentName;          // Reference name of this entry's parent
  SbName     rightSiblingName;    // Name of right sibling of the entry
  SbBool     listPart;            // Is this entry a list of nodes?
  SoType     listContainerType;   // If so, what kind of container?
  SoTypeList listItemTypes;       // If so, what types of nodes may
  // it contain?
  SbBool     publicPart;          // Can a user be given a pointer to
  // this part?
 SoINTERNAL public:
  // constructor
  SoNodekitCatalogEntry(const SbName &theName, 
                        SoType theType, SoType theDefaultType, 
                        SbBool theNullByDefault,
                        const SbName &theParentName, const SbName &theRightSiblingName, 
                        SbBool theListPart, SoType theListContainerType,
                        const SoTypeList &theListItemTypes,
                        SbBool thePublicPart);

  // clone exactly, or make a clone with a given type...
  SoNodekitCatalogEntry *clone() const;           
  SoNodekitCatalogEntry *clone( SoType newType,
                                SoType newDefaultType ) const; 

  // inquiry functions:
  const SbName  &getName() const { return name; };
  SoType  getType() const { return type; };
  SoType  getDefaultType() const { return defaultType; };
  SbBool  isNullByDefault() const { return nullByDefault; };
  SbBool  isLeaf() const { return leafPart; };
  const SbName  &getParentName() const { return parentName; };
  const SbName  &getRightSiblingName() const { return rightSiblingName; };
  SbBool  isList() const { return listPart; };
  SoType  getListContainerType() const {return listContainerType;};
  const SoTypeList &getListItemTypes() const { return listItemTypes; };
  SbBool  isPublic() const { return publicPart; };

  // For adding to the set of node types allowed beneath a list...
  void addListItemType( SoType typeToAdd );

  void setNullByDefault( SbBool newNullByDefault ) 
    { nullByDefault = newNullByDefault; }
  // these should only by used by catalogs when an entry
  // is given a new child or left sibling...
  void setPublic( SbBool newPublic ) { publicPart = newPublic; }
  void setLeaf( SbBool newLeafPart ) { leafPart = newLeafPart; }
  void setRightSiblingName( const SbName &newN ) { rightSiblingName = newN; }
  // This should only by used by catalogs when an entry is changing
  // type and/or defaultType
  void setTypes( SoType newType, SoType newDefaultType )
    { type = newType; defaultType = newDefaultType; }

  // recursively search this entry for 'name to find' in the 
  // templates of this entry and its descendants
  SbBool recursiveSearch( const SbName &nameToFind, 
                          SoTypeList *typesChecked) const;

  void printCheck() const; // prints the contents of this entry
};
#endif // HIDDEN_FROM_DOC

/**
 * Nodekit catalog class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This class describes the parts and structure of a nodekit. Each class of nodekit
 *   has one SoNodekitCatalog (a static variable for the class). Internally, the
 *   catalog contains one entry for each "part" in the nodekit's structure. Users can
 *   query the catalog for information about each entry in the catalog. This
 *   information can be obtained either by part name (a string unique for the part
 *   within the catalog) or by part number (an index into an array of parts).
 *   
 *   Note that, although the catalog for a nodekit class may contain many entries,
 *   each instance of that class is not initially created with all of these parts
 *   intact. Rather, each instance of the class has its own parts list which keeps
 *   track of which parts the user has created. The nodekit uses the catalog as a
 *   guide in creating new nodes as its descendants; the standard addChild(),
 *   removeChild() and other SoGroup methods are protected, so that users must
 *   create descendants indirectly by asking the nodekit to get and/or set the
 *   different "parts" in the catalog.
 *   
 *   The first entry in any SoNodekitCatalog corresponds to the nodekit itself. Its
 *   @B partName @b is "this" and its @B partNumber @b is 0. All other parts in the
 *   catalog are described relative to "this."
 * 
 * @SEE_ALSO
 *    SoAppearanceKit,
 *    SoBaseKit,
 *    SoCameraKit,
 *    SoLightKit,
 *    SoNodeKit,
 *    SoNodeKitDetail,
 *    SoNodeKitListPart,
 *    SoNodeKitPath,
 *    SoSceneKit,
 *    SoSeparatorKit,
 *    SoShapeKit,
 *    SoWrapperKit
 * 
 * 
 */ 

class INVENTOR_API SoNodekitCatalog {

 SoINTERNAL public:

  /**
   * Initializes this object.
   */
  static void initClass();
  static void exitClass();

 public:

  /**
   * Returns the number of entries in the catalog.
   */
  int        getNumEntries() const { return numEntries; };

  // inquiry routines, to find out about entries in the catalog,
  // Questions may be asked based on name or partNumber.
#ifdef DEBUG_NODEKITS
  /**
   * Given the name of a part, returns its part number in the catalog.
   */
  long        getPartNumber(      const SbName &theName ) const;
#else
  /**
   * Given the name of a part, returns its part number in the catalog.
   */
  int        getPartNumber(      const SbName &theName ) const;
#endif
  /**
   * Given the part number of a part, returns its name in the catalog.
   */
  const SbName     &getName(                 int    thePartNumber ) const;
  /**
   * Returns the type of the specified part.
   */
  SoType     getType(                    int    thePartNumber ) const;
  /**
   * Returns the type of the specified part.
   */
  SoType     getType(              const SbName &theName ) const;
  /**
   * Returns the default type of the specified part.
   */
  SoType     getDefaultType(             int    thePartNumber ) const;
  /**
   * Returns the default type of the specified part.
   */
  SoType     getDefaultType(       const SbName &theName ) const;
  /**
   * Returns TRUE if the specified part is null by default.
   */
  SbBool     isNullByDefault(            int    thePartNumber ) const;
  /**
   * Returns TRUE if the specified part is null by default.
   */
  SbBool     isNullByDefault(              const SbName &theName ) const;
  /**
   * Returns TRUE if the specified part is a leaf node.
   */
  SbBool     isLeaf(                     int    thePartNumber ) const;
  /**
   * Returns TRUE if the specified part is a leaf node.
   */
  SbBool     isLeaf(               const SbName &theName ) const;
  /**
   * Returns the parent of the specified part.
   */
  const SbName     &getParentName(           int    thePartNumber ) const;
  /**
   * Returns the parent of the specified part.
   */
  const SbName     &getParentName(     const SbName &theName ) const;
  /**
   * Returns the part number of the parent of the specified part.
   */
  int        getParentPartNumber(      int    thePartNumber ) const;
  /**
   * Returns the part number of the parent of the specified part.
   */
  int        getParentPartNumber(const SbName &theName ) const;
  /**
   * Returns the name of the right sibling of the specified part.
   */
  const SbName     &getRightSiblingName(      int    thePartNumber ) const;
  /**
   * Returns the name of the right sibling of the specified part.
   */
  const SbName     &getRightSiblingName(const SbName &theName ) const;
  /**
   * Returns the part number of the right sibling of the specified part.
   */
  int        getRightSiblingPartNumber(      int thePartNumber ) const;
  /**
   * Returns the part number of the right sibling of the specified part.
   */
  int        getRightSiblingPartNumber(const SbName &theName ) const;
  /**
   * Returns TRUE if the specified part is a parts list.
   */
  SbBool     isList(                     int    thePartNumber ) const;
  /**
   * Returns TRUE if the specified part is a parts list.
   */
  SbBool     isList(               const SbName &theName ) const;
  /**
   * Returns the list container type of the specified part.
   */
  SoType     getListContainerType(       int    thePartNumber ) const;
  /**
   * Returns the list container type of the specified part.
   */
  SoType     getListContainerType( const SbName &theName ) const;
  /**
   * Returns a list of the types of nodes that the specified part can contain.
   * If the part is not a parts list, the returned list is empty.
   */
  const SoTypeList    &getListItemTypes(       int    thePartNumber ) const;
  /**
   * Returns a list of the types of nodes that the specified part can contain.
   * If the part is not a parts list, the returned list is empty.
   */
  const SoTypeList    &getListItemTypes( const SbName &theName ) const;
  /**
   * Returns TRUE if the specified part is public.
   */
  SbBool     isPublic(                   int    thePartNumber ) const;
  /**
   * Returns TRUE if the specified part is public.
   */
  SbBool     isPublic(             const SbName &theName ) const;

 SoEXTENDER public:
  // Catalogs are only constructed, destructed, cloned or added to  
  // by subclasses of SoBaseKit.
  // This should be accomplished using the macros provided in SoSubKit.h

  // Constructor
  SoNodekitCatalog();

  // Destructor
  ~SoNodekitCatalog();

  // Make a new identical copy, but you must give the node type for 'this' 
  // (where 'this' is the top level node in the template )
  SoNodekitCatalog *clone( SoType typeOfThis ) const;

  // Adding entries
  SbBool addEntry(const SbName &theName, 
                  SoType theType, SoType theDefaultType,
                  SbBool  theNullByDefault,
                  const SbName &theParentName, 
                  const SbName &theRightSiblingName, SbBool theListPart, 
                  SoType theListContainerType,
                  SoType theListItemType,
                  SbBool thePublicPart);

  // For adding to the set of node types allowed beneath a list...
  void addListItemType(int thePartNumber, SoType typeToAdd);
  void addListItemType(const SbName &theName,   SoType typeToAdd);

  // For changing the type and defaultType of an entry.
  // The new types must be subclasses of the types already existing in the
  // entry.  
  // For example, in SoShapeKit, the part "shape" has type SoShape and
  // default type SoSphere.  Any shape node is acceptable, but be default a 
  // sphere will be built.
  // Well, when creating the SoVertexShapeKit class, a call of:
  //    narrowTypes( "shape", SoVertexShape::getClassTypeId(), 
  //                          SoFaceSet::getClassTypeId())
  // might be used.  This would reflect the fact that:
  // Only vertext shapes may be put in the "shape"  part, not just any shape.
  // And also, by default, a faceSet will be built, not a sphere.
  void narrowTypes( const SbName &theName, SoType newType, 
                    SoType newDefaultType );

  void setNullByDefault( const SbName &theName, SbBool newNullByDefault );

 SoINTERNAL public:
  // used by SoNodekitParts to search through catalogs.
  // recursively search a given part for 'name to find' in the 
  // templates of that entry and its descendants
  SbBool recursiveSearch( int partNumber, const SbName &nameToFind, 
                          SoTypeList *typesChecked) const;

  void printCheck() const; // prints the contents of this catalog

 private:
  static const SbName *emptyName;
  static const SoTypeList *emptyList;
  static SoType *badType;

  int                   numEntries;   // how many entries?
  SoNodekitCatalogEntry **entries;    // the array of entries
  SbDict                partNameDict; // For fast lookup of part numbers

  // Used for testing various aspects of new entries into a catalog
  SbBool    checkName( const SbName &theName );
  SbBool    checkNewName( const SbName &theName );
  SbBool    checkNewTypes( SoType theType, 
                           SoType theDefaultType );
  SbBool    checkAndGetParent(    const SbName &theName, 
                                  const SbName &theParentName, 
                                  SoNodekitCatalogEntry *& parentEntry );
  SbBool    checkAndGetSiblings(  const SbName &theParentName, 
                                  const SbName &theRightSiblingName, 
                                  SoNodekitCatalogEntry *& leftEntry,
                                  SoNodekitCatalogEntry *& rightEntry );
  SbBool    checkCanTypesBeList(  SoType theType,
                                  SoType theDefaultType,
                                  SoType theListContainerType );

};

#endif  /* _SO_NODEKIT_CATALOG */

