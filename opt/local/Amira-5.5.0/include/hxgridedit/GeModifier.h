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

/// @addtogroup hxgridedit hxgridedit
/// @{
#ifndef GeMODIFIER_H
#define GeMODIFIER_H

#include <hxgridedit/HxGridEditWinDLLApi.h>

//#include <X11/Intrinsic.h>

enum  ParamType  { PT_INT, PT_FLOAT, PT_SELECTMENU, PT_SEPARATOR};

class HxGridEdit;

class HXGRIDEDIT_API GeModifier {

  public:

    /** the inherited modifier has to store its defaults in a static struct
	of the following type: */
    struct parameterDescription {      
      const char  *name;
      float       defaultValue;
      float       defaultMin;
      float       defaultMax;
      ParamType   type;
    };

    /** here the actual parameter values are stored */
    struct parameterList {
      float   value;
      float   min;
      float   max;
    };

    /// Constructor.
    GeModifier(HxGridEdit* editor,
	       const char *fName, 
	       parameterDescription *pD, 
	       int n);

    /// Destructor.
    ~GeModifier();


    // const char* getName() { return theName; }

    /// Apply method.
    virtual void modify() = 0;

    /// Number of parameters of the Modifier (dimension of param[])
    const int            nParam;

    /// A struct - array *, containing information on the parameters
    parameterDescription *paramDescription;

    /// The actual parameter values.
    parameterList        *param;
    
    
    /// Name of the Modifier.
    char                 name[40];

  protected:
    HxGridEdit*      theGridEdit;
};

#endif


/// @}
