#ifndef COPYDIR_H  
#define COPYDIR_H  
  
#include <string>  
#include <vector> 
#include <iostream>
using namespace std; 
  
class CopyDir  
{  
public:  
    CopyDir();  
  
    void copy(const std::string& srcDirPath, const std::string& desDirPath);  
    void copy_from_to(char* dst, char* src, std::string newName, std::vector< std::pair<string, string> > list);
    void print_vector(std::vector<string> str);
  
public:  
  
private:  
    bool make_dir (const std::string& pathName);  
//    bool mkdir (char const* pathname/*, mode_t mode*/);  
    bool get_src_files_name(std::vector<std::string>& fileNameList);  
    void do_copy(const std::vector<std::string>& fileNameList);  
    void bianLi(char *dirc, std::vector<string>& doc);
  
private:  
    std::string srcDirPath, desDirPath;  
  
  
};  
  
#endif // COPYDIR_H 