#include <wx/wx.h>
#include <wx/progdlg.h>

#include <vector>

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
    std::vector<int> data;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

void BubbleSort(std::vector<int> &data, std::function<bool(int)> shouldQuit)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (shouldQuit(i * 100 / data.size()))
        {
            return;
        }

        for (int j = 0; j < data.size() - i - 1; j++)
        {

            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    for (int i = 0; i < 30000; i++)
    {
        data.push_back(rand());
    }

    auto button = new wxButton(this, wxID_ANY, "Show Dialog");
    auto textView = new wxStaticText(this, wxID_ANY, "Click the button to show the dialog");

    auto sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(button, 0, wxALL, FromDIP(10));
    sizer->Add(textView, 0, wxALL, FromDIP(10));

    this->SetSizer(sizer);

    textView->SetLabel("First Item: " + std::to_string(data[0]));

    button->Bind(wxEVT_BUTTON, [this, textView](wxCommandEvent &event)
                 {
                     wxProgressDialog dialog("Progress Dialog", "Doing work", 100, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);

                     BubbleSort(data, [&dialog](int progress)
                                { return !dialog.Update(progress); });

                     dialog.Update(100);

                     textView->SetLabel("First Item: " + std::to_string(data[0]));
                 });
}
