#ifndef _CGRAPHICFRAME_H_
#define _CGRAPHICFRAME_H_

#include <wx/wx.h>

class CGLPane;

class CGraphicFrame: public wxFrame {
    public:
        CGraphicFrame(wxWindow* pParent,
            wxWindowID id,
            const wxString& strTitle,
            const wxPoint& pos= wxDefaultPosition,
            const wxSize& size= wxDefaultSize,
            long nStyle= wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

        ~CGraphicFrame();

    private:
        enum {
            ID_ZoomIn= wxID_HIGHEST+1,
            ID_ZoomOut
        };
        
        CGLPane* m_pGLPane;
        wxToolBar* m_pToolBar;
        DECLARE_EVENT_TABLE()

    public:
        void OnZoomIn(wxCommandEvent& evt);
        void OnZoomOut(wxCommandEvent& evt);
        bool LoadImage(wxString& strFile);
};

#endif /* _CGRAPHICFRAME_H_ */
