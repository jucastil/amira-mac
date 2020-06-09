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
#ifndef HXITKIMAGEIMPORTER_H
#define HXITKIMAGEIMPORTER_H

#include <hxfield/HxUniformScalarField3.h>

#include <itkImportImageFilter.h>

/** This class implements a generic wrapper of Amira data objetcs of type
    HxUniformScalarField3 with a prim type of \c Type into an itk::Image<Type,3> object.
    
    The following illustrates how to pipe Amira data into the ITK filter pipeline, where inField
    is of type HxUniformScalarField3 with a prim type \c Type.
    
    \verbatim
    ...
    typedef itk::Image< Type, 3 > ImageType;
    typedef itk::AnITKImageFilter<ImageType, ImageType > FilterType;

    FilterType::Pointer filter = FilterType::New();

    HxItkImageImporter<Type> importer(inField);
    filter->SetInput(importer.GetOutput());
    ...
    \endverbatim
    
*/
template<class Type>
class HxItkImageImporter
{
    typedef itk::Image<Type,3> OutputImageType;

public:
    
    /** Constructor
        \param inField
               Amira data object of type HxUniformScalarField3 which should be
               wrapped as itk::Image object.
    */
    HxItkImageImporter(HxUniformScalarField3* inField)
    {
        mField = inField;
    }
    
    /// Default DTOR
    virtual ~HxItkImageImporter() {}
     
    /** Returns a pointer of the wrapped Amira HxUniformScalarField3 data object
        to the itk::Image object.

        \return OutputImageType::Pointer 
                Pointer to an itk::Image object which can be used in the ITK filter pipeline.
    */
    const typename OutputImageType::Pointer GetOutput()
    {
        typedef itk::ImportImageFilter<Type,3>  ImportImageFilterType;
        typename ImportImageFilterType::Pointer importFilter = ImportImageFilterType::New();

        const mculong* dims = mField->lattice.dimsLong();
        typename ImportImageFilterType::SizeType size;
        size[0] = dims[0];
        size[1] = dims[1];
        size[2] = dims[2];

        typename ImportImageFilterType::IndexType start;
        start.Fill( 0 );
        typename ImportImageFilterType::RegionType region;
        region.SetIndex( start );
        region.SetSize( size );
        importFilter->SetRegion( region );

        McVec3f origin = mField->getBoundingBoxOrigin();
        importFilter->SetOrigin(&origin[0]);

        McVec3f voxelSize = mField->getVoxelSize();
        importFilter->SetSpacing(&voxelSize[0]);

        mculong numberVoxels = dims[0] * dims[1] * dims[2];
        importFilter->SetImportPointer( (Type*)mField->lattice.dataPtr(), numberVoxels, false );
        importFilter->Update();
        return importFilter->GetOutput();
    }

private:
    /// Inaccessible default constructor
    HxItkImageImporter();
    /// Inaccessible copy constructor
    HxItkImageImporter(const HxItkImageImporter&);
    /// Inaccessible asign operator
    void operator=(const HxItkImageImporter&);

    HxUniformScalarField3* mField;
};

#endif //HXITKIMAGEIMPORTER_H

/// @}
