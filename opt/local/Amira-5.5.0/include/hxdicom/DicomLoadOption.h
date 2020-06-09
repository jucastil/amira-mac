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
#ifndef DICOM_LOAD_OPTIONS_H
#define DICOM_LOAD_OPTIONS_H


#include <hxdicom/HxDicomWinDLLApi.h>

#include <mclib/McHashTable.h>
#include <mclib/McString.h>

#include <dicom/dicom.h>


// DICOM load options for a certain DICOM Data Element (group, element)
// --------------------------------------------------------------------
class HXDICOM_API DicomLoadOption : public McHandable {

public:

    // default constructor (creates default option)
    DicomLoadOption (void);

    enum  Id {DC_IGNORE     = 0x0001, 
              CONSTANT   = 0x0002,
              MONOTONOUS  = 0x0004, 
              STRONG_MONOTONOUS = 0x0008, 
              LINEAR = 0x0010, 
              NUM_OPTIONS = 5};

    // initialization constructor (default option)
    DicomLoadOption (int group, int element,
		     Id defaultOption = DC_IGNORE,
		     const char * name = NULL,
		     int options = DC_IGNORE|CONSTANT);

    // default destructor
    ~DicomLoadOption () {}

    // set load options
    void setOptions (int  options);

    // set value
    void setValue (DicomLoadOption::Id  option);

    // assign a group to the load options
    void setGroup (int  group) {theGroup = group;}

    // return the group id of this options
    int  group (void) {return(theGroup);}

    // assign a group to the load options
    void setElement (int  element) {theElement = element;}

    // return the element id of this options
    int  element (void) {return(theElement);}

    // return current value of this option
    Id value() { return currValue; }

    // return the name of the option
    const char * name (void) {return(theName.getString());}

    // assign a new name
    void  setName (const char *name) {theName = name ? name : "unknown";}

    // return the number of possible values
    int numAllowedOptions();

    // return enum-value of i-th option
    Id getOption(int which);

    // return enum-value and textual description of i-th option
    void getOption(int which, DicomLoadOption::Id& key, McString& name);

    // return a short description of this option
    McString  description (int  option);

    // convert object to string representation
    McString toString();

    // convert string representation to object's attributes
    int fromString(McString str);

protected:


private:
    int  theGroup;
    int  theElement;
    Id   currValue;
    int allowedValues;

    McString  theName;
    //    McHashTable<int, McString>  theOptions;
};


#endif

/// @}
