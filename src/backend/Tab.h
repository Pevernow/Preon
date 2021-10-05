#pragma once
#include "tinyxml2/tinyxml2.h"
#include <vector>
#include <string>

#include <functional>

class Tab
{
public:
    Tab();
    Tab(std::string url);
    Tab(Tab &&);
    void Load(std::string url, std::function<void(Tab *)>);
    bool Initialized();
    tinyxml2::XMLDocument m_Dom;

private:
    bool
    LoadDoc(std::vector<char> &htmlDoc);
    bool ConvertHtmlToXhtml(const std::vector<char> &inHtml, std::vector<char> &outXhtml);
    bool LoadXhtmlToDom(const std::vector<char> &xhtml);

    bool m_Initialized;
};