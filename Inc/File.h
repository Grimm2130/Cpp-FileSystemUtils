#if !defined(__FILE_SYSTEM_FILE__)
#define __FILE_SYSTEM_FILE__

#include "Templates.h"
#include "string"

namespace FileSystem
{
    class File
    {
    public:
        bool Exists(const char* path );
        bool CanRead(const char* path );
        bool CanWrite(const char* path );
        bool CanExecute(const char* path );
        // Reader ops
        char Read(const char* path);
        std::string ReadUntil(const char* path, const char term);
        std::string ReadLine(const char* path);
        std::string ReadAll(const char* path);
        // Writer ops
        int Write(const char* path, const char);
        int Write(const char* path, const std::string&);
        int Write(const char* path, const char *, ... );
        int Append(const char* path, const char);
        int Append(const char* path, const std::string&);
        int Append(const char* path, const char *, ... );
        // FileSystem Ops on File
        int Create( const char* path, int flags );
        int Delete( const char* path );
        int Copy( const char* srcPath, const char* dstPath );
        int Move( const char* srcPath, const char* dstPath );
        int Concat( const char* srcPath, const char* dstPath );
        int Size( const char* path );
        // Error Reporting
        int GetError();
        std::string GetErrorStr();
    private:
        static int mLastError;    
    CLASS_IS_STATIC_ONLY(File)
    };
} // namespace FileSystem


#endif // __FILE_SYSTEM_FILE__
