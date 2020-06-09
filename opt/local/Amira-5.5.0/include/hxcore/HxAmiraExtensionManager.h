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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_AMIRAEXTENSIONMANAGER_H
#define HX_AMIRAEXTENSIONMANAGER_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxAmiraExtensionManagerConstants.h>
#include <mclib/McString.h>

class HxDSO;
class QPixmap;

#if defined WIN32 || defined WIN64
#define HxDeclareExtension(name) \
    extern "C" void __declspec(dllexport) \
    hx_amira_declare_extension(const char** n) { *n=name; }
#else
#define HxDeclareExtension(name) \
    extern "C" void \
    hx_amira_declare_extension(const char** n) { *n=name; }
#endif

#if defined WIN32 || defined WIN64
#define HxDeclareExtensionPackage(name, package) \
    extern "C" void __declspec(dllexport) \
    declare_extension_##package(const char** n) { *n=name; }
#else
#define HxDeclareExtensionPackage(name, package) \
    extern "C" void \
    declare_extension_##package(const char** n) { *n=name; }
#endif

// Error code returned by HxAmiraExtensionManager::isValid() if max number of users is reached.
#define LICENSE_MAXUSERS -14

// Helper class implementing Amira license checking.
class HXCORE_API HxAmiraExtensionManager
{
  public:
    /*  Checks if a license for the given shared object or DLL is available or not.
        In order to indicate that a special license is required for a shared object
        the object may define the functions hx_amira_declare_extension(const char**)
        or declare_extension_#pkg(const char**). Those functions should return the
        name of the extension package the shared object belongs to. This method
        determines the name of the extension package and checks if a license for the
        extension package is available. If this is the case (or if the shared object
        does not provide an extension package name), 1 is returned. Otherwise an
        error code < 0 is returned. */
    static int isValid(HxDSO* dso, const char* pkg);
    
    /*  Checks license and takes num_lic tokens (to verify, set num_lic to 0).
        Returns 1 if license is OK, or error code < 0 if not. */
    static int isValid(const char* ext, int showDialog = 1, int num_lic = 1);

    /*  Checks license and takes num_instances tokens.
        Returns num_instances if license is OK, or error code < 0 if not. */
    static int checkNumberOfInstances(int numInstances = 20);
        
    /*  Returns a string containing all licensed extension packages. The string
        will be displayed in the console window when Amira is started. It will
        also be displayed in the About dialog. */
    static const McString& getProductValidLicenses(bool flexcheck = false);

    /*  Returns splash screen to be displayed. The splash screen depends on the
        current license. Different pairs of licenses and splash screens can be
        configured in the product skin file. The first splash screen with a valid
        license is chosen. No splash screen will be shown if the environment variable
        AMIRA_NO_SPLASH_SCREEN is set or if the program is started with the command
        line option -nosplash. */
    static QPixmap* getSplashScreen();

    /*  Performs initial license check. If no valid product license is found the
        license dialog will be displayed and the program will be terminated.
        It will also choose an edition to activated if the product contains
        edition and if a valid license is found. If several licenses unlock
        several editions, the first unlockable edition found in the list of editions
        will be activated unless @c requestedEdition is specified.
        */
    static void init();

    /*  Returns host ID as displayed in license dialog. The host ID is computed from
        the MAC address of the primary network adapter. Virtual network adapters
        are excluded. */
    static const char* hostID();

    static const McString& getPasswordFile();

    /// Returns true if it is a trial version (i.e. the license key contains SDK-Eval or SDK-Trial)
    static bool isTrialVersion();

    /// Returns true if it is a demo version (i.e. the license key contains SDK-Demo)
    static bool isDemoVersion();

    /** Checks if the Amira license expires with the next 4 weeks and prints a message
        in the Amira console if this is the case. */
    static void checkLicenseExpires();

    static void setActiveEdition(const McString & requestedEdition);
    /**
     *  Returns the activated edition.
     *  Returns an empty string if no edition is activated.
     */
    static inline const McString& getActiveEdition() {return m_activeEdition;}

protected:
    static McString m_activeEdition;

    /**
     *  Performs initial license check. If no valid product license is found the
     *  license dialog will be displayed and the program will be terminated.
     */
    static void checkMainLicense(int currentStatus, const McString& licenseName);
};

#define GREENPACK_NAME "GreenPack"
#define MULTICOMPANALYSISPACK_NAME "MultiCompAnalysisPack"
#define SCALEPACK_NAME "ScaleViz"

// Avizo editions
#define EARTH_EDITION_NAME "EarthEdition"
#define FIRE_EDITION_NAME "FireEdition"
#define WIND_EDITION_NAME "WindEdition"
#define GREEN_EDITION_NAME "GreenEdition"
#define CLUE_EDITION_NAME "ClueEdition"

#endif

/// @}
