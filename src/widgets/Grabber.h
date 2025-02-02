/**********************************************************************

  Audacity: A Digital Audio Editor

  Grabber.cpp

  Leland Lucius

*******************************************************************//**

\file Grabber.cpp

  Implements Grabber

*//*******************************************************************//**

\class Grabber
\brief The widget to the left of a ToolBar that allows it to be dragged
around to NEW positions.

*//*******************************************************************//**

\class AStaticBitmap
\brief A widget for bitmaps which ignores the erase event for 
flicker-free use.

*//**********************************************************************/

#ifndef __AUDACITY_WIDGETS_GRABBER__
#define __AUDACITY_WIDGETS_GRABBER__



#include <wx/defs.h>
#include <wx/statbmp.h> // to inherit

class TranslatableString;

////////////////////////////////////////////////////////////
/// Grabber Class
////////////////////////////////////////////////////////////

// Custom events

DECLARE_EXPORTED_EVENT_TYPE(SAUCEDACITY_DLL_API, EVT_GRABBER_CLICKED, -1)

class GrabberEvent final : public wxCommandEvent
{
 public:

   GrabberEvent(wxEventType type = wxEVT_NULL,
                wxWindowID winid = 0,
                const wxPoint& pt = wxDefaultPosition,
                bool escaping = false)
   : wxCommandEvent(type, winid)
   {
      mPos = pt;
      mEscaping = escaping;
   }

   GrabberEvent(const GrabberEvent & event) = default;

   // Position of event (in screen coordinates)
   const wxPoint & GetPosition() const
   {
      return mPos;
   }

   void SetPosition(const wxPoint & pos)
   {
      mPos = pos;
   }

   bool IsEscaping() const { return mEscaping; }

   // Clone is required by wxwidgets; implemented via copy constructor
   wxEvent *Clone() const override
   {
      return safenew GrabberEvent(*this);
   }

 protected:

   wxPoint mPos;
   bool mEscaping {};
};

typedef void (wxEvtHandler::*GrabberEventFunction)(GrabberEvent &);

#define GrabberEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(GrabberEventFunction, &func)

#define EVT_GRABBER(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(EVT_GRABBER_CLICKED, id, wxID_ANY, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) \
    wxStaticCastEvent(GrabberEventFunction, & fn), (wxObject *) NULL),

// Specifies how wide the grabber will be

#define grabberWidth 10

class SAUCEDACITY_DLL_API Grabber final : public wxWindow
{

 public:

   Grabber(wxWindow *parent, wxWindowID id);
   virtual ~Grabber();

   // We don't need or want to accept focus since there's really
   // not a need to dock/float a toolbar from the keyboard.  If this
   // changes, remove this and add the necessary keyboard movement
   // handling.
   // Note that AcceptsFocusFromKeyboard() rather than AcceptsFocus()
   // is overridden so that ESC can cancel toolbar drag.
   bool AcceptsFocusFromKeyboard() const override {return false;}

   void PushButton(bool state);
   void SetAsSpacer( bool bIsSpacer );

   // overload and hide the inherited function that takes naked wxString:
   void SetToolTip(const TranslatableString &toolTip);

 protected:

   void OnLeftDown(wxMouseEvent & event);
   void OnLeftUp(wxMouseEvent & event);
   void OnEnter(wxMouseEvent & event);
   void OnLeave(wxMouseEvent & event);
   void OnErase(wxEraseEvent & event);
   void OnPaint(wxPaintEvent & event);
   void OnKeyDown(wxKeyEvent & event);

 private:

   void DrawGrabber(wxDC & dc);
   void SendEvent(wxEventType type, const wxPoint & pos, bool escaping);

   bool mOver;
   bool mPressed;
   bool mAsSpacer;

 public:

   DECLARE_EVENT_TABLE()
};

// Piggy back in same source file as Grabber.
// Audacity Flicker-free StaticBitmap.
class SAUCEDACITY_DLL_API AStaticBitmap : public wxStaticBitmap {
  public:
    AStaticBitmap(wxWindow *parent,
                   wxWindowID id,
                   const wxBitmap& label,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxStaticBitmapNameStr) :

    wxStaticBitmap(parent,
                   id,
                   label,
                   pos ,
                   size ,
                   style,
                   name )
    {};
    void OnErase(wxEraseEvent& event) {
       static_cast<void>(event);
    };
    DECLARE_EVENT_TABLE()
};



#endif
