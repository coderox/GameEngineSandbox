#include "url/UrlParser.h"

#include <winrt/Windows.Foundation.h>

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Engine;

namespace Engine {
    class UrlParserImpl
    {
    public:
        UrlParserImpl(std::wstring url)
            : mUri(url.c_str()) 
        {

        }

        std::wstring GetDomain() 
        {
            return L"";
        }

        std::wstring GetPath() 
        {
            return L"";
        }

    private:
        Uri mUri{ nullptr };
    };
}

UrlParser::UrlParser(std::wstring url)
: mImpl(std::make_unique<Engine::UrlParserImpl>(url))
{

}

UrlParser::~UrlParser()
{
    mImpl.reset(nullptr);
}

std::wstring UrlParser::GetDomain()
{
    return mImpl->GetDomain();
}

std::wstring UrlParser::GetPath()
{
    return mImpl->GetPath();
}
