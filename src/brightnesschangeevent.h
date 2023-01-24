#pragma once

#include <wx/wx.h>

class BrightnessChangeEvent;

wxDECLARE_EVENT(wxEVT_BRIGHTNESS_CHANGED, BrightnessChangeEvent);
wxDEFINE_EVENT(wxEVT_BRIGHTNESS_CHANGED, BrightnessChangeEvent);

class BrightnessChangeEvent : public wxCommandEvent
{
public:
    BrightnessChangeEvent(wxEventType commandType = wxEVT_BRIGHTNESS_CHANGED, int id = 0)
        : wxCommandEvent(commandType, id) {}

    BrightnessChangeEvent(const BrightnessChangeEvent &event)
        : wxCommandEvent(event), brightnessAdjustment(event.brightnessAdjustment) {}

    wxEvent *Clone() const override { return new BrightnessChangeEvent(*this); }

    double GetBrightnessAdjustment() const { return brightnessAdjustment; }
    void SetBrightnessAdjustment(double value) { brightnessAdjustment = value; }

private:
    double brightnessAdjustment;
};