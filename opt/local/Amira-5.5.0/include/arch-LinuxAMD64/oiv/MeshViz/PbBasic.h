/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_BASIC_
#define  _PB_BASIC_

#include <Inventor/SbBasic.h>
#include <MeshViz/PoMeshViz.h>

/*----------------------------------------------------------------------------*/
// These symbols are used in MeshViz header files to distinguish
// between varying levels of use of classes and members.
//
// Types of classes are:
//
//      "PoINTERNAL class" : means that the class is used only by
//                           MeshViz developers at VSG.
//
// Types of member variables and methods are :
//
//      "public:"             members are used by everybody.
//      "PoINTERNAL public:"  members are for VSG developers only.
//
/*----------------------------------------------------------------------------*/

#define PoINTERNAL

#define PPI        3.141592654f
#define PPIDIV2    1.570796327f
#define PPIDIV4    0.785398163f
#define PDEUXPI    6.283185307f
#define PSQRT2     1.414213562f
#define PSQRT3     1.732050808f

/*----------------------------------------------------------------------------*/
/// New Data type.

typedef struct {
  float xmin ;
  float xmax ;
  float ymin ;
  float ymax ;
  float zmin ;
  float zmax ;
} Plimit3 ;

typedef struct {
  float xmin ;
  float xmax ;
  float ymin ;
  float ymax ;
} Plimit ;

/*----------------------------------------------------------------------------*/

#ifdef _WIN32
#  include <float.h>
#else
#  include <limits.h>
#endif /* _WIN32 */

#endif /* _PB_BASIC_ */
