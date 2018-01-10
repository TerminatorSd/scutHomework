# scutHomework
华南理工大学助教期末一键整理实验作业（for ubuntu）

- 首先制作一份学生学号和姓名清单，格式如下，学号为12位，姓名任意，注意去掉其他多余的空格或回车
```
201565485231 张三
201565485231 李四
```
- 清单命名为list.txt，并记住其路径
- 编辑/src/main.cpp, 修改listFile为清单路径，dirRoot为你想将作业放置到的路径（会在该路径下为每个学生创建一个单独的文件夹）
```
char* listFile = "/home/siudong/list.txt";
char* dirRoot = "/home/siudong/result";
std::vector< std::pair<string, string> > list;
```
- cd /build
- cmake ..
- make
- ./cmakeTest
- 每次执行过后需要更改src目录和newName的值以便将多次实验分次放入每个学生对应的文件夹中，当然也可以一次遍历多次实验，一次放入，懒得搞了……
```
char* src = "/home/siudong/daji/exp10";
char* dst = "/home/siudong/result";
string newName = "实验10 Flash cs4";

```
