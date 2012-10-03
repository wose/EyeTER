#ifndef _CGLPANE_H_
#define _CGLPANE_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>

class CGLPane: public wxGLCanvas
{
    public:
        CGLPane(wxWindow* pParent,
            wxWindowID id,
            int* pAttribList = 0,
            const wxPoint& pos= wxDefaultPosition,
            const wxSize& size= wxDefaultSize,
            long nStyle= wxFULL_REPAINT_ON_RESIZE,
            const wxString& strName = _("GLPane"),
            const wxPalette& palette = wxNullPalette);
        virtual ~CGLPane();

    private:
        wxGLContext* m_pContext;

    public:
        void Prepare2DViewport();

        void OnRender(wxPaintEvent& evt);
        void OnResized(wxSizeEvent& evt);

        DECLARE_EVENT_TABLE()
};

#endif /* _CGLPANE_H_ */
