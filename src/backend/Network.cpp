#include "Network.h"
#include <future>

Network Network::m_Instance;

Network::Network()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Network::~Network()
{
    curl_global_cleanup();
}

Network &Network::GetInstance()
{
    return Network::m_Instance;
}

void Network::DownLoadFromURLAsync(std::string url, std::function<void(std::string, std::vector<char> &, CURLcode)> callback)
{
    std::async(std::launch::async, [&]()
               {
                   std::vector<char> output;

                   //初始化curl，这个是必须的
                   CURL *curl = curl_easy_init();
                   curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                   //设置接收数据的回调
                   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnRecvData);
                   curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
                   //curl_easy_setopt(curl, CURLOPT_INFILESIZE, lFileSize);
                   //curl_easy_setopt(curl, CURLOPT_HEADER, 1);
                   //curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
                   //curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
                   // 设置重定向的最大次数
                   curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
                   // 设置301、302跳转跟随location
                   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
                   curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
                   //设置进度回调函数
                   //curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
                   //curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &lFileSize);
                   //curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, g_hDlgWnd);
                   //开始执行请求
                   CURLcode retCode = curl_easy_perform(curl);
                   //清理curl，和前面的初始化匹配
                   curl_easy_cleanup(curl);
                   callback(url, output, retCode);
               });
}

size_t Network::OnRecvData(char *data, size_t count, size_t nmemb, std::vector<char> *stream)
{
    size_t size = count * nmemb;
    //alloc memory
    size_t previous_size = stream->size();
    stream->resize(previous_size + size);
    for (int i = previous_size, j = 0; j < size; i++, j++)
    {
        (*stream)[i] = data[j];
    }
    return size;
}