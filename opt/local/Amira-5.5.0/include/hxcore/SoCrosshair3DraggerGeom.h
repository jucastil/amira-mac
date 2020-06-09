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

/// @addtogroup hxcore hxcore
/// @{
const unsigned char SoCrosshair3Dragger::geomBuffer[] = {
    0x23,0x49,0x6e,0x76,0x65,0x6e,0x74,0x6f,0x72,0x20,0x56,0x32,0x2e,0x30,0x20,0x62,
    0x69,0x6e,0x61,0x72,0x79,0x20,0x20,0x0a,0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,
    0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
    0x00,0x00,0x00,0x03,0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x14,0x63,0x72,0x6f,0x73,
    0x73,0x68,0x61,0x69,0x72,0x58,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x4c,0x69,0x67,0x68,
    0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x42,0x41,0x53,0x45,
    0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,
    0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,0x75,0x73,0x65,0x43,
    0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x65,0x6d,0x69,0x73,
    0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
    0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,0x68,0x00,0x00,0x00,
    0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x4c,0x69,0x6e,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
    0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,0x45,0x44,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,0x53,0x65,0x74,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,
    0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x02,
    0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
    0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x1a,0x63,0x72,0x6f,0x73,0x73,0x68,0x61,0x69,
    0x72,0x58,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,0x41,0x63,0x74,0x69,
    0x76,0x65,0x00,0x00,0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,
    0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x4c,0x69,0x67,0x68,0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x42,0x41,0x53,0x45,0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,
    0x72,0x69,0x61,0x6c,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,
    0x75,0x73,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,
    0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,
    0x65,0x6d,0x69,0x73,0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,
    0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,
    0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,
    0x68,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
    0x4c,0x69,0x6e,0x65,0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,
    0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x08,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,
    0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,
    0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,
    0x45,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x14,0x63,0x72,0x6f,0x73,
    0x73,0x68,0x61,0x69,0x72,0x59,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x4c,0x69,0x67,0x68,
    0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x42,0x41,0x53,0x45,
    0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,
    0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,0x75,0x73,0x65,0x43,
    0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x65,0x6d,0x69,0x73,
    0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
    0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,0x68,0x00,0x00,0x00,
    0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x4c,0x69,0x6e,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
    0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,0x45,0x44,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,0x53,0x65,0x74,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,
    0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x02,
    0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
    0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x1a,0x63,0x72,0x6f,0x73,0x73,0x68,0x61,0x69,
    0x72,0x59,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,0x41,0x63,0x74,0x69,
    0x76,0x65,0x00,0x00,0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,
    0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x4c,0x69,0x67,0x68,0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x42,0x41,0x53,0x45,0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,
    0x72,0x69,0x61,0x6c,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,
    0x75,0x73,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,
    0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,
    0x65,0x6d,0x69,0x73,0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,
    0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,
    0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,
    0x68,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
    0x4c,0x69,0x6e,0x65,0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,
    0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x08,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,
    0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,
    0x45,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x14,0x63,0x72,0x6f,0x73,
    0x73,0x68,0x61,0x69,0x72,0x5a,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x4c,0x69,0x67,0x68,
    0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x42,0x41,0x53,0x45,
    0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,
    0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,0x75,0x73,0x65,0x43,
    0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x65,0x6d,0x69,0x73,
    0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
    0x3f,0x33,0x33,0x33,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,
    0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,0x68,0x00,0x00,0x00,
    0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x4c,0x69,0x6e,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
    0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,0x45,0x44,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,0x53,0x65,0x74,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,
    0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x02,
    0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
    0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x1a,0x63,0x72,0x6f,0x73,0x73,0x68,0x61,0x69,
    0x72,0x5a,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,0x6f,0x72,0x41,0x63,0x74,0x69,
    0x76,0x65,0x00,0x00,0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,
    0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x4c,0x69,0x67,0x68,0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x42,0x41,0x53,0x45,0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,
    0x72,0x69,0x61,0x6c,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,
    0x75,0x73,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,
    0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,
    0x65,0x6d,0x69,0x73,0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x3e,0xb8,0x51,0xec,0x3d,0x4c,0xcc,0xcd,0x3e,0xe1,0x47,0xae,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,
    0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,
    0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x4c,0x49,0x4e,0x45,0x53,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x6c,0x69,0x6e,0x65,0x57,0x69,0x64,0x74,
    0x68,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
    0x4c,0x69,0x6e,0x65,0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,
    0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,
    0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,
    0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,
    0x00,0x00,0x00,0x08,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0xbf,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,
    0x3c,0xcc,0xcc,0xcd,0xbc,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0x3c,0xcc,0xcc,0xcd,
    0x3c,0xcc,0xcc,0xcd,0x3f,0x00,0x00,0x00,0xbc,0xcc,0xcc,0xcd,0x3c,0xcc,0xcc,0xcd,
    0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,
    0x53,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x73,0x74,0x79,0x6c,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,
    0x45,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,
    0x53,0x65,0x74,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,
    0x74,0x49,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0b,0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0x44,0x45,0x46,0x00,0x00,0x00,0x00,0x12,0x63,0x72,0x6f,0x73,
    0x73,0x68,0x61,0x69,0x72,0x33,0x46,0x65,0x65,0x64,0x62,0x61,0x63,0x6b,0x00,0x00,
    0x00,0x00,0x00,0x09,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x4c,0x69,0x67,0x68,
    0x74,0x4d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,
    0x6d,0x6f,0x64,0x65,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x42,0x41,0x53,0x45,
    0x5f,0x43,0x4f,0x4c,0x4f,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,
    0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x08,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,
    0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x0c,0x64,0x69,0x66,0x66,0x75,0x73,0x65,0x43,
    0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x01,0x3f,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,
    0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x65,0x6d,0x69,0x73,
    0x73,0x69,0x76,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
    0x3f,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0c,0x74,0x72,0x61,0x6e,0x73,0x70,0x61,0x72,0x65,0x6e,0x63,0x79,
    0x00,0x00,0x00,0x01,0x3f,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
    0x00,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x3f,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,
    0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x44,0x72,0x61,0x77,0x53,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x73,0x74,0x79,0x6c,
    0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x46,0x49,0x4c,0x4c,0x45,0x44,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x46,0x61,0x63,0x65,0x53,0x65,0x74,0x00,
    0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0a,0x73,0x74,0x61,0x72,0x74,0x49,0x6e,0x64,
    0x65,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x6e,0x75,0x6d,0x56,0x65,0x72,0x74,0x69,0x63,0x65,0x73,0x00,0x00,0x00,0x00,0x01,
    0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00
};

/// @}
