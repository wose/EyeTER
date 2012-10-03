#include <wx/wx.h>

#include "config.h"
#include "EyeTERApp.h"
#include "MainFrame.h"

bool EyeTERApp::OnInit()
{
    m_pMainFrame = new CMainFrame(NULL, wxID_ANY,
        wxT("EyeTER - Eye The Evil Rauhfasertapete"),
        wxDefaultPosition, wxSize(800, 600));
    SetTopWindow(m_pMainFrame);
    m_pMainFrame->Show();

    return true;
}

IMPLEMENT_APP(EyeTERApp)

