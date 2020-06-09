/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SSDI_HEADER_FILE
#define SSDI_HEADER_FILE

#ifdef _WIN32
#include <Inventor/Win/SoWinBeginStrict.h>
#include <windows.h>

/* ssdiGetStatus return values */
#define SSDI_STATUS_OK                   0
#define SSDI_STATUS_INVALID_RENDERER     1
#define SSDI_STATUS_NOT_INITIALIZED      2
#define SSDI_STATUS_INVALID_DEVICE       3
#define SSDI_STATUS_INVALID_MODE         4
#define SSDI_STATUS_DLL_ERROR            7
#define SSDI_STATUS_NOT_INSTALLED        8
#define SSDI_STATUS_BAD_BUFFER_SET       9
#define SSDI_STATUS_BAD_BUFFER_TYPE     12
#define SSDI_STATUS_MODE_DISABLED       13
#define SSDI_STATUS_RENDER_ERRORS      100
#define SSDI_STATUS_STEREO_ERRORS      200
#define SSDI_STATUS_UNKNOWN_ERROR      300

#define SSDI_BUFFER_NONE           0
#define SSDI_BUFFER_VGA_OFFSET     1
#define SSDI_BUFFER_VESA_XY        2
#define SSDI_BUFFER_SYSTEM_FLAT    3
#define SSDI_BUFFER_SYSTEM_FAR     4
#define SSDI_BUFFER_GDI_DC         5
#define SSDI_BUFFER_GDI_WINDOW     6
#define SSDI_BUFFER_DD_SURFACE     7
#define SSDI_BUFFER_MGL_DC         8
#define SSDI_BUFFER_OPENGL_DC      9

typedef struct {
  short Type;
  short Reserved;
  union {
    struct { 
      short X;  /* vesa x offset */
      short Y;  /* vesa y offset */
    } __ssdi_coord_struct;
#ifdef __MGRAPH_H
    MGLDC *MglDC;
#endif
    void  *MemPtr;
    long   Offset;
#ifdef _INC_WINDOWS
    HDC    GdiDC;
    HWND   GdiWindow;
#endif
#ifdef __DDRAW_INCLUDED__
    LPDIRECTDRAWSURFACE Surface;
#endif
  } __ssdi_buffer_struct;
  union {
#ifdef __MGRAPH_H
    long MglPage;
#endif
    long MemPitch;
  } __ssdi_MGRAPH_H_union;
} ssdiBuffer;

/* ssdiBufferSet flags */
#define SSDI_SET_UNIQUE_RPRIMARY        0x00000001
#define SSDI_SET_UNIQUE_LPRIMARY        0x00000002
#define SSDI_SET_UNIQUE_RBACK           0x00000004
#define SSDI_SET_UNIQUE_LBACK           0x00000008
#define SSDI_SET_UNIQUE_RRENDER         0x00000010
#define SSDI_SET_UNIQUE_LRENDER         0x00000020
#define SSDI_SET_CAN_REUSE_BUFFER       0x00000100
#define SSDI_SET_DOUBLE_BUFFERED        0x00010000
#define SSDI_SET_OFFSCREEN_RENDER       0x00020000

typedef struct {
  ssdiBuffer RPrimary;
  ssdiBuffer LPrimary;
  ssdiBuffer RBack;
  ssdiBuffer LBack;
  ssdiBuffer RRender;
  ssdiBuffer LRender;
  unsigned long Flags;
} ssdiBufferSet;

typedef struct {
  unsigned short X;
  unsigned short Y;
  unsigned short W;
  unsigned short H;
  unsigned char  R;
  unsigned char  G;
  unsigned char  B;
  unsigned char  Reserved;
} ssdiRectangle;

typedef struct {
  unsigned short Width;  /* Width of this view                      */
  unsigned short Height; /* Height of this view                     */
  unsigned short XOffset;/* X offset of the (0,0) pixel of the view */
  unsigned short YOffset;/* Y offset of the (0,0) pixel of the view */
  signed   short dxdx;   /* mapping parameters                      */
  signed   short dydx;   /*        "                                */
  signed   short dxdy;   /*        "                                */
  signed   short dydy;   /*        "                                */
  double             EyeX;   /* Eye coords are wrt center of display    */
  double         EyeY;   /* X is to the left, Y is up, Z is dist    */
  double         EyeZ;   /* from screen */
  unsigned short NumRects;
  ssdiRectangle  Rects[8];
} ssdiViewInfo;

/* StereoLayout */
#define SSDI_STANDARD_COMBINED  1
#define SSDI_ROW_INTERLEAVED    2
#define SSDI_COLUMN_INTERLEAVED 3
#define SSDI_STANDARD_SEPARATE  4

/* ssdiStereoInfo flags */
#define SSDI_SEPARATE_BUFFERS   0x00000001  /* stereo device requires separate left and */
/* right eye video memory buffers */
#define SSDI_FULL_SIZE                  0x00001000  /* left and right eye views are (roughly) full size */
#define SSDI_HALF_HEIGHT                0x00002000  /* left and right eye views are half height */
#define SSDI_HALF_WIDTH                 0x00004000  /* left and right eye views are half width */

#define SSDI_DIRECT_ACCESS              0x00010000  /* direct access to the stereo buffer(s) is allowed */

#define SSDI_CAN_FORCE3D                0x00100000  /* reserved */

#define SSDI_SYSTEM_TIMER               0x01000000  /* stereo driver uses the system timer */
#define SSDI_REAL_TIME_CLOCK    0x02000000  /* stereo driver uses the real time clock */
#define SSDI_VERTICAL_IRQ               0x04000000  /* stereo driver uses the vertical retrace interrupt */
#define SSDI_DOES_FLIP                  0x08000000  /* hint to the rendering platform driver  */

#define SSDI_DYNAMIC_STEREOINFO 0x10000000      /* need to call ssdiGetStereoInfo every render loop */

typedef struct {
  unsigned short Width;
  unsigned short Height;
  unsigned short Depth;
  unsigned short Flags;
} ssdiModeInfo;

typedef struct {
  unsigned long  Flags;   
  unsigned short StereoLayout;
  unsigned short BufferWidth;
  unsigned short BufferHeight;
  unsigned short Reserved;
  double         DisplayWidth;
  double         DisplayHeight;
  double         DisplaySeparation;
  ssdiViewInfo   Left;
  ssdiViewInfo   Right;
} ssdiStereoInfo;

typedef struct {
  GUID                   ID;
  unsigned short ClientVersion;           // version number of the app
  unsigned short SSDIVersion;             // version number of ssdi32
  unsigned short DriverVersion;           // version number of the driver
  unsigned short Flags;                  
  char           DeviceManufacturer[40];  
  char           DeviceHardware[40];   
  char           DeviceName[80];  
} ssdiDeviceInfo;

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

  // {91D47601-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_vga; 
  // {91D47602-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_vesa;
  // {91D47603-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_gdi;
  // {91D47604-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_ddraw; 
  // {91D47605-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_mgl;
  // {91D47606-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_modex; 
  // {91D47607-7080-11d1-9DB7-00C04FD9BBE5}
  extern GUID CLSID_ssdi_display_opengl; 

  /* "display types" passed into ssdiInit */
#define SSDI_DISPLAY_VGA     (&CLSID_ssdi_display_vga)
#define SSDI_DISPLAY_VESA    (&CLSID_ssdi_display_vesa)
#define SSDI_DISPLAY_GDI     (&CLSID_ssdi_display_gdi)
#define SSDI_DISPLAY_DDRAW   (&CLSID_ssdi_display_ddraw)
#define SSDI_DISPLAY_MGL         (&CLSID_ssdi_display_mgl)
#define SSDI_DISPLAY_MODEX       (&CLSID_ssdi_display_modex)
#define SSDI_DISPLAY_OPENGL      (&CLSID_ssdi_display_opengl)

  /* left/right id passed into ssdiBlit */
#define SSDI_LEFT  1
#define SSDI_RIGHT 0

  /* flag passed to ssdiNumStereoModes, ssdiEnumStereoModes, and ssdiStereoOn */
#define SSDI_MODES_ENUM_DISABLED 1

  /* flags for ssdiBeginRender */
#define SSDI_CLEAR_BUFFER        0x00000001

  /* flags for ssdiEndRender */
#define SSDI_PRIMARY_CLEARED     0x00000002
#define SSDI_BACK_CLEARED        0x00000004

  /* #ifndef      SSDI_DLL_HEADER_FILE */

#ifdef    __cplusplus
#define  DEFAULTZERO  = 0
#else
#define  DEFAULTZERO
#endif /* __cplusplus */

  /* The following are the functions which make up the SSDI User API */
  int  ssdiNumStereoDevices(void);
  int  ssdiGetStereoDeviceInfo(int device_number, ssdiDeviceInfo *ssdinfo);
  int  ssdiNumRenderDevices(void);
  int  ssdiGetRenderDeviceInfo(int device_number, ssdiDeviceInfo *ssdinfo);
  int  ssdiInit(const GUID *stereo_device, const GUID *render_device);
  int  ssdiExit(void);
  int  ssdiNumStereoModes(ssdiModeInfo *modeinfo);
  int  ssdiEnumStereoModes(ssdiModeInfo *modeinfo, int stereo_mode_number, ssdiStereoInfo *stereoinfo);
  int  ssdiStereoOn(ssdiModeInfo *modeinfo, int stereo_mode_number, ssdiBufferSet *buffers, ssdiStereoInfo *stereoinfo);
  int  ssdiStereoOff(void);
  int  ssdiIsStereoOn(void);
  int  ssdiBeginRender(ssdiBufferSet *buffers, ssdiStereoInfo *stereoinfo, int left, unsigned long flags);
  int  ssdiBetweenRender(ssdiBufferSet *buffers, unsigned long flags);
  int  ssdiEndRender(ssdiBufferSet *buffers, unsigned long flags);
  int  ssdiFlip(ssdiBufferSet *buffers, unsigned long flags DEFAULTZERO);
  int  ssdiGainFocus(void);
  int  ssdiLoseFocus(void);
  int  ssdiLastStatus(void);
  const char *ssdiStatusString(void);

  /* #endif */

#ifdef    __cplusplus
} // end of extern "C"
#endif /* __cplusplus */

typedef unsigned long ssdiHandle;

// These are used to connect to the primary SSDI DLL 
typedef int   __cdecl TssdiNumStereoDevices(void);
typedef int   __cdecl TssdiGetStereoDeviceInfo(int device_number, ssdiDeviceInfo *ssdinfo);
typedef int   __cdecl TssdiNumRenderDevices(void);
typedef int   __cdecl TssdiGetRenderDeviceInfo(int device_number, ssdiDeviceInfo *ssdinfo);
typedef int   __cdecl TssdiInit(ssdiHandle *hand, const GUID *stereo_device, const GUID *render_device, int ssdi_win_version, char *status);
typedef int   __cdecl TssdiExit(ssdiHandle *hand, char *status);
typedef int   __cdecl TssdiNumStereoModes(ssdiHandle hand, int *num, ssdiModeInfo *modeinfo);
typedef int   __cdecl TssdiEnumStereoModes(ssdiHandle hand, ssdiModeInfo *modeinfo, int stereo_mode_num, ssdiStereoInfo *stereoinfo);
typedef int   __cdecl TssdiStereoOn(ssdiHandle hand, ssdiModeInfo *modeinfo, int stereo_mode_num, ssdiBufferSet *buffers, ssdiStereoInfo *stereoinfo);
typedef int   __cdecl TssdiStereoOff(ssdiHandle hand);
typedef int   __cdecl TssdiIsStereoOn(ssdiHandle hand, int *on);
typedef int   __cdecl TssdiBeginRender(ssdiHandle hand, ssdiBufferSet *buffers, ssdiStereoInfo *stereoinfo, int left, unsigned long flags);
typedef int   __cdecl TssdiBetweenRender(ssdiHandle hand, ssdiBufferSet *buffers, unsigned long flags);
typedef int   __cdecl TssdiEndRender(ssdiHandle hand, ssdiBufferSet *buffers, unsigned long flags);
typedef int   __cdecl TssdiFlip(ssdiHandle hand, ssdiBufferSet *buffers, unsigned long flags);
typedef int   __cdecl TssdiGainFocus(ssdiHandle hand);
typedef int   __cdecl TssdiLoseFocus(ssdiHandle hand);
typedef char *__cdecl TssdiStatusString(ssdiHandle hand, int status_num); 

#include <Inventor/Win/SoWinEndStrict.h>
#endif //_WIN32

#endif /* SSDI_HEADER_FILE */

