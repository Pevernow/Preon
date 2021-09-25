#pragma once

#include <string>
#include <functional>
#include "Network.h"

class ResourceManager
{
public:
    static ResourceManager &GetInstance();
    void GetResourceAsync(std::string url, std::function<void(std::string, std::vector<char> &)> callback);

private:
    ResourceManager();
    ~ResourceManager();
    Network &m_Net;
    static ResourceManager m_Instance;
};