#include "app_project.hpp"
#include "app_config.hpp"

void AppProject::build(Container& root) {
    root_ = &root;
    root.setPadding(0);

    menu_.create(root);
    const int fileMenu = menu_.add("File");
    menu_.addChild(fileMenu, "Exit", wxID_EXIT);
    const int helpMenu = menu_.add("Help");
    menu_.addChild(helpMenu, "About", wxID_ABOUT);

    header_.create(root, 0, Container::SIZER_HOR);
    header_.setPadding(12);
    title_.create(header_, wxString::FromUTF8(APP_DISPLAY_NAME), FONT_TITLEB);

    tabs_.create(root);
    tabs_.add(home_, "Home");
    home_.setPadding(16);
    welcome_.create(home_, "Start building your application here.", FONT_TEXT);
}

void AppProject::callback(wxCommandEvent& event) {
    if (event.GetId() == wxID_EXIT) {
        if (auto* frame = wxDynamicCast(wxGetTopLevelParent(root_->window()), wxFrame)) {
            frame->Close();
        }
    } else if (event.GetId() == wxID_ABOUT) {
        wxAboutDialogInfo about;
        about.SetName(wxString::FromUTF8(APP_DISPLAY_NAME));
        about.SetDescription("Application built with wxlib.");
        wxAboutBox(about, wxGetTopLevelParent(root_->window()));
    }
}

