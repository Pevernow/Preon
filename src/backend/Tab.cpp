#include "Tab.h"
#include "ResourceManager.h"
#include <tidy.h>
#include <tidybuffio.h>

Tab::Tab(std::string url) : m_Initialized(false)
{
    Load(url);
}

bool Tab::ConvertHtmlToXhtml(const std::vector<char> &inHtml, std::vector<char> &outXhtml)
{
    const char *input = &(inHtml[0]);
    TidyBuffer tbOut = {0};
    TidyBuffer tbErr = {0};
    int rc = -1;

    TidyDoc tdoc = tidyCreate(); // Initialize "document"

    bool ok = false;
    ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
    if (ok)                                    // Convert to XHTML
        rc = tidySetErrorBuffer(tdoc, &tbErr); // Capture diagnostics
    if (rc >= 0)
        rc = tidyParseString(tdoc, input); // Parse the input
    if (rc >= 0)
        rc = tidyCleanAndRepair(tdoc); // Tidy it up!
    if (rc >= 0)
        rc = tidyRunDiagnostics(tdoc); // Kvetch
    if (rc > 1)                        // If error, force output.
        rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
    if (rc >= 0)
        rc = tidySaveBuffer(tdoc, &tbOut); // Pretty Print

    ok = false;
    if (rc >= 0)
    {
        if (rc > 0)
        {
            ; //TODO: process tidy error
        }
        outXhtml.resize(tbOut.size);
        for (unsigned int i = 0; i < tbOut.size; i++)
        {
            outXhtml[i] = tbOut.bp[i];
        }
        ok = true;
    }
    else
    {
        ok = false;
    }

    tidyBufFree(&tbOut);
    tidyBufFree(&tbErr);
    tidyRelease(tdoc);
    return ok;
}

bool Tab::LoadXhtmlToDom(const std::vector<char> &xhtml)
{
    tinyxml2::XMLError ret = m_Dom.Parse(&(xhtml[0]), xhtml.size());
    if (ret == tinyxml2::XML_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tab::LoadDoc(std::vector<char> &htmlDoc)
{
    std::vector<char> xhtml;
    bool ret = ConvertHtmlToXhtml(htmlDoc, xhtml);
    if (ret)
    {
        ret = LoadXhtmlToDom(xhtml);
        if (ret)
        {
            m_Initialized = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Tab::Load(std::string url)
{
    ResourceManager &resourceManager = ResourceManager::GetInstance();
    resourceManager.GetResourceAsync(url, [&](std::string url, std::vector<char> &data)
                                     { this->LoadDoc(data); });
}

Tab::Tab() : m_Initialized(false)
{
    ;
}

Tab::Tab(Tab &&) : m_Initialized(false)
{
    ;
}

bool Tab::Initialized()
{
    return m_Initialized;
}