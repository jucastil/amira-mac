#if !defined HX_SKIN_H
#define HX_SKIN_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxAmiraExtensionManagerConstants.h>

#include <mclib/McString.h>
#include <mclib/McFilename.h>

#include <tcl.h>

#include <list>
#include <map>

/**
 * This class implements the skin mechanism used by the Amira rebranding.
 * Each product must have a skin file stored into the resources under a
 * specific directory (share/resources/PRODUCTNAME/PRODUCTNAMESkin.rc).
 * The main routine of the product sets the skin file to use and this last
 * will be evaluated at the beginning of the HxMain::main method.
 * The skin file is a list of Tcl commands used to set some information
 * specific to a product (product name, version, icons, captions, splashes,
 * licenses...):
 *
 *    Icons: theAppSkin setIcon <GuiComponent> <IconFilename>
 *
 *    Captions: theAppSkin setCaption <GuiComponent> <LicenseName> <Caption>
 *
 *    Splashes: theAppSkin setSplash <LicenseName> <SplashFilename>
 *
 *    Company Name (as used e.g. in the Registry): theAppSkin setCompanyName <CompanyName>
 *
 *    Company URL (as used e.g. in the About dialog): theAppSkin setCompanyURL <CompanyURL>
 *
 *    Online support link: theAppSkin setOnlineSupportURL <OnlineSupportURL>
 *
 *    Contact address: theAppSkin setContactAddress <ContactAddress>
 *
 *    Init file: theAppSkin setInitFile <InitFilename>
 *
 *    EULA file: theAppSkin setEULAFile <EULAFilename>
 *
 *    Index file: theAppSkin setPathToIndexFile <PathToIndexFile>
 *
 *    Password request URL (for license dialog): theAppSkin setPasswordRequestURL <PasswordRequestAddress>
 *
 *    License dialog contact (for license dialog): theAppSkin addPasswordContact <ContactName> <Email|Phone|Fax> <Info>
 *
 *    Qt style sheet file: theAppSkin setStyleSheet <LicenseName> <StyleSheetFileName>

 * If the skin file is missing or corrupted (missing product name, version,
 * patch version and EULA file), the application will quit.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
 */

class HXCORE_API HxSkin
{

public:

  /**
   * To store a caption information.
   */
  struct CaptionInfo
  {
    McString licenseName;     // The associated license name.
    McString caption;         // The caption to be displayed.
  };

  /**
   * To store a splash information.
   */
  struct SplashInfo
  {
    McString licenseName;     // The associated license name.
    McString splashFilename;  // The associated .png file.
  };

  /**
   * To store a package information.
   */
  struct PackageInfo
  {
    McString licenseName;     // The associated license name.
    McString packageDocName;  // The name displayed in the doc.
    int packageDocIndex;      // Used to sort the packages in the doc.
  };

  /**
   * To associate a package information with an extension name.
   */
  typedef std::map< McString, PackageInfo > PackageInfoList;

  /**
   * To associate an edition with a license.
   * It will help to retrieve the active edition name.
   */
  typedef std::map< McString, McString > EditionAndLicenseList;

  /**
   * For license dialog.
   * To store a contact information.
   */
  struct LicenseDialogContactInfo
  {
    McString contactInfo;       // Could be Email|Phone|Fax
    McString contactInfoValue;  // The value to display.
  };

  /**
   * To associate license information with contact information.
   */
    typedef std::list< std::pair< McString, McDArray<LicenseDialogContactInfo> > > LicenseDialogContactInfoList;

  /**
   * To store a style sheet information.
   */
  struct StyleSheetInfo
  {
    McString licenseName;       // The associated license name.
    McString styleSheetFile;    // The associated style sheet filename.
  };

  /**
   * Returns pointer to global instance.
   */
  static HxSkin* getGlobalInstance();

  /**
   * Returns pointer to global instance.
   */
  static HxSkin* getGlobalInstance(const McString& productName);

  /**
   * To set the skin file (called by the different products main routines).
   */
  static void setSkinFile(const McString& execName, const McFilename& skinFilename);

  /**
   * Interface to Tcl scripting language.
   */
  static int staticParse(ClientData data, Tcl_Interp* t, int argc, char** argv);

  /**
   * To get the product name.
   */
  const McString & getProductName() const;

  /**
   * To get the product/extension line version.
   */
  const McString & getProductVersion() const;

  /**
   * To get the license name.
   */
  const McString & getLicenseName() const;

  /**
   * To get the license version.
   */
  const McString & getLicenseVersion() const;

  /**
   * To get the product/extension line version num (for example 51).
   * It's useful to define pre-processor compilation directive for customer's modules.
   */
  int getProductVersionNum() const;

  /**
   * To get the product/extension line version num including patch number (for example 511).
   * It's useful to define pre-processor compilation directive for customer's modules.
   */
  int getProductWithPatchVersionNum() const;

  /**
   * To get the product/extension line patch version.
   */
  const McString & getProductPatchVersion() const;

  /**
   * To get the product/extension line patch version num.
   * It's useful to define pre-processor compilation directive for customer's modules.
   */
  int getProductPatchVersionNum() const;

  /**
   * To get the icon of a GUI component.
   */
  McString getIcon(const McString& guiComponentName) const;

  /**
   * To get the caption of a GUI component.
   */
  McString getCaption(const McString& guiComponentName) const;

  /**
   * To get the splashes list.
   */
  const McDArray< SplashInfo >& getSplashes() const;


  /**
   * To get the association between edition (if any registered)
   * and license.
   */
  const EditionAndLicenseList& getEditionsList() const;

  /**
   * To get the license attached to an edition.
   */
  McString getLicenseFromEdition(const McString& edition) const;



  /**
   * To get the registry path.
   */
  const McString & getRegistryPath() const;

  /**
   * To get the company name.
   */
  const McString & getCompanyName() const;

  /**
   * To get the company URL.
   */
  const McString & getCompanyURL() const;

  /**
   * To get the online support URL.
   */
  const McString & getOnlineSupportURL() const;

  /**
   * To get the logging URL.
   */
  const McString & getLoggingURL() const;

  /**
   * To get the contact address.
   */
  const McString & getContactAddress() const;

  /**
   * To get the init file.
   */
  const McString & getProductInitFile() const;

  /**
   * To get the EULA file.
   */
  const McString & getProductEULAFile() const;

  /**
   * To get the product script file format name.
   */
  const McString & getProductScriptFileFormatName() const;

  /**
   * To get the product script file format header.
   */
  const McString & getProductScriptFileFormatHeader() const;

  /**
   * To get the path of an help file according to the current product.
   */
  McFilename getPathToHelpFile(const McString& package, const McString& helpFilename) const;

  /**
   * To get the path to the product index file.
   */
  const McFilename & getPathToProductIndexFile() const;

  /**
   * To get the path to an documentation image override directory relative to a
   * package's doc directory.
   */
  const McFilename & getDocImageSubDir() const;

  /**
   * To get the base name of application executable file.
   */
  const McString & getAppFileBaseName() const;

  const McString & getWebNewsURL() const { return m_webNewsURL; }

  /**
   * For license dialog.
   * To get the password request URL.
   */
  const McString& getPasswordRequestURL() const;

  /**
   * For license dialog.
   * To get the contacts info list.
   */
  const LicenseDialogContactInfoList& getContactsInfoList() const;

  /**
   * To get the product style sheet.
   */
  McString getProductStyleSheet() const;

  McString getMaterialDatabaseFile() const;

  /**
   * Return the path to the directory containing the help files.
   */
  const char* getHelpDir() const {
    return m_HelpDir;
  }

  /**
   * Return runtime configurable option.  The default is 0.
   */
  int getOption( const char* name ) const;
private:

  /**
   * Constructor.
   */
  HxSkin(const McString& productName);

  /**
   * Destructor.
   */
  virtual ~HxSkin();

  /**
   * Called when an error occurs...
   */
  static void skinError(const McString& errorMsg);

  /**
   * Called when to notify a warning...
   */
  static void skinWarning(const McString& warningMsg);

  /**
   * The skin filename.
   */
  static McFilename s_skinFilename;

  /**
   * To get a version num from a version string.
   */
  static int getVersionNum(const McString& version);

  /**
   * To check the skin validity.
   * Some information must be present in the skin file,
   */
  void checkSkinValidity();

  /**
   * To fix the path to the product index file.
   */
  void fixPathToProductIndexFile(const McFilename& path);

  /**
   * To register the product script file format.
   */
  void registerProductScriptFileFormat();

  /**
   * To add an icon to the list.
   */
  void addGUIIcon(const McString& guiComponent, const McString& iconFilename);

  /**
   * To add a caption to the list.
   */
  void addGUICaption(const McString& guiComponent, const McString& licenseName, const McString& caption);

  /**
   * To add a splash to the list.
   */
  void addSplash(const McString& licenseName, const McString& splashFilename);


  /**
   * For license dialog.
   * Add a contact information.
   */
  void addPasswordContact(const McString& contactName, const McString& contactInfo, const McString& contactInfoValue);

  /**
   * To add a style sheet file.
   */
  void addStyleSheetFile(const McString& licenseName, const McString& styleSheetFile);

  /**
   * To add a material database file.
   */
  void addMaterialDatabaseFile(const McString& licenseName, const McString& databaseFile);

  /**
   * Set runtime option.
   */
  void setOption(const char* name, const int value);

  /**
   * Instance.
   */
  static HxSkin* s_theInstance;

  /**
   * To know if the skin is in read only mode.
   */
  bool m_isReadOnly;

  /**
   * The product name.
   */
  McString m_productName;

  /**
   * The product version.
   */
  McString m_productVersion;

  /**
   * The license name.
   */
  McString m_licenseName;

  /**
   * The license version.
   */
  McString m_licenseVersion;

  /**
   * The product patch version.
   */
  McString m_productPatchVersion;

  /**
   * The icons table.
   */
  std::map< McString, McString > m_guiIcons;

  /**
   * The captions table.
   */
  std::map< McString, McDArray< CaptionInfo > > m_guiCaptions;

  /**
   * The splashes table.
   */
  McDArray< SplashInfo > m_splashes;


  /**
   * The editions tables.
   */
  EditionAndLicenseList m_editions;

  /**
   * The company name.
   */
  McString m_companyName;

  /**
   * The company URL.
   */
  McString m_companyURL;

  /**
   * The online support URL.
   */
  McString m_onlineSupportURL;

  /**
   * The logging URL.
   */
  McString m_loggingURL;

  /**
   * The contact address.
   */
  McString m_contactAddress;

  /**
   * The init file.
   */
  McString m_initFile;

  /**
   * The EULA file.
   */
  McString m_eulaFile;

  /**
   * The product script file format name.
   */
  McString m_productScriptFileFormatName;

  /**
   * The product script file format header.
   */
  McString m_productScriptFileFormatHeader;

  /**
   * The path to the product index file.
   * For Amira: /src/amiraKernel/usersguide/doc/index.doc
   * For Avizo: /src/Avizo/usersguide/doc/index.doc
   */
  McFilename m_pathToProductIndexFile;

  /**
   * A subdirectory where images are searched first.
   */
  McFilename m_docImageSubDir;

  /**
   * The base name of application executable file.
   */
  McString m_appFileBaseName;

  McString m_webNewsURL;

  /**
   * For license dialog.
   * The password request URL.
   */
  McString m_passwordRequestURL;

  /**
   * For license dialog.
   * The list of all contacts.
   */
  LicenseDialogContactInfoList m_licenseDialogContacts;

  /**
   * The product style sheet list.
   */
  McDArray< StyleSheetInfo > m_productStyleSheetList;

  /**
   * The product material database file list.
   */
  std::map< McString, McString > m_materialDatabaseFileList;

 /**
  * The path to html documentation.
  */
  McString m_HelpDir;

  /**
   * The options table.
   */
  std::map< McString, int > m_options;
};

//------------------------------------------------------------------------------
#define theAppSkin HxSkin::getGlobalInstance()
#define theAppSkinInit(x) HxSkin::getGlobalInstance(x)

// ------------------------------ INLINE methods. ------------------------------

inline const McString &
HxSkin::getProductName() const
{
  return m_productName;
}

inline const McString &
HxSkin::getProductVersion() const
{
  return m_productVersion;
}

inline const McString &
HxSkin::getLicenseName() const
{
  return m_licenseName;
}

inline const McString &
HxSkin::getLicenseVersion() const
{
  return m_licenseVersion;
}

inline const McString &
HxSkin::getProductPatchVersion() const
{
  return m_productPatchVersion;
}

inline const McDArray< HxSkin::SplashInfo >&
HxSkin::getSplashes() const
{
  return m_splashes;
}

inline const HxSkin::EditionAndLicenseList&
HxSkin::getEditionsList() const
{
  return m_editions;
}



inline const McString &
HxSkin::getCompanyName() const
{
  return m_companyName;
}

inline const McString &
HxSkin::getCompanyURL() const
{
  return m_companyURL;
}

inline const McString &
HxSkin::getOnlineSupportURL() const
{
  return m_onlineSupportURL;
}

inline const McString &
HxSkin::getLoggingURL() const
{
  return m_loggingURL;
}

inline const McString &
HxSkin::getContactAddress() const
{
  return m_contactAddress;
}

inline const McString &
HxSkin::getProductInitFile() const
{
  return m_initFile;
}

inline const McString &
HxSkin::getProductEULAFile() const
{
  return m_eulaFile;
}

inline const McString &
HxSkin::getProductScriptFileFormatName() const
{
  return m_productScriptFileFormatName;
}

inline const McString &
HxSkin::getProductScriptFileFormatHeader() const
{
  return m_productScriptFileFormatHeader;
}

inline const McFilename &
HxSkin::getPathToProductIndexFile() const
{
  return m_pathToProductIndexFile;
}

inline const McFilename &
HxSkin::getDocImageSubDir() const
{
    return m_docImageSubDir;
}

inline const McString &
HxSkin::getAppFileBaseName() const
{
  return m_appFileBaseName;
}

inline const McString &
HxSkin::getPasswordRequestURL() const
{
  return m_passwordRequestURL;
}

inline const HxSkin::LicenseDialogContactInfoList&
HxSkin::getContactsInfoList() const
{
  return m_licenseDialogContacts;
}

#endif // HX_SKIN_H
