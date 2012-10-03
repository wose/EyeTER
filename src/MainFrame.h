#ifndef _CMAINFRAME_H_
#define _CMAINFRAME_H_

#include <wx/wx.h>
#include <wx/aui/aui.h>

class wxStyledTextCtrl;
class CGraphicFrame;

class CMainFrame: public wxFrame {
    public:
        CMainFrame(wxWindow* pParent,
            wxWindowID id,
            const wxString& strTitle,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& Size = wxDefaultSize,
            long nStyle = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

        ~CMainFrame();

    private:
        enum {
            ID_FileNew = wxID_HIGHEST+1,
            ID_FileOpen,
            ID_FileOpenImage,
            ID_FileExit,

            ID_ViewLog,
            ID_ViewGraphic,
            ID_ViewHistogram
        };

        wxAuiManager    m_AuiManager;
        wxAuiNotebook*  m_pCNotebook;
        wxAuiNotebook*  m_pBNotebook;
        wxTextCtrl*     m_pLog;

        CGraphicFrame*  m_pGraphicFrame;

        DECLARE_EVENT_TABLE()

    public:
        wxAuiDockArt* GetDockArt();
        void DoUpdate();

    private:
        void InitMenu();
        void InitNotebook();
        wxStyledTextCtrl* CreateEditor();

        void OnNew(wxCommandEvent& evt);
        void OnOpen(wxCommandEvent& evt);
        void OnOpenImage(wxCommandEvent& evt);
        void OnExit(wxCommandEvent& evt);

        void OnViewLog(wxCommandEvent& evt);
        void OnViewGraphic(wxCommandEvent& evt);

        void OnAbout(wxCommandEvent& evt);
};

#endif /* _CMAINFRAME_H_ */
