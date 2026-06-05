#if !defined(__FILE_SYSTEM_FILE__)
#define __FILE_SYSTEM_FILE__

#include "CppTemplates/Templates.h"
#include "string"
#include <sys/stat.h>
#include <fcntl.h>

namespace FileSystemUtils
{
    class File
    {
    public:
        static bool Exists(const char *path);
        static bool CanRead(const char *path);
        static bool CanWrite(const char *path);
        static bool CanExecute(const char *path);
        // Reader ops
        static char Read(const char *path);
        static std::string ReadUntil(const char *path, const char term);
        static std::string ReadLine(const char *path);
        static std::string ReadAll(const char *path);
        // Writer ops
        static int Write(const char *path, const char);
        static int Write(const char *path, const std::string &);
        static int Write(const char *path, const char *, ...);
        static int Append(const char *path, const char);
        static int Append(const char *path, const std::string &);
        static int Append(const char *path, const char *, ...);
        // FileSystemUtils Ops on File
        static int Create(const char *path, int flags);
        static int Delete(const char *path);
        static int Copy(const char *srcPath, const char *dstPath);
        static int Move(const char *srcPath, const char *dstPath);
        static int Concat(const char *srcPath, const char *dstPath);
        static int Size(const char *path);
        // Error Reporting
        static int GetError();
        static std::string GetErrorStr();

    private:
        static int mLastError;
        CLASS_IS_STATIC_ONLY(File)
    };
} // namespace FileSystemUtils

#endif // __FILE_SYSTEM_FILE__
