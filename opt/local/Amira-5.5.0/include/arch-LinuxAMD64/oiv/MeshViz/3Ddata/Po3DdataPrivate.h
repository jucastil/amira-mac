/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO3DDATAPRIVATE_H_
#define _PO3DDATAPRIVATE_H_

/*---------------------------------------------------------------------------*/

/* TYPE DEFINITIONS */

typedef          float  Pfloat;
typedef          int    Pint;

typedef struct {
  Pfloat x;                  /* x coordinate                                 */
  Pfloat y;                  /* y coordinate                                 */
  Pfloat z;                  /* z coordinate                                 */
} Ppoint3;

typedef struct {
  Pint     num_points;      /*number of Ppoint3s in the list                 */
  Ppoint3 *points;          /* list of points                                */
} Ppoint_list3;


typedef struct {
  Pint          num_point_lists;/* number of point lists                     */
  Ppoint_list3 *point_lists;    /* list of point lists                       */
} Ppoint_list_list3;

typedef struct {
  Pfloat x;                  /* x coordinate                                 */
  Pfloat y;                  /* y coordinate                                 */
} Ppoint;

typedef struct {
  Pint     num_points;      /*number of Ppoints in the list                 */
  Ppoint  *points;          /* list of points                                */
} Ppoint_list;

typedef struct {
  Pint          num_point_lists;/* number of point lists                     */
  Ppoint_list  *point_lists;    /* list of point lists                       */
} Ppoint_list_list;

typedef struct {
  Pfloat delta_x;            /* delta x value                                */
  Pfloat delta_y;            /* delta y value                                */
} Pvec;


/*---------------------------------------------------------------------------*/
typedef struct {
  Ppoint_list_list3 contours;
  Pint              num_alloc_contours,*num_alloc_points;
} Tmesh_limit_data;

struct Tisoline_list {
  Ppoint_list3 *isolines;
  float       *isolines_value;
  int         num_isolines;
};

/*---------------------------------------------------------------------------*/

#endif /* _PO3DDATAPRIVATE_H_ */

