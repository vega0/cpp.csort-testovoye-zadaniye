#include "labels_frame.h"

wxBEGIN_EVENT_TABLE(LabelsFrame, wxFrame)
    EVT_CLOSE(LabelsFrame::OnClose)
wxEND_EVENT_TABLE()

#include "main.h"

LabelsFrame::LabelsFrame(MyFrame* frame, const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size,
                  wxMINIMIZE_BOX | wxMAXIMIZE_BOX
                | wxSYSTEM_MENU | wxCAPTION
                | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    CreateStatusBar();
    SetStatusText( L"Вошёл как ' " + frame->loggened_person.get_role_name() );

}


void LabelsFrame::InitializeLabels(MyFrame* frame)
{

    m_pMyFrame = frame;

    for (int i = 0; i < 6; i ++)
    {
        wxStaticText * item = new wxStaticText(this, -1,
            L"Текст " + std::to_string(i+1), wxPoint(0, i * 20));
        _labels.push_back(item);
        item->Hide();
    }

    auto person = frame->loggened_person;

    if (person.is_operator()) {
        _labels.at(0)->Show();
        _labels.at(1)->Show();
    } else if (person.is_technical())
        for (int i = 0; i != 4; i++) _labels.at(i)->Show();
        
    else if (person.is_ingeneer())
        for (int i = 0; i != 6; i++) _labels.at(i)->Show();
}

void LabelsFrame::OnClose(wxCloseEvent& event)
{
    m_pMyFrame->_lbls_frame = nullptr;

    Destroy();
}