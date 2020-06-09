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
#ifndef HX_DICOM_IMAGE_STACK_H
#define HX_DICOM_IMAGE_STACK_H


#include <hxdicom/HxDicomWinDLLApi.h>

#include <stdlib.h>

#include <mclib/McDArray.h>
#include <mclib/McBox3f.h>
#include <mclib/McPrimType.h>
#include <mclib/McString.h>

#include <amiramesh/HxParamBundle.h>

#include <hxfield/HxCoordType.h>

#include <hxdicom/HxDicomImage.h>


// Dicom Image Stack class for Amira
// ---------------------------------
class HXDICOM_API HxDicomImageStack {

public:

    // default constructor
    HxDicomImageStack (void);

    // destructor
    ~HxDicomImageStack (void);

    // name of the stack (typically being the patient's name)
    const char  *name (void) const {return(theName.getString());}

    // alternative name of the stack that can be used as label
    const char  *alternativeName (void) const {return(theAlternativeName.getString());}

    // number of images within stack
    int  numImages (void) const {return(Images.size());}

    // memory size occupied by all images within the image stack
    mcuint64  memSize (void) const;

    // data range (minimum and maximum pixel value within the stack
    const int  *dataRange (void) const {return(theDataRange);};

    // imaging modality
    const char  *modality (void) const {return(theModality.getString());}

    // type of stack (e.g. uniform or stacked coordinates)
    HxCoordType  coordType (void) const {return(theCoordType);}

    // type of stack (e.g. uniform or stacked coordinates)
    void setCoordType (HxCoordType);

    // bounding box of the stack
    const McBox3f  &boundingBox (void) const {return(theBoundingBox);}
    float           boundingBox (int i) const {return(theBoundingBox[i]);}
    const int      *dims (void) const {return(theDimensions);}

    // slice locations in z-direction of the stack
    float  sliceLocationCM (int i) const
           {return(((i >= 0) && (i < sliceLocationsCM.size())) ? 
                   sliceLocationsCM[i] : 0);}

    // orientation of 1st slice
    McVec3f orientation(int i) const {
	return ((Images.size()==0)?  McVec3f(0.,0.,0.) : Images[0]->orientation(i));}

    // stack of oblique slices (not supported yet)
    int isOblique (void) const {return ((Images.size()==0)? 0 : Images[0]->isOblique());}

    float  isSheared (void);

    // public access methods
    int  accept (HxDicomImage *);
    int  append (HxDicomImage *);

    const HxDicomImage * operator[](int i) const {return(Images[i]);}

    enum  DIMS {X = 0, Y = 1, Z = 2};

    // image stack attributes (stringent for all images within stack)
    McPrimType  primType (void) const {return(thePrimType);}

    // put all DICOM data elements into the stacks parameter bundle
    void  setDicomParameters (bool  anonymize = false);

    // DICOM parameter as Amira parameter bundle
    const HxParamBundle  &parameters (void) const {return(theParameters);}

    /** Checks if a data overflow would occur after applying slope and
        intercept for each slice. If an overflow occurs, the method asks
        the user if the slope and intercept values should be corrected
        so that no overflow occurs anymore, or if these values should be
        completely ignored. The method returns two values slope_cor and
        intercept_cor. Within each slice the data values then should be
        corrected as follows:
            
          data = (data * slope + intercept) * slope_cor + intercept_cor

        Note, that slope and intercept may vary from slice to slice, while
        slope_cor and intercept_cor are the same for all slices. These
        values are chosen such that no overflow occurs in any slice. If
        slope and intercept should be completly ignored, slope_cor is set
        to 0 and the above transformation will be skipped.
        
        newPrimType denotes the new primitive data type of the image
        stack after applying the slope and intercept with correction. For
        example, the data type might be unsigned short before and signed
        short afterwards. 
    
        a return value of 'true' signals that a user interaction might be
        necessary */
    bool checkForDataOverflow(float & slope_cor, float & intercept_cor,
                              McPrimType & newPrimType) const;

    // determine the data range for all images within the stack
    void recomputeDataRange (void);

    // assign an alternative name for the image stack
    void  setAlternativeName(const char * name) { theAlternativeName = name; }

protected:

    // some default data windows for CT and MR data
    void  setDataRange (HxDicomImage *);

    // set imaging modality
    void  setModality (HxDicomImage *);

private:

    // array of images forming a 3D image stack
    McDArray<HxDicomImage *>  Images;

    // location of each image in z-direction in centimeters
    McDArray<float>           sliceLocationsCM;

    // should be the patient name
    McString     theName;

    // alternative name (imaging parameters)
    McString     theAlternativeName;

    // uniform or stacked coordinates
    HxCoordType  theCoordType;

    // primitive data type (1 or 2 bytes per pixel are supported)
    McPrimType   thePrimType;

    // width, height and number of slices
    int          theDimensions[3];

    // data range
    int          theDataRange[2];

    // imaging modality
    McString theModality;

    // bounding box in cm (pixel dimensions of a slice and number of slices,
    // according to slice spacing and pixel geometry)
    McBox3f      theBoundingBox;

    // specific DICOM parameters of an image stack
    HxParamBundle  theParameters;

};


#endif

/// @}
