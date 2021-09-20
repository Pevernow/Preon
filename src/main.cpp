#include "CompileConfig.h"
#include "cmdline.h"
#include "backend/ResourceManager.h"
#include <iostream>

int main(int argc, char **argv)
{
    cmdline::parser CliArg;
    CliArg.add("version", 'v', "Version of Preon");
    CliArg.add<std::string>("url", 'u', "Opening an url", false);
    CliArg.parse_check(argc, argv);

    if (CliArg.exist("version"))
    {
        std::cout << PREON_VERSION << std::endl;
        return 0;
    }

    //std::string url = CliArg.get<std::string>("url");
    std::string url = "https://www.baidu.com/";
    ResourceManager &resourceManager = ResourceManager::GetInstance();
    resourceManager.GetResourceAsync(url, [](std::string url, std::vector<char> &data)
                                     {
                                         std::string str = std::string(&(data[0]), data.size());
                                         std::cout << str.length() << std::endl;
                                     });

    return 0;
}