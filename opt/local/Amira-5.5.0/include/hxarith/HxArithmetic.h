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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_ARITHMETIC
#define HX_ARITHMETIC

#include <anna/AnnaExpression.h>
#include <mclib/McPrimType.h>
#include <mclib/McVec4l.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h> 
#include <hxcore/HxWorkArea.h>
#include <hxarith/HxArithWinDLLApi.h>

#include <hxfield/HxField3.h>
#include <hxfield/HxUniformCoord3.h>
#include <hxfield/HxTetraData.h>
#include <hxfield/HxHexaData.h>

#include <hxsurface/HxSurface.h>
#include <hxsurface/HxSurfaceField.h>

#define HX_ARITHMETIC_NUM_PORTS_INPUT   3

/// Uses an analytic expression to compute a new field

class HXARITH_API HxArithmetic : public HxCompModule
{

  HX_HEADER(HxArithmetic);

  public:
    /// Constructor.
    HxArithmetic();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Optional second input.
    HxConnection      _portInputB;

    /// Optional third input.
    HxConnection      _portInputC;

    /// Number of components of result
    HxPortMultiMenu   _portNumComponents;

    /// User defined number of components of result
    HxPortIntTextN portCustomNumComponents;

    /// Expressions
    McDArray<HxPortText*> _portExpr;

    /// Result type (0=inputA, 1=regular grid).
    HxPortRadioBox    _portResultType;

    /// Location of result (0=OnNode, 1=OnCellCenter)
    HxPortRadioBox    portResultLocation;

    /// Resolution of result grid (relevant if result type is regular).
    HxPortIntTextN    _portResolution;

    /// Default bounding box (min values).
    HxPortFloatTextN  _portMinBox;

    /// Default bounding box (max values).
    HxPortFloatTextN  _portMaxBox;

    /// Options
    HxPortToggleList  _portOptions;

    /// Do it button.
    HxPortDoIt        _portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);


  protected:

    virtual ~HxArithmetic();

    virtual int autoConnect(HxObject* primary);

    /// Calculate the inputs' maximal bounding box
    void calculateMaxBoundingBox(float bbox[6]);

    /// This calls setResult(), touchMinMax(), and sets expr as parameter.
    void touch(HxField3* result);

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);
    
    /** Used to compare undefined values of each input. 
        If one is different, or one as an undefined value whereas another one has not,
        print a warning.
     */
    void checkUndefinedValuesConsitency(bool& currentHasUndefinedValue,
                                        bool newHasUndefinedValue,
                                        double& currentUndefinedValue,
                                        double newUndefinedValue);

    /** Used to compare data windows of each input.
    If one is different, or one as a data window whereas another one has not,
    print a warning.
    */
    void checkDataWindowConsitency(bool& currentHasDataWindow,
                                   bool newHasDataWindow,
                                   double currentDataWindow[2],
                                   const double newDataWindow[2]);

    void setDefaultValue(int input, int iVar, float value);

    void updateExpressionPorts();

    void setMinNumberOfExpressionPorts(int n);

    McString getExpressionLabel(int iExpression);

  public:

    /**
        This structure represents the old "section A" of HxArithmetic_Desc.
        In this class all information is gathered that is needed to construct 
        a field. This class describes a field completely.

        Objects of this class are explicetly copy-constructable and assignable!

    */
    class FieldDescriptor
    {
    public:
        /// Constructs an empty, non-valid FieldDescriptor.
        FieldDescriptor();

        /// initializes a descriptor from an exisiting object
        void initFromObject(HxObject* o);

        /// initializes a regular uniform descriptor
        void initRegularUniform(int dimX, int dimY, int dimZ, const McBox3f& bbox);

        /// Creates a matching field for that descriptor, or 0 if descriptor was not valid.
        /// The caller is responsible of freeing the object.
        HxSpatialData* createField();

        enum GridType { t_undefined = 0, t_anna, t_regular, t_tetra, t_hexa, t_surface };
  
        /**
            Gets the grid type of this descriptor.
        */
        GridType getGridType() const
        {
            return _gridType;
        }

        /**
            Gets the grid bounding box
        */
        McBox3f getGridBoundingBox() const
        {
            return McBox3f(m_bbox);
        }

        SbMatrix getGridTransformObjToWorld() const
        {
            return _transObjToWorld;
        }

        int getNDataVar() const
        {
            return _nDataVar;
        }

        McPrimType getPrimType() const 
        {
            return _primType;
        }

    public:
        /// Part 1: Information about the grid-structure
        GridType        _gridType;  // info: if set t_undefined (==0 ==zero), this HxArithmetic_Desc is invalid and describes no object
        mclong          _gridTypeSub; // if regular:   c_uniform, c_stacked, ... anna: 0
        int             _dims[3];   // dimensions (tetra,hexa: nNodes,nTetras/nHexas,1  -  anna: 0,0,0)

    private:
        McBox3f           m_bbox;   // bounding box
    
    public:
        // transformation
        SbMatrix        _transObjToWorld;
        SbMatrix        _transWorldToObj;

        // some of the structured need some more info of the underlying structures:
        HxTetraGrid*  m_gridTetras;
        HxHexaGrid*   m_gridHexas;
        McHandle<HxCoord3>     m_gridCoord3;
        HxSurface*    m_gridSurface;


        /// Part 2: Information for the field that should be created
        int             _encoding;  // encoding (tetra,hexa: obtained from Data; regular,anna: 0)
        int             _nDataVar;  // number of values per node (may be zero e.g. if only a Grid without Data is connected)
        McPrimType      _primType;  // primitive type of the single node values (valid if _nDataVar>0)
        bool            _isSym2Tensor; // is true for symmetric second order tensors to distinguish them from complex vector fields
        bool            m_hasUndefinedValue; //Tell if the object has an undefined value
        double          m_undefinedValue; //The undefined value
        bool            m_hasDataWindow; //Tell if the object has a data window parameter
        double          m_dataWindow[2]; //Data window values

        /**
            Checks if a field structure that describes this FieldDescriptor matches another one. This method might
            be implemented very strict in the sense of a == - operator. However, this implementation is a bit more relaxed.
        */
        bool isCompatibleTo(const FieldDescriptor& other) const;

        /**
            Checks if the structure (grid) of two FieldDescriptors are compatible. 
        */
        bool hasCompatibleGrid(const FieldDescriptor& other) const;

        /**

        */
    private:
        HxSpatialData* createFieldRegular();

    };

    class HxArithmetic_Desc
    {
    public:

        ////////////////////////////////////////
        // section A - structure info
        ////////////////////////////////////////
        FieldDescriptor m_descriptor;
      
        ////////////////////////////////////////
        // section B - object info
        ////////////////////////////////////////

        // reference to data object
        void          * _dataPtr;   // raw data ( size: dims[0]*dims[1]*dims[2] * _nDataVar * BytesPerValue ), may be NULL !
        McHandle<HxObject>     _object;    // if no direct access to dataPtr is applicable, the HxField3's eval(..) gets used, may be NULL ! OR a ptr to a Grid too

        // possible interfaces of _object
        HxField3      * _IField3;
        HxLattice3    * _ILattice;
        HxTetraData   * _ITetData;
        HxHexaData    * _IHexData;
        HxSurfaceField* _ISurfFld;

        ////////////////////////////////////////
        // section C - connection info
        ////////////////////////////////////////

        // connection object for input ports
        HxConnection  * _connection;// NULL on result 'connection'

        ////////////////////////////////////////
        // section E - helper
        ////////////////////////////////////////

        // some helpers for computation
        int             mNeedsLocation;

        int             _transHasTo;        // nonzero: there is a non-identity transformation between this and the result object
        SbMatrix        _transResultToObj;  // in fact this one ( result._transWorldToObj * this._transObjToWorld )

private:
        int             _di;    // steps for each dimension
        int             _dj;    // if t_regular it is taken from _dims[]
        int             _dk;    // on t_tetra/t_hexa dj == dk == 1, di depends on _encoding and number of nodes & Tetras/Hexas in the Grid

public:

        int             _method;    // lookup method for obtaining values from source data
                                    // (valid for input objects)
                                    // 0 via eval(HxLocation3,..)
                                    // 1 via direct access with _dataPtr
                                    // 2 via HxLattice3::eval(i,j,k,..)
        int             _needPosition;

        ////////////////////////////////////////
        // section F - other stuff
        ////////////////////////////////////////

    private:
        // default values
        McDArray<float>           defaultValues;
    public:

        void setDefaultValue(int iVar, float value);
        float getDefaultValue(int iVar);



        ////////////////////////////////////////
                HxArithmetic_Desc();
               ~HxArithmetic_Desc();
        /// reset
        void    reset( int clearConn = 0 );
        /// fill in with values obtained from a given object ( interfaces, _dataPtr, ... )
        void    setObject( HxObject * o = NULL );
        /// fill in with values obtained from a given object directly given by parameter or obtained by _connection (grid info, data info) - calls setObject()
        /// used during scan of input port data and the eventually existing result object
        void    scanObjectStructure( HxObject * objP );
        /// performs some precomputations for speeding up the final computation process (the big i_j_k_-loop over all the data)
        void    initComputation( HxArithmetic_Desc & result );
        /// instanciates a new object according to values stored in Section A - fills up Section B
        void *  createObject();

        ///
        bool hasValues() {
            return (m_descriptor.getGridType() && mNeedsLocation)
                    || _ISurfFld;
        }



        /// checks, if object containes values needes in the "Big Loop" - i.e. if one of the Anna-terms stored result contains a variable that references to this input object
        int     hasNeededValues(const McDArray<AnnaExpression>& expressions, int firstVar);
        /// checks if the variable with the name varname occours in one of the anna terms of this
        int     isVarNeededForComputation(const McDArray<AnnaExpression>& expressions, const char * varname ) const;

        /**
            Initializes indexing over all dete elements. The method may set additional fields, so indexing
            must not be used several times in parallel at once.
        */
        void indexInit();

        /**
            Method to check if an index is valid. This method must be used in a loop over all elements.
        */
        bool indexIsValid(McVec4l& index);

        /**
            Method to increment the index by 1.
        */
        void indexIncr(McVec4l& index);

        /**
            A small optimization: If the last index increment was a large spatial jump (e.g. end of line),
            a re-initialization of the field3-lookup can be done.
        */
        bool indexWasLargeSpatialJump(const McVec4l& index);

        /// return the number of nodes to be traversed in the main loop of HxArithmetic::compute()
        mclong numNodes();

        /// turn node idx into spatial index
        void turnNodeIdxToSpatialIdx(mclong idx, McVec4l& index);
    };

  private:

    // description of the data
    HxArithmetic_Desc   _descInputs[HX_ARITHMETIC_NUM_PORTS_INPUT]; // inputs
    FieldDescriptor     _descTarget; // required result
    HxArithmetic_Desc   _descResult; // current result

    /// fills _descInputs[]
    void scanInputs();

    /// fills _descResult
    void scanResult();

    ////////////////////////////////////////
    // helper for ::compute() - for better understanding check out namespace HxArithmetic_comp
    ////////////////////////////////////////

    /// get the spatial position of the current result sample in result local coords to p_
    inline void computeGetCurrPosition(const McVec4l& index, 
        SbVec3f* coords, TetraGrid::Tetra* tetras,
        HexaGrid::Hexa* hexas, Surface::Triangle* triangles,
        SbVec3f &pos)
    {
        switch ( _descResult.m_descriptor.getGridType() )
        {
        ////////////////////////////////////////
        case FieldDescriptor::t_regular :
            assert( _descResult.m_descriptor.m_gridCoord3 );
            _descResult.m_descriptor.m_gridCoord3->pos( index.i, index.j, index.k, (float*)pos.getValue() );
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_tetra :
            switch ( _descResult.m_descriptor._encoding )
            {
            case HxTetraData::PER_VERTEX :
                pos = coords[ index.i ];
                break;

            case HxTetraData::PER_TETRA_VERTEX :
                pos = coords[ tetras[ index.i/4 ].points[ index.i%4 ] ];
                break;

            case HxTetraData::PER_TETRA :
                {
                    // compute center of current tetrahedron
                    int * pidx = tetras[index.i].points;
                    pos  = coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx  ) ];
                    pos *= 0.25;
                }
                break;

            default:
                assert(0);
            }
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_hexa :
            switch ( _descResult.m_descriptor._encoding )
            {
            case HxHexaData::PER_VERTEX :
                pos = coords[ index.i ];
                break;

            case HxHexaData::PER_HEXA_VERTEX :
                pos = coords[ hexas[ index.i/8 ].points[ index.i%8 ] ];
                break;

            case HxHexaData::PER_HEXA :
                {
                    // compute center of current hexahedron
                    int * pidx = hexas[index.i].points;
                    pos  = coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx  ) ];
                    pos *= 0.125;
                }
                break;

            default:
                assert(0);
            }
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_surface :
            switch ( _descResult.m_descriptor._encoding )
            {
            case HxSurfaceField::OnNodes :
                pos = coords[ index.i ];
                break;

            case HxSurfaceField::OnTriangleNodes :
                pos = coords[ triangles[ index.i/3 ].points[ index.i%3 ] ];
                break;

            case HxSurfaceField::OnTriangles :
                {
                    // compute center of current hexahedron
                    int * pidx = triangles[index.i].points;
                    pos  = coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos += coords[ *(pidx++) ];
                    pos /= 3.f;
                }
                break;

            default:
                assert(0);
            }
            break;

        ////////////////////////////////////////
        default:
            assert(0); // results never are t_anna objects
        }

    }


    /// obtain sample values at that position from the current input source indexed by s_
    inline void computeGetSourceValues(const McVec4l& index, HxArithmetic_Desc *src_,
        SbVec3f &pos, HxLocation3* myLocation, int &myLocationIsValid, 
        float srcVals[] )
    {
        switch ( src_->_method )
        {
        ////////////////////////////////////////
        // 1 via direct access with _dataPtr
        ////////////////////////////////////////
        case 1:
            memcpy( srcVals, ((char*)src_->_dataPtr) + ( index.l * src_->m_descriptor.getNDataVar() * sizeof(float) ), src_->m_descriptor.getNDataVar() * sizeof(float) );
            break;

        ////////////////////////////////////////
        // 2 via HxLattice3::eval(i,j,k,..)
        ////////////////////////////////////////
        case 2:
            assert( src_->_ILattice!=NULL );
            src_->_ILattice->eval( index.l, srcVals );
            break;

        ////////////////////////////////////////
        // 0 via eval(HxLocation3,..)
        ////////////////////////////////////////
        default:
            // No field - src_ might be a surface field
            if ( !src_->_IField3 ) {
                for( int n=src_->m_descriptor.getNDataVar() ; n-- ; )
                    srcVals[n] = src_->getDefaultValue(n);
                return;
            }

            SbVec3f srcPos;

            // do that transformation stuff
            if ( src_->_transHasTo )
                src_->_transResultToObj.multVecMatrix( pos, srcPos );
            else
                srcPos = pos;
            // focus to the current position in source local coords
            if ( myLocationIsValid )
                myLocationIsValid = myLocation->move( srcPos.getValue() );
            else
                myLocationIsValid = myLocation->set( srcPos.getValue() );
            // get value from source
            if ( myLocationIsValid )
                src_->_IField3->eval( myLocation, srcVals );
            else // if source undefined at that position take the defaults
                for( int n=src_->m_descriptor.getNDataVar() ; n-- ; )
                    srcVals[n] = src_->getDefaultValue(n);
        }
    }

    /// store the result sample values to the result data structure
    inline void computeSetResultValues(const McVec4l& index, const int numResVar, float dstvals[] )
    {
        switch ( _descResult.m_descriptor.getGridType() )
        {
        ////////////////////////////////////////
        case FieldDescriptor::t_regular :
            assert( _descResult._ILattice!=NULL );
            _descResult._ILattice->set( index.l, dstvals );
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_tetra :
            assert( _descResult._dataPtr!=NULL );
            memcpy( ((float*)_descResult._dataPtr)+(index.i*numResVar), dstvals, sizeof(float)*numResVar);
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_hexa :
            assert( _descResult._dataPtr!=NULL );
            memcpy( ((float*)_descResult._dataPtr)+(index.i*numResVar), dstvals, sizeof(float)*numResVar);
            break;

        ////////////////////////////////////////
        case FieldDescriptor::t_surface :
            assert( _descResult._dataPtr!=NULL );
            memcpy( ((float*)_descResult._dataPtr)+(index.i*numResVar), dstvals, sizeof(float)*numResVar);
            break;

        default:
            assert(0); // results never are t_anna objects
        }
    }

};

#endif

/// @}
