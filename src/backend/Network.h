#pragma once
#include <vector>
#include <string>
#include <functional>
#include "curl/curl.h"

class Network
{
public:
    static Network &GetInstance();
    void DownLoadFromURLAsync(std::string url, std::function<void(std::string, std::vector<char> &, CURLcode)> callback);

private:
    Network();
    ~Network();
    static size_t OnRecvData(char *data, size_t count, size_t nmemb, std::vector<char> *stream);
    static Network m_Instance;
};