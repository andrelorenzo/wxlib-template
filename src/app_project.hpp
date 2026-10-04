#pragma once

#include "wxlib.h"

class AppProject final : public Project {
protected:
    void build(Container& root) override;
    void callback(wxCommandEvent& event) override;

private:
    Container* root_ = nullptr;
    Menu menu_;
    Container header_;
    Text title_;
    Tab tabs_;
    Container home_;
    Text welcome_;
};

