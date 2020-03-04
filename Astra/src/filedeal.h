#ifndef __FILEDEAL_H
#define __FILEDEAL_H
#include <vector>
#include <string>
using namespace std;
// 存放图片的路径
#define PATH_SCAN_COLOR "/home/supeng/Program/C++/JDX/getimage/image/build/color"
#define PATH_SCAN_DEPTH "/home/supeng/Program/C++/JDX/getimage/image/build/depth"
// 扫描PATH_SCAN路径下的文件
vector<string> getFile(string path);
// 将int类型转为string类型
std::string Int_to_String(int n);
// 清空扫描路径下的文件，进行照片的存放
void Clear_file(string path);
// 删除指定路径下的jpg文件
void Delete_file(string path,int num);


#endif

