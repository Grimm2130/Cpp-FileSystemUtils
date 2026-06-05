#if !defined(__FILE_SYS_UTILS_FILE_TESTER_H__)
#define __FILE_SYS_UTILS_FILE_TESTER_H__

#include "CppTemplates/ITest.h"
#include <string>
#include "File.h"
#include <cassert>

namespace FileSystemUtils
{
    namespace Tests
    {
        class File : public ::Tests::ITest
        {
        public:
            File() : ITest(){}

            ~File(){};

            bool RunTests() override
            {
                printf("Tests::File Testing...\n");
                if( TestExists(sFilePath))
                {
                    if( TestCanRead(sFilePath) )
                    {
                        if( TestCanWrite(sFilePath) )
                        {
                            if( TestCanExecute(sFilePath) )
                            {
                                if(TestReads(sFilePath))
                                {
                                    if(TestWrites(sFilePath))
                                    {
                                        printf("Tests::File All tests Passed\n");
                                        return true;
                                    }
                                    return true;
                                }
                            }
                        }
                    }
                }

                return false;
            }
        private:
            
            static const std::string Phrase;
            const char* sFilePath = "/home/ubuntu/Projects/FileSystemUtils/Tests/TestFiles/TestFile.txt";

            static inline bool TestExists( const char* file )
            {
                if(::FileSystemUtils::File::Exists(file))
                {
                    return true;
                }
                else
                {
                    printf("Tests::File::TestExists() Failed\n");
                    return false;
                }
            }

            static inline bool TestCanRead( const char* file )
            {
                if(::FileSystemUtils::File::CanRead(file))
                {
                    return true;
                }
                else
                {
                    printf("Tests::File::TestCanRead() Failed\n");
                    return false;
                }
            }

            static inline bool TestCanWrite( const char* file )
            {
                if(::FileSystemUtils::File::CanWrite(file))
                {
                    return true;
                }
                else
                {
                    printf("Tests::File::TestCanWrite() Failed\n");
                    return false;
                }
            }

            static inline bool TestCanExecute( const char* file )
            {
                if(::FileSystemUtils::File::CanExecute(file) == false)
                {
                    return true;
                }
                else
                {
                    printf("Tests::File::TestCanExecute() Failed\n");
                    return false;
                }
            }

            static inline bool TestReads(const char *file )
            {
                if(::FileSystemUtils::File::Read(file) == Phrase[0])
                {
                    if(::FileSystemUtils::File::ReadUntil(file, EOF) == Phrase )
                    {
                        if(::FileSystemUtils::File::ReadAll(file) == Phrase )
                        {
                            return true;
                        }
                        else
                        {
                            printf("Tests::File::TestReads() Failed on ReadAll\n");
                        }
                    }
                    else
                    {
                        printf("Tests::File::TestReads() Failed on ReadUntil\n");
                    }
                }
                else
                {
                    printf("Tests::File::TestReads() Failed on Read\n");
                }

                return false;
            }

            static inline bool TestWrites(const char *file )
            {
                if( (::FileSystemUtils::File::Write(file, Phrase[0]) == 1) && ::FileSystemUtils::File::Read(file) == Phrase[0])
                {
                    if(::FileSystemUtils::File::Write(file, Phrase) == Phrase.size())
                    {
                        if(::FileSystemUtils::File::ReadAll(file) == Phrase )
                        {
                            return true;
                        }
                        else
                        {
                            printf("Tests::File::TestReads() Failed on Write('h')\n");
                        }
                    }
                }
                else
                {
                    printf("Tests::File::TestReads() Failed on Write('h')\n");
                }
                
                return false;
            }

            static inline bool TestAppends(const char *file )
            {
                
            }

            static inline bool TestCreate(const char *file )
            {

            }

            static inline bool TestDelete(const char *file )
            {

            }

            static inline bool TestCopy(const char *file )
            {

            }

            static inline bool TestMove(const char *file )
            {

            }

            static inline bool TestConcat(const char *file )
            {

            }

            static inline bool TestSize(const char *file )
            {

            }
        };

        const std::string File::Phrase = "Hello Chima";

    } // namespace Tests
    
}

#endif // __FILE_SYS_UTILS_FILE_TESTER_H__
