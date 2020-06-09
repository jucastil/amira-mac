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

/// @addtogroup hximio hximio
/// @{
#ifndef XSTRING_H
#define XSTRING_H
//#pragma message(">>>>>  xstring: included enhanced string")


// windows: use secure C libraries with VS2005 or higher
#if ( defined(_MSC_VER) && (_MSC_VER >= 1400) )
#define HAVE_SECURE_C
#pragma message(">>>>>  xstring: using secure c libraries")
#endif

#include <string>
#include <stdarg.h>

class xstring: public std::string {
public:
    // constructors
    explicit xstring(): std::string() {}
    xstring( const char *cstr ): std::string() { *this += cstr; }

    /*
    xstring( const value_type* _Ptr,
    size_type _Count = npos ) : std::string( _Ptr, _Count ) {}
    */
    xstring( const std::string& _Right,
        size_type _Roff = 0,
        size_type _Count = npos ) : std::string( _Right, _Roff, _Count ) {}

    xstring( size_type _Count,
        value_type _Ch ) : std::string( _Count, _Ch ) {}

    template <class InputIterator >
    xstring( InputIterator _First,
        InputIterator _Last ) : std::string( _First, _Last ) {}

    // members
    xstring &sprintf(const char *fmt, ...);
    xstring &saddf(const char *fmt, ...);
    xstring &insertAfterLast(const char *p, const xstring &s);

    static xstring xprintf(const char *fmt, ...);

    xstring &removeSpacesLeft();
    xstring &removeSpacesRight();
    xstring &removeSpacesBoth();

private:
    xstring &sprintf( const char *format, va_list ap );
};


#endif // XSTRING_H

/// @}
