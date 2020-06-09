#if !defined HX_PRODUCT_ENV_VAR_MGR_H
#define HX_PRODUCT_ENV_VAR_MGR_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxcore/HxAmiraWinDLLApi.h>
#include <mclib/McString.h>
#include <mclib/McDArray.h>

/**
* This class is used to manage environment variables according
* to the current product (Amira, Avizo...).
* Internally, we are only dealing with environment variables 
* prefixed by AMIRA (AMIRA_ROOT, AMIRA_LOCAL, AMIRAMESH_DEBUG...).
* However, it's possible that some environment variables will be
* prefixed by the current product name (AVIZO_ROOT for instance).
* The idea is to store all the AMIRAXXX environment variables in 
* a list and check if the matching PRODUCTNAMEXXX environment
* variables are set. In this case, we set the AMIRAXXX values with
* the PRODUCTNAMEXXX ones.
* WARNING: The list of AMIRAXXX environment variables must be updated!
* Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
*/

class HXCORE_API HxProductEnvVarMgr 
{

public:

  /** 
   * Returns pointer to global instance.
   */
  static HxProductEnvVarMgr* getGlobalInstance(bool create = true);

  /** 
   * To init amira environment variables according to the product.
   * Example: if AVIZO_ROOT environment variable is set, AMIRA_ROOT
   * will be set with the same value.
   */
  static void initEnvVar(McString productName);

  /** 
   * To get the right environment variable according to the product.
   */
  static McString getEnvVarName(const McString& envVar);

  /** 
  * Get the environment variables list.
  */
  const McDArray< McString > & getEnvVars() const{ return m_envVarList; }

private:

  /** 
   * Constructor.
   */
  HxProductEnvVarMgr();

  /** 
   * Destructor.
   */
  virtual ~HxProductEnvVarMgr();

  /** 
   * The environment variables list.
   */
  McDArray< McString > m_envVarList; 

  /** 
   * Instance.
   */
  static HxProductEnvVarMgr* s_theInstance;

};

//------------------------------------------------------------------------------
#define theProductEnvVarMgr HxProductEnvVarMgr::getGlobalInstance()

static McString envVarList[57] = {
  "AMIRA_CHECK_FREERAM",
  "AMIRA_COM_DESYNC_TIMEOUT",
  "AMIRA_COM_LOG",
  "AMIRA_COM_RESYNC_TIMEOUT",
  "AMIRA_DATA",
  "AMIRA_DATADIR",
  "AMIRA_DEBUG",
  "AMIRA_DEBUG_FUNC_FILTER",
  "AMIRA_DEBUG_LEVEL",
  "AMIRA_DEBUG_PACKAGE_FILTER",
  "AMIRA_DECONV_NUM_THREADS",
  "AMIRA_DEFAULTVISUAL",
  "AMIRA_DEMOS",
  "AMIRA_DICOM_JPEG_BASE",
  "AMIRA_EXEC_ARCH",
  "AMIRA_FAKEBUTTON",
  "AMIRA_FORCE_FLUENT_DIALOG",
  "AMIRA_FORCE_NOBORDER",
  "AMIRA_FORCE_VOLUMEVIZ",
  "AMIRA_GI_NOCOG",
  "AMIRA_HOSTNAME",
  "AMIRA_INIT_FILE",
  "AMIRA_JOB_LOG_FILE",
  "AMIRA_LICENSE_FILE",
  "AMIRA_LOCAL",
  "AMIRA_MESA",
  "AMIRA_MHT_STEREOTAXIS",
  "AMIRA_MULTISAMPLE",
  "AMIRA_MULTITHREAD",
  "AMIRA_NETWORKDRIVE_DIR",
  "AMIRA_NO_CONTEXT_SHARING",
  "AMIRA_NO_INDEX",
  "AMIRA_NO_INDEX_THREAD",
  "AMIRA_NO_LICENSE_MESSAGE",
  "AMIRA_NO_MULTITHREAD",
  "AMIRA_NO_OVERLAYS",
  "AMIRA_NO_SPACEMOUSE",
  "AMIRA_NO_SPLASH_SCREEN",
  "AMIRA_NUM_RECENTFILES",
  "AMIRA_OUTOFCORE_MANAGEMENT",
  "AMIRA_ROOT",
  "AMIRA_SHOW_GL_ERRORS",
  "AMIRA_SMALLFONT",
  "AMIRA_SPACEMOUSE",
  "AMIRA_STEREO_ON_DEFAULT",
  "AMIRA_TEAMWORK_AVATAR",
  "AMIRA_TECPLOT_USE_TIME_SERIES",
  "AMIRA_TEXMEM",
  "AMIRA_TRANSLATION_FILE",
  "AMIRA_USER_VIDEO_MEM_AMOUNT",
  "AMIRA_VR_CONFIGS_PATH",
  "AMIRA_XSHM",
  "AMIRA_ZIEHM_RECONSTRUCTION",
  "AMIRABU_ROOT",
  "AMIRAMESH_DEBUG",
  "AMIRAMOL_ROOT",
  "AMIRAVR_CALIB_LOG"
 };



#endif // HX_PRODUCT_ENV_VAR_MGR_H

