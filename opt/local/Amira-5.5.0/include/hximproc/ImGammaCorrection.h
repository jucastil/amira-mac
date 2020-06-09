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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IMGAMMACORRECTION_H
#define IMGAMMACORRECTION_H

#include <hxcore/HxPortFloatTextN.h>

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>
#include <mclib/McTypedData3D.h>
#include <hxcore/HxEditor.h>

class HxImageVisionEditor;

/** The sigmoid filter increases a certain intensity range. For the
meaning of the parameters, please see the user's guide */

class HXIMPROC_API ImGammaCorrection : public ImFilter3D
{
    MC_HEADER( ImGammaCorrection);
    
  public:
    /// Constructor.
    ImGammaCorrection(HxEditor* editor=0);
    
    /// Destructor.
    ~ImGammaCorrection();
    
    HxPortFloatTextN portGamma;
    HxPortFloatTextN portRange;

    /// apply filter as documented in ImFilter3D
    void apply3D(McTypedData3D* src,
        McTypedData3D* dst=NULL,
        McProgressInterface* progress=NULL);
 
    
    virtual void update();

    /// Initialize the filter's parameters if necessary
    void initializeParameters(ImFilterParameters *param);

    // Sets the filters parameters if any
    void setParameters(const ImFilterParameters *param);

    // Updates the filter parameters class
    void updateParameters(ImFilterParameters *param);

   

    static ImFilter3D* createFilter(HxEditor* e) {
        return new ImGammaCorrection(e); }


private:

   HxImageVisionEditor* mEditor;
};

#endif

/// @}
