#ifndef _VS_H_
#define _VS_H_

#include "VsVolrenAPI.h"

#define VSLOG_MODULE "VSVOLREN"

#ifndef NEWSTYLE_IOSTREAM
    #define NEWSTYLE_IOSTREAM
#endif

#ifndef STANDALONE
    #define STANDALONE
#endif

#include <mclib/McResult.h>


////////////////////////////////////////////////////////////////////////////////
// forward declarations for the classes
////////////////////////////////////////////////////////////////////////////////

class VsBackgroundWorker;
class VsCamera;
class VsColorMap;
class VsCommonRenderer;
class VsCornerCut;
class VsCropRegion;
class VsCurvedSliceData;
class VsData;
class VsDataAccess;
class VsDataAccessPrivate;
class VsDataRelay;
class VsEvaluator;
class VsGenericPolygon;
class VsInterface;
class VsJobControl;
class VsLocker;
class VsMaterial;
class VsMemoryData;
class VsMemoryDataRelay;
class VsMesh;
class VsMirrorWriter;
class VsNode;
class VsObject;
class VsObjectLocker;
class VsOverlay;
class VsOverlayElement;
class VsOverlayLine;
class VsPBuffer;
class VsPBufferPrivate;
class VsPlaneSliceData;
class VsPolygon;
class VsQuadMesh;
class VsRefNoDelete;
class VsRelay;
class VsRelayBlock;
class VsRenderQueue;
class VsRenderer;
class VsResourceManager;
class VsServer;
class VsSlice;
class VsSliceData;
class VsSliceHighResData;
class VsTask;
class VsTaskControl;
class VsViewState;
class VsVolren;
class VsVolrenRelay;
class VsVolume;
class VsVolumeLevel;
class VsVolumeParams;
class VsVolumeReader;
class VsVolumeRelay;
class VsVoxelDescriptor;


// signature of class factory functions for VsInterface subclasses
typedef VsInterface * ( * INTERFACEFACTORYFUNC ) ( class VsMeta & inMeta );


/** Default return type.

    If a method succeeds, the return value is #VS_OK. A value other
    than #VS_OK indicates, that the method failed. The generic return
    value is #VS_FAILED. In future, additional return types
    for specific error situations might be added. Thus it should be
    avoided to check if the return value of a method is #VS_FAILED.
    Instead, it should be checked if the return type is other than
    #VS_OK. To get extended error information, call Vs::lastError().
*/
enum VSRESULT 
{
    /// Indicates that a method succeeded. 
    VS_OK,
    /// Generic return value in case of an error.
    VS_FAILED
};

#define VS_ISOK(x)  ((x)==VS_OK)
#define VS_ISBAD(x) ((x)!=VS_OK)


/** Return type for rendering operations.

    This enum is used by VsNode::render() and VsRenderer::render().
    It indicates the result of a rendering operation. The numercial
    values of the individual tags should not be modified. In order
    to check if a render result \c res was either VS_RENDER_OK or
    VS_RENDER_OK_LOW_QUALITY, for example in
    VsRenderer::renderFrameEnd(), you may write this:
    \code
        if ( res<=VS_RENDER_OK_LOW_QUALITY ) {
            // do something, e.g. swap buffers
        }
    \endcode
    In order to combine the render result of multiple render methods,
    for example in VsRenderer::render(), may take just take the
    maximum numerical value.
*/
enum VsRenderResult
{
    /** Rendering completed with best quality. The \link VsNode::render()
        render() \endlink method of a VsNode should return this value if
        it successfully completed rendering with best quality. */
    VS_RENDER_OK = 0,
    /** Rendering completed with reduced quality. The \link VsNode::render()
        render() \endlink method of a VsNode should return this value if
        it successfully completed rendering, but if it decided to use some
        reduced quality settings in order to match the time limit specified
        in VsNode::setRenderTime(). */
    VS_RENDER_OK_LOW_QUALITY = 1,
    /** Rendering was canceled. The \link VsNode::render() render() \endlink
        method of a VsNode node should return this valus if it decides to
        stop rendering because VsObject::canceled() returned true. */
    VS_RENDER_CANCELED = 0xff,
    /** Rendering failed. The \link VsNode::render() render() \endlink
        method of a VsNode should return this value if rendering failed,
        for example due to some resource allocation problem. */
    VS_RENDER_FAILED = 0x0fff,
};


////////////////////////////////////////////////////////////////////////////////
typedef void * VsVoidHandle;


/** \file Vs.h
    \brief Global definitions
*/

/** The Vs namespace provides common identifiers and helper functions.
    It contains common identifiers such as event names, option names,
    or result codes. It also provides the static methods for error handling,
    namely lastError() and setError(). */

namespace Vs
{
    /** Retrieves the last error code for the current thread.

        This method is used for handling error situations. If an error
        occours inside the library a McResult object is generated and
        set with setLastError(). The library function then usually 
        returns VS_FAILED or a null pointer. This method returns the
        last McResult object. As a side-effect the error state is reset
        so that the next call to this method returns McOK.

        For possible result codes of the returned McResult objects see
        Vs::ResultCode. Since multiple threads may run simultaneously
        into error situations the last error is stored on a per thread
        basis.

        \return The McResult object set with the last call to setError().
                McOK is returned if setError() was never called at all or
                if setError() was not called since last call to lastError().
    */
    extern VSVOLREN_API McResult lastError();

    /** Set McResult object for the current thread.
        \param  inResult
                The McResult object.
    */
    extern VSVOLREN_API void setError( const McResult & inResult );

    /** Returns whether the OpenGL driver vendor is ATI. */
    extern VSVOLREN_API bool isVendorATI();

    /** Returns whether the OpenGL driver vendor is Intel. */
    extern VSVOLREN_API bool isVendorIntel();

    /** Returns whether the OpenGL driver vendor is NVIDIA. */
    extern VSVOLREN_API bool isVendorNVIDIA();

    /** Returns whether the OpenGL driver vendor is Mesa. */
    extern VSVOLREN_API bool isVendorMesa();

    /** Check whether current graphics hardware is supported.
        Requires valid rendering context that has been activated by calling
        mcglSetContext() \link vsvolren_integration (Library Integration) \endlink .
        \return VS_OK, if a supported graphics hardware was detected.
    */
    extern VSVOLREN_API VSRESULT checkGraphics();

    /** Check for a valid product license.
        \return VS_OK, if a valid license was found.
    */
    extern VSVOLREN_API VSRESULT checkLicense();

    /** Returns the version of the library.
        You can use this method at run-time to check which version
        of the library your application is working with. The
        method returns the value of the VS_VOLREN_VERSION symbol
        at compile-time.
        \sa VS_VOLREN_VERSION
    */
    extern VSVOLREN_API int version();

    
    // register class factory
    extern VSVOLREN_API VSRESULT registerClass( char const * inClassName, INTERFACEFACTORYFUNC );

    // query class factory
    extern VSVOLREN_API INTERFACEFACTORYFUNC factory( char const * inClassName );




    /** This enum identifies mouse events.
        \sa VsInteractionManager::processMouseEvent() */
    enum MouseEvent
    {
        /// Mouse move
        ME_Move = 0,
        /// Left mouse button up
        ME_LeftButtonUp = 2,
        /// Left mouse button down
        ME_LeftButtonDown = 3,
        /// Middle mouse button up
        ME_MidButtonUp = 4,
        /// Middle mouse button down
        ME_MidButtonDown = 5,
        /// Right mouse button up
        ME_RightButtonUp = 6,
        /// Right mouse button down
        ME_RightButtonDown  = 7,
        /// Mouse entered the window
        ME_WindowEnter = 8,
        /// Mouse left the window
        ME_WindowLeave = 9
    };

    /** This enum identifies modifier states. For each modifier a separate
        bit is used. Typically multiple identifiers are OR'ed together.
        \sa VsInteractionManager::processMouseEvent(),
            VsInteractionManager::processKeyEvent(),
            VsInteractionManager::processWheelEvent()
    */
    enum ButtonState
    {
        /// Left mouse button is down
        BS_LeftButton = 1 << 0,
        /// Middle mouse button is down
        BS_MidButton = 1 << 1,
        /// Right mouse button is down
        BS_RightButton = 1 << 2,
        /// Shift key is pressed
        BS_ShiftButton = 1 << 3,
        /// Control key is pressed
        BS_ControlButton = 1 << 4,
        /// Alt key is pressed
        BS_AltButton = 1 << 5,
        /// The event is a double-click event
        BS_DblClick = 1 << 6
    };

    /** This enum indicates is a key was pressed or released.
        \sa VsInteractionManager::processKeyEvent() */
    enum KeyEvent 
    {
        /// The event type is unknown
        KE_None = 0,
        /// The key was pressed
        KE_Pressed = 1,
        /// The key was released
        KE_Released = 2
    };

    /** The key names.
        \sa VsInteractionManager::processKeyEvent() */
    enum Key 
    {
        /// Escape          
        Key_Escape          = 0x1000,        // misc keys
        /// Tab             
        Key_Tab             = 0x1001,
        /// Backtab         
        Key_Backtab         = 0x1002, 
        /// BackTab         
        Key_BackTab         = Key_Backtab,
        /// Backspace       
        Key_Backspace       = 0x1003, 
        /// BackSpace       
        Key_BackSpace       = Key_Backspace,
        /// Return          
        Key_Return          = 0x1004,
        /// Enter           
        Key_Enter           = 0x1005,
        /// Insert          
        Key_Insert          = 0x1006,
        /// Delete          
        Key_Delete          = 0x1007,
        /// Pause           
        Key_Pause           = 0x1008,
        /// Print           
        Key_Print           = 0x1009,
        /// SysReq          
        Key_SysReq          = 0x100a,
        /// Clear           
        Key_Clear           = 0x100b,
        /// Home            
        Key_Home            = 0x1010,        // cursor movement
        /// End             
        Key_End             = 0x1011,
        /// Left            
        Key_Left            = 0x1012,
        /// Up              
        Key_Up              = 0x1013,
        /// Right           
        Key_Right           = 0x1014,
        /// Down            
        Key_Down            = 0x1015,
        /// Prior           
        Key_Prior           = 0x1016, 
        /// PageUp          
        Key_PageUp          = Key_Prior,
        /// Next            
        Key_Next            = 0x1017, 
        /// PageDown        
        Key_PageDown        = Key_Next,
        /// Shift           
        Key_Shift           = 0x1020,        // modifiers
        /// Control         
        Key_Control         = 0x1021,
        /// Meta            
        Key_Meta            = 0x1022,
        /// Alt             
        Key_Alt             = 0x1023,
        /// CapsLock        
        Key_CapsLock        = 0x1024,
        /// NumLock         
        Key_NumLock         = 0x1025,
        /// ScrollLock      
        Key_ScrollLock      = 0x1026,
        /// F1              
        Key_F1              = 0x1030,        // function keys
        /// F2              
        Key_F2              = 0x1031,
        /// F3              
        Key_F3              = 0x1032,
        /// F4              
        Key_F4              = 0x1033,
        /// F5              
        Key_F5              = 0x1034,
        /// F6              
        Key_F6              = 0x1035,
        /// F7              
        Key_F7              = 0x1036,
        /// F8              
        Key_F8              = 0x1037,
        /// F9              
        Key_F9              = 0x1038,
        /// F10             
        Key_F10             = 0x1039,
        /// F11             
        Key_F11             = 0x103a,
        /// F12             
        Key_F12             = 0x103b,
        /// F13             
        Key_F13             = 0x103c,
        /// F14             
        Key_F14             = 0x103d,
        /// F15             
        Key_F15             = 0x103e,
        /// F16             
        Key_F16             = 0x103f,
        /// F17             
        Key_F17             = 0x1040,
        /// F18             
        Key_F18             = 0x1041,
        /// F19             
        Key_F19             = 0x1042,
        /// F20             
        Key_F20             = 0x1043,
        /// F21             
        Key_F21             = 0x1044,
        /// F22             
        Key_F22             = 0x1045,
        /// F23             
        Key_F23             = 0x1046,
        /// F24             
        Key_F24             = 0x1047,
        /// F25             
        Key_F25             = 0x1048,        // F25 .. F35 only on X11
        /// F26             
        Key_F26             = 0x1049,
        /// F27             
        Key_F27             = 0x104a,
        /// F28             
        Key_F28             = 0x104b,
        /// F29             
        Key_F29             = 0x104c,
        /// F30             
        Key_F30             = 0x104d,
        /// F31             
        Key_F31             = 0x104e,
        /// F32             
        Key_F32             = 0x104f,
        /// F33             
        Key_F33             = 0x1050,
        /// F34             
        Key_F34             = 0x1051,
        /// F35             
        Key_F35             = 0x1052,
        /// Super_L         
        Key_Super_L         = 0x1053,         // extra keys
        /// Super_R         
        Key_Super_R         = 0x1054,
        /// Menu            
        Key_Menu            = 0x1055,
        /// Hyper_L         
        Key_Hyper_L         = 0x1056,
        /// Hyper_R         
        Key_Hyper_R         = 0x1057,
        /// Help            
        Key_Help            = 0x1058,
        /// Direction_L     
        Key_Direction_L     = 0x1059,
        /// Direction_R     
        Key_Direction_R     = 0x1060,
        /// Space           
        Key_Space           = 0x20,        // 7 bit printable ASCII
        /// Any             
        Key_Any             = Key_Space,
        /// Exclam          
        Key_Exclam          = 0x21,
        /// QuoteDbl        
        Key_QuoteDbl        = 0x22,
        /// NumberSign      
        Key_NumberSign      = 0x23,
        /// Dollar          
        Key_Dollar          = 0x24,
        /// Percent         
        Key_Percent         = 0x25,
        /// Ampersand       
        Key_Ampersand       = 0x26,
        /// Apostrophe      
        Key_Apostrophe      = 0x27,
        /// ParenLeft       
        Key_ParenLeft       = 0x28,
        /// ParenRight      
        Key_ParenRight      = 0x29,
        /// Asterisk        
        Key_Asterisk        = 0x2a,
        /// Plus            
        Key_Plus            = 0x2b,
        /// Comma           
        Key_Comma           = 0x2c,
        /// Minus           
        Key_Minus           = 0x2d,
        /// Period          
        Key_Period          = 0x2e,
        /// Slash           
        Key_Slash           = 0x2f,
        /// 0               
        Key_0               = 0x30,
        /// 1               
        Key_1               = 0x31,
        /// 2               
        Key_2               = 0x32,
        /// 3               
        Key_3               = 0x33,
        /// 4               
        Key_4               = 0x34,
        /// 5               
        Key_5               = 0x35,
        /// 6               
        Key_6               = 0x36,
        /// 7               
        Key_7               = 0x37,
        /// 8               
        Key_8               = 0x38,
        /// 9               
        Key_9               = 0x39,
        /// Colon           
        Key_Colon           = 0x3a,
        /// Semicolon       
        Key_Semicolon       = 0x3b,
        /// Less            
        Key_Less            = 0x3c,
        /// Equal           
        Key_Equal           = 0x3d,
        /// Greater         
        Key_Greater         = 0x3e,
        /// Question        
        Key_Question        = 0x3f,
        /// At              
        Key_At              = 0x40,
        /// A               
        Key_A               = 0x41,
        /// B               
        Key_B               = 0x42,
        /// C               
        Key_C               = 0x43,
        /// D               
        Key_D               = 0x44,
        /// E               
        Key_E               = 0x45,
        /// F               
        Key_F               = 0x46,
        /// G               
        Key_G               = 0x47,
        /// H               
        Key_H               = 0x48,
        /// I               
        Key_I               = 0x49,
        /// J               
        Key_J               = 0x4a,
        /// K               
        Key_K               = 0x4b,
        /// L               
        Key_L               = 0x4c,
        /// M               
        Key_M               = 0x4d,
        /// N               
        Key_N               = 0x4e,
        /// O               
        Key_O               = 0x4f,
        /// P               
        Key_P               = 0x50,
        /// Q               
        Key_Q               = 0x51,
        /// R               
        Key_R               = 0x52,
        /// S               
        Key_S               = 0x53,
        /// T               
        Key_T               = 0x54,
        /// U               
        Key_U               = 0x55,
        /// V               
        Key_V               = 0x56,
        /// W               
        Key_W               = 0x57,
        /// X               
        Key_X               = 0x58,
        /// Y               
        Key_Y               = 0x59,
        /// Z               
        Key_Z               = 0x5a,
        /// BracketLeft     
        Key_BracketLeft     = 0x5b,
        /// Backslash       
        Key_Backslash       = 0x5c,
        /// BracketRight    
        Key_BracketRight    = 0x5d,
        /// AsciiCircum     
        Key_AsciiCircum     = 0x5e,
        /// Underscore      
        Key_Underscore      = 0x5f,
        /// QuoteLeft       
        Key_QuoteLeft       = 0x60,
        /// BraceLeft       
        Key_BraceLeft       = 0x7b,
        /// Bar             
        Key_Bar             = 0x7c,
        /// BraceRight      
        Key_BraceRight      = 0x7d,
        /// AsciiTilde      
        Key_AsciiTilde      = 0x7e,
        /// nobreakspace    
        Key_nobreakspace    = 0x0a0,
        /// exclamdown      
        Key_exclamdown      = 0x0a1,
        /// cent            
        Key_cent            = 0x0a2,
        /// sterling        
        Key_sterling        = 0x0a3,
        /// currency        
        Key_currency        = 0x0a4,
        /// yen             
        Key_yen             = 0x0a5,
        /// brokenbar       
        Key_brokenbar       = 0x0a6,
        /// section         
        Key_section         = 0x0a7,
        /// diaeresis       
        Key_diaeresis       = 0x0a8,
        /// copyright       
        Key_copyright       = 0x0a9,
        /// ordfeminine     
        Key_ordfeminine     = 0x0aa,
        /// guillemotleft   
        Key_guillemotleft   = 0x0ab,    // left angle quotation mark
        /// notsign         
        Key_notsign         = 0x0ac,
        /// hyphen          
        Key_hyphen          = 0x0ad,
        /// registered      
        Key_registered      = 0x0ae,
        /// macron          
        Key_macron          = 0x0af,
        /// degree          
        Key_degree          = 0x0b0,
        /// plusminus       
        Key_plusminus       = 0x0b1,
        /// twosuperior     
        Key_twosuperior     = 0x0b2,
        /// threesuperior   
        Key_threesuperior   = 0x0b3,
        /// acute           
        Key_acute           = 0x0b4,
        /// mu              
        Key_mu              = 0x0b5,
        /// paragraph       
        Key_paragraph       = 0x0b6,
        /// periodcentered  
        Key_periodcentered  = 0x0b7,
        /// cedilla         
        Key_cedilla         = 0x0b8,
        /// onesuperior     
        Key_onesuperior     = 0x0b9,
        /// masculine       
        Key_masculine       = 0x0ba,
        /// guillemotright  
        Key_guillemotright  = 0x0bb,    // right angle quotation mark
        /// onequarter      
        Key_onequarter      = 0x0bc,
        /// onehalf         
        Key_onehalf         = 0x0bd,
        /// threequarters   
        Key_threequarters   = 0x0be,
        /// questiondown    
        Key_questiondown    = 0x0bf,
        /// Agrave          
        Key_Agrave          = 0x0c0,
        /// Aacute          
        Key_Aacute          = 0x0c1,
        /// Acircumflex     
        Key_Acircumflex     = 0x0c2,
        /// Atilde          
        Key_Atilde          = 0x0c3,
        /// Adiaeresis      
        Key_Adiaeresis      = 0x0c4,
        /// Aring           
        Key_Aring           = 0x0c5,
        /// AE              
        Key_AE              = 0x0c6,
        /// Ccedilla        
        Key_Ccedilla        = 0x0c7,
        /// Egrave          
        Key_Egrave          = 0x0c8,
        /// Eacute          
        Key_Eacute          = 0x0c9,
        /// Ecircumflex     
        Key_Ecircumflex     = 0x0ca,
        /// Ediaeresis      
        Key_Ediaeresis      = 0x0cb,
        /// Igrave          
        Key_Igrave          = 0x0cc,
        /// Iacute          
        Key_Iacute          = 0x0cd,
        /// Icircumflex     
        Key_Icircumflex     = 0x0ce,
        /// Idiaeresis      
        Key_Idiaeresis      = 0x0cf,
        /// ETH             
        Key_ETH             = 0x0d0,
        /// Ntilde          
        Key_Ntilde          = 0x0d1,
        /// Ograve          
        Key_Ograve          = 0x0d2,
        /// Oacute          
        Key_Oacute          = 0x0d3,
        /// Ocircumflex     
        Key_Ocircumflex     = 0x0d4,
        /// Otilde          
        Key_Otilde          = 0x0d5,
        /// Odiaeresis      
        Key_Odiaeresis      = 0x0d6,
        /// multiply        
        Key_multiply        = 0x0d7,
        /// Ooblique        
        Key_Ooblique        = 0x0d8,
        /// Ugrave          
        Key_Ugrave          = 0x0d9,
        /// Uacute          
        Key_Uacute          = 0x0da,
        /// Ucircumflex     
        Key_Ucircumflex     = 0x0db,
        /// Udiaeresis      
        Key_Udiaeresis      = 0x0dc,
        /// Yacute          
        Key_Yacute          = 0x0dd,
        /// THORN           
        Key_THORN           = 0x0de,
        /// ssharp          
        Key_ssharp          = 0x0df,
        /// agrave          
        Key_agrave          = 0x0e0,
        /// aacute          
        Key_aacute          = 0x0e1,
        /// acircumflex     
        Key_acircumflex     = 0x0e2,
        /// atilde          
        Key_atilde          = 0x0e3,
        /// adiaeresis      
        Key_adiaeresis      = 0x0e4,
        /// aring           
        Key_aring           = 0x0e5,
        /// ae              
        Key_ae              = 0x0e6,
        /// ccedilla        
        Key_ccedilla        = 0x0e7,
        /// egrave          
        Key_egrave          = 0x0e8,
        /// eacute          
        Key_eacute          = 0x0e9,
        /// ecircumflex     
        Key_ecircumflex     = 0x0ea,
        /// ediaeresis      
        Key_ediaeresis      = 0x0eb,
        /// igrave          
        Key_igrave          = 0x0ec,
        /// iacute          
        Key_iacute          = 0x0ed,
        /// icircumflex     
        Key_icircumflex     = 0x0ee,
        /// idiaeresis      
        Key_idiaeresis      = 0x0ef,
        /// eth             
        Key_eth             = 0x0f0,
        /// ntilde          
        Key_ntilde          = 0x0f1,
        /// ograve          
        Key_ograve          = 0x0f2,
        /// oacute          
        Key_oacute          = 0x0f3,
        /// ocircumflex     
        Key_ocircumflex     = 0x0f4,
        /// otilde          
        Key_otilde          = 0x0f5,
        /// odiaeresis      
        Key_odiaeresis      = 0x0f6,
        /// division        
        Key_division        = 0x0f7,
        /// oslash          
        Key_oslash          = 0x0f8,
        /// ugrave          
        Key_ugrave          = 0x0f9,
        /// uacute          
        Key_uacute          = 0x0fa,
        /// ucircumflex     
        Key_ucircumflex     = 0x0fb,
        /// udiaeresis      
        Key_udiaeresis      = 0x0fc,
        /// yacute          
        Key_yacute          = 0x0fd,
        /// thorn           
        Key_thorn           = 0x0fe,
        /// ydiaeresis      
        Key_ydiaeresis      = 0x0ff,
        /// Back            
        Key_Back            = 0x1061,
        /// Forward         
        Key_Forward         = 0x1062,
        /// Stop            
        Key_Stop            = 0x1063,
        /// Refresh         
        Key_Refresh         = 0x1064,
        /// VolumeDown      
        Key_VolumeDown      = 0x1070,
        /// VolumeMute      
        Key_VolumeMute      = 0x1071,
        /// VolumeUp        
        Key_VolumeUp        = 0x1072,
        /// BassBoost       
        Key_BassBoost       = 0x1073,
        /// BassUp          
        Key_BassUp          = 0x1074,
        /// BassDown        
        Key_BassDown        = 0x1075,
        /// TrebleUp        
        Key_TrebleUp        = 0x1076,
        /// TrebleDown      
        Key_TrebleDown      = 0x1077,                        
        /// MediaPlay       
        Key_MediaPlay       = 0x1080,
        /// MediaStop       
        Key_MediaStop       = 0x1081,
        /// MediaPrev       
        Key_MediaPrev       = 0x1082,
        /// MediaNext       
        Key_MediaNext       = 0x1083,
        /// MediaRecord     
        Key_MediaRecord     = 0x1084,
        /// HomePage        
        Key_HomePage        = 0x1090,
        /// Favorites       
        Key_Favorites       = 0x1091,
        /// Search          
        Key_Search          = 0x1092,
        /// Standby         
        Key_Standby         = 0x1093,
        /// OpenUrl         
        Key_OpenUrl         = 0x1094,
        /// LaunchMail      
        Key_LaunchMail      = 0x10a0,
        /// LaunchMedia     
        Key_LaunchMedia     = 0x10a1,
        /// Launch0         
        Key_Launch0         = 0x10a2,
        /// Launch1         
        Key_Launch1         = 0x10a3,
        /// Launch2         
        Key_Launch2         = 0x10a4,
        /// Launch3         
        Key_Launch3         = 0x10a5,
        /// Launch4         
        Key_Launch4         = 0x10a6,
        /// Launch5         
        Key_Launch5         = 0x10a7,
        /// Launch6         
        Key_Launch6         = 0x10a8,
        /// Launch7         
        Key_Launch7         = 0x10a9,
        /// Launch8         
        Key_Launch8         = 0x10aa,
        /// Launch9         
        Key_Launch9         = 0x10ab,
        /// LaunchA         
        Key_LaunchA         = 0x10ac,
        /// LaunchB         
        Key_LaunchB         = 0x10ad,
        /// LaunchC         
        Key_LaunchC         = 0x10ae,
        /// LaunchD         
        Key_LaunchD         = 0x10af,
        /// LaunchE         
        Key_LaunchE         = 0x10b0,
        /// LaunchF         
        Key_LaunchF         = 0x10b1,
               
        Key_MediaLast       = 0x1fff,
                                
        Key_unknown         = 0xffff        
    };

    /// Option keys to be used in the option-methods of VsObject.
    enum Option
    {
        // 
        // Only the options commented with doxygen style are officially supported.
        // The others are either used for internal testing
        //  or are evil, internal, experimental, risky, not implemented ... .
        //

        ////////////////////////////////////////
        // VsVolren
        ////////////////////////////////////////

        /**  INT : Set shader API to be used by the the node for redering.
             See enum TechniqueAPI for possible values.
             This option is accepted by instances of VsSlice, VsSurfRen and VsVolren. */
        OPT_TECHNIQUE_API       = 0x0100,   

        /*  INT : Enables normal computation on-the-fly. If this option is set normals
            are computed on the GPU even if precomputed normals are provided by
            the VsVolume object being rendered. */
        OPT_AUTO_NORMALS        = 0x0101,

        /*  INT: Number of volume samples used to render level 0 data. The
            number of samples is set automatically whenever a new volume is
            specified via setVolume(). If you wish to override this default you
            have to set this option after calling setVolume() (integer value). */
        OPT_NUM_SLICES_LEVEL0   = 0x0102,

        /*  Number of volume samples used to render level 1 data. The
            number of samples is set automatically whenever a new volume is
            specified via setVolume(). If you wish to override this default you
            have to set this option after calling setVolume() (integer value). */
        OPT_NUM_SLICES_LEVEL1   = OPT_NUM_SLICES_LEVEL0 + 1,
        OPT_NUM_SLICES_LEVEL2   = OPT_NUM_SLICES_LEVEL0 + 2,
        OPT_NUM_SLICES_LEVEL3   = OPT_NUM_SLICES_LEVEL0 + 3,
        OPT_NUM_SLICES_LEVEL4   = OPT_NUM_SLICES_LEVEL0 + 4,
        OPT_NUM_SLICES_LEVEL5   = OPT_NUM_SLICES_LEVEL0 + 5,
        OPT_NUM_SLICES_LEVEL6   = OPT_NUM_SLICES_LEVEL0 + 6,
        OPT_NUM_SLICES_LEVEL7   = OPT_NUM_SLICES_LEVEL0 + 7,

        /** Flag indicating that a pbuffer should be used inside VsVolren. If set,
            a pbuffer will be used even if it would be possible to render directly
            into the main render target. Otherwise, a pbuffer will only be used
            if viewport scaling or HDR rendering is enabled in VsVolren. (integer
            value) */
        OPT_TRY_USE_PBUFFER     = 0x0110,

        /*  INT : Flag indicating that the pbuffer is forced to have the same
            per-channel depth as the main render target. */
        OPT_ADAPT_PBUFFER_DEPTH = 0x0111,

        /*  INT : Flag indicating that the depth buffer of the main render target
            should be transfered to the offscreen render target. Currently this is
            only possible if the viewport scale factor is 1.0 or 0.5. */
        OPT_TRY_COPY_ZBUFFER    = 0x0112,

        /*  INT : If nonzero the volume textures are uploaded preswizzeled via the PBO extension.
            This is experimental and only available on certain NVIDIA drivers. */
        OPT_USE_PBO_UPLOAD      = 0x0113,

        /** Enable or disable linear texture filtering (integer value). */
        OPT_MAG_FILTER_LINEAR   = 0x0114,

        /** Viewport scaling factor. Viewport minification @c factor < 1 is
            used during interaction to improve the rendering speed (double value). */
        OPT_VIEW_PORT_SCALE     = 0x0115,

        OPT_NORMAL_CLIP_WIDTH_LEVEL0 = 0x0120,
        OPT_NORMAL_CLIP_WIDTH_LEVEL1 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 1,
        OPT_NORMAL_CLIP_WIDTH_LEVEL2 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 2,
        OPT_NORMAL_CLIP_WIDTH_LEVEL3 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 3,
        OPT_NORMAL_CLIP_WIDTH_LEVEL4 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 4,
        OPT_NORMAL_CLIP_WIDTH_LEVEL5 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 5,
        OPT_NORMAL_CLIP_WIDTH_LEVEL6 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 6,
        OPT_NORMAL_CLIP_WIDTH_LEVEL7 = OPT_NORMAL_CLIP_WIDTH_LEVEL0 + 7,

        /* INT : reserved */
        OPT_DEBUG_HUD_VISIBLE   = 0x0130,

        /* INT : reserved
           Forces shaders to be reinitialized. Before the node is rendered
           the next time all shader objects are recreated and recompiled. */
        OPT_RESET_TECHNIQUE     = 0x0131,

        /* INT : reserved */
        OPT_REUSE_PRIMS         = 0x0132,

        /* INT : reserved */
        OPT_STATS_INIT          = 0x0133,

        /* On R3x0-based GPUs (ATI 9x00), the rendering speed dramatically changes depending
            from which direction the object is viewed from. 
            This is due to the non-swizzeled representation of textures in GPU-memory which leads
            to view dependent cache latencies.
            To get fast rendering from all directions one can store each brick also in two flipped
            versions and pick the fastest one for rendering depending on the current view direction.
            This can be toggeled for each volume level independently.
            The main use of this would be to turn this feature on for volume level holding the data
            for interactive rendering. Since this is usually not so big, storing two more of them
            is usually no problem.
        */
        OPT_ATI_SWIZZLE_LEVEL0  = 0x0134,
        OPT_ATI_SWIZZLE_LEVEL1  = OPT_ATI_SWIZZLE_LEVEL0 + 1,
        OPT_ATI_SWIZZLE_LEVEL2  = OPT_ATI_SWIZZLE_LEVEL0 + 2,
        OPT_ATI_SWIZZLE_LEVEL3  = OPT_ATI_SWIZZLE_LEVEL0 + 3,
        OPT_ATI_SWIZZLE_LEVEL4  = OPT_ATI_SWIZZLE_LEVEL0 + 4,
        OPT_ATI_SWIZZLE_LEVEL5  = OPT_ATI_SWIZZLE_LEVEL0 + 5,
        OPT_ATI_SWIZZLE_LEVEL6  = OPT_ATI_SWIZZLE_LEVEL0 + 6,
        OPT_ATI_SWIZZLE_LEVEL7  = OPT_ATI_SWIZZLE_LEVEL0 + 7,

        /* INT : reserved */
        OPT_PREF_BRICK_SIZE_X   = 0x0140,
        OPT_PREF_BRICK_SIZE_Y   = 0x0141,
        OPT_PREF_BRICK_SIZE_Z   = 0x0142,

        /* INT : reserved */
        OPT_DEBUG_HUD_CM_VISIBLE = 0x0143,

        /* INT : reserved */
        OPT_ID                  = 0x0144,

        /* DOUBLE : reserved */
        OPT_VOLREN_FPS_LOWRES   = 0x0145,

        /* DOUBLE : reserved */
        OPT_VOLUME_READ_TIME    = 0x0146,
        OPT_VOLUME_READ_TIME_ASYNC      = 0x0147,

        /* INT : reserved */
        OPT_WRITE_LOCKS_ENABLED         = 0x0148,

        /* INT : reserved */
        OPT_WRITE_LOCKS_CHECK_ENABLED   = 0x0149,

        /* INT : reserved */
        OPT_VOLREN_NUM_TEX_UPLOADED     = 0x014A,

        /** Enable or disable smart sampling. Smart sampling can be used to
            improve image quality in volume rendering by reducing slicing
            artifacts. It slows down rendering performance a little bit. The
            default is on. */
        OPT_SMARTSAMPLING_ENABLE        = 0x014B,

        /* INT : reserved */
        OPT_INVOKE_BSP_DEBUGGER         = 0x014C,

        /** Enables or disables interruption of low res rendering jobs
            in VsSlice. If this option is set, and if no slice could
            be extracted in the time limit set via VsSlice::setRenderTime(),
            the rendering job will be canceled and no frame update occurs. 
            This option becomes handy, when multiple slice nodes are used.
            If in this case user interaction triggers an update of all slice
            nodes and even interactive jobs take too long (which might easily
            be the case if thick slices are involved) the application might 
            become unusable unless you allow for interruption of interative 
            jobs as well.
            The default is off.
            This option requires an integer value. */
        OPT_INTERRUPT_LOWRES            = 0x0150,

        /** INT: Enables/Disabled automatic level switching in VsSlice for improved interactivity */
        OPT_AUTOLEVEL                   = 0x0155,

        /** INT: Enables/Disables low thick slice sampling rate for improved interactivity in VsSlice */
        OPT_THICK_STRIDE                = 0x0156,

        /** INT: Enables/Disables downsampling for the slice data extraction for improved interactivity in VsSlice */
        OPT_SLICE_DOWNSAMPLING          = 0x0157,

        /** INT: Specifies a factor that is used influences the extent of downsampling. */
        OPT_SLICE_DOWNSAMPLING_FACTOR   = 0x0158,

        /** INT: Enables/Disables clamping of the slice position (see VsSlice::setPlane()) in
                  case of orthographic slice planes. If enabled (default) a slice plane that 
                  would lie outside the volume bounding box will be automatically relocated 
                  to the closest valid position inside the bounding box. */
        OPT_SLICE_CLAMP_ORTHO           = 0x0159,

        /** Enable or disable the automatic viewport scaling mechanism.
            If enabled the base viewport scaling factor for interactive
            rendering in VsVolren (see Vs::OPT_VIEW_PORT_SCALE) will be
            automatically adjusted to better meet the desired frame rate.
        */
        OPT_AUTO_VIEWSCALE_ENABLE       = 0x0170,

        /** INT : Enable/Disable HDR rendering for a VsVolren node. This improves the resulting 
            image when accumulating nearly transparent voxels. 
            If enabled, the VsVolren node renders to an extra float render target.
            Turning this on will force VsVolren to allocate an additional
            render target and to perform an additional render pass except VsCommonRenderer
            is already used in offscreen mode where this extra render target is required anyway.
        */
        OPT_HDR_ENABLE                  = 0x0171,

        /** DOUBLE: Lowest possible scale factor for the automatic viewport scaling mechanism.
        */
        OPT_AUTO_VIEWSCALE_MIN          = 0x0172,

        /** DOUBLE: Lowest possible scale factor for the automatic viewport scaling mechanism.
        */
        OPT_AUTO_VIEWSCALE_MAX          = 0x0173,

        /** INT: force \link VsRenderer::startRenderingToBuffer() 
            startRenderingToBuffer() \endlink to display the image on screen.
            This might be useful for example on movie capturing where the images taken by
            \link VsRenderer::startRenderingToBuffer() startRenderingToBuffer() \endlink might also be displayed in a window.
        */
        OPT_SHOW_RENDERED_BUFFER        = 0x0174,

        /* INT: optimization method for surface rendering
        */
        OPT_SURFREN_OPTIMIZATION        = 0x0190,

        /** DOUBLE: Level 0 scale factor for the distance between the sampling planes of the 
            slice based volume rendering. The concrete slice distance is computed by VsVolren 
            at runtime and depends mainly on volume and voxel dimensions as well as the current
            camera settings. The default value is 1.0, Larger values represent higher quality but
            result in linearly decreased performance, e.g. if the factor is set to 2.0 quality
            is "doubled".
        */
        OPT_QUALITY_LEVEL0              = 0x0180,

        /** DOUBLE: Level 1 scale factor for the distance between the sampling planes of the 
            slice based volume rendering. The concrete slice distance is computed by VsVolren 
            at runtime and depends mainly on volume and voxel dimensions as well as the current
            camera settings. The default value is 1.0, Larger values represent higher quality but
            result in linearly decreased performance, e.g. if the factor is set to 2.0 quality
            is "doubled".
        */
        OPT_QUALITY_LEVEL1              = 0x0181,

        /* Forces the VsVolren node to always render level 0 (high-res data) even for interactive
           rendering requests, provided the level 0 data completely fits into texture memory. */
        OPT_TRY_USE_LEVEL0              = 0x0182,

        // clip fusion rendering with respect to primary volume bounding box 
        OPT_CLIP_FUSION                 = 0x190,

        /**
         * Get the current slice distance or set a fixed slice distance.
         */
        OPT_SLICE_DISTANCE,

        /**
         * This options tells, if the slice distance is fixed or calculated dynamically.
         * Setting this to non-zero fails. To enable this option, set OPT_SLICE_DISTANCE
         * instead.
         * Setting this to zero reverts to the default behaviour of using a dynamic
         * slice distance.
         */
        OPT_SLICE_DISTANCE_FIXED,

        ////////////////////////////////////////
        // User Defined Options
        ////////////////////////////////////////
        OPT_USER0 = 0x8000
    };

    // Option keys to be used in the option-methods of VsObject.
    enum TechniqueAPI
    {
        /* The actual shader interface is determined automatically based on
           the current hardware and driver (default). */
        SA_AUTO     = 0,
        // Enforces GLSL (OpenGL shading language).
        SA_GLSL     = 1,
        // Enforces ARB fragment programs.
        SA_ARB      = 2
    };

    /// codes of the McResult objects returned by Vs::lastError()
    enum ResultCode
    {
        /// operation successful
        CODE_OK                = 0x0000 + 0,
        /// one of the arguments is invalid
        CODE_INVALIDARGUMENT   = 0x0000 + 1,
        /// internal error
        CODE_INTERNALERROR     = 0x0000 + 2,
        /// data expected
        CODE_NODATA            = 0x0000 + 3,
        /// not supported
        CODE_NOTSUPPORTED      = 0x0000 + 4,
        /// read only
        CODE_READONLY          = 0x0000 + 5,
        /// out of range
        CODE_OUTOFRANGE        = 0x0000 + 6,
        /// not implemented
        CODE_NOTIMPLEMENTED    = 0x0000 + 7,
        /// out of memory
        CODE_OUTOFMEMORY       = 0x0000 + 8,
        /// false
        CODE_FALSE             = 0x0000 + 9,
        /// invalid operation
        CODE_BADOPERATION      = 0x0000 + 10,
        /// time consuming operation has been interrupted by user request
        CODE_INTERRUPTED       = 0x0000 + 11,
        /// failed to write file
        CODE_FILEWRITE         = 0x0000 + 12,
        /// failed to read file
        CODE_FILEREAD          = 0x0000 + 13
    };
};

#endif
