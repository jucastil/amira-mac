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

/// @addtogroup molio molio
/// @{
#ifndef MOL_TRIPOS_H
#define MOL_TRIPOS_H

#include <molio/MolIOWinDLLApi.h>

#include <mclib/McProgressInterface.h>
#include <molecule/MolTrajectory.h>
class MolObject;

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

class Molecule;

/** reader and writer for tripos mol2 files 
**/

class MOLIO_API TriposIO {
    ostream * stream;
    McProgressInterface * workArea;
public:
    TriposIO(ostream * str = 0, McProgressInterface * wArea = 0);

    Molecule * readTriposMolecule(const char * fileName);
    bool readTriposBundle(const char * fileName,McDArray<McHandle<MolTrajectory> >& bundle);

    // calls the method below with the parameters "charge","type",0
    int writeTriposMolecule(const Molecule* M, const char* filename);
    int writeTriposBundle(const McDArray<MolObject*>& M, const char* filename);

    /** writes a molecule as a mol2 file. 
        \para[in] array of molobjects that will be written. Only the first coordinate set of each will be used
        \para[in] filename Filepath an name of mol2 file. No extension will be added.
        \para[in] chargeAttr Optional name of a float attribute containing partial charges (usually "charge")
                  if it is a null pointer, or if no such float attribute exists, no charges are written.
        \para[in] nameAttr Optional name of string attribute containing the atom name. 0 pointer: the element symbol will be used 
        \para[in] typeAttr Optional name of string attribute containing the atom type. 0 pointer: the element symbol will be used 
        */
    int write(const McDArray<MolObject*>& M, const char * filename, const char* chargeAttr=0,const char* nameAttr=0,const char* typeAttr = 0);

    /// return name of file format
    const char * getName() const { return "Tripos Mol2";}
};

#endif




/// @}
