#include "copy_dir.h"  
  
#include <stdio.h>
#include <iostream>  
#include <fstream>  
#include <cstring>
  
#include <dirent.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <pwd.h>  

  
CopyDir::CopyDir()  
{  
  
}  
  
void CopyDir::copy(const std::string& srcDirPath, const std::string& desDirPath)  
{  
    //cout<<"come into copy..";
    this->srcDirPath = srcDirPath;  
    std::string srcDir;  
 
    int n = 0;  
    while (srcDirPath.find('/', n) != std::string::npos)  
    {  
        n = srcDirPath.find('/', n) + 1;  
    }  
    if(n == 0)  
    {  
        std::cout << "src path error" << std::endl;  
        return;  
    }  
    srcDir = srcDirPath.substr(n-1, srcDirPath.size());  
   
    this->desDirPath = desDirPath + srcDir;  
  
    if(!make_dir(this->desDirPath))  
    {  
        return;  
    }  
  
    std::vector<std::string> fileNameList;  
    if(!get_src_files_name(fileNameList))  
    {  
        return;  
    }  
  
    if(fileNameList.empty())  
    {  
        std::cout << "src dir is empty" << std::endl;  
        return;  
    }  
  
    do_copy(fileNameList);  
   // cout<<"leave copy..";

}  
  
bool CopyDir::make_dir (const std::string& pathName)  
{  

    if(::mkdir(pathName.c_str(), S_IRWXU | S_IRGRP | S_IXGRP) < 0)  
    {  
        std::cout << "create path error" << std::endl;  
        return false;  
    }  
  
    return true;  
}  
  
bool CopyDir::get_src_files_name(std::vector<std::string>& fileNameList)  
{  
 
    DIR *dir;  
    struct dirent *ptr;  
  
    if ((dir=opendir(this->srcDirPath.c_str())) == NULL)  
    {  
        std::cout << this->srcDirPath << " not found" << std::endl;  
        return false;  
    }  
  
    while ((ptr=readdir(dir)) != NULL)  
    {  
        if((ptr->d_name == ".") || (ptr->d_name == ".."))  //current / parent  
            continue;  
        else if(ptr->d_type == 8)  //file  
            fileNameList.push_back(ptr->d_name);  
        else if(ptr->d_type == 10)  //link file  
            continue;  
        else if(ptr->d_type == 4)  //dir  
            fileNameList.push_back(ptr->d_name);  
    }  
    closedir(dir);  
  
    return true;  
  
}  
  
void CopyDir::do_copy(const std::vector<std::string> &fileNameList)  
{ 
    //cout<<"come into do_copy..";

#pragma omp parallel for  
    for (int i = 2; i < fileNameList.size(); i++)  
    {  
        std::string nowSrcFilePath, nowDesFilePath ;  
 
        nowSrcFilePath = this->srcDirPath + "/" + fileNameList.at(i);  
        nowDesFilePath = this->desDirPath + "/" + fileNameList.at(i);  
  
        std::ifstream in;  
        in.open(nowSrcFilePath.c_str());  
        if(!in)  
        {  
            std::cout << "open src file : " << nowSrcFilePath << " failed" << std::endl;  
            continue;  
        }  
  
        std::ofstream out;  
        out.open(nowDesFilePath.c_str());  
        if(!out)  
        {  
            std::cout << "create new file : " << nowDesFilePath << " failed" << std::endl;  
            in.close();  
            continue;  
        }  
  
        out << in.rdbuf();  
  
        out.close();  
        in.close();  
    }  
    //cout<<"leave do_copy..";

}  


void CopyDir::bianLi(char *dirc, std::vector<string>& doc)
{
    DIR *dp;
    struct dirent *dirp;
    doc.clear();

    if( (dp=opendir(dirc)) ==NULL)
        printf("can't open %s",dirc);
    while ((dirp=readdir(dp))!=NULL)
    {
        // if(dirp->d_name != "\n")
        doc.push_back(dirp->d_name);
        // printf("%s\n",dirp->d_name);
    }
    printf("\n");
    closedir(dp);
}

void CopyDir::copy_from_to(char* src, char* dst, string newName, std::vector< std::pair<string, string> > list)
{
    std::vector<string> dst_dirs;
    std::vector<string> src_dirs;
    string src_path = "";
    string dst_path = "";
    string dstName = "";
    string tag = "/";
    int srcLen = 0;
    
    // cout<<"copy_from_to"<<endl;
    // print_vector(src_dirs);

    // cout<<list.size()<<endl;
    // for(int w = 0; w < list.size(); w++)
    // {
    //     cout<<w<<" "<<list[w].first<<" "<<list[w].second;
    // }
    // cout<<endl;

    for(int i = 0; i < list.size(); i++)
    {
        int j = 0;

        // bianli src
        bianLi(src, src_dirs);

        // print_vector(src_dirs);

        // cout<<"src_dirs:"<<src_dirs.size()<<endl;
        srcLen = src_dirs.size();
    
        for(j = 2; j < srcLen; j++)
        {
            // find the folder name containing the student's number
            if((list[i].first.find(src_dirs[j].substr(0, 12))) != -1)
            {
                src_path += src + tag + src_dirs[j];
                dst_path += dst + tag + list[i].second;
                
                // cout<<src_path<<endl;
                
                copy(src_path, dst_path);  
                dstName = dst_path + tag + newName;
                dst_path += tag + src_dirs[j];
                cout<<dst_path<<endl;
                cout<<dstName<<endl;
                rename(dst_path.c_str(), dstName.c_str());
            }

            src_path = "";
            dst_path = "";
        }
        if(j == list.size()) 
        {
            cout<<list[i].second<<"failed!";
        }
    }
}

void CopyDir::print_vector(std::vector<string> str)
{
    cout<<str.size()<<endl;
    for(int i = 0; i < str.size(); i++)
    {
        cout<<str[i]<<" ";
    }
    cout<<endl;
}
