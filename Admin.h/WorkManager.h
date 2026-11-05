#pragma once
#include<iostream>
#include<fstream>
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h" 
#define FILENAME "empFile.txt"
using namespace std;
class WorkManager
{
public:
	WorkManager();

	//展示菜单函数
	void Show_Menu();

	//退出系统函数
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add();

	//保存文件
	void Save();

	//判断文件是否为空
	bool m_FileEmpty;

	//读取文件
	void Read();

	//统计文件中的人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在，存在返回其位置，不存在返回-1
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_file();
	~WorkManager();
};