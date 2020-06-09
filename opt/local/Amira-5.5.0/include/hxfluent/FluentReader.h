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

/// @addtogroup hxfluent hxfluent
/// @{
#ifndef _FluentReader_h_
#define _FluentReader_h_

#include <stdio.h>
#include <ctype.h>
#include <mclib/McAutoInit.h>
#include <mclib/McTypedPointer.h>
#include <mclib/McVec3f.h>

#include <amiramesh/HxParamBundle.h>

#include <hxfluent/HxFluentWinDLLApi.h>

enum {ok=1,format_error=0};


//#define PATCH_ID 222
//#define MATERIAL_ID 333 // old bundle structur
//#define MATERIAL_ID 334 // new bundle structur

//////////////////////////////////////////////////
// Classes and structs for Fluent Grid Sections //
//////////////////////////////////////////////////

class HXFLUENT_API Face{
public:
    enum {none=-1, mixed=0, linear=2, triangular=3, quadrilateral=4, polygonal=5};
    enum {
        noType=-1,
        interior=2,
        wall=3,
        pressureInlet=4,
        pressureOutlet=5,
        symmetry=7,
        periodicShadow=8,
        pressureFarField=9,
        velocityInlet=10,
        periodic=12,
        fan=14,
        massFlowInlet=20,
        bcinterface=24,
        parent=31,
        outflow=36,
        axis=37
    };

private:
    int nPoints;
    int* data;
    int boundaryConditionType;
    int zoneID;

public:
    int getPoint(int idx) const {
        return data[idx]-1;
    }

    int getNumPoints() const {
        return nPoints;
    }

    int getCell(int idx) const {
        return data[nPoints+idx];
    }

    int getBoundaryConditionType() const {
        return boundaryConditionType;
    }

    int getZoneID() const {
        return zoneID;
    }

    Face(int nPoints, int* data, int bcType, int zoneID) :
        nPoints(nPoints)
       ,data(data)
       ,boundaryConditionType(bcType)
      ,zoneID(zoneID)
    {
    };

    static const char* bcNameType(int bcType);
};

struct Cell{
    enum {none=-1, mixed=0, triangular=1, tetrahedral=2, quadrilateral=3,
          hexahedral=4, pyramid=5, wedge=6, polyhedral=7};

    McDArray<int> faces;
    int cellType;
    int cellCondition;
    unsigned int zoneID;
    Cell(){ cellType = cellCondition = zoneID = 0; };
};



//////////////////////////////////////////////////
// Classes and structs for Fluent Data Sections //
//////////////////////////////////////////////////

class DataField{
public:
    DataField(){
        zoneID = firstID = elementSize = 0;
        data.resize(0);
    };
    int zoneID;
    int firstID;
    int elementSize;
    McDArray<float> data;
};

class HXFLUENT_API DataSubSection{
public:
    class idTxt
    {
    public:
        int id;
        McString name;
        idTxt(int id,const char* name){
            this->id = id;
            this->name = name;
        }
    };
    static McDArray<idTxt>* subsectionNames;
    static void initSubsectionNames();
    static McAutoInit doInit;
    static McString findSubsectionName(int id);

    DataSubSection(){
        subSectionID = 0;
        dataFields.resize(0);
    };
    int subSectionID;

    McString subSectionName() {
        return DataSubSection::findSubsectionName(subSectionID);
    }

    McDArray<DataField> dataFields;
};

class FluentData{
public:
    int nCells;
    int nFaces;
    int nNodes;
    McDArray<DataSubSection> subSections;

    FluentData(){
        clear();
    };
    void clear()
    {
        nCells = nFaces = nNodes = 0;
        subSections.resize(0);
    };
};

//////////////////////////////////////////////////
// struct cntaining Amira's patch informatfion
struct Patch{
    int innerRegion;
    int outerRegion;
    McDArray<int> triangles;
};

class FluentReader;

// Fluent File
class HXFLUENT_API FluentFile{
    friend class FluentReader;

public:
    enum {
        CONTAINS_TRIANGULAR_CELLS=1,
        CONTAINS_TETRAHEDRAL_CELLS=2,
        CONTAINS_QUADRILATERAL_CELLS=4,
        CONTAINS_HEXAHEDRAL_CELLS=8,
        CONTAINS_PYRAMID_CELLS=16,
        CONTAINS_WEDGE_CELLS=32,
        CONTAINS_POLYHEDRAL_CELLS=64
    };
    int nTriOrQuadFaces;

    int nTriangularCells;
    int nQuadrilateralCells;
    int nTetrahedralCells;
    int nHexahedralCells;
    int nPyramidalCells;
    int nWedgeCells;
    int nPolyhedralCells;

    struct FaceZoneInfo {
        int zoneId;
        int bcType;
        int faceType;
        int firstIdx;
        int lastIdx;

        const char* bcLabel() const;

        FaceZoneInfo(int zoneId, int bcType, int faceType, int firstIdx, int lastIdx);
    };

    int getNumFaceZones() {
        return faceZones.size();
    }

    FaceZoneInfo getFaceZoneInfo(int idx) {
        return faceZones[idx];
    }


    McString filename;
    McDArray<McVec3f> vertices;
    McDArray<Cell> cells;
    McDArray<Patch> patches;
    HxParamBundle materials;
    FluentData data;

    McDArray<int> nodeZones;
    McDArray<int> cellZones;

    Face getFace(mclong idx) {
        return Face(faces[idx].nPoints,&faceData[faces[idx].idxInFaceData],faces[idx].boundaryConditionType,faces[idx].zoneID);
    }

    mclong getNumFaces() {
        return faces.size();
    }

    void clearFaces() {
        faces.clear();
        faceData.clear();
    }

    McDArray<int> getFaceZoneIDs();
    McDArray<int> getFaceBcTypes();

    int getFaceZoneBCType(int id);

    void addSorted(McDArray<int>& idArray,int id);

    void addNodeZone(int nodeZone);
    void addFaceZone(int faceZone,int bcType, int faceType, int firstIdx, int lastIdx);
    void addCellZone(int cellZone);

    ///  these faces/cells seem to be omitted in the datafile's grid section
    int nParentFaces;
    int nParentCells;
    int nPeriodicFaces;
    int nPeriodicShadowFaces;

    FluentFile(){
        cellTypeMask = 0;
        contains_data = false;
        dimension = -1;
        nParentFaces = nParentCells = 0;
        nPeriodicFaces = nPeriodicShadowFaces = 0;
        nTriOrQuadFaces = 0;

        nTriangularCells = nQuadrilateralCells = nTetrahedralCells = 0;
        nHexahedralCells = nPyramidalCells = nWedgeCells = 0;
        nPolyhedralCells = 0;

    };

    void setDimension(int dim){dimension = dim;};
    int getDimension(){ return  dimension;};

    bool containsCells(){ return (cellTypeMask!=0);};
    bool containsCellType(int type){ return (type&cellTypeMask);};

    bool containsGrid(){ return (vertices.size()>0);};
    bool containsData(){ return contains_data;};

    mclong getNumGridCells() {
        if (containsGrid()) return cells.size();
        else return data.nCells;
    }

    mclong getNumGridFaces() {
        if (containsGrid()) return faces.size();
        else return data.nFaces;
    }

    mclong getNumGridVertices() {
        if (containsGrid()) return vertices.size();
        else return data.nNodes;
    }

    // free memory
    void clearGridInformation()
    {
        cellTypeMask = 0;
        dimension = -1;
        vertices.clear();
        cells.clear();
        faces.clear();
        patches.clear();
        materials.removeAll();
        faceZones.clear();
        cellZones.clear();
        nodeZones.clear();
    };
    void clearDataInformation()
    {
        contains_data = false;
        data.clear();
    };

    bool belongsToSameGrid(FluentFile* other);

private:
    int cellTypeMask;
    bool contains_data;
    int dimension;

    struct FaceInfo {
        int nPoints;
        int boundaryConditionType;
        int zoneID;
        mclong idxInFaceData;

        FaceInfo() {
            nPoints = 0;
            zoneID = -1;
            boundaryConditionType = Face::noType;
            idxInFaceData = 0;
        }

    };

    McDArray<FaceInfo> faces;
    McDArray<int> faceData;

    McDArray<FaceZoneInfo> faceZones;

    FluentFile(const FluentFile&);
    void operator=(const FluentFile&);
};

class HXFLUENT_API FluentError {
    McString msg;
public:
    FluentError(const char* format, ...);
    McString getMsg() const;
};

class HXFLUENT_API FluentReader{

  public:
    enum
    {
        // Fluent grid sections
        commentID=0,
        headerID=1,
        dimensionID=2,
        machineConfigID=4,
        nodeID=10,
        cellID=12,
        faceID=13,
        // Fluent data sections
        gridSizeID=33,
        dataFieldID=300,
        residualID=301,
        // Amira patches and materials
        patchID=222,
        materialID=334
    };

    /// Constructor.
    FluentReader();

    // The destructor should be hidden.
    virtual ~FluentReader();

    FluentFile* Read( const char* filename );

    // Read in-memory fluent data (for testing).
    FluentFile* Read(const char* label, const char* data, size_t dataLength);

    class AbstractFile {
    public:
        int scanf(const char* format, int* len);
        int scanf(const char* format, void* arg1, int* len);
        int scanf(const char* format, void* arg1, void* arg2, int* len);
        int scanf(const char* format, void* arg1, void* arg2, void* arg3, int* len);
        int scanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, int* len);
        int scanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, int* len);
        int scanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, int* len);
        int scanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, int* len);

        virtual int doGetc() = 0;
        virtual size_t doRead(McTypedPointer t, int n) = 0;
        virtual ~AbstractFile() {}
    protected:
        virtual int doScanf(const char* format, int* len) = 0;
        virtual int doScanf(const char* format, void* arg1, int* len) = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, int* len)  = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, int* len)  = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, int* len)  = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, int* len)  = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, int* len)  = 0;
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, int* len)  = 0;
    };


  private:

    FluentFile* ffile;

    class FILEFile : public AbstractFile {
    public:
        FILEFile(const char* filename);
    private:
        virtual int doScanf(const char* format, int* len);
        virtual int doScanf(const char* format, void* arg1, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, int* len);
        int doGetc();
        size_t doRead(McTypedPointer t, int n);
        ~FILEFile();

        FILE* fp;
    };

    class InMemoryData : public AbstractFile {
    public:
        InMemoryData(const char* data, size_t dataLength);
    private:
        virtual int doScanf(const char* format, int* len);
        virtual int doScanf(const char* format, void* arg1, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, int* len);
        virtual int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, int* len);
        int doGetc();
        size_t doRead(McTypedPointer t, int n);

        size_t pos;
        size_t length;
        const char* data;

    };

    int doScanf(const char* format, int* len);
    int doScanf(const char* format, void* arg1, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, void* arg3, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, int* len);
    int doScanf(const char* format, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, int* len);

    int doGetc();
    size_t doRead(McTypedPointer t, int n);

    AbstractFile* fluentDataStream;
    FluentFile* parse(const char* filename);



    // endianess
    bool useBigEndian;

    /// read binary n elements form file
    size_t READBINARY(McTypedPointer t , int n);



    int ReadMachineConfigSection();

    // basic read methods
    void scanFailed(int args, int res, int count, const char* info);

    int ReadWSCR(int& c);
    int ReadWS(int& c);
    int ReadInt(int& c, int& index);
    int ReadHex(int& c, int& index);
    int ReadString(int& c);
    int ReadString(int& c, McString& text);
    int ReadWord(int& c, McString& text);
    int ReadLineEnd(int &c, McString& text);

    int ReadClosingBrackets(int num);
    int ReadSection();

    // read methods for Fluent Grid Sections
    int ReadComment();
    int ReadHeader();
    int ReadDimension();

    int ReadNodes(int binary);
    int ReadNodeDeclaration(int binary);
    int ReadNodeCoordinates(int zone_id, int binary);

    int ReadCells(int binary);
    int ReadCellDeclaration(int binary);
    int ReadCellGroups(int zone_id, int binary);
    void updateCellTypeMask(int elem_type, int num);

    int ReadFaces(int binary);
    int ReadFaceDeclaration(int binary);
    int ReadFaceNodes(int zone_id, int binary);

    // read methods for Fluent Data Sections
    int ReadGridSize();
    int ReadDataField(int binary, int sectionID);

    // read methods for Amira Material and Patch Section
    int ReadParamBundle(int& c, HxParamBundle& bundle);
    int ReadMaterials();
    int ReadPatches();

    //
    int ReadUnknownSection();
    int ReadUnknownBinarySection(int sectionID);

    int readDataInt(int n, int* data, bool isBinary);

};

#endif

/// @}
