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

/// @addtogroup dsstreamer dsstreamer
/// @{
#ifndef __IFSTREAM
#define __IFSTREAM

// IFrameStreamer interface


// { fd501041-8ebe-11ce-8183-00aa00577da1 }
DEFINE_GUID(CLSID_FrameStreamer,
0xe38b8e15,0x5285,0x40dc,0xb4, 0x89, 0x40, 0x9f, 0xb6, 0x60, 0xec, 0x93
);

DEFINE_GUID(IID_IFrameStreamer,
    0xb4713201,0xf44c,0x463c,0xb6, 0x96, 0xd1, 0x94, 0x5b, 0x6c, 0xf2, 0x2c); 
             

#undef  INTERFACE
#define INTERFACE   IFrameStreamer

DECLARE_INTERFACE_(IFrameStreamer,IUnknown)
{
  // *** IUnknown methods ***
  STDMETHOD(QueryInterface) (THIS_
			     REFIID riid,
			     LPVOID FAR* ppvObj) PURE;
  STDMETHOD_(ULONG,AddRef) (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;
  
  // *** IFrameStreamer methods ***
  
  STDMETHOD(PutFrame)(BYTE* pData,long pDataLen,
		      REFERENCE_TIME *pTimeStart,
		      REFERENCE_TIME *pTimeEnd) PURE;
  
  STDMETHOD(GetCurrentMediaType)(AM_MEDIA_TYPE *pmt) PURE;
  
  STDMETHOD(setFormat)(int w,int h,int bpp) PURE;
  
  STDMETHOD(SetFormat)(AM_MEDIA_TYPE* pmt) PURE;
};

#endif

/// @}
