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


#ifndef  _SO_NODEKIT_PARTS
#define  _SO_NODEKIT_PARTS

#include <Inventor/nodekits/SoNodekitCatalog.h>

class SoNodeKitListPart;
class SoBaseKit;
class SoNode;
class SoFullPath;
class SoSFNode;

////////////////////////////////////////////////////////////////////
//    Class: SoNodekitParts
////////////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoNodekitParts {

 SoEXTENDER public:
  // Instances of SoNodekitParts are created only by subclasses of SoBaseKit.

  // Constructor -- requires a catalog to build
  SoNodekitParts( SoBaseKit *rootOfKit );

  // Destructor
  ~SoNodekitParts();

  friend class SoBaseKit;

 private:
  const SoNodekitCatalog *catalog;   // the catalog to use in building
  // parts
  int                     numEntries;   // must be made equal to numEntries
  // in the catalog
  SoBaseKit               *rootPointer; // Pointer to the part 'this'
  SoSFNode                **fieldList;  // each 'part' is actually just
  // a node, stored in a field

  SbBool makePart( const int partNum );
  SbBool replacePart( const int partNum, SoNode *newPartNode );
  void   unregisterDescendants( const int partNum );

  SoNode *getPartFromThisCatalog( const int partNum, SbBool makeIfNeeded,
                                  SbBool leafCheck, SbBool publicCheck, 
                                  SbBool &existedBefore );
  SoFullPath *createPathToPartFromThisCatalog( const int partNum, 
                                               SbBool makeIfNeeded, SbBool leafCheck, 
                                               SbBool publicCheck,  SbBool &existedBefore );
  SbBool setPartFromThisCatalog( const int partNum, 
                                 SoNode *newPartNode,
                                 SbBool anyPart );

  SoNode *getSingleNamePart( const SbName &nameOfPart, SbBool makeIfNeeded,
                             SbBool leafCheck, SbBool publicCheck, 
                             SbBool &existedBefore );
  SoFullPath *getSingleNamePathToPart( const SbName &nameOfPart, 
                                       SbBool makeIfNeeded, SbBool leafCheck, 
                                       SbBool publicCheck, SbBool &existedBefore );
  SbBool setSingleNamePart( const SbName &nameOfPart, SoNode *newPartNode,
                            SbBool anyPart );

  // returns the part requested. If 'leafCheck' then it will only return 
  // leaves. If 'publicCheck', then it will only return public parts.
  // Otherwise it will also return interior parts.
  // Interior parts are ordinarily not obtainable through public methods.
  SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
                      SbBool leafCheck, SbBool publicCheck );
  SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
                      SbBool leafCheck, SbBool publicCheck, 
                      SbBool &existedBefore);
  SoFullPath *createPathToAnyPart( const SbName &nameOfPart, 
                                   SbBool makeIfNeeded, SbBool leafCheck, SbBool publicCheck );
  SoFullPath *createPathToAnyPart( const SbName &nameOfPart, 
                                   SbBool makeIfNeeded, SbBool leafCheck, 
                                   SbBool publicCheck,  SbBool &existedBefore );
  SbBool setAnyPart(  const SbName &nameOfPart, SoNode *newPartNode, 
                      SbBool anyPart);

  // parse a string like 'nameOfList[elementNum]' into two parts...
  // Destructive to parseString, so give it a copy if you care.
  // Replaces the '[' with an end-of-string and reads elementNum 
  // into the integer given
  SbBool parseListItem( char* parseString, int &index );

  // help to delete unneeded parts...
  SbBool partIsNonLeafAndMayBeDeleted( int partNum );

  // error check functions...
  SbBool partFoundCheck( int partNum );
  SbBool partIsLeafCheck( int partNum );
  SbBool partIsPublicCheck( int partNum );
  SbBool verifyPartExistence( int partNum );

  // builds a path from the entry 'this' down to the entry given
  // by 'nameOfPart'. Assumes that 'theNode' matches 'nameOfPart'
  SoFullPath *createPathDownTo( const SbName &nameOfPart, SoNode *theNode );

  // appends pathB after pathA and returns result.
  // result is NULL if either path is NULL or if pathA->tail != pathB->head
  SoFullPath *addPaths( const SoFullPath *pathA, 
                        const SoFullPath *pathB ) const;
};

#endif  /* _SO_NODEKIT_PARTS */
