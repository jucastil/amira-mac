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

/// @addtogroup hxradioss hxradioss
/// @{
#ifndef HXRADIOSSVIEW_H
#define HXRADIOSSVIEW_H

#include <Inventor/nodes/SoCube.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcolor/HxPortColormap.h>
#include <hxradioss/HxRadiossAPI.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMultipleCopy.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMarkerSet.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>

#include <hxradioss/HxRadiossData.h>

class HXRADIOSS_API HxRadiossView : public HxModule {

  HX_HEADER(HxRadiossView);

public:
  HxRadiossView();

  ~HxRadiossView();

  HxPortFloatSlider portSize;
  // Connection to a colormap.
  HxPortColormap portColormap;

  virtual void compute();
  virtual void update();

  // Tcl command interface.
  //    virtual int parse(Tcl_Interp* t, int argc, char **argv);

protected:
  McHandle<SoSeparator> group[HxRadiossData::LAST];
  McHandle<SoMultipleCopy> planeWalls; 
  McHandle<SoMultipleCopy> cylWalls; 
  McHandle<SoMultipleCopy> cylJoints; 
  McHandle<SoIndexedLineSet> rbodyLineSet; 
  McHandle<SoMarkerSet> rbodyMarkerSet; 
  McHandle<SoMarkerSet> admasMarkerSet; 
  McHandle<SoMarkerSet>  cloadMarkerSet; 
  McHandle<SoMultipleCopy> accels; 
  McHandle<SoIndexedLineSet> sectLineSet; 
  McHandle<SoMultipleCopy> springs;
  McHandle<SoMultipleCopy> truss; 
  McHandle<SoMultipleCopy> beams; 
  McHandle<SoMarkerSet> springMarkerSet; 
  McHandle<SoMarkerSet> trussMarkerSet; 
  McHandle<SoMarkerSet> beamMarkerSet; 
  McHandle<SoMarkerSet> cylJointsMarkerSet;

  McHandle<SoMaterial> material;
  McHandle<SoDrawStyle> drawStyle;

  HxRadiossData::Type type;
  SbBool isNew;
};

#endif

/// @}
