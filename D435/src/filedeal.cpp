#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <stdio.h> 
#include <sstream>
#include "filedeal.h"
using namespace std;

// 扫描路径下的文件
vector<string> getFile(string path)
{
    struct dirent *ptr;    
    DIR *dir;
//     string PATH = PATH_SCAN_COLOR;
    string PATH = path;

    dir=opendir(PATH.c_str()); 
    vector<string> files;    
    while((ptr=readdir(dir))!=NULL)
    {
        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
            continue;
	files.push_back(ptr->d_name);		
    }
    closedir(dir);
    return files;
}

// 将int类型转为string类型
string Int_to_String(int n)
{
  std::ostringstream stream;
  stream<<n; //n为int类型
  return stream.str();
}

// 清空扫描路径下的文件，进行照片的存放
void Clear_file(string path)
{
    vector<string> files_clear=getFile(path);
    if(files_clear.size()>0)
    {
	for(int i=0;i<files_clear.size();i++)
	{
	    string st_cl=path+files_clear[i];
	    char*p=(char*)st_cl.data();
	    if(remove(p))
	    {
		cout<<"fail"<<endl;
	    }
	}  
    }
    cout<<path<<" clear ok"<<endl;
}

void Delete_file(string path,string suffix,int num)
{
//     string savePath = path+Int_to_String(num)+".jpg";
    string savePath = path+Int_to_String(num)+suffix;

    char*p=(char*)savePath.data();
    if(remove(p))
    {
	cout<<"fail  "<<num<<endl;
    }
}
