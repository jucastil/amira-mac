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

/// @addtogroup amfio amfio
/// @{
#ifndef AMFIO_AMFREADNOTIFIER_H
#define AMFIO_AMFREADNOTIFIER_H

#include "AMFIOWinDLLApi.h"

template <class T> class McDArray;
class MolTrajectory;
class Molecule;
class RegularGrid3f1;

/** \brief Notifies user when reading instances of certain data-structures 

     AMFReadNotifer is a simple event handler which is supplied 
     as an argument to the AMFReader. It has two event notification types:
     
     -notifyStart<Element>
     -notifyEnd<Element>
     
     NotifyStart<Element> is called whenever a new instance of <element> is encountered.
     Based on the name attribute, the user can decide whether he wants to skip this element
     (by returning false) or go on with the reading (returning true).
     
     NotifyEnd<Element> is called when an instance of <element> was entirely read.
     It passes on the read data, which is allocated on the heap. Deleting this data
     is the responsibility of the user. However, if the functions are not overloaded,
     the data is deallocated immidiately.
     
	 Example of use:
	 \code
	 class MyAMFReadNotifier : public AMFReadNotifier {
	 	virtual bool notifyStartMolecule(const char* name) {return true;}
	 	virtual bool notifyEndMolecule(Molecule* mol) {doSomethingWith(mol);}
     };
     \endcode
     
     */

class AMFIO_API AMFReadNotifier {
public:
    virtual ~AMFReadNotifier() {}
    /** If the Molecule is part of a Bundle, this function will also be calle,
        to allow the user to skip certain items of the bundle.
        In any way, notifyEndMolecule will not be called in this case */
    virtual bool notifyStartMolecule(const char* name) {
        return false;
    }
    /** If the Trajectory is part of a Bundle, this function will also be called, 
        to allow the user to skip certain items of the bundle.
        In any way, notifyEndTrajectory will not be called in this case */
    virtual bool notifyStartMolTrajectory(const char* name) {
        return false;
    }
   	///
    virtual bool notifyStartMolTrajectoryBundle(const char* name) {
        return false;
    }
	///
    virtual bool notifyStartMoleculeBundle(const char* name) {
        return false;
    }
	///
    virtual void notifyEndMolecule(Molecule* mol);
    ///
    virtual void notifyEndMolTrajectory(MolTrajectory* mol);
    ///
    virtual void notifyEndMolTrajectoryBundle(McDArray<MolTrajectory*>& mol);
    ///
    virtual void notifyEndMoleculeBundle(McDArray<Molecule*>& mol);
	///
    virtual bool notifyStartScalarField3(const char* name) {
        return false;
    }
    virtual void notifyEndScalarField3(RegularGrid3f1* g);
	///
};

#endif


/// @}
