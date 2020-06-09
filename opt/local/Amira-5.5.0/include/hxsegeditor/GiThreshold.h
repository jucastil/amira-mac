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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GI_THRESHOLD_H
#define GI_THRESHOLD_H

#include <qobject.h>

#include "Gi.h"
#include "GiTool.h"
#include <hxsegeditor/ui_GiThreshold.h>

class GiFrameBuffer;

/// This class implements a simple thresholding tool
class GiThreshold : public QObject, public GiTool { 
  
    Q_OBJECT
  
  public:
    /// Constructor.
    GiThreshold(Gi* theGi);

    /// Destructor.
    ~GiThreshold();
    
    /// Name of threshold tool icon file
    virtual const char* getIconName() const;

    /// Called when tool is activated, enables masking.
    virtual void select();

    /// Called when tool is deactivated, resets masking.
    virtual void deselect(GiFrameBuffer*);

    /// Set option to threshold all slices
    void setAllSlices(bool is3d)
    {
        ui.wAllSlicesCheckBox->setChecked(is3d);
    }

    /// Set option to threshold only within same material
    void setSameMaterialOnly(bool sameMaterialOnly)
    {
        ui.wCurrentMaterialCheckBox->setChecked(sameMaterialOnly);
    }

    /// Performs the thresholding via clicking the "select" button
    void performThresholding()
    {
        ui.wSelectButton->click();
    }

  protected:
    bool mWas3D;
    bool mWasMaskingEnabled;
    Ui::GiThreshold ui;
    virtual void createWidget(QWidget* Parent);

  protected slots:
    void compute();
};

#endif

/// @}
