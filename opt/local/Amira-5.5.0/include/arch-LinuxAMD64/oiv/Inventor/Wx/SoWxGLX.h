/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_GLX
#define SO_WX_GLX

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxGLX
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoGL.h>
#include <Inventor/sys/SoGLX.h>
#include <wx/glcanvas.h>

class SoWxGLWidget;

class INVENTORWX_API SoWxGLX : public wxGLCanvas
{
public:

  SoWxGLX( wxWindow* parent, SoWxGLWidget* evtHandler, int* attribList = NULL );
  virtual ~SoWxGLX();

  // Returns the current pixel format/visual ID.
  int getPixelFormat() const;

  void OnSize( wxSizeEvent& event );
  void OnKey( wxKeyEvent& event );

protected:

  void OnEraseBackground( wxEraseEvent& event );
  void OnPaint( wxPaintEvent& event );
  void OnMouse( wxMouseEvent& event );
  void OnFocus( wxFocusEvent& event );

private:

  int m_pixelFormat;

  SoWxGLWidget* m_evtHandler; // pointer to a SoWxGLWidget to process events

  DECLARE_EVENT_TABLE()

}; 

#endif // SO_WX_GLX
