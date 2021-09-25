#pragma once

#include <vector>
#include <string>
#include "backend/Tab.h"
#include "UI/UI.h"

class Browser
{
public:
    Browser();
    bool OpenNewTab(std::string url);

private:
    UI &m_Ui;
    std::vector<Tab> m_Tabs;
};