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

/// @addtogroup hxdicom hxdicom
/// @{
#ifndef HX_DICOM_IMAGE_H
#define HX_DICOM_IMAGE_H


#include <hxdicom/HxDicomWinDLLApi.h>

#include <mclib/McPrimType.h>
#include <mclib/McHandable.h>
#include <mclib/McVec3f.h>

#include <amiramesh/HxParamBundle.h>

#include <dicom/dicom.h>
#include <hxdicom/HxDicomFile.h>


// Dicom Image class for Amira
// ---------------------------
class HXDICOM_API HxDicomImage : public McHandable {

    friend class HxDicomFile;

public:

    // constructor (image MUST belong to a DICOM file)
    // a HxDicomImage will be deleted if it's owner is deleted
    HxDicomImage (const HxDicomFile  &owner, void  *image = 0);

    // destructor
    ~HxDicomImage (void);

    // image attributes
    int    width  (void) const {return(WidthInPixel);}
    int    height (void) const {return(HeightInPixel);}
    int    depth  (void) const {return(BitsPerPixel);}
    int    size   (void) const {return(SizeInBytes);}
    int    number (void) const {return(Number);}
    int    samplesPerPixel (void) const {return(SamplesPerPixel);}
    int    planarConfiguration (void) const {return(PlanarConfiguration);}
    float  allocatedBytes  (void) const {return(AllocatedBytesPerPixel);}
    float  sliceLocationMM (void) const {return(SliceLocation_MM);}
    float  xPixelSizeMM (void) const {return(X_PixelSize_MM);}
    float  yPixelSizeMM (void) const {return(Y_PixelSize_MM);}
    float  thicknessMM  (void) const {return(SliceThickness_MM);}
    int    isOblique (void) const {return(Oblique);}
    McVec3f positionMM (void) const {return(Position_MM);}
    int    hasPosition (void) const {return(Position);}
    float  slope() const { return(Slope); }
    float  intercept() const { return(Intercept); }

    McVec3f orientation(int i) const {
	return ((i<0 || i>2)?  McVec3f(0.,0.,0.) : Orientation[i]);}
    
    /** Compare each image orientation vector's components (x,y,z) starting with orientation
        vector Orientation[0]. 

        @param refImage 
        @param tolerance Allowed tolerance per vector component.
        @return Returns 0 if all components of all orientation vectors lie within the specified tolerance.
                       -1 if the first non matching component is smaller than the same refImage's component.   
                        1 if the first non matching component is larger than the same refImage's component.
    */
    int compareOrientation(const HxDicomImage& refImage, float tolerance = 0.001f) const;

    McPrimType  primType (void) const;

    // read access to the DICOM file, image belongs to
    const HxDicomFile  &owner (void) const {return(Owner);}

    // read access to the pixel data
    const void  *pixelData (void) const;

    // retrieve the data range of the image
    // return false if no data are available yet
    bool  dataRange (int  *min, int  *max);

    // return the parameters of the image (pointer for insertions)
    HxParamBundle  *parameters (void) {return(&theParameters);}

    // access to specific Dicom data elements of the owner
    const char  *dicomInfo (u16bit  group, u16bit  element)
                           {return(Owner.dicomInfo(group, element));}
    const char  *dicomInfo (const char *name)
                           {return(Owner.dicomInfo(name));}

    // load image data into the given memory
    const void  loadToMemory (void * mem) const;

    // possibility to externally override slice location
    void  setSliceLocationMM (float location) {SliceLocation_MM = location;}

protected:

    // pixel value manipulation
    void  adjustDataRange (float  offset = -1000, float slope=1.0);
    void  adjustHighBit (int  highBit);

    // in case image data were not specified on construction (reload)
    void  setDataPointer (void  *image) {PixelData = image; MinDataValue = 1; MaxDataValue = 0;}

private:

    // images reside within a DicomFile
    const HxDicomFile  &Owner;

    // when DicomFile is deleted, images are too
    const void  *PixelData;

    // attribute initialization
    void  initialize (void);

    // get data range of the image
    // member templates are not supported on all platforms
    //template<class T> void  computeDataRange (T *pixel, int  nPixel,
    //                                        int  *minVal, int  *maxVal);

    // DICOM parameters (image specific)
    HxParamBundle  theParameters;

    // set all slice specific parameters from the owner
    void  setParameters (void);

    // private attributes of an image
    int    WidthInPixel;
    int    HeightInPixel;
    int    BitsPerPixel;
    int    SizeInBytes;
    int    SamplesPerPixel;
    int    PlanarConfiguration;
    int    Number;
    float  AllocatedBytesPerPixel;
    float  X_PixelSize_MM;
    float  Y_PixelSize_MM;
    float  SliceLocation_MM;
    float  SliceThickness_MM;
    int    Oblique;
    int    Position;
    McVec3f Position_MM;
    McVec3f Orientation[3];
    float  Slope;
    float  Intercept;
    int    MinDataValue;
    int    MaxDataValue;
    bool   SignedPixelValues;
};


#endif

/// @}
