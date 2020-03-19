#include "url/UrlParser.h"

TEST(UrlParserTests, Domain) {
    Engine::UrlParser parser(L"http://www.coderox.se/blog");
    auto result = parser.GetDomain();
    EXPECT_EQ(result, L"coderox.se");
}

TEST(UrlParserTests, Path) {
    Engine::UrlParser parser(L"http://www.coderox.se/blog");
    auto result = parser.GetPath();
    EXPECT_EQ(result, L"/blog");
}