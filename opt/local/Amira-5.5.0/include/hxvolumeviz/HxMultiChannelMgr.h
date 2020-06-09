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
#ifndef HX_MULTI_CHANNEL_MGR_H
#define HX_MULTI_CHANNEL_MGR_H

#include <mclib/McHandle.h> 
#include <mclib/McDArray.h>

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPickStyle.h>

#include <VolumeViz/nodes/SoROI.h>
#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoDataRange.h>
#include <VolumeViz/nodes/SoVolumeShader.h> 

#include <hxcolor/HxColormap256.h>
#include <hxfield/HxPortMultiChannel.h>

#include <hxvolumeviz/HxArithLDM.h>
#include "HxVolumeVizAPI.h"

// @TOBEREVIEWED_ALL
class HxVolumeData;
class HxPortMultiMenu;
class HxPortFloatTextN;
class HxMultiChannelField3;
class SoFragmentShader;
class SoDataRange;

class HXVOLUMEVIZ_API HxMultiChannelMgr
{
public:
    virtual SoGroup* getScenegraph() = 0;

    SbBox3f getVolumeBoundingBox();

protected:
    HxMultiChannelMgr(bool a_is3D);
    virtual ~HxMultiChannelMgr();

    void buildScenegraph();

    virtual void addHeadScenegraph(){};
    virtual void addTailScenegraph(){};

    bool updateData(HxVolumeData* singleChannelData, HxPortColormap& portColormap, HxMultiChannelField3* multiChannelData = 0, HxPortMultiChannel* multiChannelPort = 0, float gamma = 1.0f, HxArithLDM* arithData = 0);

    bool setPixelShader(SoFragmentShader * shader);

    void buildColorMaps(HxPortMultiMenu* portMappingType, HxMultiChannelField3* multiChannelData,
        HxPortFloatTextN* portRange, HxPortColormap* portColormap,
        HxPortRadioBox* portLookup, HxPortRadioBox* portTransparency,
        HxPortFloatSlider* portGamma = NULL);
    void tfill(SoTransferFunction * tf, const HxColormap* cmap, double minData, double maxData, float minCMap, float maxCMap, int colorMapType, int transparencyType) const;
    void setColor(float * tptr, int tsize, int idx, const float rgba[4], int nc, int transparencyType) const;

    virtual void updateBoundingBox(float*);

    /**
       Change the data range of the @c idx data. This call must be followed by a call to buildColorMaps.
       By default, the data range is set to the DataWindow parameter range and then, if not defined,
       to the defined values range.
    */
    virtual void updateDataRange(int idx, float minRange, float maxRange);

    bool buildShader(int numChannels, bool is3D) ;

    void setVolumeDataStorageHint(SoVolumeData::StorageHint storageHint);
    void setVolumeDataPalettedTexture(bool usePalettedTexture);
    SbVec3i32 getVolumeSize();


    void computeROI(HxConnection& portData, HxConnection& portROI);

    McHandle<SoPickStyle> m_pickStyle;
    McHandle<SoSwitch>    m_roiSwitch;
    McHandle<SoROI>       m_roi;

    HxMultiChannelField3* m_hxMultiChannelVolData;

    bool m_multiChannelEnabled;

    HxColormap * getDefaultColormap() const;

    McDArray<SoVolumeData*>             m_volumeDataList;
  private:
    bool                                     m_is3D;
    McDArray< McHandle<SoTransferFunction> > m_transferFunctionList;
    McDArray< McHandle<SoDataRange> >        m_dataRangeList;
    McDArray< McHandle<HxColormap> >         m_colormapList;
    McDArray< SbVec2f >                      m_dataWindow;

    McHandle<SoGroup>                   m_scenegraph;
    McHandle<SoSwitch>                  m_volShaderSwitch;    
    McHandle<SoVolumeShader>            m_volShader;

    SoFragmentShader*                   m_fragmentShader;
    McHandle<SoNode>                    m_arithLDMHeader;
};

#endif

/// @}
