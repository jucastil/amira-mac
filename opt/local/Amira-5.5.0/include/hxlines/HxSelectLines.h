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

/// @addtogroup hxlines hxlines
/// @{
#ifndef HXSELECTLINES
#define HXSELECTLINES

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxConnection.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxSelectRoi.h>
#include <anna/AnnaExpression.h>
#include "HxLinesWinDLLApi.h"

/** Select a subset of the lines by using regions of interest, a labelfield or
  * an expression evaluated on the data values per point. Only lines or line
  * segments that fullfil all requirements are copied from the input line set
  * to the output line set.
  */
class HXLINES_API HxSelectLines : public HxCompModule
{
    HX_HEADER(HxSelectLines);

  public:
    HxSelectLines();

    // This method will be called when the port changes.
    virtual void compute();

    /// this module will update the interface and compute some statistics
    virtual void update();

    /// add a Labelfield and use it instead of the roi's
    HxConnection portLabelfield;

    /// add the first two regions of interest, more regions can be added appon request
    HxConnection portRoi1, portRoi2;

    /// info field with information to linesets
    HxPortInfo portInfo;

    /// enable or disable the expression field (because of speed)
    HxPortToggleList portOptions;
 
    /// select for which Material you like to restrict the display,
    /// this field is only visible if a label field is connected
    HxPortMultiMenu portMaterials;

    /// select which data per point you would like to see,
    /// this field is only visible if the options checkbox is selected
    HxPortText portExpression;

    /// Do something only of the user insists.
    HxPortDoIt portAction;

    /// if set to true two SelectRoi will be connected initially to the field
    bool useInitTwo;
protected:
    McDArray<HxConnection *> portConnectionList;

    // we have analytic expressions as well to specify the lineset we like
    McDArray<double> mVarVals; 
    AnnaExpression mAnnaExpr;
    bool           mExpressionIsValid;
};

#endif

/// @}
