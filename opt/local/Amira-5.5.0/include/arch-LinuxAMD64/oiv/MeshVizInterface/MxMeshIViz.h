/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MXMESHIVIZ_H
#define _MXMESHIVIZ_H

#include <Inventor/STL/limits>

/**
 * @DTEXT MeshIViz: MeshViz Interface
 * 
 * @defgroup MeshIViz MeshViz Interface
 * @ingroup MeshVizXLM
 *
 * @DESCRIPTION
 * MeshViz Interface, is an API useful for extracting and visualizing features from meshes 
 * used in finite element analysis (FEA) and computer aided engineering (CAE). @n 
 * MeshViz Interface contains two separate parts: Mesh Extraction and Data Mapping.@n
 * @UL
 * @LI Mesh Extraction creates a mesh of lower dimension from a higher dimension one. 
 * For instance, when extracting a surface mesh (2D) representing an isosurface of a volume mesh (3D). @BR
 * @LI Data Mapping creates a graphical representation of an extracted mesh with advanced rendering techniques. @BR
 * @ul
 * 
 * See chapter "MeshViz XLM" of the Open Inventor User's Guide for more information.
 *
 * @defgroup MeshIViz_Mesh                      Mesh
 * @ingroup  MeshIViz    
 *
 * @defgroup MeshIViz_Mesh_Cell                 Cell
 * @ingroup  MeshIViz_Mesh
 *
 * @defgroup MeshIViz_Mesh_Topology             Topology 
 * @ingroup  MeshIViz_Mesh
 *
 * @defgroup MeshIViz_Mesh_Geometry             Geometry 
 * @ingroup  MeshIViz_Mesh
 *
 * @defgroup MeshIViz_Mesh_DataSets             DataSets
 * @ingroup  MeshIViz_Mesh
 *
 * @defgroup MeshIViz_Extract                   Extractors
 * @ingroup  MeshIViz
 *
 * @defgroup MeshIViz_Extract_Cell              Cell
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Isosurf           Isosurface
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Isoline           Isoline
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_ClipLine          Clipline
 * @ingroup  MeshIViz_Extract
 *  
 * @defgroup MeshIViz_Extract_Outline           Oultline
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Slice             Slice
 * @ingroup  MeshIViz_Extract

 * @defgroup MeshIViz_Extract_Logicalslice      Logical slice
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Skin              Skin
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Streamline        Streamline
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Probe             Probe
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Tessellate        Tessellation
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_Extract_Utilities         Utilities
 * @ingroup  MeshIViz_Extract
 *
 * @defgroup MeshIViz_ExtractedMesh             Extracted Mesh
 * @ingroup  MeshIViz    
 *
 * @defgroup MeshIViz_ExtractedMesh_Cell        Cell
 * @ingroup  MeshIViz_ExtractedMesh
 *
 * @defgroup MeshIViz_ExtractedMesh_Topology    Topology 
 * @ingroup  MeshIViz_ExtractedMesh
 *
 * @defgroup MeshIViz_ExtractedMesh_Geometry    Geometry 
 * @ingroup  MeshIViz_ExtractedMesh
 *
 * @defgroup MeshIViz_ExtractedMesh_DataSets    DataSets
 * @ingroup  MeshIViz_ExtractedMesh
 *
 * @defgroup MeshIViz_Mapping                   Mapping
 * @ingroup  MeshIViz
 * 
 * @defgroup MeshIViz_Mapping_Representation    Representations
 * @ingroup  MeshIViz_Mapping
 *
 * @defgroup MeshIViz_Mapping_Action            Actions
 * @ingroup  MeshIViz_Mapping
 * 
 * @defgroup MeshIViz_Mapping_Attributes        Attributes
 * @ingroup  MeshIViz_Mapping
 * 
 * @defgroup MeshIViz_Mapping_Elements          Elements
 * @ingroup  MeshIViz_Mapping
 *
 * @defgroup MeshIViz_Mapping_Details           Details
 * @ingroup  MeshIViz_Mapping
 * 
 * @defgroup MeshIViz_Implement                 Implement
 * @ingroup  MeshIViz
 *
 */

#include <MeshVizInterface/MiVersion.h>

#ifdef _WIN32

//  MeshVizExtractor_EXPORTS is defined only when building MeshIViz dll
#  ifdef MeshVizExtractor_EXPORTS
#    define MESHIVIZ_API __declspec(dllexport)
#  else
#    define MESHIVIZ_API __declspec(dllimport)

#if defined(_DEBUG)   
  #ifdef ADD_VERSIONING_TO_DLL
    #    define __MESHVIZEXTRLIB  "MeshVizExtractorD.LIB"
  #else
    #    define __MESHVIZEXTRLIB  "MeshVizExtractorD.LIB"
  #endif
#else
  #ifdef ADD_VERSIONING_TO_DLL
    #    define __MESHVIZEXTRLIB  "MeshVizExtractor.LIB"
  #else
    #    define __MESHVIZEXTRLIB  "MeshVizExtractor.LIB"
  #endif
#endif
#ifndef OIV_DISABLE_AUTOLINK
#    pragma comment(lib,__MESHVIZEXTRLIB)
#endif
#  endif

#else


#define MESHIVIZ_API

#endif

#define SoEXTENDER
#define SoEXTENDER_Documented
#define SoINTERNAL


#if !defined(_WIN32)
#  include <cstddef>
#endif

static size_t UNDEFINED_ID = std::numeric_limits<size_t>::max();

#if defined(_WIN32) || defined(linux) || defined(__APPLE__)
#  define MESHIVIZ_USE_TBB
#endif

// macro used to avoid warning like "unreferenced formal parameter"
// it should be used for unreferenced argt of inline function.
// this macro is redefined when launching the doc generator (doxygen)
#define UNREF_PARAM(P)   

#endif
