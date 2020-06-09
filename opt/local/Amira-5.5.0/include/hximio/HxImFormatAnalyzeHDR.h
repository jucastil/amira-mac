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

/// @addtogroup hximio hximio
/// @{
struct header_key                /* header key      */ 
{                                /* off + size      */
    int sizeof_hdr;              /* 0 + 4           */
    char data_type[10];          /* 4 + 10          */
    char db_name[18];            /* 14 + 18         */
    int extents;                 /* 32 + 4          */
    short int session_error;     /* 36 + 2          */
    char regular;                /* 38 + 1          */
    char hkey_un0;               /* 39 + 1          */
};                               /* total=40 bytes  */
struct image_dimension 
{                                /* off + size      */
    short  dim[8];               /* 0 + 16          */
    short unused8;               /* 16 + 2          */
    short unused9;               /* 18 + 2          */
    short unused10;              /* 20 + 2          */
    short unused11;              /* 22 + 2          */
    short unused12;              /* 24 + 2          */
    short unused13;              /* 26 + 2          */
    short unused14;              /* 28 + 2          */
    short datatype;              /* 30 + 2          */
    short bitpix;                /* 32 + 2          */
    short dim_un0;               /* 34 + 2          */
    float pixdim[8];             /* 36 + 32         */
    /* 
       pixdim[] specifies the voxel dimensitons: 
       pixdim[1] - voxel width
       pixdim[2] - voxel height
       pixdim[3] - interslice distance
       ...etc
    */
    float vox_offset;            /* 68 + 4          */
    float funused1;              /* 72 + 4          */
    float funused2;              /* 76 + 4          */
    float funused3;              /* 80 + 4          */
    float cal_max;               /* 84 + 4          */
    float cal_min;               /* 88 + 4          */
    float compressed;            /* 92 + 4          */
    float verified;              /* 96 + 4          */
    int glmax,glmin;             /* 100 + 8         */
};                               /* total=108 bytes */
struct data_history       
{                                /* off + size      */
    char descrip[80];            /* 0 + 80          */
    char aux_file[24];           /* 80 + 24         */
    char orient;                 /* 104 + 1         */
    char originator[10];         /* 105 + 10        */
    char generated[10];          /* 115 + 10        */
    char scannum[10];            /* 125 + 10        */
    char patient_id[10];         /* 135 + 10        */
    char exp_date[10];           /* 145 + 10        */
    char exp_time[10];           /* 155 + 10        */
    char hist_un0[3];            /* 165 + 3         */
    int views;                   /* 168 + 4         */
    int vols_added;              /* 172 + 4         */
    int start_field;             /* 176 + 4         */
    int field_skip;              /* 180 + 4         */
    int omax, omin;              /* 184 + 8         */
    int smax, smin;              /* 192 + 8         */
};

struct header
{ 
    struct header_key headerkey;            /* 0 + 40          */
    struct image_dimension dimension;       /* 40 + 108        */
    struct data_history history;            /* 148 + 200       */
};                                          /* total= 348 bytes*/

/* Acceptable values for datatype */

#define DT_NONE                  0
#define DT_UNKNOWN               0
#define DT_BINARY                1
#define DT_UNSIGNED_CHAR         2
#define DT_SIGNED_SHORT          4
#define DT_SIGNED_INT            8
#define DT_FLOAT                 16
#define DT_COMPLEX               32
#define DT_DOUBLE                64
#define DT_RGB                   128
#define DT_ALL                   255

void swap_float(float* pntr);
void swap_short(short* spntr);
///@test GW: new method is necessary.
void swap_ushort(unsigned short* uspntr);
void swap_double(double* spntr);
void swap_int(int* ipntr);


/// @}
