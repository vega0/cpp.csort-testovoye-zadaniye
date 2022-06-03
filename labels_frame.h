#ifndef __LABELS_FRAME_H_
#define __LABELS_FRAME_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyFrame;

#include <vector>

class LabelsFrame: public wxFrame
{
private:
    std::vector<wxStaticText*> _labels;

    MyFrame *m_pMyFrame;

    void OnClose(wxCloseEvent&);

    wxDECLARE_EVENT_TABLE();

public:
    LabelsFrame(MyFrame*, const wxString& title, const wxPoint& pos, const wxSize& size);

    void InitializeLabels(MyFrame*);
};


#endif __LABELS_FRAME_H_ // __LABELS_FRAME_H_