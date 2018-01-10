#include <stdio.h>
#include <iostream>  
#include "copy_dir.h"  
#include "functions.h"
using namespace std;  
  
int main(int argc, char *argv[])  
{  

	// make empty directories 
	char* listFile = "/home/siudong/list.txt";
	char* dirRoot = "/home/siudong/result";
	std::vector< std::pair<string, string> > list;

	readList(listFile, list);
	makeDir(dirRoot, list);
 
 	// for every member in list, bianli every experiment directories and do copy(renmae)
    char* src = "/home/siudong/daji/exp6";  
    char* dst = "/home/siudong/result";  
    string newName = "实验6 PPT";

    // string str1 = "/home/siudong/daji/exp4/201736461053_安文姣";
    // string str2 = "/home/siudong/result/安文姣";
    
    CopyDir cd; 
    cd.copy_from_to(src, dst, newName, list);  
    // cd.copy(str1, str2);

    return 0;  
}  