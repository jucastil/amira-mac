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

/// @addtogroup hxelasticslicereg hxelasticslicereg
/// @{
#ifndef ELASTICIMAGESTACKREGISTRATIONTHREAD2
#define ELASTICIMAGESTACKREGISTRATIONTHREAD2

#include <hxcore/HxThread.h>

class HxElasticImageStackRegistrationThreaded2;
class HxLattice;
class HxMutableLattice;

/// This thread class performs one registration step for one slice.
/// It repeatedly asks for a slice number and applies the deformation.
/// The thread finishes when the received slice number is -1.
/// The resulting deformation step is added to the total deformation.
class ElasticImageStackRegistrationThread2 : public HxThread {

public:
    ElasticImageStackRegistrationThread2(HxElasticImageStackRegistrationThreaded2* ctrl, const int num);
    ~ElasticImageStackRegistrationThread2();
    void setReverse(const bool rev) {mReverse = rev;}
    void setDeformLattice(HxMutableLattice* lat) {mDeformLattice = lat;}
    void setTemplateDataLattice(HxLattice* lat) {mTemplateDataLattice = lat;}
    void setTemplateDataTmpLattice(HxMutableLattice* lat) {mTemplateDataTmpLattice = lat;}
    void setInputImageDataLattice(HxLattice* lat) {mInputImageDataLattice = lat;}
    virtual void run();

private:
    int mTemplateSliceNum;
    HxElasticImageStackRegistrationThreaded2* mController;
    int mThreadNum;
    bool mReverse;
    HxMutableLattice* mDeformLattice;
    HxLattice* mTemplateDataLattice;
    HxMutableLattice* mTemplateDataTmpLattice;
    HxLattice* mInputImageDataLattice;
};


/// This thread class computes the error for one slice.
/// It repeatedly asks for a slice number and applies the deformation.
/// The thread finishes when the received slice number is -1.
/// The resulting error is added to the global error variable of the controller.
class ComputeErrorThread2 : public HxThread {

public:
    ComputeErrorThread2(HxElasticImageStackRegistrationThreaded2* ctrl, const int num);
    ~ComputeErrorThread2();
    virtual void run();
    void setLattice(HxLattice* lat) {mLattice = lat;}

private:
    int mTemplateSliceNum;
    HxElasticImageStackRegistrationThreaded2* mController;
    int mThreadNum;
    HxLattice* mLattice;
};



/// This thread class computes the deformed (template) image
/// from the input image and the deformation field.
/// It repeatedly asks for a slice number and applies the deformation.
/// The thread finishes when the received slice number is -1.
class ComputeTransformedStackThread2 : public HxThread {

public:
    ComputeTransformedStackThread2(HxElasticImageStackRegistrationThreaded2* ctrl, const int num);
    ~ComputeTransformedStackThread2();
    virtual void run();
    void setDeformDataLattice(HxLattice* lat) {mDeformDataLattice = lat;}
    void setInputDataLattice(HxLattice* lat) {mInputDataLattice = lat;}
    void setTemplateDataLattice(HxMutableLattice* lat) {mTemplateDataLattice = lat;}


private:
    int mTemplateSliceNum;
    HxElasticImageStackRegistrationThreaded2* mController;
    int mThreadNum;
    HxLattice* mDeformDataLattice;
    HxLattice* mInputDataLattice;
    HxMutableLattice* mTemplateDataLattice;
};

#endif




/// @}
