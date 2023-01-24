#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class BufferedBitmap : public wxWindow
{
public:
    BufferedBitmap(wxWindow *parent, wxWindowID id, const wxBitmap &b, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0)
        : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
    {
        this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

        this->Bind(wxEVT_PAINT, &BufferedBitmap::OnPaint, this);
        this->SetBitmap(b);
    }

    void OnPaint(wxPaintEvent &evt)
    {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();

        wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
            // scaling consistent with wxStaticBitmap
            const wxSize drawSize = ToDIP(GetClientSize());

            const wxSize bmpSize = bitmap.GetSize();

            double w = bmpSize.GetWidth();
            double h = bmpSize.GetHeight();

            double x = (drawSize.GetWidth() - w) / 2;
            double y = (drawSize.GetHeight() - h) / 2;

            gc->DrawBitmap(bitmap, gc->FromDIP(x), gc->FromDIP(y), gc->FromDIP(w), gc->FromDIP(h));

            delete gc;
        }
    }

    void SetBitmap(const wxBitmap &bitmap)
    {
        this->bitmap = bitmap;
        this->Refresh();
    }

    const wxBitmap &GetBitmap()
    {
        return bitmap;
    }

private:
    wxBitmap bitmap;
};