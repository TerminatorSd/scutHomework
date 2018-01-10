#include <stdio.h>
#include <sys/stat.h> 
#include <string.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
using namespace std; 

void readList(char *path, std::vector< std::pair<string, string> >& res)
{
    int i, k = 0;
    FILE *fp;
    char buf[1024];
    char s_no[15];
    char s_name[15];
    if(fp = fopen(path, "r"))
    {
        while(!feof(fp))
        {
            fgets(buf, 1024, fp);
            //read student no
            for(i = 0; i < 12; i++)
                s_no[i] = buf[i];
            s_no[i] = '\0';
            //read student name
            for(i = 0; ; i++)
            {
                if(buf[13+i] == ' ')
                {
                    // cout <<"spcae"<<endl;
                    continue;
                }
                else 
                {
                    if(buf[13+i] == '\n')
                    {
                        break;
                    }
                    s_name[i] = buf[13+i];
                }    
            }
            s_name[i] = '\0';
            res.push_back(std::make_pair(s_no, s_name));
        }
    }
    else 
        cout<<"Open file "<<path<<"failed.";
    fclose(fp);
}
void makeDir(char *dir, std::vector< std::pair<string, string> > res)
{
    for(int i = 0; i < res.size(); i++)
    {
        string str = dir;
        string str2 = "/" + res[i].second;
        str += str2;
        cout<<str<<endl;
        mkdir(str.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}
