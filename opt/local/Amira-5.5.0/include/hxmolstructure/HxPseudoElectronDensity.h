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

/// @addtogroup hxmolstructure hxmolstructure
/// @{
#ifndef HX_PSEUDO_ELECTRON_DENSITY_H
#define HX_PSEUDO_ELECTRON_DENSITY_H

#include <mclib/McVec3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortSeparator.h>

#include "HxMolStructureWinDLLApi.h"

class HxUniformScalarField3;
class HxMolecule;
class Molecule;
class MolTopology;

/**
 * This module helps representing the electronal-density of molecules,
 * recursivly overlapping the density of each atom. All density
 * values are saved in a scalarfield. This Scalarfield, which 
 * latticecoords are set to the density value, is generated
 * depending on the moleculesize and the overgiven voxelsize. 
 * The value of each coord then indicates the density at this
 * coordinate. The densityvalue depends on the atomsize (its radius), the 
 * overgiven downfactor and the distance to the atomcenter. The
 * value is beeing calculated with the Gaussian error distribution 
 * function. The options has following effects:
 *	- voxelsize: stimulates the precision. Lower value will raise the
 *		     degree of accuracy (more memory needed).
 *	- minvalue: specify the smalles value to be considered in the
 *		    gaussian function. Lower value will raise the degree
 *		    of accuracy (more CPU and memory needed).
 *	- downfactor: stimulates the slope of the gaussian curve. No affect
 *
 * Choosing your values will affect the Cuttingdistance that is needed
 * for the implementation on the algorithm.
 */


class HXMOLSTRUCTURE_API HxPseudoElectronDensity : public HxCompModule {
    HX_HEADER(HxPseudoElectronDensity); 

public:
    ///
    HxPortFloatSlider portVoxelsize;
    ///
    HxPortFloatSlider portDownFactor;
    ///
    HxPortFloatSlider portMinValue;
    ///
    HxPortSeparator   portSep1;
    ///
    HxPortDoIt        portAction;
    ///
    HxPortInfo        portDimsInfo;
    ///
    HxPortInfo	      portCuttingDistance2Info;
    
protected:
    /// The main Scalarfield, where all values are saved in
    HxUniformScalarField3 *sField;
    
    /// Length of a step inside the scalarfield
    float voxelSize;
    /// Coordinates of the 6 vertex of the Boundingbox (Xmin,Xmax,Ymin...)
    float bbox[6];
    /// Number of voxelsize steps in the boundingbox for each axis (X,Y,Z)
    int dims[3];
    /// Factor or the gradient for the Gaussian curve (((1/sqrt(2*PI))*e^(-Downfactor*distance^2))
    float downFactor;
    /// Smallest set value to be still consired in the gaussian curve
    float minvalue;    
    /// Biggest radius appearing in the molecule
    float maxRadius;
    
public:
    /// Constructor.
    HxPseudoElectronDensity();

    /// Update GUI.
    void update();
    /// Check ports and trigger computation.
    void compute();
    
protected:
    /// collects all values from the ports and calculates the new cuttingdistance
    void updateAllValues();
    /// Depending on the given radius, calculates the new cuttingdistance^2.
    float calcCuttingdistance2(float atomRadius);
    /// Initialize a new scalarfield with the dimensions and coordinates of the boundingbox
    void createScalarField(HxMolecule * hxmol);
    /// Recursive algorithm generating all needed datas for each atom of the molecule
    int handleAllAtoms();
    /// Creats the boundingbox, by adding to the molecule bbox the needed cuttingdistance
    void handleAtom(const McVec3f & atomPos, const float atomRadius, const int atomicNumber);
};

#endif



/// @}
