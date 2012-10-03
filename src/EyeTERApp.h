#ifndef _EyeTERAPP_H_
#define _EyeTERAPP_H_

#include <wx/app.h>

class CMainFrame;

class EyeTERApp: public wxApp {
    public:
        virtual bool OnInit();

    protected:
        CMainFrame* m_pMainFrame;
};

DECLARE_APP(EyeTERApp)

#endif /* _EyeTERAPP_H_ */
