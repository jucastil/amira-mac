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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_SELECT_ROI_LDM_H
#define HX_SELECT_ROI_LDM_H

#include <hxcore/HxModule.h>

#include <hxfield/HxSelectRoi.h>

#include <hxvolumeviz/HxVolumeData.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxfield/HxMultiChannelField3.h>
#include <hxfield/HxPortMultiChannel.h> 
#include <hxcore/HxPortInfo.h>

#include <Inventor/nodes/SoSeparator.h>
#include <VolumeViz/manips/SoROIManip.h>

class SoFieldSensor;

// @TOBEREVIEWED_ALL

/*----------------------------------------------------------------------------*/

class HXVOLUMEVIZ_API HxSelectROILDM : public HxModule
{
    MC_HEADER(HxSelectROILDM);

  public:
    /// Constructor
    HxSelectROILDM();

    /// Update method.
    virtual void update();

    /// Compute method
    virtual void compute();

    /// Controlling: 0=ROI box, 1=Subvolume
    HxPortRadioBox    portControlling;
    enum {M_ROI_CONTROLLING, M_SUBVOLUME_CONTROLLING};

    /// Min bbox
    HxPortIntTextN  portMinimum;

    /// Max bbox
    HxPortIntTextN  portMaximum;

    /// For switching parts of a multi-channel field on or off.
    HxPortMultiChannel portMultiChannel;

    /// Options: 0=Show box
    HxPortToggleList  portOptions;
    enum {M_SHOW_BOX_OPTION};

    /// Cropping Type: 0=Subvolume, 1=Exclusion, 2= Cross, 3=Fence
    HxPortMultiMenu   portCropping;
    enum {M_SUBVOLUME_CROPPING, M_EXCLUSION_CROPPING, M_CROSS_CROPPING, M_FENCE_CROPPING};

    ///
    HxPortButtonList  portAction ;
    enum {M_RESET_ACTION};

    ///
    HxPortInfo portMemSizeInfo;

    /// Returns the ROI node
    SoROI* getROI() const {return m_ROIManip;}
	
  protected:
    virtual ~HxSelectROILDM();
    McHandle<SoSeparator> m_scene;

	virtual void updateBBoxToGUI();

  private:
    void initBBox(const SbVec3i32& volDim);
    void resetBBox(const SbVec3i32& volDim);
    void updateBBoxFromGUI();
    static void ROIManipBoxChangedCB(void *data, SoSensor *);
    static void ROIManipSubVolumeChangedCB(void *data, SoSensor *);

    SoFieldSensor* m_ROIManipBoxSensor;
    SoFieldSensor* m_ROIManipSubVolumeSensor;
    McHandle<SoROIManip> m_ROIManip;
    
    bool           m_isSubVolume;
};

/*----------------------------------------------------------------------------*/

#endif

/// @}
