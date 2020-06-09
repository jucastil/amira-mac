/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_TOGGLE_BITMAP_BUTTON
#define SO_WX_TOGGLE_BITMAP_BUTTON

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWx
//
//////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
    #pragma interface
#endif

class SoWxBitmapToggleButton : public wxControl
{
public:
  // Default constructor.
	SoWxBitmapToggleButton();
  
  // Constructor, creating and showing a toggle.
	SoWxBitmapToggleButton( wxWindow* parent,
		                      wxWindowID id,
		                      const wxBitmap& bitmap,
		                      const wxPoint& pos = wxDefaultPosition,
		                      const wxSize& size = wxDefaultSize,
		                      long style = 0,
		                      const wxValidator& val = wxDefaultValidator,
		                      const wxString& name = "bitmapToggleButton" );
  
  //Destructor, destroying the toggle.
	~SoWxBitmapToggleButton();
		
  // Creates the toggle for two-step construction.
	bool Create( wxWindow* parent,
		           wxWindowID id,
		           const wxBitmap& bitmap,
		           const wxPoint& pos = wxDefaultPosition,
		           const wxSize& size = wxDefaultSize,
		           long style = 0,
		           const wxValidator& val = wxDefaultValidator,
		           const wxString& name = "bitmapToggleButton" );
		
  // Gets the state of the toggle : TRUE means depressed.	
	bool GetValue() const;

  // Sets the toggle to the given state : TRUE means depressed.
	void SetValue( const bool state );

  // Sets the bitmap for the button
  void SetBitmap( const wxBitmap& bitmap );

  // overrided standard events handled differently for this control
	virtual void OnPaint( wxPaintEvent& event );
	virtual void OnLeftClick( wxMouseEvent& event );
  virtual void OnMouseOver( wxMouseEvent& event );

protected:
  // overrided version for wxControl:DoGetBestSize()
	virtual wxSize DoGetBestSize() const;
	
private:
	bool m_down;		// keeps track of toggle state
  wxBitmap m_bitmap;
  bool m_over;
	
	void Init();		// "standard" Init() function
	bool IsCursorOnButton();

  DECLARE_DYNAMIC_CLASS( SoWxToggleBitmapButton )
	DECLARE_EVENT_TABLE()
};

// the single event tag
#define wxEVT_COMMAND_BITMAP_TOGGLED (wxID_HIGHEST + 2001)

// the event table entry macro
#define EVT_BITMAP_TOGGLE(id,func) \
	EVT_CUSTOM(wxEVT_COMMAND_BITMAP_TOGGLED,id,func)

// constants for event handler functions to test against event.GetInt()
#define wxBITMAP_TOGGLE_IS_UP 0
#define wxBITMAP_TOGGLE_IS_DOWN 1

#endif // SO_WX_TOGGLE_BITMAP_BUTTON

