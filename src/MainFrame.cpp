#include "config.h"
#include "MainFrame.h"
#include "GraphicFrame.h"

#include <wx/stc/stc.h>
#include <wx/log.h>
#include <wx/aboutdlg.h>

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(ID_FileNew,        CMainFrame::OnNew)
    EVT_MENU(ID_FileOpen,       CMainFrame::OnOpen)
    EVT_MENU(ID_FileOpenImage,  CMainFrame::OnOpenImage)
    EVT_MENU(wxID_EXIT,         CMainFrame::OnExit)
    EVT_MENU(ID_ViewLog,        CMainFrame::OnViewLog)
    EVT_MENU(ID_ViewGraphic,    CMainFrame::OnViewGraphic)
    EVT_MENU(wxID_ABOUT,        CMainFrame::OnAbout)
END_EVENT_TABLE()

CMainFrame::CMainFrame(wxWindow* pParent, wxWindowID id,
    const wxString& strTitle, const wxPoint& pos, const wxSize& Size,
    long nStyle)
    : wxFrame(pParent, id, strTitle, pos, Size, nStyle)
{
    m_AuiManager.SetManagedWindow(this);
    
    InitMenu();
    InitNotebook();

    CreateStatusBar();
    GetStatusBar()->SetStatusText(_("Ready"));

    SetMinSize(wxSize(400,300));

    m_pGraphicFrame= new CGraphicFrame(pParent, wxID_ANY, _("Graphic View"));
    GetMenuBar()->Check(ID_ViewGraphic, m_pGraphicFrame->IsShown());
    GetMenuBar()->Check(ID_ViewLog, m_AuiManager.GetPane(m_pBNotebook).IsShown());
    
    m_AuiManager.Update();
}

CMainFrame::~CMainFrame() {
    m_AuiManager.UnInit();
}

void CMainFrame::InitMenu() {
    wxMenuBar* pMenuBar = new wxMenuBar;

    wxMenu* pFileMenu = new wxMenu;
    pFileMenu->Append(ID_FileNew, _("New"));
    pFileMenu->Append(ID_FileOpen, _("Open"));
    pFileMenu->Append(ID_FileOpenImage, _("Open Image"));
    pFileMenu->AppendSeparator();
    pFileMenu->Append(wxID_EXIT, _("Exit"));

    wxMenu* pViewMenu = new wxMenu;
    pViewMenu->AppendCheckItem(ID_ViewLog, _("Show Log"));
    pViewMenu->AppendSeparator();
    pViewMenu->AppendCheckItem(ID_ViewGraphic, _("Graphic Window"));
    pViewMenu->Append(ID_ViewHistogram, _("Histogram"));

    wxMenu* pHelpMenu = new wxMenu;
    pHelpMenu->Append(wxID_ABOUT, _("About..."));

    pMenuBar->Append(pFileMenu, _("File"));
    pMenuBar->Append(pViewMenu, _("View"));
    pMenuBar->Append(pHelpMenu, _("Help"));

    SetMenuBar(pMenuBar);
}

void CMainFrame::InitNotebook() {
    m_pCNotebook= new wxAuiNotebook(this, wxID_ANY);
    m_pCNotebook->SetArtProvider(new wxAuiSimpleTabArt);

    m_pBNotebook= new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
        wxDefaultSize);
    m_pBNotebook->SetArtProvider(new wxAuiSimpleTabArt);
    m_pLog= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
        wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    wxLog* pLogger= new wxLogTextCtrl(m_pLog);
    wxLog::SetActiveTarget(pLogger);

    m_pBNotebook->AddPage(m_pLog, _("Log"), true);

    m_AuiManager.AddPane(m_pCNotebook, wxCENTER);
    m_AuiManager.AddPane(m_pBNotebook, wxBOTTOM, _("Misc"));
    m_AuiManager.GetPane(m_pBNotebook).BestSize(100, 200);
    m_AuiManager.Update();
    wxLogDebug(_("InitNotebook() complete"));
}

wxStyledTextCtrl* CMainFrame::CreateEditor() {
    wxStyledTextCtrl* pEditor= new wxStyledTextCtrl(this, wxID_ANY);

    pEditor->SetMarginWidth(0, 50);
    pEditor->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
    pEditor->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
    pEditor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
        
    pEditor->SetWrapMode (wxSTC_WRAP_WORD);
                
    pEditor->StyleClearAll();
    pEditor->SetLexer(wxSTC_LEX_PERL);

    return pEditor;
}

wxAuiDockArt* CMainFrame::GetDockArt() {
    return m_AuiManager.GetArtProvider();
}

void CMainFrame::DoUpdate() {
    m_AuiManager.Update();
}

void CMainFrame::OnExit(wxCommandEvent& evt) {
    m_pGraphicFrame && m_pGraphicFrame->Close(true);
    Close(true);
}

void CMainFrame::OnAbout(wxCommandEvent& evt) {
    wxAboutDialogInfo info;

    info.SetName(_("EyeTER"));
    info.SetVersion(_(GIT_VERSION));
    info.SetDescription(_("OpenCV Prototyping Environment"));
    info.SetCopyright(_T("(C) 2012 Sebastian Woetzel <wose (at) zuendmasse.de>"));
    info.SetWebSite(_("http://github.com/wose/EyeTER"), _("Fork me on github!"));

    wxAboutBox(info);
}

void CMainFrame::OnNew(wxCommandEvent& evt) {
    m_pCNotebook->AddPage(CreateEditor(), _("Unknown"), true);
    wxLogDebug(_("New notebook page added"));
}

void CMainFrame::OnOpen(wxCommandEvent& evt) {
    evt.Skip();
}

void CMainFrame::OnOpenImage(wxCommandEvent& evt) {
    wxFileDialog OpenImageDlg(this, _("Open Image File"), _(""), _(""),
        _("BMP files (*.bmp)|*.bmp|PNG files (*.png)|*.png|GIF files (*.gif)|*.gif|All files (*.*)|*.*"),
        wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(OpenImageDlg.ShowModal() == wxID_CANCEL)
        return;
    wxString strImagePath= OpenImageDlg.GetPath();
    wxLogDebug(strImagePath);
    if(!m_pGraphicFrame->LoadImage(strImagePath))
        wxLogMessage(_("Failed to load image"));
}

void CMainFrame::OnViewLog(wxCommandEvent& evt) {
    if(m_AuiManager.GetPane(m_pBNotebook).IsShown())
        m_AuiManager.GetPane(m_pBNotebook).Hide();
    else
        m_AuiManager.GetPane(m_pBNotebook).Show();
    GetMenuBar()->Check(ID_ViewLog, m_AuiManager.GetPane(m_pBNotebook).IsShown());
    m_AuiManager.Update();
}

void CMainFrame::OnViewGraphic(wxCommandEvent& evt) {
    if(m_pGraphicFrame->IsShown())
        m_pGraphicFrame->Hide();
    else
        m_pGraphicFrame->Show();
    GetMenuBar()->Check(ID_ViewGraphic, m_pGraphicFrame->IsShown());
}
