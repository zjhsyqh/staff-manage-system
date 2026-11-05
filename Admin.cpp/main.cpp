#include<iostream>
#include"WorkManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
using namespace std;
int main()
{
	/*Worker* worker=NULL;
	worker = new Employee(1, "张三", 1);
	worker->ShowInfo();
	delete worker;

	worker = new Manager(2, "李四", 2);
	worker->ShowInfo();
	delete worker;

	worker = new Boss(3, "sb", 3);
	worker->ShowInfo();
	delete worker;*/
	WorkManager p;
	int choice;
	while (true)
	{
		//调用展示菜单成员函数
		p.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: //退出系统
			p.ExitSystem();
			break;
		case 1: //增加职工
			p.Add();
			break;
		case 2: //显示职工
			p.show_Emp();
			break;
		case 3: //删除职工
			p.Del_Emp();
			break;
		case 4: //修改职工
			p.Mod_Emp();
			break;
		case 5: //查找职工
			p.find_Emp();
			break;
		case 6: //排序职工
			p.Sort_Emp();
			break;
		case 7: //清空文档
			p.Clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}