#include "GraphicFrame.h"
#include "GLPane.h"

#include <wx/artprov.h>

#include <cv.h>
#include <highgui.h>

BEGIN_EVENT_TABLE(CGraphicFrame, wxFrame)
    EVT_MENU(ID_ZoomIn,  CGraphicFrame::OnZoomIn)
    EVT_MENU(ID_ZoomOut, CGraphicFrame::OnZoomOut)
END_EVENT_TABLE()

using namespace std;
using namespace cv;

CGraphicFrame::CGraphicFrame(wxWindow* pParent, wxWindowID id,
    const wxString& strTitle, const wxPoint& pos, const wxSize& Size,
    long  nStyle)
    : wxFrame(pParent, id, strTitle, pos, Size, nStyle)
{
    wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);

    int pAttrList[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

    m_pGLPane= new CGLPane(this, wxID_ANY, pAttrList);
    pSizer->Add(m_pGLPane, 1, wxEXPAND);
	
    SetSizer(pSizer);
    SetAutoLayout(true);

    m_pToolBar= CreateToolBar();
    m_pToolBar->AddTool(ID_ZoomIn, wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_MENU));
    m_pToolBar->AddTool(ID_ZoomOut, wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK, wxART_MENU));
    m_pToolBar->Realize();

    CreateStatusBar();
    GetStatusBar()->SetStatusText(_("No Image"));
    SetMinSize(wxSize(400, 300));
}

CGraphicFrame::~CGraphicFrame() {
}

bool CGraphicFrame::LoadImage(wxString& strFile) {
    Mat cvImage;
    cvImage= imread(string(strFile.mb_str()));
    if(cvImage.empty())
        return false;

    m_pGLPane->SetOutputImage(cvImage);

    GetStatusBar()->SetStatusText(strFile);
    return true;
}

void CGraphicFrame::OnZoomIn(wxCommandEvent& evt) {
    m_pGLPane->ZoomIn();
}

void CGraphicFrame::OnZoomOut(wxCommandEvent& evt) {
    m_pGLPane->ZoomOut();
}
