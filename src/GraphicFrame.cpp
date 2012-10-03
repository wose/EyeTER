#include "GraphicFrame.h"
#include "GLPane.h"

#include <cv.h>
#include <highgui.h>

BEGIN_EVENT_TABLE(CGraphicFrame, wxFrame)
END_EVENT_TABLE()

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

    CreateStatusBar();
    GetStatusBar()->SetStatusText(_("No Image"));
    SetMinSize(wxSize(400, 300));
}

CGraphicFrame::~CGraphicFrame() {
}

bool CGraphicFrame::LoadImage(wxString& strFile) {
    cv::Mat cvImage;
    cvImage= cv::imread(std::string(strFile.mb_str()));
    if(cvImage.empty())
        return false;

    m_pGLPane->SetOutputImage(cvImage);
    GetStatusBar()->SetStatusText(strFile);
    return true;
}
