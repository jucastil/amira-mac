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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_MULTI_FIELD
#define HX_MULTI_FIELD

#include <mclib/McPrimType.h>
#include <hxfield/HxRegField3.h>
#include <hxfield/HxLocation3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxPortChannelConfig;
class HxColormap;
class Hxspatialdata;

/** This class is a proxy object which groups multiple HxRegScalarField3
objects (channels). It offers the possibility to edit a color and a data
range for each channels. */

class HXFIELD_API HxMultiChannelField : public HxSpatialData{

  HX_HEADER(HxMultiChannelField);

public:

  /// Constructor.
  HxMultiChannelField();

  /// Returns number of channels.
  int getNumChannels() const;

  int getNumChannelsExt() const { return channels.size(); }

  /// Returns scalar field representing the specified channel.
  HxSpatialData* getChannel(int which) const;

  HxSpatialData * getChannelExt(int which) const;

  virtual int parse(Tcl_Interp* t, int argc, char **argv);

  virtual void savePorts(FILE* fp);

  /** Returns the preferred data window of the specified channel.
  The preferred data window is displayed for each channel in
  a separate config port. It can be changed interactively. */
  void getDataWindow(int which, float& min, float& max) const;

  /** Returns a channel's color. Like the data window,the channel's
  color is also displayed for each channel in the config port
  and can be changed interactively. */
  void getColor(int which, McColor& color) const;

  /** Returns a channel's alpha. Like the data window,the channel's
  alpha is also displayed for each channel in the config port
  and can be changed interactively. */
  float getAlpha(int which) const;

  /// Returns a channel's colormap.
  HxColormap * getColormap(int which) const;

  virtual void update();

  virtual void compute();

  virtual bool acceptConnect(HxConnection*);

  virtual void notifyConnect(HxConnection*);

  virtual void notifyDisconnect(HxConnection*);

  virtual int saveCreation(FILE* fp, const char* path, int flags);

  /// To set the accepted channels types.
  virtual bool checkType(HxObject* object);

  /// To know if a channel is valid.
  virtual bool checkValidity(HxObject* object);

  static int sourceCheck(void* userdata, HxObject* object);

  void setFireEnabled(bool value);

private:

  void forceSaveChannels();

protected:
  /// Destructor.
  ~HxMultiChannelField();
  
  /// Icon color (light gray).
  virtual McColor getIconColor();

  HxPortChannelConfig* config;

  void addFreeChannel();

  McDArray<HxPortChannelConfig*> channels;
  McDArray<HxPortChannelConfig*> freeChannels;
  bool mBlockChannelDelete;
};

#endif

/// @}
