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

/// @addtogroup hxcore hxcore
/// @{
#ifndef PFM_INCLUDE
#define PFM_INCLUDE

#include <stdio.h>
#include <mclib/McString.h>
#include <hxcore/HxAmiraWinDLLApi.h>

/** @name PFM
    Provides some base routines (wildcard substitution, directory scan) */
//@{

/**  This routine tests a string against a wild card
     pattern. The wild characters are '*' and '?'.
     '*' matches an arbitrary sequence of characters
     while '?' matches any single character. Returns <True>
     if the match is successful. */
HXCORE_API int	pfm_wildMatch(const char* str, const char* pat);
/// Find a praefix of @c pattern in @c str of maximal length.
HXCORE_API char*	pfm_strmaxspn(char* str, const char* pattern);
/// 
HXCORE_API int	pfm_scanDir(int n, const char* const* pat, char**& res); 
/// 
HXCORE_API void	pfm_scanDirFree(int n, char**& res);
/** Converts a list of strings into floats. 
    Returns the number of floats that have been read.
*/
HXCORE_API int	convertToFloat(float** vals , int ac, char** av, int minalloc);
/** Converts a list of strings into ints.
    Returns the number of ints that have been read.
*/
HXCORE_API int	convertToInt(int** vals, int ac, char** av, int minalloc);
/// Reads words from a file.
HXCORE_API int	nextWord(FILE* fp, McString& word);
//@}

#endif // PFM_INCLUDE

/// @}
