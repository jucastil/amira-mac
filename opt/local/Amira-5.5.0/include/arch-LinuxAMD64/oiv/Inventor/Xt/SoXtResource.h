/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef _WIN32
#  include <Inventor/Win/SoWinResource.h>
#else // _WIN32

#ifndef _SO_XTRESOURCE_
#define _SO_XTRESOURCE_

#include <X11/Intrinsic.h>
#include <X11/Xresource.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/Xt/SoXtDef.h>

/**
 * Used to retrieve X resources for SoXt components and widgets .
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   This class provides an easy-to-use interface for retrieving X resource values
 *   for widgets and components. Rather than use standard Xt calls to traverse up a
 *   widget hierarchy, this class performs its own traversal so that it may provide
 *   special care for widgets which are Open Inventor components. For instance, the
 *   Open Inventor Material Editor top level widget is a Motif form widget. Its class
 *   name is thus @B XmForm @b. SoXtResource knows that the editor is an Open
 *   Inventor component, though, so it uses the class name provided by the editor (in
 *   this case "SoXtMaterialEditor") when looking up resource values.
 *
 *   EXAMPLE:
 *
 *   <PRE>
 *    SoXtResource xr( materialEditor->getWidget() );
 *    xr.getResource("tile1Color", "Tile1Color", color);
 *    xr.getResource("updateFrequency", "UpdateFrequency", freq);
 *   </PRE>
 *
 *
 * @NOTES
 *   Components will typically look up their own resources during buildWidget(). In
 *   order for a component to have its Open Inventor class name recognized by
 *   SoXtResource, it must call SoXtComponent::registerWidget() in its
 *   @B buildWidget @b() method. (This is done in every Open Inventor component.)
 *
 * @SEE_ALSO
 *    X Resources (Xrm),
 *    X Intrinsics (Xt),
 *    SoXt,
 *    SoXtComponent
 *
 *
 */

class INVENTORXT_API SoXtResource {
 public:
  /**
   * Constructor. The constructor takes the widget for which it will
   * retrieve resource values.
   */
  SoXtResource(SoWidget w);
  /**
   * Destructor.
   */
  ~SoXtResource();

  //
  // These methods look up X resource values by calling XrmQGetResource.
  // They return TRUE if successfully located the resource.
  //
  // NOTE: you do not have to specify the complete widget hierarchy.
  // This is automatically performed by this class. Simply name the
  // specific resource that should be searched for. The most efficient
  // use of this class is to construct an instance for a widget, then
  // call getResource repeatedly with different resource strings which
  // are valid for the widget.
  //
  // For example:
  //    SoXtResource xr(colorEditor->getWidget());
  //    xr.getResource("wysiwyg", "Wysiwyg", onOrOff);
  //    xr.getResource("colorSliders", "ColorSliders", rgbOrHsv);
  //    xr.getResource("updateFrequency", "UpdateFrequency", freq);

  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, SbColor &c);
  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, short &i);
  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, unsigned short &u);
  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, char *&s);
  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, SbBool &b);
  /**
   * Returns the X resource value for the specified resource name and class.
   * There is no need to specify the widget hierarchy; this is automatically computed
   * in the constructor.
   */
  SbBool      getResource(char *resName, char *resClass, float &f);

 private:
  XrmQuarkList    nameList;
  XrmQuarkList    classList;
  int             listSize;
  Display         *display;

  // These methods look up X resource values by calling XrmGetResource.
  // e.g. getResource("*backgroundColor", "*BackgroundColor", c);
  // They return TRUE if successfully located the resource.

  static SbBool getResource(Display *, char *sName, char *sClass, SbColor &c);
  static SbBool getResource(Display *, char *sName, char *sClass, short &i);
  static SbBool getResource(Display *, char *sName, char *sClass, unsigned short &u);
  static SbBool getResource(Display *, char *sName, char *sClass, char *&s);
  static SbBool getResource(Display *, char *sName, char *sClass, SbBool &b);
  static SbBool getResource(Display *, char *sName, char *sClass, float &f);


  // These methods look up X resource values by calling XrmQGetResource.
  // That is, they use XrmQuarks instead of strings. (A quark is an Xrm
  // notion - it is simply a key into a hash table of strings.)
  // They are used by SoXtResource for SoComponents.
  // They return TRUE if successfully located the resource.

  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, SbColor &c);
  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, short &i);
  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, unsigned short &u);
  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, char *&s);
  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, SbBool &b);
  static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, float &f);

};

#endif /* _SO_XTRESOURCE_ */

#endif // _WIN32


