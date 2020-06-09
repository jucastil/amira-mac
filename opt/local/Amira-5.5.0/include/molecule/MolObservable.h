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
#ifndef MOL_OBSERVABLE_H
#define MOL_OBSERVABLE_H

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <mclib/McDArray.h>

#include "MoleculeWinDLLApi.h"

class MOLECULE_API MolObservable : public McHandable{
public:
    float getFloatObsValue(int idx=0) { return doGetFloatObsValue(idx); }
    int   getIntObsValue(int idx=0) { return doGetIntObsValue(idx); }
    void  getFloatObsValues(McDArray<float> & values) { 
        doGetFloatObsValues(values); }
    void  getIntObsValues(McDArray<int> & values) { 
        doGetIntObsValues(values); }
    
    void  resize(int size) { doResize(size); }
    int   getSize() { return numObservableValues; }
    
    MolObservable * duplicate(McDArray<int> * selection=0) {
        return doDuplicate(selection); }

protected:
    int numObservableValues;

private:
    virtual float doGetFloatObsValue(int idx) = 0;
    virtual int   doGetIntObsValue(int idx) = 0;
    virtual void  doGetFloatObsValues(McDArray<float> & values) = 0;
    virtual void  doGetIntObsValues(McDArray<int> & values) = 0;
        
    virtual void  doResize(int newSize) { numObservableValues = newSize; }
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection) = 0;
};

class MOLECULE_API ConstMolObservable : public MolObservable {
public:
    void  setFloatObsValue(float value) { doSetFloatObsValue(value); }
    void  setIntObsValue(int value) { doSetIntObsValue(value); }
    
    void resize(int size) { doResize(size); }
    
private:
    virtual void  doSetFloatObsValue(float value) = 0;
    virtual void  doSetIntObsValue(int value) = 0;
    
    virtual void  doResize(int newSize) { numObservableValues = newSize; }

    virtual MolObservable * doDuplicate(McDArray<int> * selection) = 0;
};

class MOLECULE_API ConstIntMolObservable : public ConstMolObservable {
public:
    ConstIntMolObservable(int numValues);
    
private:
    int value;       
    
private:
    virtual float doGetFloatObsValue(int idx);
    virtual int   doGetIntObsValue(int idx);
    virtual void  doGetFloatObsValues(McDArray<float> & values);
    virtual void  doGetIntObsValues(McDArray<int> & values);

    virtual void  doSetFloatObsValue(float value);
    virtual void  doSetIntObsValue(int value);
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection);
};

class MOLECULE_API ConstFloatMolObservable : public ConstMolObservable {
public:
    ConstFloatMolObservable(int numValues);
    
private:
    float value;
    
private:
    virtual float doGetFloatObsValue(int idx);
    virtual int   doGetIntObsValue(int idx);
    virtual void  doGetFloatObsValues(McDArray<float> & values);
    virtual void  doGetIntObsValues(McDArray<int> & values);

    virtual void  doSetFloatObsValue(float value);
    virtual void  doSetIntObsValue(int value);
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection);
};

class MOLECULE_API NonConstMolObservable : public MolObservable {
public:
    void  setFloatObsValue(int idx, float value) { 
        doSetFloatObsValue(idx, value); }
    void  setIntObsValue(int idx, int value) { 
        doSetIntObsValue(idx, value); }
    void  setFloatObsValues(McDArray<float> & values) { 
        doSetFloatObsValues(values); }
    void  setIntObsValues(McDArray<int> & values) { 
        doSetIntObsValues(values); }
    
    void resize(int size) { doResize(size); }

private:
    virtual void  doSetFloatObsValue(int idx, float value) = 0;
    virtual void  doSetIntObsValue(int idx, int value) = 0;
    virtual void  doSetFloatObsValues(McDArray<float> & values) = 0;
    virtual void  doSetIntObsValues(McDArray<int> & values) = 0;

    virtual void  doResize(int newSize) = 0;
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection) = 0;
};

class MOLECULE_API IntMolObservable : public NonConstMolObservable {
public:
    IntMolObservable(int numValues);
    void appendValues(McDArray<int> & values);

    int getValue(int ix) const { return values[ix]; }
    void setValue(int ix,int val) { values[ix]=val;}
    McDArray<int> values;

private:


    virtual float doGetFloatObsValue(int idx);
    virtual int   doGetIntObsValue(int idx);
    virtual void  doGetFloatObsValues(McDArray<float> & values);
    virtual void  doGetIntObsValues(McDArray<int> & values);

    virtual void  doSetFloatObsValue(int idx, float value);
    virtual void  doSetIntObsValue(int idx, int value);
    virtual void  doSetFloatObsValues(McDArray<float> & values);
    virtual void  doSetIntObsValues(McDArray<int> & values);
        
    virtual void  doResize(int size);
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection);
};
    
class MOLECULE_API FloatMolObservable : public NonConstMolObservable {
public:
    FloatMolObservable(int numValues);
    void appendValues(McDArray<float> & values);

    float getValue(int ix) const { return values[ix]; }
    void setValue(int ix,float val) { values[ix]=val;}
    McDArray<float> values;

private:
    

    virtual float doGetFloatObsValue(int idx);
    virtual int   doGetIntObsValue(int idx);
    virtual void  doGetFloatObsValues(McDArray<float> & values);
    virtual void  doGetIntObsValues(McDArray<int> & values);

    virtual void  doSetFloatObsValue(int idx, float value);
    virtual void  doSetIntObsValue(int idx, int value);
    virtual void  doSetFloatObsValues(McDArray<float> & values);
    virtual void  doSetIntObsValues(McDArray<int> & values);

    virtual void  doResize(int size);
    
    virtual MolObservable * doDuplicate(McDArray<int> * selection);
};

#endif

/// @}
