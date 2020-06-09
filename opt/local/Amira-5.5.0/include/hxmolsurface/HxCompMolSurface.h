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

/// @addtogroup hxmolsurface hxmolsurface
/// @{
#ifndef HX_COMPMOLSURFACE_H
#define HX_COMPMOLSURFACE_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortText.h>

#include <hxmolecule/HxMolecule.h>
#include <hxmolecule/MolFilter.h>

#include <molsurface/CompMolSurface.h>
#include "HxMolSurfaceWinDLLApi.h"

/** This module works as a wrapper of the @c CompMolSurface class that
    allows you to compute the van der Waals, the solvent accessible,
    and the solvent excluded surface of up to two molecules. The
    module produces an object of class @c HxMolSurface which can be 
    viewed with the @c HxMolSurfaceView. */

class HXMOLSURFACE_API HxCompMolSurface : public HxCompModule {

    HX_HEADER(HxCompMolSurface);

public:
    /// Second connection to a molecule for which the surface should
    /// be computed.
    HxConnection portMolecule2;
    /// Filter for first molecule to allow the computation of a
    /// selected set of atoms.
    MolFilter filter;
    /// Filter for second molecule.
    MolFilter filter2;

    /// Surface type.
    HxPortRadioBox portSurfaceType;
    /// Quality: correct, possibly incomplete.
    HxPortRadioBox portQuality;
    /// radius
    HxPortRadioBox portRadius;
    HxPortText portRadiusAttribute;
    /// Scale atom radii by this value.
    HxPortFloatSlider portAtomRadiusScale;
    /// Add this value to atom radii.
    HxPortFloatSlider portAtomRadiusOffset;
    /// Radius of probe sphere.
    HxPortFloatSlider portProbeRadius;
    /// Approximated edge length of surface.
    HxPortFloatSlider portEdgeLength;
    /// Approximated number of points on surface.
    HxPortFloatSlider portNOPPerAngstroem2;
    /// Some options.
    HxPortToggleList portOptions;
    /// This port is used when contracting edges. The edge length is
    /// multiplied by this value to determine the min edge length.
    HxPortFloatSlider portEdgeContractionScaleFactor;
    /// Surface area options.
    HxPortToggleList portSurfaceArea;
    /// Attribute name for surface area attribute.
    HxPortText portAttributeName;
    ///
    HxPortToggleList portFilterOptions;
    /// Button to start the computation.
    HxPortDoIt portAction;

public:
    // Constructor.
    HxCompMolSurface();
    // Destructor.
    ~HxCompMolSurface();
    // Overloaded function that handles the interface.
    void update();
    // Overloaded function that handles the computation.
    void compute();
    
protected:
    /// Computes surface area and writes atom or residue specific
    /// surface area to topology of molecules.
    void computeSurfaceArea();
    /// Overloaded parse method to interpret tcl commands.
    int parse(Tcl_Interp* t, int argc, char **argv);
    /// Overloaded method which returns if the current result can be
    /// computed from the current setting (needed saveNetwork).
    int canCreateData(HxData* data, McString& createCmd);
    /// Overloaded method that writes the state of the ports to a file.
    void savePorts(FILE* fp);
    
private:
    // Compute atom radii for @c hxmol according to 
    // @c portAtomRadiusScale and @c portAtomRadiusScale.
    void computeAtomRadii(const HxMolecule * hxmol, McDArray<float> & radii);

    // Molecule for which surface should be computed.
    HxMolecule * hxmol;
    // Molecule 2 for which surface should be computed.
    HxMolecule * hxmol2;
    // Object of class CompMolSurface in which the actual surface
    // computation is implemented.
    CompMolSurface compMolSurface;
    
    // Some flags.
    unsigned char oldOptions[2];
    unsigned char filterTouched[2];
    unsigned char highlightingTouched[2];
    unsigned char selectionTouched;
    unsigned char radiiSettingsTouched;
};

#endif

/// @}
