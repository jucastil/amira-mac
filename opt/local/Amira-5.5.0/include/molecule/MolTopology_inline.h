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
int MolTopology::getNumLevels() const
{
    return levels.size();
}

const char* MolTopology::getLevelName(int levelIx) const 
{
    return levels[levelIx]->getName();
}

int MolTopology::getFixedGroupSize(int levelIx) const
{
    return levels[levelIx]->getFixedGroupSize();
}

/***********************************************************
        Methods to return level index of common levels
        If level is not found -1 will be returned 
*/
    
int MolTopology::getAtomLevelIx() const
{
    return 0;
}

int MolTopology::getBondLevelIx() const
{
    return 1;
}

int MolTopology::getResidueLevelIx() const
{
    return getLevelIx("residues");
}

int MolTopology::getStrandLevelIx() const
{
    return getLevelIx("strands");
}

int MolTopology::getSiteLevelIx() const
{
    return getLevelIx("sites");
}

int MolTopology::getSecondaryStructureLevelIx() const 
{
    return getLevelIx("secondary_structure");
}

int MolTopology::getChainLevelIx() const  
{
    return getLevelIx("chains");
}

int MolTopology::getAngleLevelIx() const 
{
    return getLevelIx("angles");
}

int MolTopology::getDihedralLevelIx() const
{
    return getLevelIx("dihedrals");
}

/***********************************************************
                     Groups
***********************************************************/

/***********************************************************
        Methods to request the number of groups 
        of a level 
*/
    
int MolTopology::getNumAtoms() const
{
    return levels[getAtomLevelIx()]->getNumGroups();
}

int MolTopology::getNumBonds() const
{
    return levels[getBondLevelIx()]->getNumGroups();
}

int MolTopology::getNumGroups(int levelIx) const
{
    return levels[levelIx]->getNumGroups();
}


/***********************************************************
        Methods to access group content 
*/

int MolTopology::getGroupSize(int levelIx,int groupIx) const
{
    return levels[levelIx]->getGroupSize(groupIx);
}

void MolTopology::resizeGroup(int levelIx,int groupIx, int size)
{
    levels[levelIx]->resizeGroup(groupIx,size);
}

int MolTopology::getGroupElement(int levelIx,int groupIx, int elementIx) const
{
    return levels[levelIx]->getGroupElement(groupIx,elementIx);
}

void MolTopology::getGroupElements(int levelIx,int groupIx,McDArray<int>& list) const
{
    levels[levelIx]->getGroupElements(groupIx,list);
}

void MolTopology::removeGroupElement(int levelIx,int groupIx, int elIx)
{
    levels[levelIx]->removeGroupElement(groupIx,elIx);
}

void MolTopology::addGroupElement(int levelIx,int groupIx, int elIx)
{
    levels[levelIx]->addGroupElement(groupIx,elIx);
}

void MolTopology::setGroupElement(int levelIx,int groupIx, int entryIx, int elIx)
{
    levels[levelIx]->setGroupElement(groupIx,entryIx,elIx);
}

void MolTopology::setGroupElements(int levelIx,int groupIx, const McDArray<int>& elements)
{
    levels[levelIx]->setGroupElements(groupIx,elements);
}

/***********************************************************
         Names 
*/

int MolTopology::findGroup(int levelIx,const char *name)  const
{
    return levels[levelIx]->findGroup(name);
}

int MolTopology::findGroupBackward(int levelIx,const char *name) const
{
    return levels[levelIx]->findGroupBackward(name);
}

const char* MolTopology::getGroupName(int levelIx,int ix) const
{
    return levels[levelIx]->getGroupName(ix);
}

bool MolTopology::hasGroupNames(int levelIx) const
{ 
    return levels[levelIx]->hasGroupNames();
}

void MolTopology::setGroupName(int levelIx,int ix, const char * name)
{
    levels[levelIx]->setGroupName(ix,name);
}

/***********************************************************
                     Attributes
***********************************************************/

/***********************************************************
         Information 
*/

/// Return number of Attributes
int MolTopology::getNumAttributes(int levelIx) const
{
    return levels[levelIx]->getNumAttributes();
}

/// Returns name of ix'th attribute
const char * MolTopology::getAttributeName(int levelIx, int attrIx) const
{
    return levels[levelIx]->getAttributeName(attrIx);
}


/***********************************************************
         Getting 
*/

int MolTopology::getAttributeIx(int levelIx,const char *name) const
{
    return levels[levelIx]->getAttributeIx(name);
}

MtGroupAttribute* MolTopology::getAttribute(int levelIx, int attrIx)
{
    return levels[levelIx]->getAttribute(attrIx);
}

const MtGroupAttribute* MolTopology::getAttribute(int levelIx, int attrIx) const
{
    return levels[levelIx]->getAttribute(attrIx);
}

MtGroupAttribute* MolTopology::getAttribute(int levelIx,const char *name) 
{
    return levels[levelIx]->getAttribute(name);}

const MtGroupAttribute* MolTopology::getAttribute(int levelIx,const char *name) const
{
    return levels[levelIx]->getAttribute(name);
}

MtIntegerAttribute* MolTopology::getIntegerAttribute(int levelIx, int attrIx)
{
    return levels[levelIx]->getIntegerAttribute(attrIx);
}

const MtIntegerAttribute* MolTopology::getIntegerAttribute(int levelIx, int attrIx) const
{
    return levels[levelIx]->getIntegerAttribute(attrIx);
}

MtFloatAttribute* MolTopology::getFloatAttribute(int levelIx, int attrIx)
{
    return levels[levelIx]->getFloatAttribute(attrIx);
}

const MtFloatAttribute* MolTopology::getFloatAttribute(int levelIx, int attrIx) const
{
    return levels[levelIx]->getFloatAttribute(attrIx);
}

MtStringAttribute* MolTopology::getStringAttribute(int levelIx, int attrIx)
{
    return levels[levelIx]->getStringAttribute(attrIx);
}

const MtStringAttribute* MolTopology::getStringAttribute(int levelIx, int attrIx) const
{
    return levels[levelIx]->getStringAttribute(attrIx);
}

MtIntegerAttribute* MolTopology::getIntegerAttribute(int levelIx,const char* name)
{
    return levels[levelIx]->getIntegerAttribute(name);
}

const MtIntegerAttribute* MolTopology::getIntegerAttribute(int levelIx,const char* name) const
{
    return levels[levelIx]->getIntegerAttribute(name);
}

MtFloatAttribute* MolTopology::getFloatAttribute(int levelIx,const char* name)
{
    return levels[levelIx]->getFloatAttribute(name);
}

const MtFloatAttribute* MolTopology::getFloatAttribute(int levelIx,const char* name) const
{
    return levels[levelIx]->getFloatAttribute(name);
}

MtStringAttribute* MolTopology::getStringAttribute(int levelIx,const char* name)
{
    return levels[levelIx]->getStringAttribute(name);
}

const MtStringAttribute* MolTopology::getStringAttribute(int levelIx,const char* name) const
{
    return levels[levelIx]->getStringAttribute(name);
}

/// @}
