#include <url\UrlParser.h>

namespace Engine {

	class UrlParserImpl {

	};

	UrlParser::UrlParser(std::wstring url) 
		: mImpl(new UrlParserImpl())
	{

	}

	UrlParser::~UrlParser() {
		mImpl.reset();
	}

	std::wstring UrlParser::GetDomain() {
		return L"";
	}

	std::wstring UrlParser::GetPath() {
		return L"";
	}
}