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

/// @addtogroup amiramesh amiramesh
/// @{
#ifndef HX_PARAM_EDIT_CHECK_H
#define HX_PARAM_EDIT_CHECK_H

#include <amiramesh/AmiraMeshWinDLLApi.h>

class HxParamBase;
class HxParamBundle;
class HxParameter;

/** Default edit checker class. An edit checker may be registered with any 
    object of type HxParamBase. The checker provides a number of
    methods which are called before operations like renaming or deletion
    are performed. Checkers are used in two ways. On the one hand they may
    disallow certain edit operations (check method returns 0). On the other
    hand they may update some other data structure whenever a parameter is
    changed. 

    If no edit checker is registered with a parameter, automatically the
    default checker provided by this class is used.
*/

class AMIRAMESH_API HxParamEditCheck
{
  public:
    /// Constructor.
    HxParamEditCheck() { }

    /// Destructor.
    virtual ~HxParamEditCheck();

    /// Returns 1 unless flag NO_RENAME is set.
    virtual int checkRename(HxParamBase* param, const char* newName);

    /// Returns 1 unless flag NO_DELETE is set.
    virtual int checkDelete(HxParamBase* param);

    /// Returns 1 unless flag NO_INSERT_BUNDLE is set.
    virtual int checkInsertBundle(HxParamBundle* bundle, const char* name);

    /// Returns 1 unless flag NO_INSERT_PARAM is set.
    virtual int checkInsertParam(HxParamBundle* bundle, const char* name);

    /// Returns 1 unless flag NO_SETVALUE is set.
    virtual int checkSetValue(HxParameter* param, const char* newValue);

    /// Returns pointer to default edit checker.
    static HxParamEditCheck* defaultEditCheck();
};

#endif

/// @}
