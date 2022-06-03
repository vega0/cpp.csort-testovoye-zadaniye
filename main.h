#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

#include <vector>

// declare a new type of event, to be used by our MyThread class:
wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxThreadEvent);

#include "person.h"

class MyThread;

#include "labels_frame.h"

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
    void create_login_grid_element();
    void do_login_button_click(wxCommandEvent& event);
    void do_panel_timer_reset(wxTimerEvent& event);

    void DoStartThread();
    void DoPauseThread();
    void OnThreadCompletion(wxCommandEvent&);
    void OnThreadUpdate(wxCommandEvent&);
    void OnClose(wxCloseEvent&);

    void do_new_window_btn_click(wxCommandEvent&);

public:
    LabelsFrame *_lbls_frame = nullptr;

public:
    MyThread *m_pThread;
    wxCriticalSection m_pThreadCS;    // protects the m_pThread pointer
    wxPanel *login_form_items;
    wxTextEntry *login_password_item;
    std::vector<wxButton*> _buttons;
    wxStaticText *_lbl_caption;
    Person loggened_person;

    void perform_primary_buttons_layer(Person);

    wxButton * _new_window_button;
};

enum {
    ID_Hello = 1,
    BUTTON_Hello = wxID_HIGHEST + 1,
    TIMER_RESET_LOGIN_PANEL = 2,

    BUTTON_NewFrame = wxID_HIGHEST + 2
};

class MyThread : public wxThread
{
public:
    MyThread(MyFrame *handler)
        : wxThread(wxTHREAD_DETACHED)
        { m_pHandler = handler; }
    ~MyThread();
protected:
    virtual ExitCode Entry();
    MyFrame *m_pHandler;
};

#endif _MAIN_H_ // __MAIN__H__