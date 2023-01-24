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

    void OnOpenImage(wxCommandEvent &event);

    void UpdateBitmapImage(const wxImage &image);
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

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
    staticBitmap->SetScaleMode(wxStaticBitmap::Scale_None);

    auto imageButton = new wxButton(this, wxID_ANY, "Load Image...");

    imageButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenImage, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(imageButton, 0, wxLEFT, FromDIP(5));

    sizer->Add(textView, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP(10));
    sizer->Add(staticBitmap, 1, wxEXPAND | wxALL, FromDIP(10));
    sizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

void MyFrame::OnOpenImage(wxCommandEvent &event)
{
    wxFileDialog dialog(this, "Open Image File", "", "", "Image Files (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!image.LoadFile(dialog.GetPath()))
    {
        wxMessageBox("Failed to load image file", "Error", wxOK | wxICON_ERROR);
        return;
    }

    UpdateBitmapImage(image);
}

void MyFrame::UpdateBitmapImage(const wxImage &image)
{
    staticBitmap->SetBitmap(wxBitmap(image));
    this->Layout();
}