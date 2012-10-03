#include "GLPane.h"

BEGIN_EVENT_TABLE(CGLPane, wxGLCanvas)
    EVT_SIZE(CGLPane::OnResized)
    EVT_PAINT(CGLPane::OnRender)
END_EVENT_TABLE()

using namespace std;
using namespace cv;

CGLPane::CGLPane(wxWindow* pParent, wxWindowID id,
    int* pAttribList, const wxPoint& pos, const wxSize& Size, long nStyle,
    const wxString& strName, const wxPalette& palette)
    : wxGLCanvas(pParent, id, pAttribList, pos, Size, nStyle, strName, palette)
{
    m_pContext= new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

CGLPane::~CGLPane() {
    glDeleteTextures(1, &m_nOutputTexture);
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

	glEnable(GL_TEXTURE_2D);

    int nWidth= GetSize().x;
    int nHeight= GetSize().y;

    if(!m_cvOutputImage.empty()) {
      	glBindTexture(GL_TEXTURE_2D, m_nOutputTexture);
        
        float fScale= min((float)nWidth / m_cvOutputImage.cols,
            (float)nHeight / m_cvOutputImage.rows);
        float fX= (nWidth - m_cvOutputImage.cols * fScale) / 2;
        float fY= (nHeight - m_cvOutputImage.rows * fScale) / 2;

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(fX, fY);
        glTexCoord2f(1, 0);
        glVertex2f(nWidth - fX, fY);
        glTexCoord2f(1, 1);
        glVertex2f(nWidth - fX, nHeight - fY);
        glTexCoord2f(0, 1);
        glVertex2f(fX, nHeight - fY);
        glEnd();

    	glDisable(GL_TEXTURE_2D);
    }

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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(0, 0, GetSize().x, GetSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, GetSize().x, GetSize().y, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CGLPane::SetOutputImage(Mat& cvImage) {
    m_cvOutputImage= cvImage;

    glGenTextures(1, &m_nOutputTexture);

    glBindTexture(GL_TEXTURE_2D, m_nOutputTexture);               
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, m_cvOutputImage.channels(), m_cvOutputImage.cols, 
        m_cvOutputImage.rows, 0, GL_BGR, GL_UNSIGNED_BYTE,
        m_cvOutputImage.data);    
}
