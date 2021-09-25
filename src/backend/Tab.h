#pragma once
#include "tinyxml2/tinyxml2.h"
#include <vector>
#include <string>

class Tab
{
public:
    Tab();
    Tab(std::string url);
    Tab(Tab &&);
    void Load(std::string url);
    bool Initialized();

private:
    bool
    LoadDoc(std::vector<char> &htmlDoc);
    bool ConvertHtmlToXhtml(const std::vector<char> &inHtml, std::vector<char> &outXhtml);
    bool LoadXhtmlToDom(const std::vector<char> &xhtml);
    tinyxml2::XMLDocument m_Dom;
    bool m_Initialized;
};