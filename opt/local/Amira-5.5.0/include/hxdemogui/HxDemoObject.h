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

/// @addtogroup hxdemogui hxdemogui
/// @{
#ifndef HX_DEMOOBJECT_H
#define HX_DEMOOBJECT_H


#include <mclib/McFilename.h>
#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <hxdemogui/HxDemoGUIWinDLLApi.h>
#include <hxdemogui/HxDemoAttributes.h>


class HxDemoObject;


/** information that describes a demo for an Amira demoSequence.*/
class HXDEMOGUI_API HxDemoObject : public McHandable
{

  public:

    /// Default constructor, creates an empty demo object
    HxDemoObject (void) {}

    /// Returns true if demo information is complete
    bool  isValid (void) const;

    /// Returns true if demo object is a demo container
    bool  isGroup (void) const;

    /// Returns true if demo object is a demo
    bool  isDemo (void) const;

    /// Returns true if demo object is empty
    bool  isNull (void) const;

    /// Returns true in case the step sequence cannot be modified
    bool  isStatic (void) const;

    /// Returns true in case a valid icon is given
    bool  hasIcon (void) const;

    /// Convenience function, representing an empty HxDemoObject
    static HxDemoObject  emptyDemo (void) { return HxDemoObject(); }

    struct DemoStep
    {
        int number;
        McString  name;
        McString  command;
        McString  jump;
        McString  description;
        McString  icon;
    };

    McFilename  descriptionFile;
    HxDemoAttributes  demoAttributes;
    McString  name;
    McString  description;
    McString  iconFile;
    McString  responsible;
    McFilename  directory;
    McFilename  scriptFile;
    McDArray<DemoStep>  steps;
    McString  type;
    McString  stepMode;

};


#endif

/// @}
