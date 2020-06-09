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
#ifndef HX_REPLACE_H
#define HX_REPLACE_H

#include <stdio.h>
#include <mclib/McDArray.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QRegExp;
class McString;

/** Utility class performing text replacements in files. The
    reason this class is located in Amira and not in mclib is that
    it uses QRegExp for evaluation of regular expressions. However,
    mclib is not linked against Qt.

    In order replace text in a file, first create an instance of
    this class. Then define one or more replacements using the
    replace method. The @c originalText argument is a regular
    expression. The replacement text is taken as is. After all
    replacements have been defined, use one of the compute
    methods in order to perform the replacements. */
class HXCORE_API HxReplace
{
  public:
    /// Constructor.
    HxReplace();

    /// Destructor.
    ~HxReplace();

    /// Clears all replacement texts.
    void clear();

    /** Add a replacement text. @c orginalText is a regular
        expression. For details see Qt's QRegExp class.
        If the regular expression is not valid 0 is returned,
        otherwise 1. */
    int replace(const char* orginalText, const char* byThis);

    /** Performs replacement on a file. If @c dstFile is null,
        the original file will be overwritten without warning.
        Returns 1 on success, 0 otherwise. */
    int compute(const char* srcFile, const char* dstFile=0);

    /** Performs replacement on an open file. @c srcFile is assumed
        to be opened for reading, @c dstFile is assumed to be
        opened for writing. Returns 1 on success, 0 otherwise. */
    int compute(FILE* srcFile, FILE* dstFile);

  protected:
    McDArray<QRegExp*> regexs;
    McDArray<McString*> replacements;
};

#endif

/// @}
