/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VERTEX_PROPERTY_CACHE
#define  _SO_VERTEX_PROPERTY_CACHE

#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>

#include <Inventor/sys/SoGLType.h>
#include <Inventor/STL/vector>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#ifndef HIDDEN_FROM_DOC

class SoVertexProperty;
class SoCache;

//////////////////////////////////////////////////////////////////////////////
//
//   Description:
//      The SoVertexPropertyCache class is a convenient way for vertex-based
//      shapes to store information on how they should render
//      themselves.  It takes care of some messiness that they'd
//      otherwise have to figure out.  It is designed to be a very
//      lightweight class.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/elements/SoShapeStyleElement.h>

typedef WINGDIAPI void APIENTRY SoVPCacheFunc(const char *const);
typedef WINGDIAPI void APIENTRY SoVPCacheFunc2(int, const char *const);

class SoBufferObject;

/**
 * [OIV-WRAPPER-NO-WRAP]
 */
SoEXTENDER class INVENTOR_API SoVertexPropertyCache {
 public:

   // API used by shapes:
   
   inline SbBool mightNeedSomethingFromState(const SoShapeStyleElement *sse) const
   { return needFromState & sse->getRenderCaseMask(); }
   
   void fillInCache(const SoVertexProperty *, SoState *, SbBool isMultiTexturingUsed = FALSE);
   
   // Returns TRUE if at least one texture unit has texture coordinates to be sent explicitly.
   SbBool hasTexCoordsUnits(const SoShapeStyleElement *sse) const ;

   inline SbBool shouldGenerateNormals(const SoShapeStyleElement *sse) const
   { return (m_generateNormals && sse->needNormals()); }
   
   // Should be used by shapes which do not use/manage multi-texturing
   inline SbBool shouldGenerateTexCoords(const SoShapeStyleElement *sse) const
   { 
     if (m_texCoordDataVec[m_firstImageUnit] != NULL )
       return (m_texCoordDataVec[m_firstImageUnit]->generateTexCoords && sse->needTexCoords());
     return FALSE;
   }

   // Should be used by shapes which do NOT use/manage multi-texturing
   inline SbBool shouldGenerateTexCoords3(const SoShapeStyleElement *sse) const
   { 
     if (m_texCoordDataVec[m_firstImageUnit] != NULL )
      return (m_texCoordDataVec[m_firstImageUnit]->generateTexCoords && sse->needTexCoords3());
     return FALSE;
   }

   // Should be used by shapes which use/manage multi-texturing
   // Suppress some element to the list of texture units where the texture 
   // coords should be generated.
   SbBool shouldGenerateTexCoordsUnits(const SoShapeStyleElement *sse) ;

   // Returns the list of texture units where texture coords should be sent
   inline const SbIntList& getTexCoordsUnits() const
   { return m_texUnitCoordsList ;}

   // Returns the list of texture units where texture coords should be generated
   inline const SbIntList& getGenTexCoordsUnits() const
   { return m_texUnitGenCoordsList ;}

   // Returns the texture unit which contains texture coords in VP, -1 if none.
   inline int getUnitTexCoordsInVP() const
   { return m_unitTexCoordInVP ; }
   
   inline int getRenderCase(const SoShapeStyleElement *sse) const
   { return m_renderCase & sse->getRenderCaseMask(); }
   
   inline SbBool haveTexCoordsInVP()
   { return needFromState & TEXTURE_FUNCTION_BIT; }
   
   inline SbBool isTexCoordsInVP3D()
   { return haveTexCoordsInVP() && m_texCoords3InVP ; }
   
   inline void sendVertex(const char *vp) const
   { (*vertexFunc)(vp); }

   inline void sendNormal(const char *np) const
   { (*normalFunc)(np); }

   inline void sendColor(const char *cp) const
   { (*colorFunc)(cp); }

   inline void sendTexCoord(const char *tcp, int unit=0) const
   { 
      if (m_texCoordDataVec[unit] != NULL )
        (*m_texCoordDataVec[unit]->texCoordFunc)(tcp);
   }
   
   inline int getNumVertices() const 
   { return numVerts; }

   inline void setNormals(const char *normals) 
   { normalPtr = normals ;} 

    inline void setNumNormals(int _numNorms) 
   { numNorms = _numNorms ;} 

   inline int getNumNormals() const 
   { return numNorms; }

   inline int getNumColors() const 
   { return numColors; }

   inline int getNumTexCoords(int unit=0) const 
   { 
     if (m_texCoordDataVec[unit] != NULL )
      return m_texCoordDataVec[unit]->numTexCoords;
     return 0;
   }

   inline int getForceSending(int unit=0) const 
   { 
     if (m_texCoordDataVec[unit] != NULL )
        return m_texCoordDataVec[unit]->forceSend;
     return 0;
   }

   inline const char *getVertices(int i) const
   { return vertexPtr + vertexStride*i; }

   inline const char *getNormals(int i) const 
   { return normalPtr + normalStride*i; }

   inline const char *getColors(int i) const
   { return colorPtr + colorStride*i; }

   inline SoVPCacheFunc *getTexCoordFunc(int unit=0) const
   {
     if (m_texCoordDataVec[unit] != NULL )
       return m_texCoordDataVec[unit]->texCoordFunc ;
     return NULL;
   }

   inline SoVPCacheFunc2 *getMultiTexCoordFunc(int unit=0) const
   { 
     if (m_texCoordDataVec[unit] != NULL )
       return m_texCoordDataVec[unit]->multiTexCoordFunc;
     return NULL;
   }

   inline int getTexCoordStride(int unit=0) const 
   { 
     if (m_texCoordDataVec[unit] != NULL )
      return m_texCoordDataVec[unit]->texCoordStride;
     return 0;
   }

   inline const char *getTexCoords(int i, int unit=0) const
   { 
     if (m_texCoordDataVec[unit] != NULL )
       return m_texCoordDataVec[unit]->texCoordPtr + m_texCoordDataVec[unit]->texCoordStride*i;
     return NULL;
   }
   
   inline SbBool colorIsInVtxProp() const 
   { return m_colorIsInVP; }
   
   //Indicates if non-opaque transparency is in vertex property.
   inline SbBool transpIsInVtxProp() const 
   { return m_transpIsInVP; }
   
   inline int getVertexStride() const 
   { return vertexStride; }

   inline int getNormalStride() const 
   { return normalStride; }

   inline int getColorStride() const 
   { return colorStride; }
   
   inline SoNormalBindingElement::Binding getNormalBinding() const
   { return (SoNormalBindingElement::Binding)m_normalBinding; }
   
   inline SoMaterialBindingElement::Binding   getMaterialBinding() const
   { return (SoMaterialBindingElement::Binding)m_materialBinding; }
   
   inline SoTextureCoordinateBindingElement::Binding  getTexCoordBinding(int unit=0) const
   { 
     if (m_texCoordDataVec[unit] != NULL )
       return (SoTextureCoordinateBindingElement::Binding)m_texCoordDataVec[unit]->texCoordBinding;
     return SoTextureCoordinateBindingElement::PER_VERTEX;
   }
   
   inline void invalidate() 
   { needFromState = ALL_FROM_STATE_BITS; }
   
   // Constructor.   Initializes everything.
   SoVertexPropertyCache();

   // Destructor
   ~SoVertexPropertyCache() ;
   
   // New function for OIV2.5:
   // If VertexProperty has everything needed for state, should
   // the shape asked to be render cached?  Default is TRUE.
   // If using too much memory, this can be made FALSE.
   static void setEncourageRenderCaching(SbBool onOff) 
   { s_encourageRenderCaching = onOff; };

   static SbBool isEncourageRenderCaching()
   { return s_encourageRenderCaching; };
   
   int getNumVertexAttrib(int index) const
   { return m_genericVertexAttribData[index].num; }

   inline SoVPCacheFunc2 * getVertexAttribFunc(int index) const
   { return m_genericVertexAttribData[index].func; }

   inline const char * getVertexAttribs(int index) const
   { return m_genericVertexAttribData[index].ptr; }

   inline size_t getVertexAttribStride(int index) const
   { return m_genericVertexAttribData[index].stride; }

   inline int getVertexAttribSize(int index) const
   { return m_genericVertexAttribData[index].size; }

   inline GLenum getVertexAttribType(int index) const
   { return m_genericVertexAttribData[index].type; }

   inline SbBool getVertexAttribToNorm(int index) const
   { return m_genericVertexAttribData[index].toNorm; }

   inline SoBufferObject* getVertexAttribBufferObject(int index) const
   { return m_genericVertexAttribData[index].bufferObject; } 

   inline void sendVertexAttrib(int index, const char * genVertexAttribPointer) const
   { (*m_genericVertexAttribData[index].func)(index, genVertexAttribPointer); }

   inline void setVertexAttribs(int index, const char * genVertexAttribPointer) const
   { m_genericVertexAttribData[index].ptr = genVertexAttribPointer; }

   SbBool	hasVertexAttrib() const
   { return m_genericVertexAttribList.getLength(); }

   inline const SbIntList& getVertexAttribList() const
   { return m_genericVertexAttribList; }

   void disableNormalBinding();
   void disableMaterialBinding();
   void disableTextureBinding();
   void updateNormalBinding(const SoNormalBindingElement::Binding normalBinding);

   static void initClass();
   static void exitClass();

   static inline SbBool isForceSendingSet()
   {
     return s_forceTexCoordSending;
   }

 public :
   
   // Tables of functions, data, and strides to increment through data.
   SoVPCacheFunc *vertexFunc;
   const char *vertexPtr;
   int vertexStride, numVerts;
   SoVPCacheFunc *normalFunc;
   const char *normalPtr;
   int normalStride, numNorms;
   SoVPCacheFunc *colorFunc;
   const char *colorPtr;
   int colorStride, numColors;   
   
   unsigned char needFromState;
   
   // 32 rendering cases.  Non-indexed shapes can get away with just
   // looking at the low 5 bits.  The bits are arranged like this:
   // 43210  BITS
   // -----  ----
   // 00...  Overall color
   // 01...  Part color
   // 10...  Face color
   // 11...  Vtx color
   // ..00.  Overall/No norm
   // ..01.  Part norm
   // ..10.  Face norm
   // ..11.  Vtx norm
   // ....?  Explicit texture coordinates needed
   SoINTERNAL public:
   enum { 
     COLOR_BITS = 0x18,
     PART_COLOR = 0x8,
     FACE_COLOR = 0x10,
     VERTEX_COLOR = 0x18,
       
     NORMAL_BITS = 0x6,
     PART_NORMAL = 0x2,
     FACE_NORMAL = 0x4,
     VERTEX_NORMAL = 0x6,
       
     TEXCOORD_BIT = 0x1     // Explicit texture coordinate needed for at least one texture unit.
   };
   // Bit-mask, set by ::fillInCache method
   // Bits use same as above, plus one for coords and one for 
   // overrides (diffuse color, material binding, transparency)
   // plus one for texture function (if tcoords in VP)
   
   enum {
     TEXTURE_FUNCTION_BIT = 0x80,
     OVERRIDE_FROM_STATE_BIT = 0x40, 
     COORD_FROM_STATE_BIT = 0x20,
     COLOR_FROM_STATE_BITS = COLOR_BITS,
     NORMAL_FROM_STATE_BITS = NORMAL_BITS,
     TEXCOORD_FROM_STATE_BIT = TEXCOORD_BIT,
     ALL_FROM_STATE_BITS = 0xFF
   };

 private:
   //
   // VertexPropertyCache also stores whether or not colors, normals and
   // texture coordinates should be indexed.  Suggestion for writing
   // rendering loops:
   //   
   // To minimize loop overhead, loop unrolling is a good idea.
   // Doing two iterations per loop makes it about 20% faster.  Doing
   // three iterations per loop makes it about 28% faster (only 8%
   // more than two iterations).
   //  
   // On 200MHZ machines, an unrolled-by-3 loop can do close to 5
   // million iterations per second, assuming one call per iteration
   // (e.g. one-color, unlit polygons).
   //
   bool m_generateNormals;

   // Contains the list of texture units where the texture coords should be sent
   SbIntList m_texUnitCoordsList ;

   // Contains the list of texture units where the texture coords should be generated
   SbIntList m_texUnitGenCoordsList ;

   bool          m_isMultiTexture ;
   unsigned char m_normalBinding;
   unsigned char m_materialBinding;
   unsigned char m_renderCase;
   unsigned char m_colorIsInVP;
   unsigned char m_transpIsInVP;
   unsigned char m_texCoords3InVP ;
            char m_unitTexCoordInVP ; // texture unit which contains texture coords in VP.
                                      // -1 one if none.

   struct SoTexCoordData {
    SoVPCacheFunc   *texCoordFunc;
    SoVPCacheFunc2  *multiTexCoordFunc;
    const char      *texCoordPtr;
    int             texCoordStride, 
                    numTexCoords;
    unsigned char   texCoordBinding ;
    bool            generateTexCoords ;
    bool            forceSend;

    // Constructor
    SoTexCoordData()
    {
      texCoordFunc = NULL ;
      multiTexCoordFunc = NULL ;
      texCoordPtr  = NULL ;
      texCoordStride  = 0 ;
      numTexCoords = 0 ;
      texCoordBinding = 0;
      generateTexCoords = false ;
      forceSend = false ;
    }
   };

   void growtexCoordDataVec(const int unit);

   std::vector<SoTexCoordData *> m_texCoordDataVec ;
   int             m_firstImageUnit ; // First texture unit corresponding to IMAGE_MAPPING

   struct SoVertexAttribData {
     SoVPCacheFunc2 * func;
     const char     * ptr;
     size_t           stride;
     int              size;
     GLenum           type;
     bool             toNorm;
     int              num;
     SoBufferObject * bufferObject;
   };

   SoVertexAttribData *m_genericVertexAttribData;
   SbIntList           m_genericVertexAttribList;
   SoCache            *m_genericVertexAttribCache;

   void allocGenericVertexAttribs(const int num);
   void loadGenericVertexAttribData(SoState * state);

   static SbBool s_encourageRenderCaching;
   static SbBool s_forceTexCoordSending;
   static SbBool s_oivVertexAttrib;
};
#endif // HIDDEN_FROM_DOC

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_VERTEX_PROPERTY_CACHE */

