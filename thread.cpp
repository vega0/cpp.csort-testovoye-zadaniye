#include "main.h"

void MyFrame::OnClose(wxCloseEvent&)
{
    {
        wxCriticalSectionLocker enter(m_pThreadCS);
        if (m_pThread)         // does the thread still exist?
        {
            wxMessageOutputDebug().Printf("MYFRAME: deleting thread");
            if (m_pThread->Delete() != wxTHREAD_NO_ERROR )
                wxLogError("Can't delete the thread!");
        }
    }       // exit from the critical section to give the thread
            // the possibility to enter its destructor
            // (which is guarded with m_pThreadCS critical section!)
    while (1)
    {
        { // was the ~MyThread() function executed?
            wxCriticalSectionLocker enter(m_pThreadCS);
            if (!m_pThread) break;
        }
        // wait for thread completion
        wxThread::This()->Sleep(1);
    }
    Destroy();
}

void MyFrame::OnThreadCompletion(wxCommandEvent&)
{
    wxMessageOutputDebug().Printf("MYFRAME: MyThread exited!\n");
}

#include <thread>
#include <chrono>

void MyFrame::OnThreadUpdate(wxCommandEvent&)
{
    auto password = login_password_item->GetValue();
    std::cout << "thread function " << password << std::endl;

    Person p;
    if (password == "111") {
        p.set_role_name("technical");
    } else if (password == "222") {
        p.set_role_name("ingeneer");
    } else {
        p.set_role_name("operator");
    }
    std::cout << "Role setted `" << p.get_role_name() << std::endl;
    loggened_person = p;
    perform_primary_buttons_layer(p);
    login_form_items->Show();



    _new_window_button->Show();
}

void MyFrame::DoPauseThread()
{
    // anytime we access the m_pThread pointer we must ensure that it won't
    // be modified in the meanwhile; since only a single thread may be
    // inside a given critical section at a given time, the following code
    // is safe:
    wxCriticalSectionLocker enter(m_pThreadCS);
    if (m_pThread)         // does the thread still exist?
    {
        // without a critical section, once reached this point it may happen
        // that the OS scheduler gives control to the MyThread::Entry() function,
        // which in turn may return (because it completes its work) making
        // invalid the m_pThread pointer
        if (m_pThread->Pause() != wxTHREAD_NO_ERROR )
            wxLogError("Can't pause the thread!");
    }
}

void MyFrame::DoStartThread()
{
    m_pThread = new MyThread(this);

    m_pThread->Create();

    if ( m_pThread->Run() != wxTHREAD_NO_ERROR )
    {
        wxLogError("Can't create the thread!");
        delete m_pThread;
        m_pThread = NULL;
    }
    // after the call to wxThread::Run(), the m_pThread pointer is "unsafe":
    // at any moment the thread may cease to exist (because it completes its work).
    // To avoid dangling pointers OnThreadExit() will set m_pThread
    // to NULL when the thread dies.

    std::cout << "Thread started!\n";
}



#include <cstdio>
#include <thread>
#include <chrono>

wxThread::ExitCode MyThread::Entry()
{



    //while (!TestDestroy())
    //{
        // ... do a bit of work...
        wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_MYTHREAD_UPDATE));
    //}

    // signal the event handler that this thread is going to be destroyed
    // NOTE: here we assume that using the m_pHandler pointer is safe,
    //       (in this case this is assured by the MyFrame destructor)
    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_MYTHREAD_COMPLETED));
    return (wxThread::ExitCode)0;     // success
}


MyThread::~MyThread()
{
    wxCriticalSectionLocker enter(m_pHandler->m_pThreadCS);
    // the thread is being destroyed; make sure not to leave dangling pointers around
    m_pHandler->m_pThread = NULL;
}
