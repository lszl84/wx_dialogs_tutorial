#pragma once

#include <wx/wx.h>
#include "brightnesschangeevent.h"

wxDECLARE_EVENT(EVT_PREVIEW_CHECKBOX_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_PREVIEW_CHECKBOX_CHANGED, wxCommandEvent);

class BrightnessDialog : public wxDialog
{
public:
    BrightnessDialog(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = "Adjust Brightness", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE) : wxDialog(parent, id, title, pos, size, style)
    {
        slider = new wxSlider(this, wxID_ANY, 0, -100, 100);
        label = new wxStaticText(this, wxID_ANY, "Adjustment: 0%");

        previewCheckbox = new wxCheckBox(this, wxID_ANY, "Preview");
        previewCheckbox->Bind(wxEVT_CHECKBOX, &BrightnessDialog::OnPreviewCheckboxChanged, this);

        slider->Bind(wxEVT_SLIDER, &BrightnessDialog::OnSliderChanged, this);

        auto mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(slider, 0, wxEXPAND | wxALL, FromDIP(20));
        mainSizer->Add(label, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, FromDIP(20));
        mainSizer->Add(previewCheckbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, FromDIP(20));
        mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxALL, FromDIP(10));

        this->SetSizerAndFit(mainSizer);
    }

    double GetBrightnessAdjustment() const { return slider->GetValue() / 100.0; }

private:
    wxSlider *slider;
    wxStaticText *label;

    wxCheckBox *previewCheckbox;

    void OnSliderChanged(wxCommandEvent &event)
    {
        label->SetLabel(wxString::Format("Adjustment: %d%%", event.GetInt()));

        if (previewCheckbox->IsChecked())
        {
            SendBrightnessChangeEvent();
        }
    }

    void OnPreviewCheckboxChanged(wxCommandEvent &event)
    {
        if (event.IsChecked())
        {
            SendBrightnessChangeEvent();
        }

        SendPreviewCheckboxChangeEvent();
    }

    void SendBrightnessChangeEvent()
    {
        BrightnessChangeEvent evt(wxEVT_BRIGHTNESS_CHANGED);
        evt.SetBrightnessAdjustment(GetBrightnessAdjustment());
        evt.SetEventObject(this);
        ProcessWindowEvent(evt);
    }

    void SendPreviewCheckboxChangeEvent()
    {
        wxCommandEvent evt(EVT_PREVIEW_CHECKBOX_CHANGED);
        evt.SetEventObject(this);
        evt.SetInt(previewCheckbox->IsChecked() ? 1 : 0);
        ProcessWindowEvent(evt);
    }
};