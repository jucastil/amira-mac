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

/// @addtogroup molecule molecule
/// @{
int MtGroupingLevel::getGroupSize(int groupIx) const
{
    return theGroups[groupIx]->size();
}
int MtGroupingLevel::getReferenceLevelIx() const
{
    // this is a legacy hack - as long as not all modules use addLevel with a referencing level
    // we need to look it up in the first group
    if (theGroups.size()>0) {
        if (theGroups[0]->size()>0)
            return (*theGroups[0])[0].level;
    }
    return referenceLevelIx;
}

bool MtGroupingLevel::hasFixedGroups() const
{
    return (groupSize>=0);
}

const char* MtGroupingLevel::getName() const {
    return name;
}

int MtGroupingLevel::getFixedGroupSize() const
{
    return groupSize;
}

    /***********************************************************
                     Groups
     ***********************************************************/

void MtGroupingLevel::remax(int size) 
{
    theGroups.remax(size);
    for (int i=0;i<theAttributes.size();i++)
        theAttributes[i]->remax(size);
}


    /***********************************************************
        Methods to access group content */


void MtGroupingLevel::resizeGroup(int groupIx, int size)
{
    MtDynamicGroup* d = dynamic_cast<MtDynamicGroup*>(theGroups[groupIx]);
    assert(d && (groupSize<0 || size == groupSize));
    d->resize(size);
}

int MtGroupingLevel::getGroupElement(int groupIx, int elementIx) const
{
    return (*((theGroups)[groupIx]))[elementIx].ix;
}

void MtGroupingLevel::getGroupElements(int groupIx,McDArray<int>& list) const
{
    list.clear();
    MtGroup* G = theGroups[groupIx];
    for (int i=0;i<G->size();i++) 
        list.append((*G)[i].ix);
}

void MtGroupingLevel::addGroupElement(int groupIx, int elIx)
{
    assert(!hasFixedGroups());
    makeGroupDynamic(groupIx);
    MtDynamicGroup* d = dynamic_cast<MtDynamicGroup*>(theGroups[groupIx]);
    d->addElement(MtGroupRef(getReferenceLevelIx(),elIx));
}

void MtGroupingLevel::removeGroupElement(int groupIx, int elIx)
{
    assert(!hasFixedGroups());
    makeGroupDynamic(groupIx);
    MtDynamicGroup* d = dynamic_cast<MtDynamicGroup*>(theGroups[groupIx]);
    d->removeElement(elIx);
}

void MtGroupingLevel::setGroupElement(int groupIx, int entryIx, int elIx)
{
    theGroups[groupIx]->setElement(entryIx,MtGroupRef(getReferenceLevelIx(),elIx));
}

void MtGroupingLevel::setGroupElements(int groupIx, const McDArray<int>& elements)
{
    int refLevel = getReferenceLevelIx();
    if (dynamic_cast<MtIntraLevelRange*>(theGroups[groupIx]))
        makeGroupDynamic(groupIx);
    MtGroup * d = theGroups[groupIx];
    if (d->size()!=elements.size())
        resizeGroup(groupIx,elements.size());
    for (int i=0;i<elements.size();i++) 
        d->setElement(i,MtGroupRef(refLevel,elements[i]));
}

void MtGroupingLevel::setGroupElements(int groupIx, int numElements,const int* elements)
{
    int refLevel = getReferenceLevelIx();
    if (dynamic_cast<MtIntraLevelRange*>(theGroups[groupIx]))
        makeGroupDynamic(groupIx);
    MtGroup * d = theGroups[groupIx];
    if (d->size()!=numElements)
        resizeGroup(groupIx,numElements);
    for (int i=0;i<numElements;i++) 
        d->setElement(i,MtGroupRef(refLevel,elements[i]));
}

int MtGroupingLevel::getNumGroups() const
{
    return theGroups.size();
}

/***********************************************************
                     Attributes
***********************************************************/

/***********************************************************
         Information
*/

/// Return number of Attributes
int MtGroupingLevel::getNumAttributes() const
{
    return theAttributes.size();
}

const char * MtGroupingLevel::getAttributeName(int attrIx) const
{
    return theAttributes[attrIx]->getName();
}

int MtGroupingLevel::getAttributeIx(const char *name) const
{
    for (int i=0;i<getNumAttributes();i++) 
        if (!strcmp(theAttributes[i]->getName(),name))
            return i;
    return -1;
}

MtGroupAttribute* MtGroupingLevel::getAttribute(const char *name) 
{
    int ix = getAttributeIx(name);
    if (ix>=0)
		return getAttribute(ix);
// replaced following line by previous one to avoid problems with MtSelfSubstitutingAttributes
//        return theAttributes[ix];
    return 0;
}

const MtGroupAttribute* MtGroupingLevel::getAttribute(const char *name) const
{
    int ix = getAttributeIx(name);
    if (ix>=0)
		return getAttribute(ix);
// replaced following line by previous one to avoid problems with MtSelfSubstitutingAttributes
//        return theAttributes[ix];
    return 0;
}

MtIntegerAttribute* MtGroupingLevel::getIntegerAttribute(int attrIx)
{
    return dynamic_cast<MtIntegerAttribute*>(getAttribute(attrIx));
}

const MtIntegerAttribute* MtGroupingLevel::getIntegerAttribute(int attrIx) const
{
    return dynamic_cast<const MtIntegerAttribute*>(getAttribute(attrIx));
}

MtFloatAttribute* MtGroupingLevel::getFloatAttribute(int attrIx)
{
    return dynamic_cast<MtFloatAttribute*>(getAttribute(attrIx));
}

const MtFloatAttribute* MtGroupingLevel::getFloatAttribute(int attrIx) const
{
    return dynamic_cast<const MtFloatAttribute*>((MtGroupAttribute*)getAttribute(attrIx));
}

MtStringAttribute* MtGroupingLevel::getStringAttribute(int attrIx)
{
    return dynamic_cast<MtStringAttribute*>(getAttribute(attrIx));
}

const MtStringAttribute* MtGroupingLevel::getStringAttribute(int attrIx) const
{
    return dynamic_cast<const MtStringAttribute*>(getAttribute(attrIx));
}

MtIntegerAttribute* MtGroupingLevel::getIntegerAttribute(const char* name)
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<MtIntegerAttribute*>(getAttribute(ix));
}

const MtIntegerAttribute* MtGroupingLevel::getIntegerAttribute(const char* name) const
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<const MtIntegerAttribute*>(getAttribute(ix));
}

MtFloatAttribute* MtGroupingLevel::getFloatAttribute(const char* name)
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<MtFloatAttribute*>(getAttribute(ix));
}

const MtFloatAttribute* MtGroupingLevel::getFloatAttribute(const char* name) const
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<const MtFloatAttribute*>(getAttribute(ix));
}

MtStringAttribute* MtGroupingLevel::getStringAttribute(const char* name)
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<MtStringAttribute*>(getAttribute(ix));
}

const MtStringAttribute* MtGroupingLevel::getStringAttribute(const char* name) const
{
    int ix = getAttributeIx(name); 
    if (ix<0) return 0;
    return dynamic_cast<const MtStringAttribute*>(getAttribute(ix));
}


/// @}
