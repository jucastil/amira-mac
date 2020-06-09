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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_HELPERS_H
#define MOLCHEM_HELPERS_H

#include "MolChemWinDLLApi.h"

class McVec3f;
class McVec3i;
class McVec3d;
class McString;
class McMat4f;
//template <class T> class McDArray;
class Molecule;
//class McBitfield;
class MolTopology;
class MolTrajectory;
class MolTrajectoryMem;
class McBox3f;
class RegularGrid3f1;
class MolObject;
class McVec2i;
class McProgressInterface;
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>


namespace molchem {
    class Logger;
    class Molecule;
    class AtomTyper;
    /// Converstion from array of char pointers to array of mcstring
    void MOLCHEM_API convert(const char* txt_in[],int num, McDArray<McString>& txt_out);

    void MOLCHEM_API convert(const McDArray<McVec3f>& x1, McDArray<McVec3d>& x2);
    
    template <class A, class B> void convert(const McDArray<A>& x1, McDArray<B>& x2) 
    {x2.resize(x1.size());for (int i=x1.size();i--;)x2[i]=x1[i];}
    
    /** restricts a mcdarray to only those entries, whose index is set in the bitfield. Maintains order.*/
    template <class A> void restrictArray(McDArray<A>& x, const McBitfield& b) 
    { int numdel=0;for (int i=0;i<x.size();i++) {if (numdel) x[i-numdel]=x[i];if (!b[i]) numdel++;}
      if (numdel) x.removeLast(numdel);
    }

    void MOLCHEM_API convert(const McDArray<double>& x1, McDArray<McVec3f>& x2);

    void MOLCHEM_API convert(const McDArray<float>& x1, McDArray<McVec3d>& x2);

    void MOLCHEM_API convert(const McDArray<double>& x1, McDArray<McVec3d>& x2);

    void MOLCHEM_API convert(const McDArray<float>& x1, McDArray<McVec3f>& x2);

    void MOLCHEM_API convert(const double * x1, int num, McDArray<McVec3d>& x2);

    void MOLCHEM_API convert(const float * x1, int num, McDArray<McVec3d>& x2);

    void MOLCHEM_API convert(const float * x1, int num, McDArray<McVec3f>& x2);    

    void MOLCHEM_API convert(const double * x1, int num, McDArray<McVec3f>& x2);    
    
    void MOLCHEM_API convert(const double * x1, int num,  float* x2); 
    
    void MOLCHEM_API convert(const float * x1, int num,  double* x2); 

    void MOLCHEM_API convert(const McDArray<McVec3d>& x1,double * const x2, int num);
    
    void MOLCHEM_API fillZero(McDArray<McVec3d>& );
    /** Meta Programming implementation of pow(double,unsigned int) */
    template< unsigned N >  inline  double  pow_meta( double x )  { return  pow_meta<N % 2>( x )  *  pow_meta<N / 2>( x * x );}
    template<> inline  double  pow_meta<1u>( double x )  {  return x;  }
    template<> inline  double  pow_meta<0u>( double x )  {  return 1.;  }

    /** Resets atoms/radius attribute to default value if it exists.
        throws molchem::Exception */
    void MOLCHEM_API resetRadii(MolTopology* mol);
    /** return a list of radii for each atom, taken from the standard vdw radius of the element table
        throws molchem::Exception */
    void MOLCHEM_API getRadii(const MolTopology* mol, McDArray<float>& radii);

    /** Adds atoms/mass attribute containing atomic mass as defined in the element table
        throws molchem::Exception */
    void MOLCHEM_API addMassAttribute(MolTopology* mol,const char* name);
    /** Adds atoms/radius attribute containing standard vdw radii as defined in the element table
        throws molchem::Exception */
    void MOLCHEM_API addRadiusAttribute(MolTopology* mol,const char* name);
    
    /** throws molchem::Exception */
    void MOLCHEM_API copyBonds(const MolTopology* t1,MolTopology* t2);
    /** Adds hydrogens incl. 3D coordinates to object. To determine correct number, the formal_charge attribute is used, if given.*/
    void MOLCHEM_API addHydrogens(MolObject* mem);
    /** Removes hydrogens.*/
    void MOLCHEM_API removeHydrogens(MolObject* mem);
    /** Removes non polar hydrogens.*/    
    void MOLCHEM_API removeNonPolarHydrogens(MolObject* mem);
    /** Removes all molecules of the form HxOy(where x and u are integers equal or greater one. */
    void MOLCHEM_API removeWater(MolObject* m);
    /** Returns the resdidue index each atom belongs to. Throws molchem::Exception. */
    void MOLCHEM_API getResidueIxPerAtom(const MolTopology*,McDArray<int>& );
    /** looks for each hydogen and if not in a residue assign residue of first neighboring heavy atom if existant.*/
    void MOLCHEM_API assignResiduesToHydrogens(MolTopology* top);
    /** divides all element of array a by SUM(a) */
    void MOLCHEM_API normalizeSum(float* a, int n);

    /** Converts a molecule which contains several timesteps of the same topology into a trajectory */
    MOLCHEM_API MolTrajectoryMem*  moleculeToTrajectory(::Molecule* m,const char* timestepLevelName);
    
    /** Converts a molecule with several timesteps into a single molecule. Timesteps can be encoded in a timestep level */
    MOLCHEM_API ::Molecule* trajectoryToMolecule(MolTrajectory* m,const char* timestepLevelName=0);

    /** Adds MMFF Parameterization. Formal charges of the molecule must be assigned in the atoms attribute formal_charge.
        Optionally, the assignment may take place without explicit hydrogens.*/
    MOLCHEM_API void addMMFFParameterization(MolTopology* m,bool addImplicitHydrogens);
    MOLCHEM_API void addMMFFParameterization(MolTopology* m);

    // initializes the bbox with maximum values
    MOLCHEM_API void initBBox(McBox3f& box);
    /** expands bbox by all coordinates in trajectory */
    MOLCHEM_API void expandBBox(const MolTrajectory& m,McBox3f& box);

    /** by keeping atom order */
    MOLCHEM_API void addBondsFromTemplate1(MolObject* t,const MolTopology* temp);
    
    /** by matching atom type attribute */
    MOLCHEM_API void addBondsFromTemplate2(MolObject* t,const MolTopology* temp);

    /** add bonds for all non bonded hydrogens by looking at closest heavy atom  */
    MOLCHEM_API void addBondsForH(MolObject* t);

    /** Counts the occurence of val as attribute value */
    MOLCHEM_API int countAttributeValueOccurance(MolTopology* t,const char* levelName, const char* attrName, int val);
    MOLCHEM_API int countAttributeValueOccurance(McDArray<MolTrajectory*>& t,const char* levelName, const char* attrName, int val);
    /** */
    void MOLCHEM_API test();
    void MOLCHEM_API computeAtomTypeDensityCorrelation(McDArray<MolTrajectoryMem*> t,McDArray<MolTrajectoryMem*> tRef,const char* filename,float atomRadius=1.,float voxelSize=.3,const char* energyWeightingObs=0, const char* energyWeightingObsRef=0);
    void MOLCHEM_API computeDensityCorrelationPerFragment(McDArray<MolTrajectoryMem*> t,McDArray<MolTrajectoryMem*> tRef,const char* filename, float atomRadius,float voxelSize,const char* energyWeightingObs);

    /** Reads an electrostatic field from an APBS generated file
        throws molchem::Exception */
    MOLCHEM_API RegularGrid3f1* readAPBSField(const char* filename);
    /** Reads an electrostatic field from a CONGEN generated file
        throws molchem::Exception */
    MOLCHEM_API RegularGrid3f1* readCONGENField(const char* filename);
    /** Reads grid map from an Autogrid generated .map file.
		\exception throws molchem::Exception */
    MOLCHEM_API RegularGrid3f1* readAutogridField(const char* filename);
    /** Saves grid map to an Autogrid .map file.
		\exception throws molchem::Exception */
    MOLCHEM_API void saveAutogridField(const char* filename,const RegularGrid3f1& g);

    /** Method checks whether trajectory is a MolTrajectoryMem and if not converts its into one. 
        If del is true, the old MolTrajectory will be deleted if it is converted.*/
    MOLCHEM_API MolTrajectoryMem* makeMolTrajectoryMem(MolTrajectory* m,bool del=true);

    /** Returns the measurement between a set of atoms. atomIx must be of size 2-4 and contain the atom indices in correct order.
        For size 2 distance will be returned (in A), for 3 the angle (in grad), for 4 the dihedral(in grad).
        timeStep defines the timestep in the molObject that will be used.
    */
    MOLCHEM_API float getMeasurement(const MolObject* M, const McDArray<int>& atomIx,int timeStep=0); 
    /** Returns the measurement between a set of atoms. atomIx must be of size 2-4. Each entry contains as x
        the molecule index in the mol array, as y the timestep, as z the atomIndex in the molecule.
        For size 2 distance will be returned (in A), for 3 the angle (in grad), for 4 the dihedral(in grad).
        timeStep defines the timestep in the molObject that will be used.
     */
    MOLCHEM_API float getMeasurement(const McDArray<MolObject*>& mol, const McDArray<McVec3i>& atomIx);
    /** Returns the measurement between a set of coordinates.
        For size 2 distance will be returned (in A), for 3 the angle (in grad), for 4 the dihedral(in grad).
     */
    MOLCHEM_API float getMeasurement(const McDArray<McVec3f>& co);
    MOLCHEM_API float getDistance(const McVec3f& v1,const McVec3f& v2);
    /** Returns angle in the range [0,Pi] */
    MOLCHEM_API float getAngle(const McVec3f& v1,const McVec3f& v2,const McVec3f& v3);
    MOLCHEM_API double getDistance(const McVec3d& v1,const McVec3d& v2);
    /** Returns angle in the range [0,Pi] */
    MOLCHEM_API double getAngle(const McVec3d& v1,const McVec3d& v2,const McVec3d& v3);
    /** Returns angle as rotation of v3-v2 in relation to v2-v1 in the range [0,2Pi]. 
        To define the directionality of the angle the following method is used:
        Let n be the normal (v1-v2)x(v3-v2). Then take the coordinate axis of the largest absolute component
        of n. If n.dot(axis)>0 the angle will be in [0,Pi] else [Pi,2Pi]. */
    MOLCHEM_API double getDirectionalAngle(const McVec3d& v1,const McVec3d& v2,const McVec3d& v3);
    /** Returns dihedral in the range [-Pi,Pi]. Positive if rotation of x=v2-v1  -> y=v4-v3 follows right hand rule
    in relation of z=v3-v2, i.e. rotation in clockwise direction ie. if (x.cross(y).dot(z))>0. */
    MOLCHEM_API float getDihedral(const McVec3f& v1,const McVec3f& v2,const McVec3f& v3,const McVec3f& v4);
    MOLCHEM_API double getDihedral(const McVec3d& v1,const McVec3d& v2,const McVec3d& v3,const McVec3d& v4);

    /** This function can be used to add 2 attributes containing the atom typing information to a MolObject.
        mcMol must be the molchem representation of the Molecule, at the atom typer.
        If symbolAttrName is not a 0 pointer a string attribute containing the atom type symbols  will be created with this name.
        If indexAttrName is not  a 0 pointer an integer attribute containing the atom type indices  will be created with this name.
        Will return the number of atoms for which the atom type assignment failed.
        */
    MOLCHEM_API int addAtomTypeAttribute(MolObject* mol,molchem::Molecule* mcMol, molchem::AtomTyper& at,const char* symbolAttrName,const char* indexAttrName=0);
    /** Adds float attribute attrName to the atom level, filling it with vdw radii according to the equilibrium vdw distance between the 
        atom and another atom of the same type according to the equation: Rii*=Ai * pow(alphai,.25) MMFF atom type already needs to be assigned in the integer
        attruibute mmffTypeAttrName.
        throws molchem::Exception */
    MOLCHEM_API void addMMFF94VDWRadiusAttribute(MolTopology* mol, const char* attrName,const char*mmffTypeAttrName);
    MOLCHEM_API void getMMFF94VDWRadii(const MolTopology* mol,const char*mmffTypeAttrName,McDArray<float>& radii);
    MOLCHEM_API void getMMFF94VDWRadii(const McDArray<int>& mmffAtomType, McDArray<float>& radii);

    /** Computes 3d line of best fit through a set of points */
    MOLCHEM_API void fitLine3D(const McDArray<McVec3f>& co,McVec3f& p1,McVec3f& p2);

    /** Computes the solvent accessible surface area and derivatives */
    MOLCHEM_API void computeSASA(
        const McDArray<McVec3d>& atomsX,
	    const McDArray<double>& radius, 
        const McDArray<double>* weight, 
        double probe,
        double& total,
        McDArray<double>& area, 
        McDArray<McVec3d>& darea);
    
    /** Computes the solvation energy with the sheffield model */
    MOLCHEM_API void computeSheffield(
        const McDArray<McVec2i>& pairs,
        const McDArray<McVec3d>& pos,
        const McDArray<double>& charges,
        const McDArray<double>& radii, 
        double A, 
        double B,
        double epsin,
        double epsout,
        double& result,
        McDArray<double>* resPerAtom=0,
        McDArray<McVec3d>* gradient=0);

    /** Applies small random perturbations to an array of coordinates.
        Each coordinate will be changed by a value between -pmax,pmax (equally distributed).
    */
    MOLCHEM_API void perturbCoordinates(McDArray<McVec3d>& co,double pmax=.001);

    /** Write APBS pqr file. 
     \para[in] o Molecule that will be written
     \para[in] timestep Timestep of coordinates (must be valid). 0 if MolObject represents a molecule .
     \para[in] filename Name of the file that will be written
     \para[in] chargeAttrName Name of charge attribute
     \para[in] radiusAttrName Name of radius attribute
     \exception molchem::Exception
    */
    MOLCHEM_API void writePQRFile(const MolObject& o,int timestep,const char* filename,const char* chargeAttrName,const char* radiusAttrName);
    
    /** Compute atom distances between first and second structure.
        The algorithm works the following way: It iterates over each atom of the first structure and
        searches for the closest atom of the same atom type in the second structure.  This is used as the distance.
        If no such atom exists, -1 will be assigned.
        \para[in] o1 First Molecule
        \para[in] timestep1 Timestep of first molecule
        \para[in] o2 Second Molecule
        \para[in] timestep2 Timestep of second Molecule
        \para[out] d List of distances per atom of first molecule
    */
    MOLCHEM_API void computeDistance(const MolObject& o1, const int timestep1, const MolObject& o2, const int timestep2, McDArray<float>& d);

    MOLCHEM_API void addAttribute(MolTopology* t,int level,const char* attrName,McDArray<float>& values);
    MOLCHEM_API void addAttribute(MolTopology* t,int level,const char* attrName,McDArray<int>& values);

    class MOLCHEM_API bla {
    public:
        static McDArray<int> type;
        static McDArray<float> x1;
        static McDArray<float> x2;
        static McDArray<float> x3;
        static McDArray<float> x4;//###
        static McDArray<float> area;//###
        static double p1;
        static double p2;
        static double p3;
        static double p4;
        static double p5;
    };
    /** This will compute the change of protonation based on standark pka values of some residues and termini.
        It will return indices of heavy atoms which need a hydrogen removed or added.
        termini = DO_NOT_CHANGE,NEUTRAL,STANDARD*/
    MOLCHEM_API void getAminoAcidProtonationChange(const MolTopology* t, const float ph, int termini, McDArray<int>& hToRemove,McDArray<int>& hToAdd);
    
    /** Returns C and N terminal atom of each residue (i.e. atoms with atoms/type attribute 'C' and 'N')
        \throws molchem::Exception
    */
    MOLCHEM_API void getAminoAcidTerminiPerResidue(const MolTopology* top,McDArray<int>& nTerm,McDArray<int>& cTerm);

    /** Computes the chains of amino acids by looking at bonds between their termini.
        This requires correct pdb atom types in the atoms/type attribute containing 'C' and 'N' string for the amino acid
        terminii.
        The resulting chains start with the n and end with the c terminus.
        \throws molchem::Exception
    */

    MOLCHEM_API void getAminoAcidChains(const MolTopology* top,McDArray<McDArray<int> >& chains);

    /** Returns for each amino acid the index of the amino acid residue that is bonded to it's c and n terminus.
        This requires correct pdb atom types in the atoms/type attribute containing 'C' and 'N' string for the amino acid
        terminii.
        \throws molchem::Exception
    */
    MOLCHEM_API void getAminoAcidTerminusBonding(const MolTopology* top, McDArray<int>& nTermBondedToRes,McDArray<int>& cTermBondedToRes);

    /**returns number of bonded hydrogens for each heavy atoms */
    MOLCHEM_API void getHNumPerHeavyAtom(const MolTopology* top, McDArray<int>& hNumPerAtom);

    /** Minimizes molecule with MMFF94 force field
        throws molchem::Exception
    */
    MOLCHEM_API void minimize(::Molecule& mol,float cutoff,int maxSteps,const McBitfield* fixed);
    MOLCHEM_API void minimize(molchem::Molecule& mol,float cutoff,int maxSteps,const McBitfield* fixed);
    /** This takes a bundle of molecules and computes average bond lengths. This is used to generate the file bondLength.cfg */
    MOLCHEM_API void generateAverageBondLengths(const McDArray<MolObject*>& mols,McString& result);
    /** Aligns two timesteps of MolObjects using translation and rotations by minimizing the rmsd. */    
    MOLCHEM_API void computeAlignment(const MolObject& o1,int step1, const MolObject& o2, int step2,McMat4f& transform); 
    /** Aligns a point set co1 to point set co2 using translation and rotations by minimizing the rmsd. */    
    MOLCHEM_API void align( McDArray<McVec3f>& co1,const McDArray<McVec3f>& co2); 
    /** Aligns a point set co1 to point set co2 using translation and rotations by minimizing the rmsd. */
    MOLCHEM_API void align( McDArray<McVec3d>& co1,const McDArray<McVec3d>& co2); 
    /** generates a smiles string from a molecule */
    MOLCHEM_API void generateSmiles(molchem::Molecule& mol,McString& smiles);
    MOLCHEM_API void generateSmiles(const MolObject& mol,McString& smiles);

    /** Partitions molobject into its residues and creates one molecule for each residue containing all information that does
        not depend on residue level (ie. residue, atoms, bond but not chains for example).
        the mol object must have at least one time step.
        Coordinates will be copied from the first time step.
    */
    MOLCHEM_API void partitionMoleculeIntoResidues(const MolObject& mol,McDArray< ::Molecule *>& residues);


    /** Indexed sorter. Will return an index array so that the value of each index is in ascending order. */
    MOLCHEM_API void sortIndexByValue(const McDArray<float>& value,McDArray<int>& index);
    MOLCHEM_API void sortIndexByValue(const McDArray<double>& value,McDArray<int>& index);
    MOLCHEM_API void sortIndexByValue(const McDArray<const char*>& value,McDArray<int>& index);

    MOLCHEM_API void generateInternalCoordinatesLevel(MolTopology* top,const char* levelName);

    /** Generates a random selection of nsel out of n and writes it into the bitfield */
    MOLCHEM_API void randomSelection(int n, int nsel,McBitfield& selection);

    /** converts bond orders in MolTopology to represent kekule structure */
    MOLCHEM_API void assignKekuleBondOrders(MolTopology& t);
    
    /** converts bond orders in MolTopology to represent non-kekule structure */
    MOLCHEM_API void assignNonKekuleBondOrders(MolTopology& t);

    /** computes all possible matchings from atoms of molecule m1 to m2 by generating a smiles string of m1 and matching it
        to m2. 
        
        \para[out] matchings Each matching in the list contains for each atom of m1 indices that map these atoms to m2.
                  -1 indicates no matching and these atoms will not be used in the rmsd computation.
        \para[in] single if single is true only the first found matching is returned
        \para[in] smiles Smiles string by which the structures are matched. If it is a null pointer, it will be automatically
                  generated from the molecule m1.
    */
    MOLCHEM_API void computeSmilesMatchings(const MolObject& m1, const MolObject& m2,McDArray<McDArray<int> >& matchings,bool single=false,const char* smiles=0);


    /** Computes the RMSD between the two MolObjects. MolObjects must have the same number of atoms with the same sequence */
    MOLCHEM_API float computeRMSD(const MolObject& o1, int step1, const MolObject& o2, int step2);

    /** Computes the RMSD between the matching of the two MolObjects. 
    
        \para[in] matchings Each matching in the list contains for each atom of m1 indices that map these atoms to m2.
                  -1 indicates no matching and these atoms will not be used in the rmsd computation.
     */
    MOLCHEM_API float computeRMSDOfMatching(const MolObject& o1,int step1, const MolObject& o2,int step2,const McDArray<int>& match);

    /** Computes the RMSD between the best alignment of each matching of the two MolObjects. 
    
        \para[in] matchings Each matching in the list contains for each atom of m1 indices that map these atoms to m2.
                  -1 indicates no matching and these atoms will not be used in the rmsd computation.
     */
    
    MOLCHEM_API float computeAlignedRMSDOfMatching(const MolObject& o1,int step1, const MolObject& o2,int step2,const McDArray<int>& match);

    /** Computes the rmsd of each matching from m1 to m2. 
    
        \para[in] matchings Each matching in the list contains for each atom of m1 indices that map these atoms to m2.
                  -1 indicates no matching and these atoms will not be used in the rmsd computation.
        \para[out] rmsd RMSD for each matching
        \return Index of matching with lowest rmsd.*/
    MOLCHEM_API int computeRMSDOfMatchings(const MolObject& m1, int step1,const MolObject& m2,int step2, 
            const McDArray<McDArray<int> >& matchings, McDArray<float>& rmsd);
    /** Computes the rmsd of the best alignment of each matching from m1 to m2. 
    
        \para[in] matchings Each matching in the list contains for each atom of m1 indices that map these atoms to m2.
                  -1 indicates no matching and these atoms will not be used in the rmsd computation.
        \para[out] rmsd RMSD for best alignment for each matching
        \return Index of matching with lowest rmsd.*/
    MOLCHEM_API int computeAlignedRMSDOfMatchings(const MolObject& m1, int step1,const MolObject& m2,int step2, 
        const McDArray<McDArray<int> >& matchings,McDArray<float>& rmsd);

    /** Aligns a point set co1 to point set co2 by translation and rotation by minimizing the rmsd. 
        The coordinates are matched to each other using the given matching. */    
    MOLCHEM_API void alignByMatching( McDArray<McVec3f>& co1,const McDArray<McVec3f>& co2,const McDArray<int>& matching); 

    /** Aligns mol1 to mol2 by a smarts matching
        Uses the first found matching. If there is no matching for both molecules, does nothing and return false.
        If ix1 is -1, it will align all timesteps of m1.*/    
    MOLCHEM_API bool alignBySmartsMatching( MolObject& m1,int ix1,const MolObject& m2,int ix2,const McString smarts); 

    /** Will return a guess whether the molecule has the full set of hydrogens.
        This can be used if the molecule has correct bond orders but formal charges are missing.

        Heuristic: Count number of C (and N) that have less than 4 (3) heavy valencies.
        If this number is larger than 0 and if at least half of these have less than 
        4 (3) overall valencies we assume missing hydrogens.

        Note: This algorithm will fairly accurately predict missing hydrogens for
        molecules largen than a few atoms and allows for some positively charged atoms.
        It may fail for small molecules which have a high ratio of charged atoms to overall atoms.
        It will also fail for molecules which have partial but not complete explicit hydrogens.
    */
    
    MOLCHEM_API bool guessHasMissingHydrogens(const molchem::Molecule& m);

    /** Will randomize dihedral angles. This function is used for generating test sets for global minimization */
    MOLCHEM_API void randomizeDihedrals(molchem::Molecule& mol);

    /** Splits the Molecule by turning each group of a level into a seperate molecule.
    */
    MOLCHEM_API void splitByLevel(const ::Molecule* o,int levelIx, McDArray< ::Molecule*>& result);

    /** Splits the Molecule by turning each group with a different attribute into a separate trajectory.
    */
    MOLCHEM_API void splitByAttribute(const ::Molecule* o,int levelIx,int attrIx, McDArray< ::Molecule*>& result);

    /** returns 1 letter amino acid code from three letter input. All upper case. Returns 0 if not found. */
    MOLCHEM_API char convertAminoAcidCode3To1(const char* threeLetterCode);
    /** returns 3 letter amino acid code from one letter input. All upper case. Return 0 if not found */
    MOLCHEM_API const char* convertAminoAcidCode1To3(char oneLetterCode);

    /** converts to 1 letter amino acid code string  from three letter input. All upper case. 
    \throws molechem::Exception*/
    MOLCHEM_API void convertAminoAcidCodeString3To1(const McString& code3,McString& code1);
    /** converts to string with 3 letter amino acid code from one letter input. All upper case.
    \throws molechem::Exception*/
    MOLCHEM_API void convertAminoAcidCodeString1To3(const McString& code1, McString& code3);

    /** Parses a string of amino acid one letter code (which has start with the N terminus) and creates a molecule.
        The resulting polypeptide will be linear and close to a local minimum conformation.
        throws molchem::Exception
    */
    MOLCHEM_API ::Molecule* createMoleculeFromAminoAcidCode1(const McString& code);

    /** Subsitutes the amino acid with index resIx in the residues level 
        with the amino acid with the given 3 letter code substName.
        The old atoms will be removed, the new atoms appended at the end.
        The old group residues/resIx will stay intact only its elements will change
        to the new atoms and the type attribute will be overwritten with substName.
        The input molecule must have the atoms/type attribute containing the pdb atom types,
        the residues/type attribute, and the bonds/type attribute.
    \throws molchem::Exception
    */
    MOLCHEM_API void substituteAminoAcid(::Molecule* o,int resIx,const char* substName);
    /** same as the function above but uses the mutation notation (like A124H) 
        the types may be either 1 or 3 letter code. The index corresponds to the index attribute of the
        residues level (groups index+1) except if indexAttr is not 0 in which case it corresponds to the given attribute 
        integer attribute of the residues level. If no index is given (like AH) all residues of that type will be replaced.
    /throws molchem::Exception */
    MOLCHEM_API void substituteAminoAcid(::Molecule* o,const char* mutationString,const char* indexAttr=0);
    /** Extends the amino acid resIx with a new aminoacid of given type at the given
        terminus ('C' or 'N') by forming a peptide bond.
        The input molecule must have the atoms/type attribute containing the pdb atom types,
        the residues/type attribute, and the bonds/type attribute.
    \throws molchem::Exception
    */
    MOLCHEM_API void extendAminoAcid(::Molecule* o,int resIx,char terminus,const char* type);
    /** Connect 2 amino acids by forming peptide bond between C terminus of resIx1 and N terminux of resIx2
        The input molecule must have the atoms/type attribute containing the pdb atom types,
        the residues/type attribute, and the bonds/type attribute.
    \throws molchem::Exception
    */
    MOLCHEM_API void connectAminoAcids(::Molecule* o,int resIx1,int resIx2);
    /** switched amino acid chirality to D or L form. Chirlaity must be 'D' or 'L' */
    MOLCHEM_API void setAminoAcidChirality(::Molecule* o,int resIx,char chirality);
    /** Returns whether amino acid is 'D' or 'L'. For Glycine: \throws molchem::Exception */
    MOLCHEM_API char getAminoAcidChirality(::Molecule* o,int resIx);

    /** converts a bitfield of atoms into an arrays of the number of atoms per group that
        are set/unset in bitfield. This is for example used to convert atom selections
        into selection in relation to other levels */
    MOLCHEM_API void convertAtomsToGroupsOfLevel(const MolTopology* top,const McBitfield& bf,int levelIx,
        McDArray<int>& atomsSetPerGroup,McDArray<int>& atomsUnsetperGroup);

    /** Sorts the timesteps of a moltrajectory by the values of an observable. 
        Sorts for ascending or descending values. */
    MOLCHEM_API void sortTimestepsByObservable(MolTrajectoryMem* o,int obsIx,bool ascending=true);


    /** Applies QT-clustering with rmsd distance metric. clusterRadius is the threshold rmsd radius for a cluster.
        minMemberNum is the minumum number of members of a cluster. clusterIx returns the cluster index for each point. 
       0 means no cluster assigned. Returns whether successful (not interrupted by user)
       \throws molchem::Exception*/
    MOLCHEM_API bool clusterQT(const McDArray<McDArray<float> >& points,float clusterRadius,int minMemberNum,McDArray<int>& clusterIx,McProgressInterface* progress=0);

    /** Applies QT-clustering with rmsd distance metric. clusterRadius is the threshold rmsd radius for a cluster.
        minMemberNum is the minumum number of members of a cluster. clusterIx returns the cluster index for each point. 
       0 means no cluster assigned. Returns whether successful (not interrupted by user)
       \throws molchem::Exception*/
    MOLCHEM_API bool clusterQT(const MolObject& mo,float radius,int minMemberNum,McDArray<int>& clusterIx,McProgressInterface* progress=0);

    /** Applies K-Means clustering with rmsd distance metric. num is the number of clusters. 
    clusterIx returns the cluster index for each cluster which will be between [0,num]. Returns whetehr successful 
    (not interrupted by user. \throws molchem::Exception */
    MOLCHEM_API bool clusterKMeans(const McDArray<McDArray<float> >& points,int num,McDArray<int>& clusterIx,McProgressInterface* progress=0);

    /** Applies K-Means clustering with rmsd distance metric. num is the number of clusters. 
    clusterIx returns the cluster index for each cluster which will be between [0,num]. Returns whetehr successful 
    (not interrupted by user. \throws molchem::Exception */
    MOLCHEM_API bool clusterKMeans(const MolObject& mo,int num,McDArray<int>& clusterIx,McProgressInterface* progress=0);

    /** Splits the MolTrajectory by seperating timesteps with different observable. For each different value 
        result will contain a trajectory with all timesteps having this observable value. 
        \throws molchem::Exception
    */
    MOLCHEM_API void splitByObservable(const MolTrajectoryMem* o,int obsIx, McDArray< MolTrajectoryMem*>& result);

    /** Computes possible hydrogen bonds within a molecule. The hydrogens bonds are returned in the bonds array
        whereby the first atom in each entry is the donor and the second the acceptor.
        
        The algorithm considers all heteroatoms and charged carbons
        as hydrogen donors and all atoms with free electron pairs as hydrogen acceptors. It will iterate through all
        donors and look up close acceptors in a grid. Several geometic criteria are then checked including
        D-A distance (minDistDA, maxDistDA), H-A distance (maxDistHA), and D-A-X angle (minAngleDax).
        D is the Donor, A the acceptor, H a possible hydrogen position and X a heavy atom bonded to the acceptor.
        If the filter is set, only atoms that are set in the bitfield are considered as donors or acceptors.
        
        The algorithm will compute implicit hydrogens if some hydrogens are missing. 
        If any atom has a non zero formal charge the molecule needs to contains a 'atoms/formal_charge' 
        attribute, else results for these atoms might be incorrect.
    */
    MOLCHEM_API void computeHBonds(const ::Molecule* mol, McDArray<McVec2i>& bonds,const McBitfield* filter=0,
        float maxDistDA=3.8,float maxDistHA=3,float minAngleDAX=110);
    /** Same as computeHBonds but will not return an array of index pairs but will create a new level 'hBonds'
        which will contain each group as an MtBond. If hBonds already exists it will be cleared before being refilled. */
    MOLCHEM_API void computeHBondsLevel(::Molecule* mol, const McBitfield* filter=0,
        float maxDistDA=3.8,float maxDistHA=3,float minAngleDAX=110);
    
	/**	Returns bitfield of all oxygens and hydrogens which are not bonded to another heavy atom
	*/
	MOLCHEM_API void getWaters(const MolTopology* top, McBitfield& result);
	/**	Returns bitfield of all atoms of residues whose name starts with HET
	*/
	MOLCHEM_API void getHetResidueAtoms(const MolTopology* top, McBitfield& result);

    /** finds duplicates (identical topologies for atoms and bonds) within a set of molecules.
        Will first check for identical number of atoms and bonds.
        Those pairs which pass this test will be tested for having identical canonical smiles strings.
        The duplicates array will contain the indices of duplicates for each atom in the mols array.
        The return value will contain the number of duplicates (i.e. number of molecules which would
        have to be removed to make each member in the list unique). This function uses the progress interface
        and returns -1 if interrupted.
    */
    MOLCHEM_API int findDuplicates(const McDArray<MolObject*>& mols,McDArray<McDArray<int> >& duplicates);

    /** Returns the protein sequence in FASTA format for all convertible chains. 
        Input topology must have chains and residues level.
        It also needs to have attributes chains/name, residues/type, and residues/name. 
        All residues whose name starts with 'HET' will be cut out.
        If apart from the HET residues a chain contains a residue whose type cannot be converted
        from 3 letter code to 1 letter code, this chain will be skipped.
        Throws molchem::Exception. */
    MOLCHEM_API void getProteinFASTASequence(const MolTopology* top, McString& result);
    
    /** Applies a multi unit transform (as encountered multimeric pdb records).
        The first tranform will be applied to the current structure. For the remaining ones, the structure
        will be duplicated. Thus, the number of groups in each level in the structure will be the original * 
        the number matrices.
    */
    MOLCHEM_API void generateMultiUnit(MolObject& obj,const McDArray<McMat4f>& matrices);
    
    /** Reads matrices from BIOMT REMARK records that are sometimes part of pdb files.
        These BIOMT records represent transformation to reconstruct multimers from the single unit records.
        If they exist, they are read in by Amira into the PDB_REMARK data field.

        This function parses this field and returns all valid matrices.
        If no valid BIOMT record was found, the matrices array will be empty

        The resulting matrices can be applied to the data by using the generateMultiUnit function
    */
    MOLCHEM_API void getBiomtMatrices(const MolTopology& top,McDArray<McMat4f>& matrices);
    /** Returns molecular weight of compound. The calculation will include the weight of implicit hydrogens
        that are specified in the implicit_hnum attribute. Requires atoms/atomic_number attribute.
        Throws exception upon failure.*/
    MOLCHEM_API float getMolWeight(MolTopology& mol);
}

#endif

/// @}
