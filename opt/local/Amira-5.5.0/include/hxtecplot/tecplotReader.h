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

/// @addtogroup hxtecplot hxtecplot
/// @{
#ifndef TECPLOTREADER_WIN_DLL_API_H
#define TECPLOTREADER_WIN_DLL_API_H

class HxScalarField3;
class HxData;
class HxCurvilinearCoord3;

#include <mclib/McVec3f.h>

#include <stdio.h>

#define MAX_LENGTH 4096
#define MAX_VARIABLES 1024
#define MAX_ZONES 256

class tecPlotReader {
public:
	void readDummyBinary();
	tecPlotReader(const char* filename, FILE *_fp);
	~tecPlotReader();
	int readAllBinary();
	int readAllASCII();
	
protected:
	void readTitleASCII();
	void readVariablesASCII();
	void readZoneASCII();
    void readIJKRegularLine(const McDArray<McVec3f>& coords, const McDArray<McDArray<float> >& fields);
    void readIJKRegularSurface(McDArray<McVec3f>& coords,McDArray<McDArray<float> >& fields, int nI, int nJ);

	void readIJKRegular(const bool bBlockFormat);
	int readIJKRegularGridCoordinatesBlock(const int numPoints, const bool bReadZCoord, int& startIndex, HxCurvilinearCoord3* pCoords);
	void readIJKHexa();
	void readFETriangleQuad();
	void readFETetra();
	void readFEHexa();

    /**
        \param numPoints total number of points to read. Might be zero. In that case: Read as much as possible.
        \param numCoordVars number of coordinates stored in file. if for example numCoordVars=2, we have a grid embedded in 2D
    
    */
    void readDataFromFile(int numPoints, int numCoordVars, McDArray<McVec3f>& coords, McDArray<McDArray<float> >& fields, bool bBlockFormat);

    // track the number of registered data. Set the correct load commands when several
    // grids and fields are stored in a tecplot file.
	void registerData(HxData *geom, HxScalarField3 **fields);

    void registerData(HxData* dataObj, char* name);
    int  numberOfRegisteredData;

	float getNextValueASCII(int *index);
	void readDummyASCII();
	void readZoneBinary();
	void readZoneDataBinary();
	void readGeometryBinary();
	void readTextBinary();
	void readCustomLabelBinary();
	void buildIt();

    /**
        Reads the next ascii line via fgets in "currentBuffer" and removes leading whitespaces / tabs.
        Returns 0 if eof was reached, otherwise currentBuffer.
    */
    char* readLineInCurrentBuffer();

	FILE *fp;
	char currentBuffer[MAX_LENGTH];
    
    McDArray<McString> m_variableNames;

    char zoneFormat[MAX_ZONES][132],elementType[MAX_ZONES][132],titleString[MAX_ZONES][132],fileName[4096];
	int nVariables, nI[MAX_ZONES], nJ[MAX_ZONES], nK[MAX_ZONES], nN[MAX_ZONES], nE[MAX_ZONES];
	bool dynamicData;
	bool initTitle;
	bool initVariables;
	bool flagContinue;
	bool isBinary;
	int nZone,currentZone;

    enum IJGridReadMethod
    {
        IJ_ASK = -1,               // show a dialog and ask.
        IJ_SURFACE = 0,            // read as surface.
        IJ_CURVILINEAR = 1,        // read as curvilinear grid.
        IJ_CURVILINEAR_BLOWUP = 2
    };

    IJGridReadMethod m_ijGridReadMethod;

    /**
        decodes the given string and counts the number of numbers delimited by one of " \t,"
    */
    static int getNumberOfFloatsInString(const char* str);
};

#endif


/// @}
