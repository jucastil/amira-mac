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

/// @addtogroup taglib taglib
/// @{
#include <mclib/McDArray.h>
#include <mclib/McString.h>

#define TAGSTARTPLAIN "47RalfKubis11"
#define TAGSTOPPLAIN  "11sibuKflaR74"

// the following are the "hashed" tags used in the tag scanner program code
// in this way it's assured that the tags don't appear in the object code section holding the tag scanner code
#define TAGSTART      "4#7#R#a#l#f#K#u#b#i#s#1#1#"
#define TAGSTOP       "1#1#s#i#b#u#K#f#l#a#R#7#4#"

/**
  * This functions gathers and stores some system information into the given string.
  */
void setInfo( char * inFilePath, char * inDst, int inLen, int inPreserve=1, int inIsPatch=0 );


/**
  * This functions scans the given file for the version literal string which is tagged by
  * a start and an end tag. If inReplace is zero, the stored version string is scanned and
  * the file remains untouched. If inReplace is nonzero, setInfo() gets called and the
  * version string inside the file gets replaced. Additionally this function computes
  * the md5 checksum of the file even if it gets altered when inReplace is nonzero.
  *
  * @param  inFilePath  path of the file to scan
  * @param  inReplace   zero: scan version string, remain file untouched
  *                     nonzero: update version string
  * @param  outMd5      the resulting md5 checksum
  * @param  outVersion  the scanned version string
  * @param  inTagCmd    additionally per tag commands. each consists of a triple of McStrings: <cmd-id><tag><value>
  *                     so the length of inTagCmd is a multiple of 3
  * @return             0 on success
  */
int scanFile( char * inFilePath, int inReplace, unsigned char outMd5[16], McString & outVersion, McDArray<McString> * inTagCmd = 0 );


/**
  * This functions parses a version string into the single tag-value pairs.
  *
  * the value string is structured like this:
  * "tag|value|tag|value|tag|value|......."
  *
  * @param  inVersion   version string
  * @return             reference to an internal static array containing the tag-value pairs
  *                     tag-value-tag-value-tag-value........
  */
McDArray<McString> & versionParse( char * inVersion );

/**
  * The counterpart to parseVersion().
  */
char * versionAssemble( McDArray<McString> & inVersionArray );


/**
  * removes a tag-value pair.
  */
void   versionDelTag( McDArray<McString> & inVersionArray, McString & inTag );

/**
  * checks for a tag-value pair.
  */
int   versionHasTag( McDArray<McString> & inVersionArray, McString & inTag );


/**
  * Executes a single command on the version array.
  */
void versionExecCmd( McDArray<McString> & ioVersionArray, McString & inCmd, McString & inTag, McString & inVal );

/**
  * Executes a bunch of commands on the version array.
  */
void versionExecCmd( McDArray<McString> & ioVersionArray, McDArray<McString> * inCmdArray );


/**
  * Executes relevant commands on the windows PE file structure,
    which can be seen in the properties of a dll or an executable.
  */
#ifdef _WINDOWS
bool versionExecCmdWindows(McDArray<McString> * inCmdArray, char* filename);
#endif

/// @}
