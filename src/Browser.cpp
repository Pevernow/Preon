#include "Browser.h"

Browser::Browser() : m_Ui(UI::GetInstance())
{
}

bool Browser::OpenNewTab(std::string url)
{
    m_Tabs.push_back(Tab());
    m_Tabs.back().Load(url);
    m_Ui.MainLoop();
    return true;
}