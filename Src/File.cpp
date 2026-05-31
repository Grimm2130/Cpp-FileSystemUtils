#include "File.h"
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace FileSystem
{

    #define FILE_STREAM_TERM( c, termc )  ( ((c) != (termc)) && ((c) != EOF) )

    int File::mLastError = 0;
    
    bool File::Exists(const char* path )
    {
        bool res;
        int err = access(path, F_OK);

        if( err == 0 )
        {
            res = true;
        }
        else
        {
            res = false;
            mLastError = err;
        }

        return res;
    }

    bool File::CanRead(const char* path )
    {
        bool res;
        int err = access(path, R_OK);

        if( err == 0 )
        {
            res = true;
        }
        else
        {
            res = false;
            mLastError = err;
        }

        return res;
    }

    bool File::CanWrite(const char* path )
    {
        bool res;
        int err = access(path, W_OK);

        if( err == 0 )
        {
            res = true;
        }
        else
        {
            res = false;
            mLastError = err;
        }

        return res;
    }

    bool File::CanExecute(const char* path )
    {
        bool res;
        int err = access(path, X_OK);

        if( err == 0 )
        {
            res = true;
        }
        else
        {
            res = false;
            mLastError = err;
        }

        return res;
    }

    char File::Read(const char* path)
    {
        char res;
        FILE* fp = fopen(path, "r");

        if( fp )
        {
            res = fgetc(fp);
            fclose(fp);
        }
        else
        {
            res = EOF;
            mLastError = errno;
        }

        return res;
    }

    std::string File::ReadUntil(const char* path, const char term)
    {
        int c;
        std::string res = "";
        FILE* fp = fopen(path, "r");

        if( fp )
        {
            while((c = fgetc(fp)) != EOF)
            {
                if( c == int(term) ) break;
                res += c;
            }
            
            fclose(fp);
        }
        else
        {
            mLastError = errno;
        }

        return res;
    }

    std::string File::ReadLine(const char* path)
    {
        return File::ReadUntil( path, '\n');
    }

    std::string File::ReadAll(const char* path)
    {
        return File::ReadUntil( path, EOF);
    }

    int File::Write(const char* path, const char c )
    {
        int res = 0;
        FILE* fp = fopen(path, "w");

        if( fp )
        {
            res = fprintf( fp, "%c", c );
            fclose(fp);
        }
        else
        {
            res = mLastError = errno;
        }

        return res;
    }

    int File::Write(const char* path, const std::string& str )
    {
        int res = 0;
        FILE* fp = fopen(path, "w");

        if( fp )
        {
            res = fprintf( fp, "%s", str.c_str() );
            fclose(fp);
        }
        else
        {
            res = mLastError = errno;
        }

        return res;
    }

    int File::Write(const char* path, const char * str, ... )
    {
        int res;
        static const size_t sBufferSize = 1024;
        
        if( str )
        {
            va_list args;
            char buffer[ sBufferSize] = {0};
    
            va_start( args, str );
            int bytes = vsnprintf( buffer, sBufferSize, str, args );
            va_end( args );

            // API was successful
            if( bytes >= 0 )
            {
                FILE* fp = fopen(path, "w");
    
                if( fp )
                {
                    res = fprintf( fp, "%s", buffer );
                    fclose(fp);
                }
                else
                {
                    res = mLastError = errno;
                }
            }
            else
            {
                res = mLastError = errno;
            }
        }
        else
        {
            res = EFAULT;
        }

        return res;
    }

    int File::Append(const char* path, const char c )
    {
        int res = 0;
        FILE* fp = fopen(path, "a");

        if( fp )
        {
            res = fprintf( fp, "%c", c );
            fclose(fp);
        }
        else
        {
            res = mLastError = errno;
        }

        return res;
    }

    int File::Append(const char* path, const std::string& str )
    {
        int res = 0;
        FILE* fp = fopen(path, "a");

        if( fp )
        {
            res = fprintf( fp, "%s", str.c_str() );
            fclose(fp);
        }
        else
        {
            res = mLastError = errno;
        }

        return res;
    }

    int File::Append(const char* path, const char * str, ... )
    {
        int res;
        static const size_t sBufferSize = 1024;
        
        if( str )
        {
            va_list args;
            char buffer[ sBufferSize] = {0};
    
            va_start( args, str );
            int bytes = vsnprintf( buffer, sBufferSize, str, args );
            va_end( args );

            // API was successful
            if( bytes >= 0 )
            {
                FILE* fp = fopen(path, "a");
    
                if( fp )
                {
                    res = fprintf( fp, "%s", buffer );
                    fclose(fp);
                }
                else
                {
                    res = mLastError = errno;
                }
            }
            else
            {
                res = mLastError = errno;
            }
        }
        else
        {
            res = EFAULT;
        }

        return res;
    }

    int File::Create( const char* path, int flags )
    {
        return (mLastError = open(path, flags));
    }

    int File::Delete( const char* path )
    {
        return (mLastError = remove(path));
    }

    int File::Copy( const char* srcPath, const char* dstPath )
    {
        int res = 0;
        if( dstPath )
        {
            if( srcPath )
            {
                std::string contents = File::ReadAll(srcPath);
                if( contents.length() )
                {
                    res = File::Write( dstPath, contents );
                }
                else
                {
                    res = mLastError;
                }
            }
            else
            {
                res = mLastError;
            }
        }
        else
        {
            res = EDESTADDRREQ;
        }

        return res;
    }

    int File::Move( const char* srcPath, const char* dstPath )
    {
        int res = Copy( srcPath, dstPath );

        if( res == 0 )
        {
            res = File::Delete( srcPath );
        }

        return res;
    }

    /// @brief Appends the contents of one file to another
    /// @param srcPath Source File
    /// @param dstPath Destination File (File to be appended to)
    /// @return zero or Error code on failure
    int File::Concat( const char* srcPath, const char* dstPath )
    {
        int res;
        if(dstPath)
        {
            if( srcPath )
            {
                std::string content = ReadAll(srcPath);

                if( content.length() )
                {
                    res = File::Append( dstPath, content );
                }
                else
                {
                    res = mLastError;
                }
            }
            else
            {
                res = EFAULT;
            }
        }
        else
        {
            res = EDESTADDRREQ;
        }

        return res;
    }

    /// @brief Return the size of a file
    /// @param path Path to be read from
    /// @return 
    int File::Size( const char* path )
    {
        int res;
        if( path )
        {
            std::string content = ReadAll(path);
            res = content.size();
        }
        else
        {
            return -1;
        }

        return res;
    }

    int File::GetError()
    {
        return mLastError;
    }

    std::string File::GetErrorStr()
    {
        return  std::string( strerror(mLastError) );
    }

} // namespace FileSystem