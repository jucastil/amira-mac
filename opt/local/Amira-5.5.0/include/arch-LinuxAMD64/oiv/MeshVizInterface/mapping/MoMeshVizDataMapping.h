/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MOMESHVIZDATAMAPPING_H
#define _MOMESHVIZDATAMAPPING_H

#include <MeshVizInterface/MxMeshIViz.h>

#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)   
#    define __MESHVIZDMDLL  "MeshVizDataMappingD.dll"
#    define __MESHVIZDMLIB  "MeshVizDataMappingD.lib"
#  else
#    define __MESHVIZDMDLL  "MeshVizDataMapping.dll"
#    define __MESHVIZDMLIB  "MeshVizDataMapping.lib"
#  endif

//  MeshVizExtractor_EXPORTS is defined only when building MeshIViz dll
#  ifdef MeshVizDataMapping_EXPORTS
#    define MESHIVIZDM_API __declspec(dllexport)
#  else
#    define MESHIVIZDM_API __declspec(dllimport)
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__MESHVIZDMLIB)
#    endif
#  endif
#else
#  define  MESHIVIZDM_API
#  define __MESHVIZDMDLL  "libMeshVizDataMapping"
#endif

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoMeshVizDataMapping, __MESHVIZDMDLL)

// Macro that allows to enable an element for all type of actions
#define MO_ENABLE_ELT_ALL_ACTIONS(_elt)\
SO_ENABLE(SoCallbackAction, _elt);\
SO_ENABLE(SoGLRenderAction, _elt);\
SO_ENABLE(SoGetMatrixAction, _elt);\
SO_ENABLE(SoSearchAction, _elt);\
SO_ENABLE(SoGetBoundingBoxAction, _elt);\
SO_ENABLE(SoWriteAction, _elt);\
SO_ENABLE(SoHandleEventAction, _elt);\
SO_ENABLE(SoPickAction, _elt);\
SO_ENABLE(SoGetPrimitiveCountAction, _elt);

/**
 * @ingroup MeshIViz_Mapping
 * 
 *   All supported mesh types
 * 
 */ 
enum MeshType {
  VOLUME_MESH_UNSTRUCTURED,      /**< Unstructured Volume Mesh */
  VOLUME_MESH_UNSTRUCTURED_IJK,  /**< Unstructured IJK Volume Mesh */
  VOLUME_MESH_HEXAHEDRON_IJK,    /**< Unstructured IJK Hexahedron Mesh */
  HEXAHEDRON_MESH_IJK,           /**< Unstructured IJK Vertex Hexahedron Mesh */
  VOLUME_MESH_REGULAR,           /**< Regular Volume Mesh */
  VOLUME_MESH_RECTILINEAR,       /**< Rectilinear Volume Mesh */
  VOLUME_MESH_CURVILINEAR,       /**< Curvilinear Volume Mesh */
  SURFACE_MESH_UNSTRUCTURED,     /**< Unstructured Surface Mesh */
  SURFACE_MESH_REGULAR,          /**< Regular Surface Mesh */
  SURFACE_MESH_RECTILINEAR,      /**< Rectilinear Surface Mesh */
  SURFACE_MESH_CURVILINEAR,      /**< Curvilinear Surface Mesh */
  LINE_MESH_UNSTRUCTURED,        /**< Unstructured Line Mesh */
  LINE_MESH_REGULAR,             /**< Regular Line Mesh */
  LINE_MESH_CURVILINEAR,         /**< Curvilinear Line Mesh */
  UNDEFINED_MESH                 /**< Mesh not defined */
};

/**
 * @ingroup MeshIViz_Mapping
 * 
 *   Type of cell filter
 * 
 */ 
enum CellFilterType {
  CELL_FILTER_I,        /**< Cell Filter for unstructured meshes */
  CELL_FILTER_IJ,       /**< Cell Filter for structured surface meshes */
  CELL_FILTER_IJK,       /**< Cell Filter for structured volume meshes */
  UNDEFINED_CELL_FILTER /**< Cell Filter not defined */
};
 
#endif
