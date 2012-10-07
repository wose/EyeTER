#ifndef _CGLPANE_H_
#define _CGLPANE_H_

#include <cv.h>

#ifdef __WXMAC__
    #include "OpenGL/glu.h"
    #include "OpenGL/gl.h"
#else
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif

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
        cv::Mat m_cvOutputImage;
        GLuint m_nOutputTexture;

        float m_fZoom;
        static const float m_fZoomStep= 0.1;
        static const float m_cfZoomMin= 0.1;
        static const float m_cfZoomMax= 10.0;

    public:
        void Prepare2DViewport();
        void SetOutputImage(cv::Mat& cvImage);
        void ZoomIn();
        void ZoomOut();

        void OnRender(wxPaintEvent& evt);
        void OnResized(wxSizeEvent& evt);

        DECLARE_EVENT_TABLE()
};

#endif /* _CGLPANE_H_ */
