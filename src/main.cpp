#include "app_project.hpp"
#include "app_config.hpp"

class MainFrame final : public wxFrame {
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8(APP_DISPLAY_NAME),
                  wxDefaultPosition, wxSize(1200, 800)) {
        root_.create(this);
        project_.create(root_, 0);

        Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event) {
            project_.destroy();
            event.Skip();
        });

        Centre();
    }

private:
    Container root_;
    AppProject project_;
};

class MainApplication final : public wxApp {
public:
    bool OnInit() override {
        wxInitAllImageHandlers();
        auto* frame = new MainFrame();
        frame->Show();
        return true;
    }
};

#if defined(NDEBUG)
wxIMPLEMENT_APP(MainApplication);
#else
wxIMPLEMENT_APP_CONSOLE(MainApplication);
#endif

