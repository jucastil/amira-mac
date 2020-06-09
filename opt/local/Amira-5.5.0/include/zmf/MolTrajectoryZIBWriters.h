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

/// @addtogroup zmf zmf
/// @{
#ifndef MolTrajectoryZIBWriters_H
#define MolTrajectoryZIBWriters_H

#include "SomeType.h"
#include "MolTrajectoryZIB.h"
#include "molecule/MtGroupAttribute.h"
#include "mclib/McAssert.h"

namespace MolTrajectoryZIBWriters 
{
    class ArraySizeWriter : public SomeTypeWriter
    {
        ///
        int mSize;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            zmfw.writeArraySize(mSize);
        }

    public:
        ///
        ArraySizeWriter(int size) : mSize(size) {}
    };

    class ComponentsWriter : public SomeTypeWriter
    {
        ///
        MolTopology * mTopology;
        
        ///
        McDArray<int> mComponents;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            MtGroup * g = mTopology->level(indexPath[end-3])->groups()[indexPath[end-2]];
            int i, size = g->size();
            mComponents.resize(size);
            for(i=0; i<size; i++) 
                mComponents[i] = mTopology->refToLinIndex((*g)[i]);
            
            zmfw.writeIntegerMatrix(1, &size, (int*)mComponents); 
        }
        
    public:
        ///
        ComponentsWriter(MolTopology * topo) : mTopology(topo) { mcassert(mTopology); }
    };


    class IntraLevelRangeFromWriter : public SomeTypeWriter
    {
        ///
        MolTopology * mTopology;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            MtIntraLevelRange * ilr = dynamic_cast<MtIntraLevelRange *>(mTopology->level(indexPath[end-3])->groups()[indexPath[end-2]]);
            mcassert(ilr);
            zmfw.writeInteger(mTopology->refToLinIndex(MtGroupRef(ilr->level, ilr->first)));
        }
        
    public:
        ///
        IntraLevelRangeFromWriter(MolTopology * topo) : mTopology(topo) { mcassert(mTopology); }
    };

    class IntraLevelRangeToWriter : public SomeTypeWriter
    {
        ///
        MolTopology * mTopology;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            MtIntraLevelRange * ilr = dynamic_cast<MtIntraLevelRange *>(mTopology->level(indexPath[end-3])->groups()[indexPath[end-2]]);
            mcassert(ilr);
            zmfw.writeInteger(mTopology->refToLinIndex(MtGroupRef(ilr->level, ilr->last)));
        }
        
    public:
        ///
        IntraLevelRangeToWriter(MolTopology * topo) : mTopology(topo) { mcassert(mTopology); }
    };


//     class TrajectoryCoordinatesWriter : public SomeTypeWriter
//     {
//         ///
//         MolTrajectory * mTrajectory;

//         ///
//         virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
//             int end = indexPath.size();
//             McHandle<Molecule> mol = new Molecule;
//             mTrajectory->getTimeStep(indexPath[end-2], mol);
            
//             int ext[2];
//             ext[0]=3; 
//             ext[1]=mol->positions().size();
            
//             zmfw.writeFloatMatrix(2, ext, (float*)(McVec3f*)mol->positions()); 
//         }
//     public:
//         ///
//         TrajectoryCoordinatesWriter(MolTrajectory * traj) : mTrajectory(traj) {}
//     };

    class FloatAttributeWriter : public SomeTypeWriter
    {
        ///
        const MtFloatAttribute * mAttribute;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeFloat(mAttribute->getValue(indexPath[end-2]));
        }

    public:
        ///
        FloatAttributeWriter(const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtFloatAttribute*>(att)) 
        {
            mcassert_debug(mAttribute);
        }
    };
    
    class IntegerAttributeWriter : public SomeTypeWriter
    {
        ///
        const MtIntegerAttribute * mAttribute;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeInteger(mAttribute->getValue(indexPath[end-2]));
        }

    public:
        ///
        IntegerAttributeWriter(const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtIntegerAttribute*>(att)) 
        {
            mcassert_debug(mAttribute);
        }
    };
    
    class StringAttributeWriter : public SomeTypeWriter
    {
        ///
        const MtStringAttribute * mAttribute;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeString(mAttribute->getValue(indexPath[end-2]));
        }

    public:
        ///
        StringAttributeWriter(const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtStringAttribute*>(att)) 
        {
            mcassert_debug(mAttribute);
        }
    };

    class FloatWriter : public SomeTypeWriter
    {
        ///
        float mValue;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            zmfw.writeFloat(mValue);
        }
        
    public:
        ///
        FloatWriter(float value) : mValue(value) {}
    };
    
    class IntegerWriter : public SomeTypeWriter
    {
        ///
        int mValue;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            zmfw.writeInteger(mValue);
        }
        
    public:
        ///
        IntegerWriter(int value) : mValue(value) {}
    };
    
    class StringWriter : public SomeTypeWriter
    {
        ///
        McString mValue;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            zmfw.writeString(mValue);
        }
        
    public:
        ///
        StringWriter(const char * value) : mValue(value) { mcassert(value); }
    };

    class NothingWriter: public SomeTypeWriter
    {
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {}
    };

    class GroupIdWriter : public SomeTypeWriter
    {
        ///
        int mCount;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            zmfw.writeInteger(++mCount);
        }
        
    public:
        ///
        GroupIdWriter() : mCount(-1) {}
    };

    class MultiFloatAttributeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtFloatAttribute *> mAttributes;
        
        ///
        McDArray<float> mValues;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            mValues.resize(size);
            for(i=0; i<size; i++) {
                mValues[i] = mAttributes[i]->getValue(indexPath[end-2]);
            }
            
            zmfw.writeFloatMatrix(1, &size, (float*)mValues); 
        }

    public:
        ///
        void add(const MtGroupAttribute * att) 
        {
            mAttributes.append(dynamic_cast<const MtFloatAttribute*>(att));
            mcassert_debug(mAttributes.last());
        }
    };

    class MultiIntegerAttributeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtIntegerAttribute *> mAttributes;
        
        ///
        McDArray<int> mValues;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            mValues.resize(size);
            for(i=0; i<size; i++) {
                mValues[i] = mAttributes[i]->getValue(indexPath[end-2]);
            }
            
            zmfw.writeIntegerMatrix(1, &size, (int*)mValues); 
        }

    public:
        ///
        void add(const MtGroupAttribute * att) 
        {
            mAttributes.append(dynamic_cast<const MtIntegerAttribute*>(att));
            mcassert_debug(mAttributes.last());
        }
    };

    class MultiStringAttributeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtStringAttribute *> mAttributes;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            for(i=0; i<size; i++) {
                zmfw.writeString(mAttributes[i]->getValue(indexPath[end-2]));
            }
        }

    public:
        ///
        void add(const MtGroupAttribute * att) 
        {
            mAttributes.append(dynamic_cast<const MtStringAttribute*>(att));
            mcassert_debug(mAttributes.last());
        }
    };

  class TBTreeNavigator : public McHandable
    {
        ///
        int mDepth, mCurrIx;

        ///
        McDArray<int> mIxPath;

        ///
        McDArray<McHandle<MolTrajectoryZIB::TBTreeNode> > mNodePath;

        ///
        McDArray<int> mTypeIds;
        
    public: 
        TBTreeNavigator(MolTrajectoryZIB::TBTreeNode * tree)
        {
            mNodePath.append(tree);
            while(mNodePath.last()->childs[0]->childs.size()){
                mNodePath.append(mNodePath.last()->childs[0]);
            }
            
            mDepth = mNodePath.size();
            
            mIxPath.resize(mDepth);
            mIxPath.fill(0);

            mCurrIx = 0;

            updateTypeIds();
        }

        
        int getValueIndex(int leafIx, int level)
        {
            if(leafIx == mCurrIx){
                // everything fine
            } else if(leafIx == mCurrIx+1) {
                mNodePath.pop_back();
                mIxPath.pop_back();
                mIxPath.last()++;
                while (mIxPath.size() > 1 && mIxPath.last() == mNodePath.last()->childs.size()){
                    mNodePath.pop_back();
                    mIxPath.pop_back();
                    mIxPath.last()++;
                } 

                mcassert(mIxPath.size() > 0);
                
                while(mIxPath.size() < mDepth){
                    mNodePath.append(mNodePath.last()->childs[mIxPath.last()]);
                    mIxPath.append(0);
                }

                mCurrIx = leafIx;

                updateTypeIds();
            } else {
                mcassert(0);
            }

            return mNodePath[level+1]->which;
        }

        void updateTypeIds(){
            int & ix = mIxPath.last();
            McDArray<McHandle<MolTrajectoryZIB::TBTreeNode> > & table = mNodePath.last()->childs;
            
            for(; ix<table.size(); ix++){
                if(mTypeIds.size() <= table[ix]->which){
                    mTypeIds.remax(table[ix]->which+1);
                    do {
                        mTypeIds.append(-1);
                    } while (mTypeIds.size() <= table[ix]->which);    
                }
                
                assert(table[ix]->childs.size() == 0);
                assert(mTypeIds[table[ix]->which] == -1);
                
                mTypeIds[table[ix]->which] = mCurrIx;
            }
        }
        
        ///
        int getTypeId(int ix) {
            return mTypeIds[ix];
        }
    };

    class TypeIdsWriter : public SomeTypeWriter
    {
        ///
        McHandle<TBTreeNavigator> mNavigator;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeInteger(mNavigator->getTypeId(indexPath[end-2]));
        }
        
    public:
        ///
        TypeIdsWriter(TBTreeNavigator * navi) : mNavigator(navi) { mcassert(mNavigator); }
    };
    
    class StringTBTreeWriter : public SomeTypeWriter
    {
        ///
        const MtStringAttribute * mAttribute;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;
        
        ///
        int mAttIx;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeString(mAttribute->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIx)));
        }
        
    public:
        /// 
        StringTBTreeWriter(TBTreeNavigator * navi, 
                           int attIx, 
                           const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtStringAttribute*>(att)), 
              mNavigator(navi),
              mAttIx(attIx)
                {
                    mcassert_debug(mAttribute && mNavigator);
                }
    };
    
    class FloatTBTreeWriter : public SomeTypeWriter
    {
        ///
        const MtFloatAttribute * mAttribute;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;
        
        ///
        int mAttIx;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeFloat(mAttribute->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIx)));
        }
        
    public:
        ///
        FloatTBTreeWriter(TBTreeNavigator* navi, int attIx, const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtFloatAttribute*>(att)), 
              mNavigator(navi),
              mAttIx(attIx)
        {
            mcassert_debug(mAttribute && mNavigator);
        }
    };

    class IntegerTBTreeWriter : public SomeTypeWriter
    {
        ///
        const MtIntegerAttribute * mAttribute;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;
        
        ///
        int mAttIx;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            zmfw.writeInteger(mAttribute->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIx)));
        }
        
    public:
        ///
        IntegerTBTreeWriter(TBTreeNavigator* navi, int attIx, const MtGroupAttribute * att) 
            : mAttribute(dynamic_cast<const MtIntegerAttribute*>(att)), 
              mNavigator(navi),
              mAttIx(attIx)
        {
            mcassert_debug(mAttribute && mNavigator);
        }
    };
    
    class MultiFloatTBTreeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtFloatAttribute *> mAttributes;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;

        ///
        McDArray<int> mAttIndices;

        ///
        McDArray<float> mValues;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            mValues.resize(size);
            for(i=0; i<size; i++) {
                mValues[i] = mAttributes[i]->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIndices[i]));
            }
            
            zmfw.writeFloatMatrix(1, &size, (float*)mValues); 
        }
        
    public:
        ///
        MultiFloatTBTreeWriter(TBTreeNavigator* navi) : mNavigator(navi) { mcassert_debug(mNavigator); }
        
        ///
        void add(const MtGroupAttribute * att, int attIx) 
        {
            mAttributes.append(dynamic_cast<const MtFloatAttribute*>(att));
            mcassert_debug(mAttributes.last());
            mAttIndices.append(attIx);
        }
    };

    class MultiIntegerTBTreeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtIntegerAttribute *> mAttributes;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;

        ///
        McDArray<int> mAttIndices;

        ///
        McDArray<int> mValues;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            mValues.resize(size);
            for(i=0; i<size; i++) {
                mValues[i] = mAttributes[i]->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIndices[i]));
            }
            
            zmfw.writeIntegerMatrix(1, &size, (int*)mValues); 
        }
        
    public:
        ///
        MultiIntegerTBTreeWriter(TBTreeNavigator* navi) : mNavigator(navi) { mcassert_debug(mNavigator); }
        
        ///
        void add(const MtGroupAttribute * att, int attIx) 
        {
            mAttributes.append(dynamic_cast<const MtIntegerAttribute*>(att));
            mcassert_debug(mAttributes.last());
            mAttIndices.append(attIx);
        }
    };

    class MultiStringTBTreeWriter : public SomeTypeWriter
    {
        ///
        McDArray<const MtStringAttribute *> mAttributes;
        
        ///
        McHandle<TBTreeNavigator> mNavigator;

        ///
        McDArray<int> mAttIndices;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();
            
            int i, size = mAttributes.size();
            for(i=0; i<size; i++) {
                zmfw.writeString(mAttributes[i]->getValueByIx(mNavigator->getValueIndex(indexPath[end-2], mAttIndices[i])));
            }
        }
        
    public:
        ///
        MultiStringTBTreeWriter(TBTreeNavigator* navi) : mNavigator(navi) { mcassert_debug(mNavigator); }
        
        ///
        void add(const MtGroupAttribute * att, int attIx) 
        {
            mAttributes.append(dynamic_cast<const MtStringAttribute*>(att));
            mcassert_debug(mAttributes.last());
            mAttIndices.append(attIx);
        }
    };

    class NonConstObservableNamesWriter : public SomeTypeWriter
    {
        ///
        MolObservables * mObs;

        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int i, count = indexPath.last()+1;
            for ( i=0; i<mObs->nObservables() && count; i++ ) {
                if ( !mObs->isConstObservable(i) ) {
                    --count;
                }
            }
            zmfw.writeString(mObs->observableName(i-1));
        }
    public:
        ///
        NonConstObservableNamesWriter(MolObservables * obs) : mObs(obs) { mcassert(mObs); }
    };
    
    class NonConstObservablesWriter : public SomeTypeWriter
    {
        ///
        McDArray<NonConstMolObservable *> mObs;

        ///
        McDArray<float> mObsPerStep;

        ///
        int mNumNonConstObservables;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int end = indexPath.size();

            int i;
            for ( i=0; i<mObs.size(); i++ ) {
                mObsPerStep[i] = mObs[i]->getFloatObsValue(indexPath[end-2]);
            }
            zmfw.writeFloatMatrix(1, &mNumNonConstObservables, (float*)mObsPerStep);
        }
    public:
        ///
        NonConstObservablesWriter(MolObservables * obs) 
        {
            mcassert(obs);
            obs->getNonConstObservables(mObs);
            mNumNonConstObservables = mObs.size();
            mObsPerStep.resize(mNumNonConstObservables);
        }
    };

    class MolCoordsWriter : public SomeTypeWriter
    {
        ///
        McHandle<Molecule> mMol;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int ext[2];
            
            ext[0]=3; 
            ext[1]=mMol->getTopology()->getNumAtoms();
            
            // "coordinates"
            zmfw.writeFloatMatrix(2, ext, (float*)(McVec3f*)mMol->positions()); 
        }
    public:
        ///
        MolCoordsWriter(Molecule * mol) 
            : mMol(mol)
        {
            mcassert(mMol);
        }
    };

    class MolTrajectoryCoordsWriter : public SomeTypeWriter
    {
        ///
        McHandle<MolTrajectory> mTrajectory;

        ///
        McHandle<Molecule> mMol;
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            mTrajectory->getTimeStep(indexPath[indexPath.size()-2], mMol);

            int ext[2];
            
            ext[0]=3; 
            ext[1]=mMol->getTopology()->getNumAtoms();
            
            // "coordinates"
            zmfw.writeFloatMatrix(2, ext, (float*)(McVec3f*)mMol->positions()); 
        }
    public:
        ///
        MolTrajectoryCoordsWriter(MolTrajectory * traj) 
            : mTrajectory(traj),
            mMol(new Molecule)
        {
            mcassert(mTrajectory);
        }
    };

    class FieldsWriter : public SomeTypeWriter
    {
        ///
        const McDArray<MolTrajectoryZIB::FieldRecord> & mFields;

        ///
        float mBB[6];
        
        ///
        int ext[2];
        
        ///
        virtual void doWrite(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) {
            int index = indexPath[indexPath.size()-2];
            
            zmfw.writeString(mFields[index].name);
            
            for(int j=0; j<3; j++) {
                mBB[j]   = mFields[index].bbox[(j)*2];
                mBB[j+3] = mFields[index].bbox[(j)*2+1];
            }
            zmfw.writeFloatMatrix(2, ext, mBB);
            
            zmfw.writeFloatMatrix(3, mFields[index].dims, mFields[index].data);
        }
        
    public:
        ///
        FieldsWriter(const McDArray<MolTrajectoryZIB::FieldRecord> & fields)
            : mFields(fields)
        {
            ext[0]=3;
            ext[1]=2;
        }

    };
};


#endif


/// @}
