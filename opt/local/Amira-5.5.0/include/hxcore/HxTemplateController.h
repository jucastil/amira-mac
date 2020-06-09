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
#ifndef HX_TEMPLATE_CONTROLLER_H
#define HX_TEMPLATE_CONTROLLER_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McString.h>

/*
  Internal interface for templates networks support.
  Implementation can be found in hxtemplate package.
  If hxtemplate package is not loaded, template networks are not supported.

  HxTemplateController is a singleton, but may be null if hxtemplate is not loaded.
  Each call to one of HxTemplateController methods must be preceded by a check of the singleton:
  if (theTemplateController) theTemplateController->...
*/
class HXCORE_API HxTemplateController
{
public:
    // the singleton accessor. used by hxtemplate to set the instance.
    static HxTemplateController*& getInstance();

    // Returns TRUE when a template network backup is in progress.
    // Since it is based on the normal network backup, this test is used to alter the process if needed.
    virtual bool isSaving() const = 0;
    // Returns TRUE when a template network is being executed.
    // Since it is based on the normal network evaluation, this test is used to alter the process if needed.
    virtual bool isExecuting() const = 0;

    // Notify the template controller that an object has been renamed during template execution.
    // This manages objects created during template execution that whose names could collide with pre-existant ones.
    // "alias" is the object name recorded in template network, "target" is the real object name at runtime.
    virtual void setAlias(const McString & alias, const McString & target) = 0;
    // Retrieve the real object name at runtime from its "alias" recorded in template network.
    // This manages objects created during template execution that whose names could collide with pre-existant ones.
    virtual McString getAliasTarget(const McString & alias) = 0;
    // Notify the template controller that the "target" object is about to be renamed. Its former alias must be purged.
    // This manages objects created during template execution that whose names could collide with pre-existant ones.
    virtual void removeAliasByTarget(const McString & target) = 0;

    virtual ~HxTemplateController();
protected:
    static HxTemplateController* s_instance;
};

#define theTemplateController (HxTemplateController::getInstance())

#endif // HX_TEMPLATE_CONTROLLER_H


/// @}
