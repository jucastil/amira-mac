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

/// @addtogroup hxmulticomp hxmulticomp
/// @{
#ifndef IM_FILTER_WATERSHED_2D_H
#define IM_FILTER_WATERSHED_2D_H

#include "HxMultiCompWinDLLApi.h"
#include "hxitk/HxItkImageImporter.h"
#include "hxitk/HxItkProgressObserver.h"

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>

#include <hxfield/HxUniformScalarField3.h>

#include <itkCommand.h>
#include <itkObject.h>
#include <itkProcessObject.h>
#include "itkGenericWatershedImageFilter.h"

namespace {

    /// abstract filter base class
    class HxWatershedFilterBase {
    public:
        HxWatershedFilterBase() {};

        virtual ~HxWatershedFilterBase(){};
        virtual void setLevel(float inLevel) = 0;
        virtual void setThreshold(float inThreshold) = 0;
        virtual void touch() = 0;
        virtual void update() = 0;

        virtual void setResult(HxUniformScalarField3* inResult) = 0;
    };


    template <class SrcType, class DstType>
    class  HxWatershedFilter : public HxWatershedFilterBase
    {
        typedef itk::Image<DstType, 3> OutputImageType;
        typedef itk::Image<SrcType, 3> InputImageType;
        typedef itk::GenericWatershedImageFilter<InputImageType, OutputImageType> WatershedFilterType;

    public:

        HxWatershedFilter(HxUniformScalarField3* inField) {
           watershedFilter = WatershedFilterType::New();
           watershedFilter->ReleaseDataBeforeUpdateFlagOff();
           HxItkImageImporter<SrcType> importer(inField);
           watershedFilter->SetInput(importer.GetOutput());

           progress.startObservingProcessObject(watershedFilter);
           progress.setProgressMessage(McString("Applying watershed segmentation..."));
        }

        ~HxWatershedFilter() {
        }

        void setLevel(float inLevel) {
            watershedFilter->SetLevel(inLevel);
        }

        void setThreshold(float inThreshold) {
            watershedFilter->SetThreshold(inThreshold);
        }

        void touch() {
            watershedFilter->Modified();   
        }

        void update() {
            watershedFilter->Update();
        }

        void setResult(HxUniformScalarField3* inResult) {
           
            const mculong* dims = inResult->lattice.dimsLong();
            
            // Set output image region
            typename OutputImageType::SizeType size;
            size[0] = dims[0];
            size[1] = dims[1];
            size[2] = dims[2];

            typename OutputImageType::IndexType start;
            start[0] = 0;
            start[1] = 0;
            start[2] = 0;

            typename OutputImageType::RegionType region;
            region.SetSize( size );
            region.SetIndex( start );

            watershedFilter->GetOutput()->SetRegions( region );
            
            // Provide the Amira lattice data buffer
            DstType* buffer = static_cast<DstType* >(inResult->lattice.dataPtr());
            mculong voxelCount = dims[0] * dims[1] * dims[2];
            bool deleteInputBuffer = false; // do not delete the Amira lattice data buffer
            watershedFilter->GetOutput()->GetPixelContainer()->SetImportPointer(
                       buffer,
                       voxelCount,
                       deleteInputBuffer);
            watershedFilter->GetOutput()->Allocate();
        }
    
    private:
        HxItkProgressObserver progress;
        typename WatershedFilterType::Pointer watershedFilter;
    };

}; //end namespace

class HXMULTICOMP_API HxWatershedSegmentation :  public HxCompModule {

    MC_HEADER( HxWatershedSegmentation);

public:
    ///Constructor
    HxWatershedSegmentation();

    ///Destructor
    ~HxWatershedSegmentation();

    /// Update method
    virtual void update();

    /// Compute method
    virtual void compute();

    void doIt();

    HxPortFloatSlider mPortThresholdSlider;
    HxPortFloatSlider mPortLevelSlider;
    /// Output data prim type 
    HxPortMultiMenu   mPortOutputPrimType;
    HxPortDoIt        mPortDoIt;

protected:

    virtual int canCreateData(HxData* data, McString& createCmd);

    template <class SrcType> 
    HxWatershedFilterBase* filterFactory(HxUniformScalarField3* srcField);

private:

    bool mImageDataTouched;
    bool mThresholdTouched;

    HxWatershedFilterBase *mWatershedFilter;

};
#endif

/// @}
