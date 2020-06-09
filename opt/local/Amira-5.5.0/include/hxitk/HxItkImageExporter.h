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

/// @addtogroup hxitk hxitk
/// @{
#ifndef HX_ITK_IMAGE_EXPORTER
#define HX_ITK_IMAGE_EXPORTER

#include <mclib/McPrimType.h>

#include <hxfield/HxUniformScalarField3.h>


/** This class implements a generic wrapper of an ITK image object of type \c TOutputImage itk::Image<Type,3> 
    with a prim type of \c Type into a HxUniformScalarField3 data object.
    Basically two different approches exist: 

    - Provide the buffer of an existing HxUniformScalarField3 data object for the ITK output image of type 
    \c TOutputImage itk::Image<Type,3> with a prim type of \c Type of the last process object of the filtering pipeline:
    
    \verbatim
    ...

    HxUniformScalarField3* resultField = new HxUniformScalarField3(dims, Type); 

    typedef itk::Image< Type, 3 > ImageType;
    typedef itk::AnITKImageFilter<ImageType, ImageType > FilterType;

    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(importer.GetOutput());

    HxItkImageExporter<ImageType> exporter(filter->getOutput, resultField);
    
    filter->Update();

    ...
    \endverbatim

    - Use the buffer of the ITK output image of type \c TOutputImage itk::Image<Type,3> with a prim type of \c Type 
    of the last process object of the filtering pipeline an provide it as buffer for a to be created HxUniformScalarField3.

    \verbatim
    ...

    typedef itk::Image< Type, 3 > ImageType;
    typedef itk::AnITKImageFilter<ImageType, ImageType > FilterType;

    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(importer.GetOutput());

    HxItkImageExporter<ImageType> exporter(filter->getOutput);
    
    filter->Update();

    HxUniformScalarField3* resultField = exporter->getResult();

    ...
    \endverbatim
    
*/

template <class TOutputImage>
class HxItkImageExporter
{
public:
  
    /** Constructor
        @param outputImage The output image which should be mapped to a HxUniformScalarField3
        @param resultField Result field whose buffer should be provided for the ITK image.
    */
    HxItkImageExporter(TOutputImage* outputImage, HxUniformScalarField3* resultField=0)
        : mOutputImage(outputImage), 
          mResult(resultField)
    {
        if (outputImage && mResult) {
            const mculong* dims = resultField->lattice.dimsLong();

            // Set output image region
            typename TOutputImage::SizeType size;
            size[0] = dims[0];
            size[1] = dims[1];
            size[2] = dims[2];

            typename TOutputImage::IndexType start;
            start[0] = 0;
            start[1] = 0;
            start[2] = 0;

            typename TOutputImage::RegionType region;
            region.SetSize( size );
            region.SetIndex( start );

            outputImage->SetRegions( region);
            
            
            // Provide the Amira lattice data buffer
            typename TOutputImage::PixelType* buffer = static_cast<typename TOutputImage::PixelType* >(resultField->lattice.dataPtr());
            mculong voxelCount = dims[0] * dims[1] * dims[2];
            bool deleteInputBuffer = false; // do not delete the Amira lattice data buffer
            outputImage->GetPixelContainer()->SetImportPointer(
                                buffer,
                                voxelCount,
                                deleteInputBuffer);
            outputImage->Allocate();
        }
    }
    
    /** Returns a pointer of type HxUniformScalarField3 of the wrapped ITK image of type \c TOutputImage 
        itk::Image<Type,3> with a prim type of c\ Type. 

        @param Pointer to a HxUniformScalarField3 

        Note: If no valid pointer of type HxUniformScalarField3 has been provided via the constructor a new
        HxUniformScalarField3 will be created, taking over the buffer of the ITK image of type \c TOutputImage 
        itk::Image<Type,3> with a prim type of c\ Type. In order to avoid memory leaks the result Amira data object 
        of type HxUniformScalarField3 is ref counted via a McHandle. Use a McHandle to store the result in order 
        to increase the reference count of the result Amira data object, otherwise it will be deleted within the 
        of this class destructor! 
    */
    HxUniformScalarField3* getResult() 
    { 
        if (mOutputImage && !mResult) {
            typename TOutputImage::RegionType region;
            region = mOutputImage->GetBufferedRegion();
            
            int dims[3];
            typename TOutputImage::SizeType  size  = region.GetSize();
            typename TOutputImage::IndexType start = region.GetIndex();
            dims[0] = size[0];
            dims[1] = size[1];
            dims[2] = size[2];

            float bbox[6];

            typename TOutputImage::SpacingType spacing = mOutputImage->GetSpacing();
            typename TOutputImage::PointType origin    = mOutputImage->GetOrigin();

            bbox[0] = origin[0];
            bbox[1] = origin[0] + spacing[0] * (dims[0]-1);
            bbox[2] = origin[1];
            bbox[3] = origin[1] + spacing[1] * (dims[1]-1);
            bbox[4] = origin[2];
            bbox[5] = origin[2] + spacing[2] * (dims[2]-1);

            typename TOutputImage::PixelContainer* container;
            container = mOutputImage->GetPixelContainer();
            container->SetContainerManageMemory( false);
            typename TOutputImage::PixelType* buffer = container->GetBufferPointer();
            
            mResult = new HxUniformScalarField3(dims, McPrimType(buffer), buffer);
            mResult->coords()->setBoundingBox(&bbox[0]);
        }
        return mResult; 
    }

private:
    /// Inaccessible default constructor
    HxItkImageExporter();
    /// Inaccessible copy constructor
    HxItkImageExporter(const HxItkImageExporter&);
    /// Inaccessible asign operator
    void operator=(const HxItkImageExporter&);

    TOutputImage*          mOutputImage;
    McHandle<HxUniformScalarField3> mResult;

};
#endif


/// @}
