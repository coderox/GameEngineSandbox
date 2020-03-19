#pragma once
#include <memory>
#include <string>


namespace Engine {
    class UrlParserImpl;

    class UrlParser {
    public:
        UrlParser(std::wstring url);
        ~UrlParser();

        std::wstring GetDomain();
        std::wstring GetPath();

    private:
        std::unique_ptr<UrlParserImpl> mImpl;
    };
}
