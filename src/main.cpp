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
    wxStaticBitmap *staticBitmap;
    wxStaticText *textView;

    wxImage image;
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
    auto sizer = new wxBoxSizer(wxVERTICAL);

    textView = new wxStaticText(this, wxID_ANY, "Here's your image:");
    staticBitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, FromDIP(wxSize(500, 200)));

    auto imageButton = new wxButton(this, wxID_ANY, "Load Image...");

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(imageButton, 0, wxLEFT, FromDIP(5));

    sizer->Add(textView, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP(10));
    sizer->Add(staticBitmap, 1, wxEXPAND | wxALL, FromDIP(10));
    sizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, FromDIP(10));

    this->SetSizerAndFit(sizer);
}
