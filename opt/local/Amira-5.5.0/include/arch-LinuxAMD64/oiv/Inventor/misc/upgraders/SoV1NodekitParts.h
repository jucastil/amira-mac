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


#ifndef  _SO_V1_NODEKIT_PARTS
#define  _SO_V1_NODEKIT_PARTS

#include <Inventor/misc/upgraders/SoV1NodekitCatalog.h>

class SoGroup;
class SoV1BaseKit;
class SoNode;
class SoPath;

////////////////////////////////////////////////////////////////////
//    Class: SoV1NodekitParts
////////////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoV1NodekitParts {

 SoEXTENDER public:
  // Instances of SoV1NodekitParts are created only by subclasses of SoV1BaseKit.

  // Constructor -- requires a catalog to build
  SoV1NodekitParts( SoV1BaseKit *rootOfKit, SoV1NodekitParts *partsSoFar = NULL );

  // Destructor
  ~SoV1NodekitParts();

  friend class SoV1BaseKit;

 private:
  const SoV1NodekitCatalog *catalog;   // the catalog to use in building
  // parts
  int                     numEntries;   // must be made equal to numEntries
  // in the catalog
  SoNode                  **nodeList;   // each 'part' is actually just
  // a node
  SbBool makePart( const int partNum );
  SbBool replacePart( const int partNum, SoNode *newPartNode );

  SoNode *getPartFromThisCatalog( const int partNum, SbBool makeIfNeeded,
                                  SbBool leafCheck, SbBool publicCheck );
  SbBool setPartFromThisCatalog( const int partNum, 
                                 SoNode *newPartNode,
                                 SbBool anyPart );

  // returns the part requested. If 'leafCheck' then it will only return 
  // leaves. If 'publicCheck', then it will only return public parts.
  // Otherwise it will also return interior parts.
  // Interior parts are ordinarily not obtainable through public methods.
  SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
                      SbBool leafCheck, SbBool publicCheck );
  SbBool setAnyPart(  const SbName &nameOfPart, SoNode *newPartNode, 
                      SbBool anyPart);

  // error check functions...
  SbBool partFoundCheck( int partNum );
  SbBool partIsLeafCheck( int partNum );
  SbBool partIsPublicCheck( int partNum );
  SbBool partIsNotListCheck( int partNum );
  SbBool verifyPartExistence( int partNum );
};

#endif  /* _SO_V1_NODEKIT_PARTS */
