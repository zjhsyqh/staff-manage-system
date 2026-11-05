#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;
class Manager :public Worker
{
public:
	Manager(int id, string name, int departid);
	//显示个人信息
	void ShowInfo();
	//获取岗位名称
	string GetDepartName();
};