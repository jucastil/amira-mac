/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_TO_PDF_ACTION_H
#define SO_TO_PDF_ACTION_H

#include <HardCopy/SoToU3DAction.h>

#include <Inventor/SbColor.h>
#include <Inventor/actions/SoSubAction.h>
#include <HardCopy/SoHardCopy.h>

class SoToPDFActionPrivate;

/**
 * @HCEXT Class for exporting a scene graph to a PDF file.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 * This class can export an Open Inventor scenegraph into a simple PDF file.
 * In addition to 3D scene encapsulation, the exporter can insert a title to the document
 * and an unique block of text. Moreover, PDF encryption can lock access to the file contents.
 * To import a 3D model inside a more complex PDF file, prefer SoToU3DAction.
 * U3D files can be used to import 3D models inside PDF files by advanced PDF editors.
 * 
 * @B Limitations @b
 *  - inherits limitations of SoToU3DAction.
 * 
 * @B Use case @b
 *  \code
 *  SoHardCopy::init();
 *  ...
 *  // setup the root scene graph to export
 *  SoSeparator* root = new SoSeparator;
 *  ...
 *  SoToPDFAction pdfAction;
 *  bool result = pdfAction.openFile( "output.pdf" );
 *  if ( !result ) 
 *  {
 *    // error management
 *  }
 *  pdfAction.setTitle( "Scene Name" );
 *  pdfAction.setText( "Some text describing the exported scene." );
 *  pdfAction.apply( root );
 *  result = pdfAction.closeFile();
 *  if ( !result )
 *  {
 *  // error management
 *  }
 * \endcode
 *
 * @B Warning @b 
 *  - On some platforms, some third parties may encounter problems to load 
 *    displaying an error message like: "IFXOSFileIterator::ProcessDir: 
 *    error opening /usr/local/u3d/lib/Plugins/ No such file or directory".
 *    In such case, declare the environment variable U3D_LIBDIR (UNIX only) and set it with 
 *    the path to the Open Inventor libraries ($OIVHOME/lib).
 *  - It is necessary to create a directory named Plugins containing the files IFXExporting.so/dll
 *    and IFXScheduling.so/dll in the directory where IFXCore.so/dll is.
 *  - Limitations are common to SoToU3DAction.
 *
 * @SEE_ALSO 
 *    SoToU3DAction.
 *
 */

class HARDCOPY_API SoToPDFAction : public SoToU3DAction
{
  SO_ACTION_HEADER(SoToPDFAction);

public:

  /*
   * Constructor
   */
  SoToPDFAction();

  /*
   * Destructor
   */
  virtual ~SoToPDFAction();

  /**
   * Set the PDF output file. Returns false if an error has occured. 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE bool openFile(const char* filename);

  /**
   * Set the PDF output file. Returns false if an error has occured. 
   */
  bool openFile( const SbString& filename );

  /**
   * finalize export to the U3D output file. Returns false if an error has occured. 
   */
  bool closeFile();

  /**
   * [Optional] 
   * Set passwords to lock write & read access to the PDF file contents.
   * Passwords are optional.
   * A write password is required before setting a read password.
   * Write and read passwords must be different.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setPassword(const char* writePass, const char* readPass = NULL);

  /**
   * [Optional] 
   * Set passwords to lock write & read access to the PDF file contents.
   * Passwords are optional.
   * A write password is required before setting a read password.
   * Write and read passwords must be different.
   */
  void setPassword( const SbString& writePass, const SbString& readPass = "" );

  /**
   * [Optional] 
   * Set a title into the output PDF file.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setTitle(const char* title);

  /**
   * [Optional] 
   * Set a title into the output PDF file.
   */
  void setTitle(const SbString& title);

  /**
   * [Optional] 
   * Add a text block into the output PDF file.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setText(const char* text);

  /**
   * [Optional] 
   * Add a text block into the output PDF file.
   */
  void setText(const SbString& text);

  /**
   * [Optional] 
   * Changes the page orientation from portrait to landscape.
   */
  void setLandscape( const SbBool enable );

SoINTERNAL public:
  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

  static bool writeFile(
    const SbString& pdfOutput, 
    const SbString& writePass, 
    const SbString& readPass, 
    const SbString& title, 
    const SbString& text, 
    const SbString& u3dInput,
    const SbString& u3dView,
    bool hasPerspective,
    float fov,
    float focalDistance,
    bool hasLights,
    const SbColor& background,
    bool landscape = false);

private:

  SoToPDFActionPrivate* m_private;
};

#endif // SO_TO_PDF_ACTION_H
