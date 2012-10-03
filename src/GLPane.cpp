#include "GLPane.h"

BEGIN_EVENT_TABLE(CGLPane, wxGLCanvas)
    EVT_SIZE(CGLPane::OnResized)
    EVT_PAINT(CGLPane::OnRender)
END_EVENT_TABLE()

CGLPane::CGLPane(wxWindow* pParent, wxWindowID id,
    int* pAttribList, const wxPoint& pos, const wxSize& Size, long nStyle,
    const wxString& strName, const wxPalette& palette)
    : wxGLCanvas(pParent, id, pAttribList, pos, Size, nStyle, strName, palette)
{
    m_pContext= new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

CGLPane::~CGLPane() {
    if(m_pContext)
        delete m_pContext;
    m_pContext= NULL;
}

void CGLPane::OnRender(wxPaintEvent& evt) {
    if(!IsShown())
        return;

    wxGLCanvas::SetCurrent(*m_pContext);
    wxPaintDC(this);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Prepare2DViewport();

    glLoadIdentity();
	
    int nWidth= GetSize().x;
    int nHeight= GetSize().y;

    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(nWidth, 0, 0);
    glVertex3f(nWidth, nHeight, 0);
    glVertex3f(0, nHeight, 0);
    glEnd();
	
    // red square
    glColor4f(1, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3f(nWidth / 8, nHeight / 3, 0);
    glVertex3f(nWidth * 7 / 8, nHeight / 3, 0);
    glVertex3f(nWidth * 7 / 8, nHeight * 2 / 3, 0);
    glVertex3f(nWidth / 8, nHeight * 2 / 3, 0);
    glEnd();

    glFlush();
    SwapBuffers();
}

void CGLPane::OnResized(wxSizeEvent& evt) {
    Refresh();
}

void CGLPane::Prepare2DViewport() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(0, 0, GetSize().x, GetSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, GetSize().x, GetSize().y, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
