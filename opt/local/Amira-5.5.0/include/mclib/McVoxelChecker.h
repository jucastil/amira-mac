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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_CHECKER_H
#define MC_CHECKER_H

#include "McWinDLLApi.h"

/** @name Checker classes
    Some checker classes as needed by mcFloodFill2D and
    mcFloodFill3D.
    Checker classes provide a @c check() method which performs some sort of
    testing on its argument. The method returns 1 if the test was successful, 0
    otherwise. Checker class are designed to be used together with
    global flood fill methods. This class can be used with the
    mcFloodFill methods. See mcFloodFill2D, mcFloodFill3D.
*/

//@{

/// This class checks an item with a predefined reference value.
template<class T>
class McEqualityChecker {

 public:
    /// Check method.
    int check(const T& pixel,int x,int y,int z=0) {
	return (value==pixel);
    }
  /// Check method.
    int check2(const T& pixel, const T& last,int x,int y,int z=0) {
       return (value==pixel);
    }

    /// Initializes the checker class.
    void init(const T& value) {
	this->value = value;
    }

 protected:
    T value;
};

/// This class checks if an item lies within a given data range.
template<class T>
class McRangeChecker {

 public:
    /// Check method.
    int check(const T& pixel,int x,int y,int z=0) {
	return (minVal<=pixel && pixel<=maxVal);
    }

    /// Check method.
    int check2(const T& pixel, const T& last,int x,int y,int z=0) {
		if (!considerLast)
		    return check(pixel,x,y,z);
		return ((last>=minVal && last<=maxVal &&
	         pixel>=minVal && pixel<=maxVal) ||
	        (pixel<minVal && pixel<=last) ||
		(pixel>maxVal && pixel>last));
    }

    /// Initializes the checker class.
    void init(const T& minVal, const T& maxVal, int considerLast=1) {
		this->minVal = minVal;
		this->maxVal = maxVal;
		this->considerLast = considerLast;
    }

 protected:
	 int considerLast;
    T minVal;
    T maxVal;
};

//@}

#endif

/// @}
