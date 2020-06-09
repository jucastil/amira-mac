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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef HX_AFFINEREGISTRATION
#define HX_AFFINEREGISTRATION

#include <mclib/McMat3d.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortRadioBox.h>
#include <Inventor/SbLinear.h>
#include <hxregistration/hxregistrationAPI.h>
#include <hxregistration/HxVoxelRegistration.h>

/// Compute module affine registration.
class HXREGISTRATION_API HxAffineRegistration : public HxVoxelRegistration
{
public:
    HxAffineRegistration();

    virtual ~HxAffineRegistration();

    /// Third input connection to second reference dataset (optional)
    HxConnection portReference2;

    /// Fourth input connection to third reference dataset (optional)
    HxConnection portReference3;

    ///Number of DOF for transform vector
    HxPortToggleList portDOFs;


    /// Select 2D/3D registration.
    HxPortRadioBox port23;

    virtual RegFunctional* createFunctional(McDArray<HxSpatialData*>  &ref,
                 McDArray<HxSpatialData*> &mod, int prolongations = -1, int dataLevel = -1);

    virtual void compute();

    void rotateModelAroundPrincipalAxis(int axis, SbVec3d &centerRef,
                                        McMat3d &axesRef, double angle);

    virtual void update();

    virtual bool applyTransform (RegParametricTransform *transform = NULL) ;

    virtual bool checkForInterrupt();

    /** Set a callback function which is invoked each time the
        progress changes */
    virtual bool setProgressCallback(void (*callbackFunction)(float progress,
                                                      bool &interrupt) );

    /** Set the flag which passes exceptions to the calling routine.
    */
    virtual void setPassExceptions(bool flag);

private:
    virtual void createTransform();

    HX_HEADER( HxAffineRegistration );

#ifdef REG_USE_HX_OPTIMIZE
    ///prolongations must be cast to McDArray< McDArray<int> > *.
    virtual int getProlongationsPerDataLevel();
#endif

    ///Is called by computePrincipalAxes(..)
    SbVec3d computeCenter(HxRegScalarField3 *input, int field);

    McMat3d computePrincipalAxes(HxRegScalarField3 *input,
                                 SbVec3d& center, int field);

    virtual void doResolution(int index, int numResolutionLevels, RegFunctional* currentFunctional,
                              double initialStepSize, double finalStepSize);

    /** Enter a resolution level.
    * This function mainly determines the next effective number of degrees of
    * freedom of the optimization. It sets the transformation object accordingly
    * and writes a comment to the "Callback" object. Afterwards, the inherited
    * EnterResolution() function is called.
    *@param level Index of the current resolution level. 0 is first (coarsest),
    * subsequent (finer) resolutions have increasing numbers.
    *@param total Total number of resolution levels.
    */
    virtual int doneResolution(int level, int total);

    virtual void enterResolution(int level, int total, RegFunctional* f = NULL);

    virtual int initRegistration ();

    virtual void doneRegistration ();

    virtual void updateReference();

    /** Numbers of degrees of freedom.
    * This list contains the numbers of degrees of freedom for every resolution
    * level. Possible configurations are: 6; 6, 7; 6, 7, 9; or 6, 7, 9, 12.
    * The actual configuration is determined by the value specified by the user.
    * Registration is repeated with the same data as many times as there
    * are entries in this list. If the derived classes do not set any entries,
    * initRegistration() will push a "6"  into the list, resulting in an affine
    * registration.
    * In addition, as a guard element -1 is pushed to the end of the list.
    */
    McDArray<int> *numberDOFs;

#ifdef REG_USE_HX_OPTIMIZE
    McDArray<int> degreesOfFreedom;
#endif

    int numberDOFsIterator;

    /** Optional external callback function which is invoked each time the
    *   progress changes.
    */
    void (*m_progress_callback_function)(float progress, bool &interrupt);

    /** If this flag is set, exceptions occuring in compute() are passed
    *   to the calling routine.
    */
    bool mPassExceptions;
};

#endif

/// @}
