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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef HIERARCHICALLABELS_H
#define HIERARCHICALLABELS_H

/** This class represents a hierarchical label tree. Each node in the tree has a name, id and a color.
 *  The class synchonises with a HxParamBundle object. Changes in this class are applied to the
 *  HxParamBundle. After a change in the parameter bundle (e.g. by the parameter editor) \a update needs to be
 *  called on this class.
 *  The label tree has exactly one root label, all other labels are direct or indirect children of this label.
 *  The name of the root label is the same as the name of the labelGroup and the name of the parameter bundle.
 *  The id of the root label is also the id of the default label value and equals 0 (zero).
 */

#include "hxspatialgraphAPI.h"

#include <mclib/McString.h>
#include <mclib/McColor.h>
#include <Inventor/SbColor.h>
#include <mclib/McHashTable.h>

class HxParamBundle;

static const int RootLabelValue = 0;
static const float RootLabelColor[3] = {0.0f, 0.0f, 0.0f};

class HXSPATIALGRAPH_API HierarchicalLabels {
public:
    HierarchicalLabels(HxParamBundle* pb);
    ~HierarchicalLabels();

    /// Get the name of the label group
    const char* getLabelGroupName() const;

    /// Get the id of the root label (should be zero)
    bool getRootLabel(int& id) const ;

    /// Get the total number of labels
    int getNumLabels() const;

    /// Get the name of the label with id \a id
    bool getLabelName(const int id, McString& name) const;

    /// Get the color of the label with id \a id
    bool getLabelColor(const int id, SbColor& color) const;

    int getMaxLabelId() const;

    /// Adds a label with name \a name and color \color as a child of \a parentId and returns the id of the new label
    int addLabel(const int parentId, const char* name, const SbColor color);

    void update();

    /// get number of childs of the label with \a parentId
    int getNumLabels(int parentId) const;

    /// get \a iChild of the label with \a parentId
    int getChildId(int parentId, int iChild) const;

    /// get all label ids of all children of the label with id \a parentId
    McDArray<int> getChildIds(int parentId) const;

    void setLabelColor(int id, const McColor& color);

    void setLabelName(int id, const McString& name);

    /// removes all children of the label id \a parentId
    /// exclusive the label itself
    /// if no parentId has been specified, the rootLabelId will be used
    void removeChildLabels(const int parentId = -1);

    /// removes all children of the label with id \a parentId
    /// inclusive the label itself
    /// returns an array of labels ids which have been deleted
    void removeLabel(int id, McDArray<int> &deletedLabels);

    /// Returns whether there exists a label with name \a name anywhere in the tree.
    bool hasLabel(const McString& name) const;

    /// Return label id of label with name \a name (-1 if it does not exist).
    int getLabelIdFromName(const McString& name) const;

    /// Returns whether the label with id \a ChildId is a direct child of \a parentId
    bool isDirectChild(const int childId, const int parentId);

    /// Returns whether the label with id \a childId in the subtree rooted by \a parentId
    /// Returns false when childId == parentId
    bool isChild(const int childId, const int parentId);

    /// Swap label \a srcLblId and all its children with label \a dstLblId and all its children
    void relocateLabel(int srcLblId, int dstLblId);

    /// Returns whether this label should be displayed expanded in a tree view.
    bool isLabelExpanded(int id) const;

    /// Sets whether this label should be displayed expanded in a tree view.
    void setLabelExpanded(int id,bool state);

    /// Creates a copy of itself and inserts it to \a parameters.
    HierarchicalLabels* duplicateAndInsertToParamBundle(HxParamBundle& parameters);

    // check whether every bundle in the tree has at least a color and an id parameter
    static bool isConsistent(HxParamBundle* pb);

protected:
    HxParamBundle* mRootBundle;

    HxParamBundle* getLabelBundle(HxParamBundle* bundle, const int id) const;
    int getNumLabels(HxParamBundle* pb) const;
    int getMaxLabelId(HxParamBundle* pb) const;

    int getLabelId(const HxParamBundle* pb) const;
    int getParentId(const int childId) const;

    /// Returns whether there exists a label with name \a name anywhere in the tree rooted by \a pb.
    bool hasLabel(const HxParamBundle* pb, const McString& name) const;

    /// Returns the label id of label with name \a name anywhere in the tree rooted by \a pb.
    /// Returns -1 if there is no such label.
    int findLabel(const HxParamBundle* pb, const McString& name) const;

    /** Returns an array of label \a ids of all children of the param bundle \a pb
        inclusive its own label id.
    */
    void gatherSubBundleIds(HxParamBundle* pb, McDArray<int> &ids) const;

};

#endif

/// @}
