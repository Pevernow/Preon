#include "ResourceManager.h"

#include <future>

#include <iostream>

ResourceManager ResourceManager::m_Instance;

ResourceManager::ResourceManager() : m_Net(Network::GetInstance()) {}

ResourceManager::~ResourceManager() {}

ResourceManager &ResourceManager::GetInstance()
{
    return ResourceManager::m_Instance;
}

void ResourceManager::GetResourceAsync(std::string url, std::function<void(std::string, std::vector<char> &)> callback)
{
    std::async(std::launch::async, [&]()
               {
                   m_Net.DownLoadFromURLAsync(url, [=](std::string url, std::vector<char> &data, CURLcode retcode)
                                              {
                                                  if (retcode == CURLcode::CURLE_OK)
                                                  {
                                                      callback(url, data);
                                                  }
                                                  else
                                                  {
                                                      //TODO: process error
                                                      ;
                                                  }
                                              });
               });
    return;
}