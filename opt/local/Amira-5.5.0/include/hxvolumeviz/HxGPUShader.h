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
#ifndef HXGPUSHADER_H
#define HXGPUSHADER_H

#include "HxVolumeVizAPI.h"

#include <Inventor/nodes/SoShaderObject.h> 
#include <Inventor/nodes/SoFragmentShader.h>

#include <hxcore/HxData.h>
#include <hxcore/HxPortFilename.h>

#include <mclib/McFilename.h>

#include <map>

// Example: simple.glsl
// Simple fragment shader
//
// <ShaderParameters version="1.0">
//     <Description> Simple fragment shader </Description>
//     <UniformParameter name="rgb" type="3f"> 
//         <UIWidget type="TextEdit" default="1.0 0.0 0.0"> color value </UIWidget>
//     </UniformParameter>
//     <UniformParameter name="show" type="1i" >
//         <UIWidget type="None" default="1"></UIWidget>
//     </UniformParameter>
//     <UniformParameter name="alpha" type="1f" >
//         <UIWidget type="Slider" default="1" min="0" max="1" step="0.1"> alpha value</UIWidget>
//     </UniformParameter> 
// </ShaderParameters>

class SoShaderParameter;

class HXVOLUMEVIZ_API HxGPUShader : public HxData
{
  MC_HEADER(HxGPUShader);
public:
  /// Constructor.
  HxGPUShader();

  /// GLSL filename
  HxPortFilename portFilename;

  /// Compute method
  virtual void compute();

  /// Reads a glsl shader object from a file.
  static int read(const char *filename);

  SoFragmentShader * getFragmentShader() const { return m_fragmentShader; }
protected:
  
  /// Destructor
  virtual ~HxGPUShader();

  virtual void info();

  bool parseFile(const McFilename & filename);
  
private:
  McHandle<SoFragmentShader> m_fragmentShader;

  std::map<HxPort*, SoShaderParameter*> m_parameters;

  McString m_description; //<! shader description

  friend class GlSlHandler;
};
#endif //!HXGPUSHADER_H

/// @}
