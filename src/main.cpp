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

private:
    wxString userName;
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
                     wxTextEntryDialog dialog(this, "Enter your name", "Name", "John Doe");

                     dialog.SetTextValidator(wxTextValidator(wxFILTER_NONE, &userName));

                     userName = "Some other name";

                     if (dialog.ShowModal() == wxID_OK)
                     {
                         textView->SetLabel(userName);
                     }
                     else
                     {
                         textView->SetLabel("You cancelled the dialog");
                     } });
}
