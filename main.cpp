// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "main.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_CLOSE(MyFrame::OnClose)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    //EVT_MENU(99,  MyFrame::DoStartThread)
    EVT_BUTTON ( BUTTON_Hello, MyFrame::do_login_button_click ) 
    EVT_BUTTON(BUTTON_NewFrame, MyFrame::do_new_window_btn_click)
    EVT_TIMER(TIMER_RESET_LOGIN_PANEL, MyFrame::do_panel_timer_reset)
    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_MYTHREAD_UPDATE, MyFrame::OnThreadUpdate)
    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_MYTHREAD_COMPLETED, MyFrame::OnThreadCompletion)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);

wxDEFINE_EVENT(wxEVT_COMMAND_MYTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxThreadEvent);


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World",
            wxPoint(50, 50),
            wxSize(450, 340) );

    frame->Centre();
    frame->Show( true );
    return true;
}



MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size,
                  wxMINIMIZE_BOX | wxMAXIMIZE_BOX
                | wxSYSTEM_MENU | wxCAPTION
                | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );


    this->create_login_grid_element();
}


void MyFrame::create_login_grid_element()
{
    wxPanel * panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(628, 528));
    panel->SetBackgroundColour(wxColour(wxT("#0000ff")));
    
    wxPanel * panel2 = new wxPanel(this, wxID_ANY,
        wxPoint(130, 104),
        wxSize(358, 108));

    panel2->SetBackgroundColour(wxColour(wxT("#ff0000")));

    wxTextEntry * te = new wxTextCtrl(panel2, -1, "Ecvcvcvc",
        wxPoint(20, 10), wxSize(280, 35), wxTE_PASSWORD);
    wxButton * lbtn = new wxButton(panel2, BUTTON_Hello, L"Войти!",
        wxPoint(20, 45), wxSize(280, 35));

    this->login_password_item = te;
    this->login_form_items = panel2;


    for(int i = 0;  i < 6; i++)
    {
        wxButton *btn = new wxButton(this, 10 + i, L"Кнопка " + std::to_string(i+1),
            wxPoint(2, i * 21 + 25), wxSize(100, 20));
        btn->Hide();
        _buttons.push_back(btn);
    }

    _lbl_caption = new wxStaticText(this, -1, "CAPTION");
    _lbl_caption->SetForegroundColour(wxColour(wxT("#ffff00")));



    _new_window_button = new wxButton(panel,
            BUTTON_NewFrame,
            L"Новое окно!",
            wxPoint(0, 225),
            wxSize(80, 25));

    _new_window_button->Hide();
}

#include <thread>
#include <chrono>
#include "person.h"

void MyFrame::do_login_button_click(wxCommandEvent& event)
{
    if (this->login_password_item->IsEmpty() ||
            this->login_password_item->GetLastPosition() == 1)
        return;

    auto password = this->login_password_item->GetValue();
    std::cout << "Button clicked!\n";
    std::cout << "\tLogin password data : " << password << "\n";

    //this->login_password_item->SetValue("");
    this->login_form_items->Hide();

    this->DoStartThread();
}

void MyFrame::do_panel_timer_reset(wxTimerEvent& event)
{
    this->login_form_items->Show();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}


void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}


void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}



void MyFrame::perform_primary_buttons_layer(Person person)
{
    delete _lbl_caption;
    //_lbl_caption = nullptr;

    _lbl_caption = new wxStaticText(this, 10, "logged as `" + person.get_role_name());
    _lbl_caption->SetForegroundColour(wxColour(wxT("#ffff00")));


    for (auto it = _buttons.begin(); it != _buttons.end(); it++)
    {
        std::cout << "hiding\n";
        if ((**it).IsShown()) (**it).Hide();
    }

    if (person.is_operator()) {
        _buttons.at(0)->Show();
        _buttons.at(1)->Show();
    } else if (person.is_technical())
        for (int i = 0; i != 4; i++) _buttons.at(i)->Show();
        
    else if (person.is_ingeneer())
        for (int i = 0; i != 6; i++) _buttons.at(i)->Show();
}

void MyFrame::do_new_window_btn_click(wxCommandEvent& event)
{
    if (_lbls_frame == nullptr)
    {
        _lbls_frame = new LabelsFrame(this, L"Текстовые поля.",
            wxPoint(100, 100), wxSize(200, 200));

        _lbls_frame->Show(true);
        _lbls_frame->InitializeLabels(this);
    }
}