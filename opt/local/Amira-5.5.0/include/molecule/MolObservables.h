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
#ifndef MOL_OBSERVABLES_H
#define MOL_OBSERVABLES_H

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <mclib/McDArray.h>

#include "MolObservable.h"
#include "MolObservableProvider.h"

#include "MoleculeWinDLLApi.h"

/** Molecule Observables */
class MOLECULE_API MolObservables : virtual public McHandable 
{
public:
    /// Constructor.
    MolObservables();

    /// Return overall (const and non-const) number of observables.
    int nObservables() const { return observables.size(); }
    /// Return number of const observables.
    int nConstObservables();
    /// Fill array @c molObs with non-const observables.
    void getNonConstObservables(McDArray<NonConstMolObservable *> & molObs);
    /// Return number of non-const observables.
    int nNonConstObservables();
    /// Returns -1 if an observable @c name does not exist.
    int observableIndex(const char * name) const;
    /// Returns -1 if an observable @c name does not exist.
    const char * observableName(int idx) const;
    /// Return pointer to observable with index @c idx.
    MolObservable * observable(int idx); 
    /// Return pointer to observable with name @c name.
    MolObservable * observable(const char * name);
    /// Set value for observable with name @c name. Create new
    /// observable, if observable does not yet exists.
    void setObservableValue(const char * name, int value, int idx=-1);
    void setObservableValue(const char * name, float value, int idx=-1);
    /// Set value for observable with index @c obsIdx. It is assumed
    /// that an observable with this index already exists.
    void setObservableValue(int obsIdx, int value, int idx=-1);
    void setObservableValue(int obsIdx, float value, int idx=-1);
    /// Set values for observable with name @c name. Create new
    /// observable, if observable does not yet exists.
    void setObservableValues(const char * name, McDArray<int> & values);
    void setObservableValues(const char * name, McDArray<float> & values);
    /// Set values for observable with index @c obsIdx. It is assumed
    /// that an observable with this index already exists.
    void setObservableValues(int obsIdx, McDArray<int> & values);
    void setObservableValues(int obsIdx, McDArray<float> & values);
    /// Append observable @c obs to observable with index @c idx.
    void appendObservable(int primaryObIdx, MolObservable * secondaryOb);
    
    /// Returns true, if observable with index @c index is an integer
    /// observable (const or non-const).
    bool isIntObservable(int idx);
    /// Returns true, if observable with index @c index is a const
    /// observable (int or float).
    bool isConstObservable(int idx);
    /// Fill @c names with list of observable names.
    void getListOfObservableNames(McDArray<McString> & names);
    
    /// Set number of time steps of trajectory and resize observables.
    void setNumTimeSteps(int newNumTimeSteps);
    
    /// Set global weight to be multiplied with all timestep weights.
    void setGlobalWeight(float w) { theGlobalWeight=w; }
    /// Return global weight.
    float globalWeight() const { return theGlobalWeight; }
    /// Return weight of @c index.
    float weight(int idx);
    /// Compute normalized weights (single weight divided by sum of
    /// weights), i.e. normalized sum of weights should be 1.0.
    void getNormalizedStepWeights(McDArray<float> & weights);
    
    enum ObservableType { INT_OBS, CONST_INT_OBS, FLOAT_OBS, CONST_FLOAT_OBS };
    
    /// Add observable name to list of observableNames. The data is
    /// assumed to get provided by one of the molecule observable
    /// providers.
    void addObservableWithoutData(const char * name);
    /// Add molecule observable data provider.
    void addMolObsProvider(MolObservableProvider * provider);

    /// Return observable type.
    static int getObservableType(MolObservable * ob);
    /// Replace observable @c ob by new observable of type
    /// @c replaceObsType.
    static void replaceObservable(McHandle<MolObservable> & ob, 
                                  int replaceObsType);
    /// Append observable @c obs to observable with index @c idx.
    static void appendObservable(McHandle<MolObservable> & primaryOb, 
                                 MolObservable * secondaryOb);
    /// add a new Obersvable. Observable will be resized automatically
    int addObservable(const char* name,MolObservable* obs);
private:
    int numTimeSteps;
    McDArray<McHandle<MolObservable> > observables;
    McDArray<McString> observableNames;
    McDArray<McHandle<MolObservableProvider> > molObsProvider;
    float theGlobalWeight;
};

#endif

/// @}
