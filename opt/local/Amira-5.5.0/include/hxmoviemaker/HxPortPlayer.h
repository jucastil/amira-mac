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

/// @addtogroup hxmoviemaker hxmoviemaker
/// @{
#ifndef HX_PORT_PLAYER_H
#define HX_PORT_PLAYER_H

#include <hxcore/HxPort.h>

#include <hxmoviemaker/HxMovieMakerWinDLLApi.h>

class QToolButton;

class HXMOVIEMAKER_API HxPortPlayer : public HxPort
{
    MC_ABSTRACT_HEADER( HxPortPlayer );

  public:

      enum { T_PLAYL=0x0010, T_PLAYR=0x0020, T_SEEKL=0x0040, T_SEEKR=0x0080, T_PAUS=0x0100, T_RESUM=0x0200, T_STOP=0x0400 };
     
             HxPortPlayer(HxObject *obj, const char *name );
    virtual ~HxPortPlayer();
    
    int  getPlayButtonState();
    void stop();
    void pauseStart();
    void pauseStop();
    void play( int inBackward=0 );

  protected:
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
  private:
    
    QxGuardedPtr<QToolButton> bPlayL;
    QxGuardedPtr<QToolButton> bPlayR;
    QxGuardedPtr<QToolButton> bPaus;
    QxGuardedPtr<QToolButton> bSeekL;
    QxGuardedPtr<QToolButton> bSeekR;

    // these flags are used if there are no widgets yet
    bool _bPlayLDown;
    bool _bPlayRDown;
    bool _bPausDown;
    bool _bSeekLDown;
    bool _bSeekRDown;
};

#endif

/// @}
