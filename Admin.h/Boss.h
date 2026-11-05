#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;
class Boss :public Worker
{
public:
	Boss(int id, string name, int departid);
	//显示个人信息
	void ShowInfo();
	//获取岗位名称
	string GetDepartName();
};