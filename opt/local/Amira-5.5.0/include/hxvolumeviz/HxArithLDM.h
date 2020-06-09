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
#ifndef HXARITHLDM_H
#define HXARITHLDM_H

#include <hxvolumeviz/HxVolumeVizAPI.h>

#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortDoIt.h>

#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/nodes/SoGroup.h>
#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoDataCompositor.h>

class HXVOLUMEVIZ_API HxArithLDM : public HxSpatialData {
  MC_HEADER(HxArithLDM);
public:
  HxArithLDM();
  virtual ~HxArithLDM();

  HxPortDoIt        portDoIt;
  /// Optional second input.
  HxConnection      portInputA;

  /// Optional second input.
  HxConnection      portInputB;

  /// Optional third input.
  HxConnection      portInputC;

  /// Expressions
  HxPortText portExpr;

  virtual void update();
  virtual void compute();
  virtual void getBoundingBox(float bbox[6]) const;

  SoDataCompositor* getGraphHeader() {
    if (m_doDataComposition)
      return m_dataCompositor;
    return 0;
  }

  virtual void getRange(float& min, float& max, RangeType rangeType=RAW_DATA);

  SoVolumeData* getVolumeData(int vdId) {
      if (vdId < m_vd.size())
          return m_vd[vdId];
      else
          return 0;
  }

  virtual McColor getIconColor();

  virtual void info() {};

protected:
  McHandle<SoGroup> m_arithGroup;
  McDArray<McHandle<SoVolumeData> > m_vd;

  McHandle<SoDataCompositor> m_dataCompositor;

  static void dataSetCallback(SoDataSet* ds, const SbVec3i32& bufferDimension, void *bufferToTransform,
                              const SbBox3i32& dataBox, int resolutionLevel, void* userData);

  McDArray<McString> m_variableNames;
  McDArray<McString> m_variables;
private:
  HxConnection* portInput[3];
  bool m_doDataComposition;
};

#endif /* HXARITHLDM_H */

/// @}
