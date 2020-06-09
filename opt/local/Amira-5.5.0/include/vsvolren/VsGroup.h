/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_GROUP_H_
#define _VS_GROUP_H_


#include "Vs.h"

#include "VsNode.h"

class McBox3f;

// VS_RELAY_CLASS VsGroup VsNodeRelay


/** Objects of this class are able to contain a number of child nodes of type VsNode.
    Using this class it is possible to construct scene graphs.
    An node can be added multiple times.
*/
class VSVOLREN_API VsGroup : public VsNode
{
    VS_DECL_INTERFACE        ( VsGroup )
    VS_DECL_INTERFACE_IMPL   ( VsGroup )
    VS_DECL_INTERFACE_FACTORY( VsGroup )
    VS_DECL_INTERFACE_RELAY  ( VsGroup )

public:

    /** 
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET

    /** 
    */
    virtual void * extension( int inEnum, void * inData); // ???

    /** Hook a node to the list of child nodes. Returns the index of the added node.
        If the node is already in the goup, it is added again.
        \param  inNode
                Node that gets hooked. If zero, no operation is performed.
        \return 
                Index of the newly added reference node if inNode is non-zero. -1 if inNode is zero.
    */
    virtual int addNode( VsNode * inNode ); // VS_RELAY

    /** Hook a node at a specific position to the list of child nodes. 
        Returns the index of the added node.
        \param  inBefore
                The position, where the node gets hooked.
                Valid values are between 0 and size(). 
        \param  inNode
                Node that gets hooked. Must be non-zero.
        \return 
                Index of the node. If inBefore is not in the valid range, 
                the return value is -1. 
    */
    virtual int insertNode( int inBefore, VsNode * inNode ); // VS_RELAY

    /** Search a node in the list of child nodes beginning at index zero.
        Remode the first reference to the given node from the list.
        Returns the index of the removed node or -1 if node wasn't found.
        \param  inNode
                Node that gets unhooked.
        \return 
                Index of the node or -1 if node was not a child of this group node.
    */
    virtual int removeNode( VsNode * inNode ); // VS_RELAY

    /** Remove Node at a specific index.
        Returns the index of the removed node or -1 if node wasn't found.
        \param  inIndex
                Index of the reference that has to be removed.
        \return 
                Index of the node or -1 if node was not a child of this group node.
    */
    virtual int removeNode( int inIndex ); // VS_RELAY removeNodeByIndex( int inIndex );

    /** Returns true if the given node is a child node of the scene graph,
        of which \c inRoot is the root node.
        \param  inRoot
                Root of the scene graph to query.
        \param  inNode
                Non-zero pointer to the node to be tested.
        \return
                \c True if node is contained in graph below inRoot.
    */
    static bool containsNode( const VsNode * inRoot, const VsNode * inNode ); // LOCAL_GET

    /** Unhook all child nodes.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT removeAll(); // VS_RELAY

    /** Number of child nodes.
        \return 
                Current number of child nodes.
    */
    int size() const; // LOCAL_GET

    /** Return index of the specified node in the child node list or -1 if the node is not a child node of this group.
        \param  inNode
                Non-zero pointer to the node to be found.
        \param  inStartIndex
                index in the node list, where the searching starts.
        \return 
                Index of the node or -1 if node was not a child of this group node.
    */
    int findNode( VsNode * inNode, int inStartIndex=0  ) const; // LOCAL_GET
   
    /** Return child node with the given index in the child list.
        \param  inIndex
                Index of the node to be retrieved.
        \return 
                Pointer to the node or zero on error. 
                To get extended error information, call Vs::lastError().
    */
    VsNode * node( int inIndex ) const; // LOCAL_GET

    /** Set the transformation matrix that is applied to all
        child nodes during rendering.
        \param  inMatrix
                The transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setTransformation( const McMat4f & inMatrix ); // VS_RELAY

    /** Get the transformation matrix.
        \param  outMatrix
                Receives the current transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT transformation( McMat4f & outMatrix ) const; // LOCAL_GET

    /** Indicates if the node has a transformation matrix different from
        the identity matrix.
        \return 
                \c True if the current transformation is different from the identity matrix.
                \c False if the current transformation is the identity matrix.
    */
    bool hasTransformation() const; // LOCAL_GET

    /** Renders all attached nodes. 
        If a transformation has been definded for that node, the method
        will multiply the current model-view transformation with that
        local transformation matrix and afterwards call the \link 
        VsNode::render() render() \endlink method
        of all attached nodes. The order of rendering is thereby determined
        by the index of that node within the child node list. 
        If the rendering gets canceled the remaining unrendered child nodes 
        are skipped.
        After all child nodes have been rendered the original model-view
        transformation is restored.
        \return 
                The result of VsNode::render() calls of the child nodes 
                with the highest numerical value.
                See VsRenderResult for details.
    */
    virtual VsRenderResult render();
};


#endif

/// @}
