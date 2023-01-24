#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>

#include "brightnessdialog.h"

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
    void OnChangeColor(wxCommandEvent &event);
    void OnChangeFont(wxCommandEvent &event);
    void OnChangeBrightness(wxCommandEvent &event);

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
    auto colorButton = new wxButton(this, wxID_ANY, "Change Color...");
    auto fontButton = new wxButton(this, wxID_ANY, "Change Font...");
    auto brightnessButton = new wxButton(this, wxID_ANY, "Change Brightness...");

    imageButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenImage, this);
    colorButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeColor, this);
    fontButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeFont, this);
    brightnessButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeBrightness, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(imageButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(colorButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(fontButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(brightnessButton, 0, wxLEFT, FromDIP(5));

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

void MyFrame::OnChangeColor(wxCommandEvent &event)
{
    wxColourData data;
    data.SetColour(this->GetBackgroundColour());
    wxColourDialog dialog(this, &data);

    if (dialog.ShowModal() == wxID_OK)
    {
        auto backgroundColor = dialog.GetColourData().GetColour();
        this->SetBackgroundColour(backgroundColor);
        this->Refresh();
    }
}

void MyFrame::OnChangeFont(wxCommandEvent &event)
{
    wxFontData data;
    data.SetInitialFont(textView->GetFont());
    wxFontDialog dialog(this, data);

    if (dialog.ShowModal() == wxID_OK)
    {
        auto font = dialog.GetFontData().GetChosenFont();
        textView->SetFont(font);
        this->Fit();
        this->Layout();
    }
}

void MyFrame::OnChangeBrightness(wxCommandEvent &event)
{
    if (!image.IsOk())
    {
        wxMessageBox("Please load an image first", "Error", wxOK | wxICON_ERROR);
    }
    else
    {
        BrightnessDialog dialog(this);

        if (dialog.ShowModal() == wxID_OK)
        {
            double adj = dialog.GetBrightnessAdjustment();
            image.ChangeBrightness(adj);

            UpdateBitmapImage(image);
        }
    }
}

void MyFrame::UpdateBitmapImage(const wxImage &image)
{
    staticBitmap->SetBitmap(wxBitmap(image));
    this->Layout();
}