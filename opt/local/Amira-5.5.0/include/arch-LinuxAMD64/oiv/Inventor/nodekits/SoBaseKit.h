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


#ifndef  _SO_BASE_KIT_
#define  _SO_BASE_KIT_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodekits/SoNodekitParts.h>
#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/SoNodeKitPath.h>
#include <Inventor/SbViewportRegion.h>

class SoSeparator;
class SbBox3f;
class SbDict;
class SoGroup;

////////////////////////////////////////////////////////////////////
//    Class: SoBaseKit -- 
//
//  This is the base class for all node kits.
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoBaseKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoBaseKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//  It contains only 'this' and a callbackList beneath it.
//  It's catalog is made to describe the following structure:
//
//                            this
//                              |
//                            "callbackList"
//
////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Base class for all node kits.
* 
* @ingroup nodekits
* 
* @DESCRIPTION
*   This is the base class from which all nodekit nodes are derived. Nodekits
*   provide a convenient mechanism for creating groups of scene graph nodes with
*   some larger meaning. When you create a shape node such as an indexed face set,
*   for example, you almost always precede it with a coordinate node. You may also
*   want to add a transform node or specify properties with material, drawing style,
*   material binding, etc. Instead of creating each of these nodes individually and
*   then arranging them into a subgraph, you can use a nodekit of the appropriate
*   type (in this case, SoShapeKit).
*   
*   Each class of nodekit has a @B nodekit catalog @b (SoNodekitCatalog) that
*   describes the nodes in the subgraph, referred to as @B parts @b. The catalog
*   has an entry for each part, with information such as the @B partName @b,
*   @B partType @b, and @B nullByDefault @b (if false the constructor creates it).
*   The catalog also describes the arrangement of parts in the subgraph. (Other
*   information is described below; a complete description is in the
*   SoNodekitCatalog reference page.)
*   
*   If we regard the scene graph arrangement as a branching tree, then the top node
*   (root) of the arrangement is always the nodekit itself. The leaf nodes are those
*   at the bottom (containing no children). Some leaves of the tree are defined in
*   the catalog to be @B public @b parts, while other leaves are @B private @b.
*   All non-leaf parts are considered internal to the nodekit structure and are
*   marked private. Public parts are accessible; they may be requested, changed, or
*   set by the programmer with member functions such as getPart(). Private
*   parts are not accessible, so methods such as getPart() will have no
*   effect on them. For example, if you call getPart() to retrieve a private
*   part, NULL will be returned even when the part exists.
*   
*   Every nodekit reference page has a Parts section describing the function of each
*   public part it adds to those inherited from its parent class. Also, a Catalog
*   Parts section has tables of often-needed information from the catalog (part
*   type, etc.). These tables include all public parts, both new and inherited. Only
*   the public parts of a nodekit are described in the reference pages. Nodekits
*   take care of the rest for you; they automatically arrange the subgraph, creating
*   and deleting the private parts when necessary. (The SoNodekitCatalog reference
*   page has methods for finding out the part names and arrangement of all parts,
*   both public and private.)
*   
*   The nodekit catalog is a template shared by all instances of a class. They use
*   the shared catalog as a @B guide @b when creating parts (i.e., constructing
*   actual nodes), but each instance stores its own parts separately. Moreover,
*   nodekits are @B not @b SoGroup nodes, and parts are added as @B hidden
*   children @b; you can only access parts with the methods of SoBaseKit and its
*   derived classes.
*   
*   Any public part may be retrieved with getPart(), installed with
*   setPart(), or removed by giving a NULL argument to setPart().
*   Paths from the nodekit down to a part can be created by
*   createPathToPart().
*   
*   By default, parts are not created until the user requests or sets them. This
*   keeps the subgraph uncluttered and efficient for traversal. Additionally,
*   removing a part (setting it to NULL) has the extra effect of removing any
*   internal parts that are no longer needed.
*   
*   Since nodekits hide their children, any SoPath containing nodekits will end at
*   the topmost nodekit. However, since nodekits may be nested within other
*   nodekits, you may wish to cast an (SoPath *) into an (SoNodeKitPath *). 
*   The methods of SoNodeKitPath allow you to view
*   all nodekits that lie on the path (see the reference page for SoNodeKitPath).
*   
*   Public parts in the nodekit catalog fall into three categories:
*   
*     -# @B regular nodes @b
*     -# @B nodekits @b, or @B nested nodekits @b (which may nest recursively). Any
*        node which is public in a nested nodekit is accessible to the higher level
*        nodekit(s) that contains it. The description of getPart() below shows how
*        to refer to nested parts by name (e.g., "appearance.material"). This works for
*        any nodekit method that takes a part name for an argument.
*     -# @B lists @b, or @B list parts@b. These parts group together children
*        (@B list elements @b) of a particular type or types. As with nested nodekits,
*        you can refer to individual elements using notation described in
*        getPart() (e.g., "childList[0]", or if the list elements are in turn
*        nodekits, "childList[2].transform").
*   
*   When the catalog denotes that a part is a list, the part itself is always a node
*   of type SoNodeKitListPart. The catalog specifies a set of permissible
*   listItemTypes and a listContainerType for that part. It gives this information
*   to the SoNodeKitListPart when it creates it. From then on, the list part will
*   enforce type checking. So even if you retrieve the SoNodeKitListPart with
*   getPart(), you will not be able to add illegal children. (See the
*   SoNodeKitListPart reference page for more information). As an example, the
*   @B callbackList @b part of SoBaseKit has an SoSeparator container and allows
*   only SoCallback and SoEventCallback nodes in the list. Children may be added,
*   retrieved, and removed from an SoNodeKitListPart node using methods that
*   parallel those of SoGroup. However, type-checking is strictly enforced.
*   
*   Note that, although all public parts are leaves in the nodekit catalog, you are
*   free to add children to them (assuming that they are groups, nodekits, or list
*   parts). A part's status as a leaf in the catalog just means that the nodekit
*   will not manage the part's children. For example, SoWrapperKit has a part called
*   @B contents @b with a part type of SoSeparator. You can put whatever you want
*   underneath the separator, as long as @B contents @b itself is an SoSeparator.
*   
*   Thus, a nodekit only controls a section of the scene graph. Above and below that
*   section, anything goes.
*   
*   However, when nodekits are nested, they effectively create a larger `known'
*   section of the scene graph. For example, the @B appearance @b part of the
*   SoSeparatorKit is a leaf node in the SoSeparatorKit catalog. But
*   @B appearance @b is in turn an SoAppearanceKit, containing parts such as
*   @B material @b and @B drawStyle@b. The two nodekits combine to make an even
*   larger template, which the SoSeparatorKit can examine by looking at the catalogs
*   for both classes. So an SoSeparatorKit can successfully return a part named
*   "material"; first it finds (or creates) the @B appearance @b part, then it gets
*   the @B material @b by calling getPart() on the @B appearance @b.
*   
*   When the catalog defines the listItemTypes of a list part to be nodekits, the
*   name-able space expands further. For example, SoSeparatorKit has a part
*   @B childList @b which permits only SoSeparatorKits, so each list element can be
*   further searched. Hence the name
*   @B "childList[0].childList[1].childList[2].material" @b is perfectly legal.
* 
* @PARTS
*   
*    (SoNodeKitListPart)  callbackList@BR
*       This is the only part that the base class SoBaseKit creates. It is a public part
*       that is inherited by all nodekits. It provides an easy way to add callbacks for
*       a nodekit to use during action traversal (e.g. SoHandleEventAction). It is a
*       list part and may contain numerous SoCallback and/or SoEventCallback nodes. 
* 
* 
* @FILE_FORMAT_DEFAULT
*    BaseKit {
*    @TABLE_FILE_FORMAT
*       @TR callbackList   @TD NULL
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction @BR
*        Behaves like an SoGroup. Traverses each child in order.
* 
*    SoRayPickAction @BR
*        Traverses each child in order. Then, for any pick containing the kit on its
*        path, makes an SoNodeKitDetail as follows: Sets the &quot;detailNodeKit&quot;
*        (retrievable with SoNodeKitDetail::getNodeKit()) to be a reference to
*        itself. Sets the &quot;detailPart&quot; (retrievable with
*        SoNodeKitDetail::getPart()) to be a reference to the kit's leaf-most part
*        that lies on the pickPath. Sets the &quot;detailPartName&quot; (retrievable with
*        SoNodeKitDetail::getPartName()) to be the partName of that part, as found
*        in the catalog.
*        
*        Does not descend into nested nodekits. Each nodekit along the path is the
*        &quot;detailPart&quot; in its parent's detail. However, if the pick path goes
*        through a list part, a reference to the child is used for the
*        &quot;detailPart&quot;, and &quot;detailPartName&quot; is of the form
*        &quot;listName[i]&quot;.
* 
*    SoGetMatrixAction @BR
*        Behaves like an SoGroup. Does nothing unless the kit is in the middle of the
*        path chain the action is being applied to. If so, the children up to and
*        including the next node in the chain are traversed.
* 
*    SoSearchAction @BR
*        First, searches itself like an SoNode. Then, checks the value of
*        isSearchingChildren(). If true, traverses the children in order. If
*        false, returns.
* 
*    SoWriteAction @BR
*        Begins by writing out regular fields, then writes out the parts. A nodekit does
*        @B not @b write out its parts the way an SoGroup writes out its children.
*        Instead, it writes each part as an SoSFNode field. First the partName is
*        written, then the node being used for that part.
*        
*        To keep the files terse, nodekits write out as few parts as possible. However,
*        nodekits @B always @b write a part if another instance or a path is writing it.
*        If this is not the case, parts are left out according to the following rules:
*          -# NULL parts only write if the catalog states they are created by default.
*          -# Empty SoGroup and SoSeparator nodes do not write.
*          -# Non-leaf parts only write if they have non-default field values.
*          -# List parts only write if they have children or if the container node has
*             non-default field values.
*          -# Nested nodekit parts only write if they need to write one or more parts, or
*             if they have non-default field values.
* 
* 
* @CATALOG_PARTS
*    All Parts
*    @TABLE_CATALOG_PART
*       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes     
*    @TABLE_END
* 
*    Extra Information for List Parts from Above Table
*    @TABLE_LIST_PART
*       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
*    @TABLE_END
* 
* @SEE_ALSO
*    SoAppearanceKit,
*    SoCameraKit,
*    SoLightKit,
*    SoNodeKit,
*    SoNodeKitDetail,
*    SoNodeKitListPart,
*    SoNodeKitPath,
*    SoNodekitCatalog,
*    SoSceneKit,
*    SoSeparatorKit,
*    SoShapeKit,
*    SoWrapperKit
* 
* 
*/ 
#else
/**
* Base class for all node kits.
* 
* @ingroup nodekits
* 
* @DESCRIPTION
*   This is the base class from which all nodekit nodes are derived. Nodekits
*   provide a convenient mechanism for creating groups of scene graph nodes with
*   some larger meaning. When you create a shape node such as an indexed face set,
*   for example, you almost always precede it with a coordinate node. You may also
*   want to add a transform node or specify properties with material, drawing style,
*   material binding, etc. Instead of creating each of these nodes individually and
*   then arranging them into a subgraph, you can use a nodekit of the appropriate
*   type (in this case, SoShapeKit).
*   
*   Each class of nodekit has a @B nodekit catalog @b (SoNodekitCatalog) that
*   describes the nodes in the subgraph, referred to as @B parts @b. The catalog
*   has an entry for each part, with information such as the @B partName @b,
*   @B partType @b, and @B nullByDefault @b (if FALSE the constructor creates it).
*   The catalog also describes the arrangement of parts in the subgraph. (Other
*   information is described below; a complete description is in the
*   SoNodekitCatalog reference page.)
*   
*   If we regard the scene graph arrangement as a branching tree, then the top node
*   (root) of the arrangement is always the nodekit itself. The leaf nodes are those
*   at the bottom (containing no children). Some leaves of the tree are defined in
*   the catalog to be @B public @b parts, while other leaves are @B private @b.
*   All non-leaf parts are considered internal to the nodekit structure and are
*   marked private. Public parts are accessible; they may be requested, changed, or
*   set by the programmer with member functions such as getPart(). Private
*   parts are not accessible, so methods such as getPart() will have no
*   effect on them. For example, if you call getPart() to retrieve a private
*   part, NULL will be returned even when the part exists.
*   
*   Every nodekit reference page has a Parts section describing the function of each
*   public part it adds to those inherited from its parent class. Also, a Catalog
*   Parts section has tables of often-needed information from the catalog (part
*   type, etc.). These tables include all public parts, both new and inherited. Only
*   the public parts of a nodekit are described in the reference pages. Nodekits
*   take care of the rest for you; they automatically arrange the subgraph, creating
*   and deleting the private parts when necessary. (The SoNodekitCatalog reference
*   page has methods for finding out the part names and arrangement of all parts,
*   both public and private.)
*   
*   The nodekit catalog is a template shared by all instances of a class. They use
*   the shared catalog as a @B guide @b when creating parts (i.e., constructing
*   actual nodes), but each instance stores its own parts separately. Moreover,
*   nodekits are @B not @b SoGroup nodes, and parts are added as @B hidden
*   children @b; you can only access parts with the methods of SoBaseKit and its
*   derived classes.
*   
*   Any public part may be retrieved with getPart(), installed with
*   setPart(), or removed by giving a NULL argument to setPart().
*   Paths from the nodekit down to a part can be created by
*   createPathToPart().
*   
*   By default, parts are not created until the user requests or sets them. This
*   keeps the subgraph uncluttered and efficient for traversal. Additionally,
*   removing a part (setting it to NULL) has the extra effect of removing any
*   internal parts that are no longer needed.
*   
*   Since nodekits hide their children, any SoPath containing nodekits will end at
*   the topmost nodekit. However, since nodekits may be nested within other
*   nodekits, you may wish to cast an (SoPath *) into an (SoNodeKitPath *). 
*   The methods of SoNodeKitPath allow you to view
*   all nodekits that lie on the path (see the reference page for SoNodeKitPath).
*   
*   Public parts in the nodekit catalog fall into three categories:
*   
*     -# @B regular nodes @b
*     -# @B nodekits @b, or @B nested nodekits @b (which may nest recursively). Any
*        node which is public in a nested nodekit is accessible to the higher level
*        nodekit(s) that contains it. The description of getPart() below shows how
*        to refer to nested parts by name (e.g., "appearance.material"). This works for
*        any nodekit method that takes a part name for an argument.
*     -# @B lists @b, or @B list parts@b. These parts group together children
*        (@B list elements @b) of a particular type or types. As with nested nodekits,
*        you can refer to individual elements using notation described in
*        getPart() (e.g., "childList[0]", or if the list elements are in turn
*        nodekits, "childList[2].transform").
*   
*   When the catalog denotes that a part is a list, the part itself is always a node
*   of type SoNodeKitListPart. The catalog specifies a set of permissible
*   listItemTypes and a listContainerType for that part. It gives this information
*   to the SoNodeKitListPart when it creates it. From then on, the list part will
*   enforce type checking. So even if you retrieve the SoNodeKitListPart with
*   getPart(), you will not be able to add illegal children. (See the
*   SoNodeKitListPart reference page for more information). As an example, the
*   @B callbackList @b part of SoBaseKit has an SoSeparator container and allows
*   only SoCallback and SoEventCallback nodes in the list. Children may be added,
*   retrieved, and removed from an SoNodeKitListPart node using methods that
*   parallel those of SoGroup. However, type-checking is strictly enforced.
*   
*   Note that, although all public parts are leaves in the nodekit catalog, you are
*   free to add children to them (assuming that they are groups, nodekits, or list
*   parts). A part's status as a leaf in the catalog just means that the nodekit
*   will not manage the part's children. For example, SoWrapperKit has a part called
*   @B contents @b with a part type of SoSeparator. You can put whatever you want
*   underneath the separator, as long as @B contents @b itself is an SoSeparator.
*   
*   Thus, a nodekit only controls a section of the scene graph. Above and below that
*   section, anything goes.
*   
*   However, when nodekits are nested, they effectively create a larger `known'
*   section of the scene graph. For example, the @B appearance @b part of the
*   SoSeparatorKit is a leaf node in the SoSeparatorKit catalog. But
*   @B appearance @b is in turn an SoAppearanceKit, containing parts such as
*   @B material @b and @B drawStyle@b. The two nodekits combine to make an even
*   larger template, which the SoSeparatorKit can examine by looking at the catalogs
*   for both classes. So an SoSeparatorKit can successfully return a part named
*   "material"; first it finds (or creates) the @B appearance @b part, then it gets
*   the @B material @b by calling getPart() on the @B appearance @b.
*   
*   When the catalog defines the listItemTypes of a list part to be nodekits, the
*   name-able space expands further. For example, SoSeparatorKit has a part
*   @B childList @b which permits only SoSeparatorKits, so each list element can be
*   further searched. Hence the name
*   @B "childList[0].childList[1].childList[2].material" @b is perfectly legal.
* 
* @PARTS
*   
*    (SoNodeKitListPart)  callbackList@BR
*       This is the only part that the base class SoBaseKit creates. It is a public part
*       that is inherited by all nodekits. It provides an easy way to add callbacks for
*       a nodekit to use during action traversal (e.g. SoHandleEventAction). It is a
*       list part and may contain numerous SoCallback and/or SoEventCallback nodes. 
* 
* 
* @FILE_FORMAT_DEFAULT
*    BaseKit {
*    @TABLE_FILE_FORMAT
*       @TR callbackList   @TD NULL
*       @TR   boundingBoxIgnoring  @TD FALSE
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction @BR
*        Behaves like an SoGroup. Traverses each child in order.
* 
*    SoRayPickAction @BR
*        Traverses each child in order. Then, for any pick containing the kit on its
*        path, makes an SoNodeKitDetail as follows: Sets the &quot;detailNodeKit&quot;
*        (retrievable with SoNodeKitDetail::getNodeKit()) to be a pointer to
*        itself. Sets the &quot;detailPart&quot; (retrievable with
*        SoNodeKitDetail::getPart()) to be a pointer to the kit's leaf-most part
*        that lies on the pickPath. Sets the &quot;detailPartName&quot; (retrievable with
*        SoNodeKitDetail::getPartName()) to be the partName of that part, as found
*        in the catalog.
*        
*        Does not descend into nested nodekits. Each nodekit along the path is the
*        &quot;detailPart&quot; in its parent's detail. However, if the pick path goes
*        through a list part, a pointer to the child is used for the
*        &quot;detailPart&quot;, and &quot;detailPartName&quot; is of the form
*        &quot;listName[i]&quot;.
* 
*    SoGetMatrixAction @BR
*        Behaves like an SoGroup. Does nothing unless the kit is in the middle of the
*        path chain the action is being applied to. If so, the children up to and
*        including the next node in the chain are traversed.
* 
*    SoSearchAction @BR
*        First, searches itself like an SoNode. Then, checks the value of
*        isSearchingChildren(). If TRUE, traverses the children in order. If
*        FALSE, returns.
* 
*    SoWriteAction @BR
*        Begins by writing out regular fields, then writes out the parts. A nodekit does
*        @B not @b write out its parts the way an SoGroup writes out its children.
*        Instead, it writes each part as an SoSFNode field. First the partName is
*        written, then the node being used for that part.
*        
*        To keep the files terse, nodekits write out as few parts as possible. However,
*        nodekits @B always @b write a part if another instance or a path is writing it.
*        If this is not the case, parts are left out according to the following rules:
*          -# NULL parts only write if the catalog states they are created by default.
*          -# Empty SoGroup and SoSeparator nodes do not write.
*          -# Non-leaf parts only write if they have non-default field values.
*          -# List parts only write if they have children or if the container node has
*             non-default field values.
*          -# Nested nodekit parts only write if they need to write one or more parts, or
*             if they have non-default field values.
* 
* 
* @CATALOG_PARTS
*    All Parts
*    @TABLE_CATALOG_PART
*       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes     
*    @TABLE_END
* 
*    Extra Information for List Parts from Above Table
*    @TABLE_LIST_PART
*       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
*    @TABLE_END
* 
* @SEE_ALSO
*    SoAppearanceKit,
*    SoCameraKit,
*    SoLightKit,
*    SoNodeKit,
*    SoNodeKitDetail,
*    SoNodeKitListPart,
*    SoNodeKitPath,
*    SoNodekitCatalog,
*    SoSceneKit,
*    SoSeparatorKit,
*    SoShapeKit,
*    SoWrapperKit
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoBaseKit : public SoNode, public SoGetView {

  // Instead of calling SO_KIT_HEADER(className) here,
  // which is the norm for all nodekits, explicitly write the contents
  // of that macro, so as to expose the base class virtual function
  // getNodekitCatalog for the C-api...
  //
  SO_NODE_HEADER(SoBaseKit);

public:
  /**
   * Whether to ignore this node during bounding box traversal. Default is FALSE.
   */
  SoSFBool boundingBoxIgnoring;

 private:
  /* design of this class */
  static SoNodekitCatalog *nodekitCatalog;
  /* parent design */
  static const SoNodekitCatalog **parentNodekitCatalogPtr;

 public:
  /**
   * Returns the SoNodekitCatalog for the class SoBaseKit.
   */
  static const SoNodekitCatalog *getClassNodekitCatalog();

#ifdef OIV_NET_DOC
  /**
  * Returns the SoNodekitCatalog for this instance of SoBaseKit. While each instance
  * of a given class creates its own distinct set of parts (which are actual nodes),
  * all instances share the same catalog (which describes the parts but contains no
  * actual node references).
  */

#else
  /**
  * Returns the SoNodekitCatalog for this instance of SoBaseKit. While each instance
  * of a given class creates its own distinct set of parts (which are actual nodes),
  * all instances share the same catalog (which describes the parts but contains no
  * actual node pointers).
  */

#endif //OIV_NET_DOC
  /* Returns an SoNodekitCatalog for the node */
  virtual const SoNodekitCatalog *getNodekitCatalog() const;
  // ...end of contents of SO_KIT_HEADER

 protected:
  static const SoNodekitCatalog **getClassNodekitCatalogPtr();

  // Define fields for the new parts of the kit...
  SO_KIT_CATALOG_ENTRY_HEADER(callbackList);

 public:

  /**
   * Constructor.
   */
  SoBaseKit();

#ifdef OIV_NET_DOC
  /**
  * Searches the nodekit catalog (and those of all nested nodekits) for the part
  * named partName. Returns a reference to the part if a @B match is found @b, the
  * part is @B public @b, and the part has @B already been built @b. If no match
  * is found, or if the part is @B private @b, NULL is returned. If partName is in
  * the catalog (or that of one of its nested nodekit parts), but the part has not
  * been built yet, the argument makeIfNeeded determines the course of action. When
  * makeIfNeeded is false, NULL is returned; when makeIfNeeded is true,
  * getPart() will create the part (as well as any necessary intermediary
  * parts), put it in the correct place, and return a reference to the newly created
  * part.
  * 
  * Elements of @B list parts @b and parts within nested nodekits can all be
  * retrieved with getPart() The full syntax for legal partName arguments is
  * given below.
  * 
  * @B Part name BNF notation @b:
  * 
  * partName = singleName | compoundName
  * 
  * compoundName = singleName | compoundName.singleName
  * 
  * singleName = singlePartName | singleListElementName
  * 
  * singlePartName = the name of any single part in the catalog (including those that
  * are lists or nodekits), or in the recursively nested catalogs of any of its
  * parts.
  * 
  * singleListElementName = singleListName[index]
  * 
  * singleListName = the name of any single list-type part in the catalog, or in the
  * recursively nested catalogs of any of its parts.
  * 
  * index = integer
  * 
  * Examples of valid part names are:
  * 
  * "transform", "appearance.material", "childList[2].drawStyle", "foot",
  * "bird.leftLeg.foot", "octopus.leg[4].suctionCup[2].material"
  */

#else
  /**
  * Searches the nodekit catalog (and those of all nested nodekits) for the part
  * named partName. Returns a pointer to the part if a @B match is found @b, the
  * part is @B public @b, and the part has @B already been built @b. If no match
  * is found, or if the part is @B private @b, NULL is returned. If partName is in
  * the catalog (or that of one of its nested nodekit parts), but the part has not
  * been built yet, the argument makeIfNeeded determines the course of action. When
  * makeIfNeeded is FALSE, NULL is returned; when makeIfNeeded is TRUE,
  * getPart() will create the part (as well as any necessary intermediary
  * parts), put it in the correct place, and return a pointer to the newly created
  * part.
  * 
  * Elements of @B list parts @b and parts within nested nodekits can all be
  * retrieved with getPart() The full syntax for legal partName arguments is
  * given below.
  * 
  * @B Part name BNF notation @b:
  * 
  * partName = singleName | compoundName
  * 
  * compoundName = singleName | compoundName.singleName
  * 
  * singleName = singlePartName | singleListElementName
  * 
  * singlePartName = the name of any single part in the catalog (including those that
  * are lists or nodekits), or in the recursively nested catalogs of any of its
  * parts.
  * 
  * singleListElementName = singleListName[index]
  * 
  * singleListName = the name of any single list-type part in the catalog, or in the
  * recursively nested catalogs of any of its parts.
  * 
  * index = integer
  * 
  * Examples of valid part names are:
  * 
  * "transform", "appearance.material", "childList[2].drawStyle", "foot",
  * "bird.leftLeg.foot", "octopus.leg[4].suctionCup[2].material"
  */

#endif //OIV_NET_DOC
  virtual SoNode *getPart( const SbName &partName, SbBool makeIfNeeded );

  /**
   * Given a node or a path to a node, checks if the part exists in the nodekit, in a
   * nested nodekit, or an element of a list part. If so, returns a string describing
   * the part name; otherwise, returns an empty string ("").
   */
  SbString getPartString( const SoBase *part );
                     
                     
  /**
   * Returns a path that begins at this nodekit and ends at partName. Searching for
   * the part is the same as in getPart(). NULL is returned if partName cannot
   * be found, or if makeIfNeeded is FALSE and the part is not yet built. If the the
   * part is retrieved and the argument pathToExtend is NULL, the path returned
   * begins at this and ends at partName. If pathToExtend is not NULL, the path
   * created is a copy of pathToExtend with entries appended all the way down to
   * partName. It is okay for pathToExtend to go beyond the nodekit; extra nodes will
   * be popped off the tail before continuing from this down to partName.
   */
  virtual SoNodeKitPath *createPathToPart( const SbName &partName, 
                                           SbBool makeIfNeeded, const SoPath *pathToExtend = NULL );
                   
  #ifdef OIV_NET_DOC
 /**
   * Inserts the given node (not a copy) as the new part specified by partName. See
   * GetPart() for the syntax of partName. This method adds any extra nodes
   * needed to fit the part into the nodekit's catalog. Run-time type checking verifies that the node type of
   * newPart matches the type called for by partName. For example, if partName was a
   * @B material @b for an SoSeparatorKit, but newPart was an SoTransform node, then
   * the node would not be installed, and false would be returned.
   * 
   * If newPart is null, then the node specified by partName is removed. If this
   * renders any private parts useless (as occurs when you remove the last child of
   * an SoGroup node), they will also be removed. Hence nodekits do not retain
   * unnecessary nodes.
   * 
   * true is returned on success, and false upon error.
   */
 #else
  /**
   * Inserts the given node (not a copy) as the new part specified by partName. See
   * getPart() for the syntax of partName. This method adds any extra nodes
   * needed to fit the part into the nodekit's catalog. For example, if you call:
   * 
   * <PRE> 
   *  mySepKit->setPart("childList[0]", myNewChild);
   *  </PRE>
   *  the kit may need to create the part @B childList @b before it can
   * install myNewChild. Run-time type checking verifies that the node type of
   * newPart matches the type called for by partName. For example, if partName was a
   * @B material @b for an SoSeparatorKit, but newPart was an SoTransform node, then
   * the node would not be installed, and FALSE would be returned.
   * 
   * If newPart is NULL, then the node specified by partName is removed. If this
   * renders any private parts useless (as occurs when you remove the last child of
   * an SoGroup node), they will also be removed. Hence nodekits do not retain
   * unnecessary nodes.
   * 
   * TRUE is returned on success, and FALSE upon error.
   */
#endif
                 
  
  virtual SbBool setPart( const SbName &partName, SoNode *newPart );

  #ifdef OIV_NET_DOC
 /**
   * This function allows field values of parts (nodes) to be set in several
   * different parts simultaneously. The argument string,
   * @B nameValuePairListString@b, contains @B name-value @b pairs: "partName1 parameters1 ...
   * partNameN parametersN ".
   *
   * @UNICODE_WARNING
   */
 #else
  /**
   * This function allows field values of parts (nodes) to be set in several
   * different parts simultaneously. The argument string,
   * @B nameValuePairListString@b, contains @B name-value @b pairs: "partName1 parameters1 ...
   * partNameN parametersN ".
   * 
   * For example,
   * 
   * <PRE> 
   *  mySepKit->set("material {diffuseColor 1 1 1} 
   *  transform {translation 4 3 .6}");
   *  mySepKit->set("childList[0].material {ambientColor .5 .5 .5}");
   *  </PRE>  
   *
   * @UNICODE_WARNING
   */
#endif
  
  SoNONUNICODE SbBool set(char *nameValuePairListString);

  #ifdef OIV_NET_DOC
 /**
   * This function allows field values of parts (nodes) to be set in several
   * different parts simultaneously. The argument string,
   * @B nameValuePairListString@b, contains @B name-value @b pairs: "partName1 parameters1 ...
   * partNameN parametersN ".
   */
 #else
  /**
   * This function allows field values of parts (nodes) to be set in several
   * different parts simultaneously. The argument string,
   * @B nameValuePairListString@b, contains @B name-value @b pairs: "partName1 parameters1 ...
   * partNameN parametersN ".
   * 
   * For example,
   * 
   * <PRE> 
   *  mySepKit->set("material {diffuseColor 1 1 1} 
   *  transform {translation 4 3 .6}");
   *  mySepKit->set("childList[0].material {ambientColor .5 .5 .5}");
   *  </PRE>  
   */
#endif

  SbBool set( const SbString& nameValuePairListString);

  #ifdef OIV_NET_DOC
 /**
   * This function allows field values of parts (nodes) to be set. 
   * A single part is specified by @B partNameString@b; the field
   * values are specified in @B parameterString@b. The format of parameters is the Open
   * Inventor File Format syntax. The values used in parameters must of course be appropriate for the
   * node-type to which partName belongs. In this case, the nodekit SoSeparatorKit
   * has a part named @B material @b which is of type SoMaterial.
   *
   * @UNICODE_WARNING
   */
 #else
  /**
   * This function allows field values of parts (nodes) to be set. 
   * A single part is specified by @B partNameString@b; the field
   * values are specified in @B parameterString@b. The format of parameters is the Open
   * Inventor File Format syntax. For example,
   * 
   * <PRE> 
   *  mySepKit->set("material", "diffuseColor 1 0 0 shininess 0.6");
   *  </PRE>
   *  sets the part @B material @b to the values "diffuseColor 1 0 0 shininess
   * 0.6". The values used in parameters must of course be appropriate for the
   * node-type to which partName belongs. In this case, the nodekit SoSeparatorKit
   * has a part named @B material @b which is of type SoMaterial.
   *
   * @UNICODE_WARNING
   */
#endif
  
  SoNONUNICODE SbBool set(const char *partNameString, const char *parameterString);

  #ifdef OIV_NET_DOC
 /**
   * This function allows field values of parts (nodes) to be set. 
   * A single part is specified by @B partNameString@b; the field
   * values are specified in @B parameterString@b. The format of parameters is the Open
   * Inventor File Format syntax. The values used in parameters must of course be appropriate for the
   * node-type to which partName belongs. In this case, the nodekit SoSeparatorKit
   * has a part named @B material @b which is of type SoMaterial.
   */
 #else
  /**
   * This function allows field values of parts (nodes) to be set. 
   * A single part is specified by @B partNameString@b; the field
   * values are specified in @B parameterString@b. The format of parameters is the Open
   * Inventor File Format syntax. For example,
   * 
   * <PRE> 
   *  mySepKit->set("material", "diffuseColor 1 0 0 shininess 0.6");
   *  </PRE>
   *  sets the part @B material @b to the values "diffuseColor 1 0 0 shininess
   * 0.6". The values used in parameters must of course be appropriate for the
   * node-type to which partName belongs. In this case, the nodekit SoSeparatorKit
   * has a part named @B material @b which is of type SoMaterial.
   */
#endif
  
  SbBool set( const SbString& partNameString, const SbString& parameterString);

  /**
   * Sets if nodekit children are searched during SoSearchAction
   * traversal. By default, they are not.
   */
  static void   setSearchingChildren( SbBool newVal );

  /**
   * Returns TRUE if nodekit children are searched during SoSearchAction
   * traversal. By default, they are not.
   */
  static SbBool isSearchingChildren() { return searchingChildren; }

 SoEXTENDER public:

  /**
   * Returns TRUE if bounding box computation should be ignored during
   * SoGetBoundingBoxAction traversal. @BR
   *
   * By default returns value of boundingBoxIgnoring field.
   */
  inline virtual SbBool isBoundingBoxIgnoring() const
  { return boundingBoxIgnoring.getValue(); }

  virtual void doAction( SoAction *action );
  // These functions implement all actions for nodekits.
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );
  virtual void getMatrix(SoGetMatrixAction *action );
  virtual void handleEvent( SoHandleEventAction *action );
  virtual void rayPick( SoRayPickAction *action );
  virtual void search( SoSearchAction *action );
  virtual void write( SoWriteAction *action );
  virtual void getPrimitiveCount (SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Convenience method to remove warning (conversion from const char* to char*) 
  // in set("...", "...");
  // So set(const char*, const char*) replaces set(char*, char*) and 
  // set(char*, char*) becomes deprecated/internal
  SbBool set(char *partNameString, char *parameterString) 
    { return set((const char*)partNameString, (const char*)parameterString); };

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  static SoNode *typeCheck( const SbName &partName, const SoType &partType, 
                            SoNode *node );

  void printDiagram();
  void printSubDiagram( const SbName &rootName, int level );
  void printTable();

  // Overrides the default method to use countMyFields() instead of 
  // the regular SoFieldData writing mechanism.
  virtual void        addWriteReference(SoOutput *out,
                                        SbBool isFromField = FALSE);

  friend class SoNodekitCatalogEntry;
  friend class SoNodekitParts;
  friend class SoV1BaseKit;

  // This returns TRUE if the nodekit intends to write out.
  //   [a] call shouldWrite(). If TRUE, trivial return.
  //   [b] If the kit thinks it shouldn't write, it first does a recursive
  //       call to its children.  If any children must write, then so must
  //       the kit.
  //   [c] If kit has changed its mind because of [b], then add a writeRef.
  //
  //   [d] If kit should not write, it will delete the fieldDataForWriting, 
  //       since there will no writing pass applied to take care of this.
  SbBool forceChildDrivenWriteRefs( SoOutput *out );

  // enable/disable callbacks.
  static void enableNotification(SbBool);
  static SbBool isEnabledNotification();

  virtual SbBool setAnyPart( const SbName &partName, SoNode *from, SbBool anyPart = TRUE );
 
  SoNode *internalGetAnyPart( const SbName &partName, SbBool makeIfNeeded, 
    SbBool leafCheck = FALSE, SbBool publicCheck = FALSE );

 protected:

  SoChildList *children;

  // Redefines this to add this node and all part nodes to the dictionary
  virtual SoNode *    addToCopyDict() const;

  // Copies the contents of the given nodekit into this instance
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

  // Returns the containerNode within the SoNodeKitListPart given 
  // by listName.
  SoGroup *getContainerNode( const SbName &listName,
                             SbBool makeIfNeeded = TRUE );

  // like their public versions, but are allowed access to non-leaf
  // and private parts.
  // These are virtual so subclasses may do extra things
  // when certain parts are requested.
  virtual SoNode *getAnyPart( const SbName &partName, SbBool makeIfNeeded, 
                              SbBool leafCheck = FALSE, SbBool publicCheck = FALSE );
  virtual SoNodeKitPath *createPathToAnyPart(const SbName &partName, 
                                             SbBool makeIfNeeded, 
                                             SbBool leafCheck = FALSE, SbBool publicCheck = FALSE,
                                             const SoPath *pathToExtend = NULL );

  // parts list.
  SoNodekitParts      *nodekitPartsList;

  // called during construction to create parts list
  void createNodekitPartsList();
  // called during construction to create any parts that are created by
  // default (such as the cube in the SoCubeKit)
  virtual void createDefaultParts();

  // Return the node's partsList
  const SoNodekitParts *getNodekitPartsList() const 
    { return nodekitPartsList; };

  // Prints an Error when there's trouble building a catalog.
  void catalogError();

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copyContents.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor to add their own connections to the ones already
  // connected by the base classes.
  // The doItAlways flag can force the method to do the work.
  // But if (doItAlways == FALSE && onOff == connectionsSetUp), then
  // the method will return immediately without doing anything.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );
  SbBool connectionsSetUp;

  // Reads in from file. Takes care of setting parts and stuff.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
    
  // This is called during countMyFields() method. It calls setDefault()
  // on those fields we do not wish to write out. setDefault does not change
  // the field value, but it sets a flag indicating that the field should
  // not get written by this node.
  // Fields that we do not write are [a] parts that are NULL and are defined
  // in the catalog to be NULL by default. [b] non-leaf parts for which
  // isNodeFieldValuesImportant() is FALSE.
  // [c] leaf parts that are empty groups, empty separators, 
  // [d] leaf parts that are empty lists (but they must have group or 
  //     separator container nodes.
  virtual void setDefaultOnNonWritingFields();

  // This is called during addWriteReference() to write the fields.
  // It sometimes treats fields for parts of the nodekit in a special way.
  // Under normal circumstances, they write like other fields.
  // The special case is when a part-field has a non-NULL value, but has 
  // also been set to default, indicating that we would rather not write it.
  // If the part is a regular node, we give it a field-connection style
  // write ref.  So it only writes if some other instance of the node forces
  // a write.
  // If the part is a nodekit, then we additionally write ref the fields of 
  // the nodekit, using this same method.
  // Later, in the WRITE stage, the kit-part will be written if at least
  // one of its fields or ancestor parts has shouldWrite() ==TRUE.
  // This way, if a nodekit part or any of its ancestors has non-NULL fields,
  // it will later be forced to write, even though it has been set to default.
  // Example: 
  //   Parent draggers attempt not to write out child draggers.
  //   But the parentDragger must at least traverse the childDragger to see 
  //   if any of the part geometry has been changed from its default. Such 
  //   changes must be written to file.
  void countMyFields(SoOutput *out);

  virtual ~SoBaseKit();

  static SbBool m_enableBaseKitNotification;

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(child)); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { addChild(child); }
  virtual int internalFindChild( const SoNode *child ) const             { return findChild(child); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { insertChild(child, newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { replaceChild(index, newChild); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(oldChild,newChild); }


  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return (SoNotificationInfo*)(&m_notificationInfo); }

protected:

  // end basekit writing.
  void endWrite( SoOutput* out );

private:
  void skipWhiteSpace(char *&string);

  // Returns FALSE if every field has either [a] hasDefaultValue() == TRUE or
  // [b] isDefault() == TRUE
  SbBool isNodeFieldValuesImportant( SoNode *n );

  // This creates a copy of fieldData with a few changes that make
  // it write out 'prettier'
  void createFieldDataForWriting();

  // Used to store field data during writing. Need this because a temporary
  // version of fieldData is made that differs from the real thing.
  SoFieldData *fieldDataForWriting;

  // This list contains pointers to fields whose default 
  // flag has been changed so they won't write out.
  
  SbPList savedList;

  // Called by the readInstance routine...
  SbBool readMyFields(SoInput *in, SoFieldData *&unknownFieldData );

  // Called by write() after the (virtual) setDefaultOnNonWritingNodes() 
  // method.  This method looks at the part fields which have isDefault()
  // set to TRUE.    This method will setDefault(FALSE) on any part fields
  // that MUST write.   
  //     This happens when the part-field is for a part whose parent 
  //     is going to write out anyway. Therefore, it will appear in file as 
  //     a node within this kit, so we better write out the part field to 
  //     explain where the node belongs in the kit.
  void undoSetDefaultOnFieldsThatMustWrite();

  // Only nodekits themselves can access the private children.
  int  getNumChildren() const { return (children->getLength()); }
  void removeChild( int index );
  void removeChild( SoNode *child  ) { removeChild(findChild(child)); }
  void removeAllChildren();
  void addChild( SoNode *child );
  int  findChild( const SoNode *child ) const;
  void insertChild( SoNode *child, int newChildIndex );
  SoNode *getChild( int index) const { return (*children)[index]; }
  void replaceChild( int index, SoNode *newChild);
  void replaceChild( SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild),newChild); }

  static SbBool searchingChildren;

  SoNode::SoNotificationInfo m_notificationInfo;
};

// Macro for getting at parts without doing type casting yourself:
// for example, the code:
//  xf = (SoTransform *) myKit->getPart("transform",
//                                      SoTransform::getClassTypeId(), TRUE);
// becomes:
//  xf = SO_GET_PART( myKit, "transform", SoTransform );
//      
// The macro SO_CHECK_PART will not build the part if it is not already in the
// kit, since it sends 'FALSE' as the 'makeIfNeeded' argument.
//
// CAUTION:  These macros will not work in the C-api, and nothing will be
//           gained from making them.  So, don't make them.


#if defined(_DEBUG)
#define SO_GET_PART( kitContainingPart, partName, partClassName )              \
        ((partClassName *) SoBaseKit::typeCheck( partName,                     \
                               partClassName::getClassTypeId(),               \
                               kitContainingPart->getPart( partName, TRUE )))

#define SO_CHECK_PART( kitContainingPart, partName, partClassName )            \
        ((partClassName *) SoBaseKit::typeCheck( partName,                    \
                               partClassName::getClassTypeId(),               \
                               kitContainingPart->getPart( partName, FALSE )))

#define SO_GET_ANY_PART( kitContainingPart, partName, partClassName )         \
        ((partClassName *) SoBaseKit::typeCheck( partName,                    \
                partClassName::getClassTypeId(),                              \
                kitContainingPart->getAnyPart( partName, TRUE, FALSE, FALSE )))

#define SO_CHECK_ANY_PART( kitContainingPart, partName, partClassName )       \
        ((partClassName *) SoBaseKit::typeCheck( partName,                    \
                partClassName::getClassTypeId(),                              \
                kitContainingPart->getAnyPart( partName, FALSE, FALSE, FALSE )))
#else

#define SO_GET_PART( kitContainingPart, partName, partClassName )             \
        ((partClassName *) kitContainingPart->getPart( partName, TRUE ))
#define SO_CHECK_PART( kitContainingPart, partName, partClassName )           \
        ((partClassName *) kitContainingPart->getPart( partName, FALSE ))
#define SO_GET_ANY_PART( kitContainingPart, partName, partClassName )        \
        ((partClassName *) kitContainingPart->getAnyPart( partName, TRUE,    \
                                                          FALSE, FALSE ))
#define SO_CHECK_ANY_PART( kitContainingPart, partName, partClassName )      \
        ((partClassName *) kitContainingPart->getAnyPart( partName, FALSE,   \
                                                          FALSE, FALSE ))
#endif

#endif  /* _SO_BASE_KIT_ */

