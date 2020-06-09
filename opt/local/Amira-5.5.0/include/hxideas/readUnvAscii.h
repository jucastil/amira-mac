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

/// @addtogroup hxideas hxideas
/// @{
#ifndef READUNVASCII_H_
#define READUNVASCII_H_

#include <mclib/McDArray.h>
#include <vector>

/*---------------------------
   Cell Type Definitions        
 ---------------------------*/

#define UCD_NTYPES              8
#define UCD_NUM_CELL_TYPES      8

#define UCD_POINT               0
#define UCD_LINE                1
#define UCD_TRIANGLE            2
#define UCD_QUADRILATERAL       3
#define UCD_TETRAHEDRON         4
#define UCD_PYRAMID             5
#define UCD_PRISM               6
#define UCD_HEXAHEDRON          7

#define UCD_MAX_NODE_PER_CELL    20

class Ctype {
public:
    int id, mat, n, cell_type;
    Ctype() { id = mat = n = cell_type = 0; };
};

class Ntype {
public:
    int n, node_list[20];
    Ntype() { n=0;};
};

class Mtype {
public:
    char node_data_labels[100], cell_data_labels[100],model_data_labels[100],
	node_data_units[100], cell_data_units[100],model_data_units[100];
    
    int num_nodes, num_cells, num_node_data, num_cell_data, num_model_data,
	node_active_list[20], cell_active_list[20], model_active_list[20],
	num_node_comp, node_comp_list[20], num_cell_comp,cell_comp_list[20],
	num_model_comp, model_comp_list[20], num_nlist_nodes;
    Mtype()
    {
	num_nodes = num_cells = num_node_data = num_cell_data = num_model_data = 0;
	num_node_comp = num_cell_comp =	num_model_comp = num_nlist_nodes = 0;
    };

};

class UniversalFile {
public:

    struct Node {
        int id;
        float x, y, z;
    };

    class Dataset55 {
    public:
	static McString modelTypeTxt[];
	static McString analysisTypeTxt[];
	static McString specDataTypeTxt[];
	
	enum EDataChar { dc_unknown=0, dc_scalar=1, dc_trans=2, dc_transRot=3, 
			 dc_symmetricTensor=4, dc_generalTensor=5};
	enum EDataType {dt_real=2, dt_complex=5};
	enum EAnalysisType { at_unknown=0, at_static=1, at_normalMode=2, at_complexEigenvalueFirstOrder=3, 
			     at_transient=4, at_frequencyResponse=5, at_buckling=6,
			     at_complexEigenvalueSecondOrder=7 };


	static McString paramsUnknown[];
	static McString paramsStatic[];
	static McString paramsNormalMode[]; 
	static McString paramsComplexEigenvalue[]; 
	static McString paramsTransient[];
	static McString paramsFrequencyResponse[];
	static McString paramsBuckling[];
	
	static McString* paramsTxt[];
	
    };
    
    class DataOnNodes {
    public:
	
	enum EDataType {dt_real=2, dt_complex=5};
	enum EDataChar { dc_other=0, dc_scalar=1, dc_trans=2, dc_transRot=3, dc_sym2Tensor=4 };

	class DataUnOrdered {
	public:
	    int nodeID;
	    McDArray<float> values;
	};
	
	DataOnNodes();
	virtual ~DataOnNodes();
	
	int nFloats() const
	{
	    if(dataType == dt_complex)
		return 2*nDataVar;
	    else return nDataVar;
	};

	int dataset;
	int timeStep;

	int nDataVar;
	EDataChar dataChar;
	EDataType dataType;

	int invalidData;
  std::vector<float> orderedData;
	
	int maxNodeID;
	McDArray<DataUnOrdered> unorderedData;
	HxParamBundle parameters;
	bool onElement;
    };

    class DataOnNodesBundle {
    public:
	DataOnNodesBundle();
	virtual ~DataOnNodesBundle();

	void clear();
	
	int dataset;
	McString label;
	McDArray<DataOnNodes*> data;
    };


    McString filename;
    Ctype *cells;
    Mtype model_stats;
    Ntype *cell_nlists;
    float *node_data, *cell_data, *model_data;
    
    int maxNodeID;
    McDArray<Node> nodes;
    McDArray<DataOnNodesBundle> nodeDataBundles;


    UniversalFile();
    virtual ~UniversalFile();

    static UniversalFile* readUnv(const char* filename);

    bool containsCells();
    bool containsOrderedData();
    bool containsUnOrderedData();
    int getMaxNodeID();
    
    void clearAll();
    void clearGrid();
    void clearNodeData();
    void clearCellData();
    void clearModelData();

    ////////////////////////////////////////////////////////////////
    // When reading nodes some node-Id's may be missing/unused,
    // for some reason. -> they must be sorted and mapped correctly 
    // when reading cells or node-data.

    // are there missing/unused node-Id's
    bool nodesOrdered;
    inline bool isNodeOrdered() const {return nodesOrdered;}
    // even if nodes are ordered, there may be an offset 
    // (3,4,5,6,... -> 0,1,2,3,.., offset=3)
    int nodeOffset;
    // check for missing node-Id's, set 'nodesOrdered' 
    // and (if necessary) 'nodeOffset'
    void checkNodeOrder();
    // fix node-id's for all cells
    void relabelCells();
    // map node-id
    int findSorted(const UniversalFile::Node& key) const;
    ////////////////////////////////////////////////////////////////

    DataOnNodesBundle* find(int dataset, const McString& label);
    void insertNodeData(const McString& label, DataOnNodes* don, bool isTimeDependent=0);

private:
    static inline bool read_lines(FILE *fp, int nLines, int dataset);
    static void read_ascii(FILE *fp, UniversalFile& uf);
    static int isHead(const char* str);
    static int isBinary ( FILE* fp);
    static void readUnOrderedData(FILE *fp, UniversalFile& uf, 
				  UniversalFile::DataOnNodes& don);
    static void readOrderedData(FILE *fp, UniversalFile& uf, 
				UniversalFile::DataOnNodes& don);
    static int find_cell_type ( int code );
};


#endif

/// @}
