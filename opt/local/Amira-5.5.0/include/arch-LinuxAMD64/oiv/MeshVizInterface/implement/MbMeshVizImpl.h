/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBMESHVIZIMPL_H
#define _MBMESHVIZIMPL_H

#include <Inventor/STL/limits>

/**
 * @DTEXT MeshIViz: MeshViz Interface
 * 
 * @DESCRIPTION
 * 
 * @defgroup MeshIViz_Implement_Mesh  Mesh
 * @ingroup  MeshIViz_Implement
 * @defgroup MeshIViz_Implement_Geometry  Geometry
 * @ingroup  MeshIViz_Implement
 * @defgroup MeshIViz_Implement_Data  Data
 * @ingroup  MeshIViz_Implement
 * @defgroup MeshIViz_Implement_Cell  Cell
 * @ingroup  MeshIViz_Implement
 * @defgroup MeshIViz_Implement_Topology  Topology
 * @ingroup  MeshIViz_Implement
 * @defgroup MeshIViz_Implement_Colormapping  Colormapping  
 * @ingroup  MeshIViz_Implement
 *
 */
#ifndef HIDDEN_FROM_DOC

#ifdef _WIN32

#  ifdef MeshVizImpl_EXPORTS
#    define MESHIVIZIMPL_API __declspec(dllexport)
#  else
#    define MESHIVIZIMPL_API __declspec(dllimport)

#if defined(_DEBUG)   
  #ifdef ADD_VERSIONING_TO_DLL
    #    define __MESHVIZIMPLLIB  "MeshVizImplD.LIB"
  #else
    #    define __MESHVIZIMPLLIB  "MeshVizImplD.LIB"
  #endif
#else
  #ifdef ADD_VERSIONING_TO_DLL
    #    define __MESHVIZIMPLLIB  "MeshVizImpl.LIB"
  #else
    #    define __MESHVIZIMPLLIB  "MeshVizImpl.LIB"
  #endif
#endif
#ifndef OIV_DISABLE_AUTOLINK
#    pragma comment(lib,__MESHVIZIMPLLIB)
#endif
#  endif

#else 
#  define MESHIVIZIMPL_API
#endif

#define SoEXTENDER
#define SoEXTENDER_Documented
#define SoINTERNAL

#endif //HIDDEN_FROM_DOC

#endif
