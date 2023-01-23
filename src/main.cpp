#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    auto button = new wxButton(this, wxID_ANY, "Show Dialog");
    auto textView = new wxStaticText(this, wxID_ANY, "Click the button to show the dialog");

    auto sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(button, 0, wxALL, FromDIP(10));
    sizer->Add(textView, 0, wxALL, FromDIP(10));

    this->SetSizer(sizer);

    button->Bind(wxEVT_BUTTON, [this, textView](wxCommandEvent &event)
                 {
                     auto result = wxMessageBox("Hello World", "Message", wxYES_NO | wxCANCEL | wxICON_INFORMATION);

                     switch (result)
                     {
                     case wxYES:
                         textView->SetLabel("You clicked Yes");
                         break;
                     case wxNO:
                         textView->SetLabel("You clicked No");
                         break;
                     case wxCANCEL:
                         textView->SetLabel("You clicked Cancel");
                         break;
                     default:
                         break;
                     }
                 });
}
