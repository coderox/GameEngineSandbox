#include "File.h"
#include "winrt/Windows.Foundation.Collections.h"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Engine;

void File::Open(wstring filename)
{
    std::replace(filename.begin(), filename.end(), '/', '\\');
    mStorageFile = StorageFile::GetFileFromPathAsync(filename).get();
}

void File::Close() 
{
    if(mStorageFile) {
        mStorageFile = nullptr;
    }
}