#include"WorkManager.h"
WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1、文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，内容为空
	char op;
	//读取文件中第一个位置的数
	ifs >> op;
	//读取文件第一个位置即末尾位置，则文件为空
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		//初始化人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//3、文件存在，内容不为空，并记录数据
	int num = 0;
	num = this->get_EmpNum();
	cout << "当前文件中记录职工人数有" <<" "<< num <<" "<< "人" << endl;
	this->m_EmpNum = num;

	//开辟数组空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中
	this->init_Emp();
}
//展示菜单函数
void WorkManager::Show_Menu()
{
	cout << "欢迎使用职工管理系统!!!" << endl;
	cout << "0.退出管理系统" << endl;
	cout << "1,增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7,清空所有文档" << endl;
	cout << endl;
}
//退出系统函数
void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用本系统" << endl;
	system("pause");
	exit(0);//退出程序
}
//添加职工
void WorkManager::Add()
{
	cout << "请输入添加职工的人数: " << endl;
	//保存用户的输入量
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算添加新空间大小
		//新空间大小=原来记录人数+新增人数
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原本数组里的数据传入到新数组里
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0;i < addNum;i++)
		{
			int id;
			string name;
			int departid;
			cout << "请输入第 " << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			while (true)
			{
				int ret = this->IsExist(id);
				if (ret != -1)
				{
					cout << "该职工编号已存在，请重新输入一个编号" << endl;
					cin >> id;
				}
				else
				{
					break;
				}
			}
			cout << "请输入第 " << i + 1 << "个新职工名字：" << endl;
			cin >> name;

			cout << "请选择该职工岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> departid;
			Worker* worker = NULL;
			switch (departid)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			if (worker == NULL)
			{
				i--;
				cout << "岗位输入有误，请重新输入" << endl;
				continue;
			}
			//将创建职工职责保存到新数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//更新文件内容不为空
		this->m_FileEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
		//保存数据到文件中
		this->Save();
	}
	else
	{
		cout << "输入有误，请重新输入" << endl;
	}
	//按任意键，清屏
	system("pause");
	system("cls");
}
//保存文件
void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将每个人的信息写入
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DepartId << endl;
	}
	ofs.close();
}
//统计文件中的人数
int WorkManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败，请重新尝试" << endl;
		return 0;
	}
	int id;
	string name;
	int departid;
	int num = 0;
	//统计人数
	while (ifs >> id && ifs >> name && ifs >> departid)
	{
		num++;
	}
	return num;
}

//初始化员工
void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int departid;
	int index=0;
	while (ifs >> id && ifs >> name && ifs >> departid)
	{
		Worker* worker = NULL;
		if (departid == 1)
		{
			worker = new Employee(id, name, departid);
		}
		else if (departid == 2)
		{
			worker = new Manager(id, name, departid);
		}
		else
		{
			worker = new Boss(id, name, departid);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}

//显示职工
void WorkManager::show_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或者为空文件" << endl;
	}
	else
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除的编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		//职工存在，删除index位置上的职工
		if (index != -1)
		{
			for (int i = index;i < this->m_EmpNum - 1;i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			//更新数组中记录人员的数量
			this->m_EmpNum--;
			//数据同步到文件中
			this->Save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在，存在返回其位置，不存在返回-1
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_id== id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号: " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);;
		if ( ret != -1)
		{
			delete this->m_EmpArray[ret];
			int new_id;
			string new_name;
			int new_departid;
			cout << "查到：" << id << "号职工，请输入新信息" << endl;

			cout << "请输入新id" << endl;
			cin >> new_id;

			cout << "请输入新名字" << endl;
			cin >> new_name;

			cout << "请输入新岗位" << endl;
			cout << "请选择该职工岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> new_departid;

			Worker* worker = NULL;
			if (new_departid == 1)
			{
				worker = new Employee(new_id, new_name, new_departid);
			}
			else if (new_departid == 2)
			{
				worker = new Manager(new_id, new_name, new_departid);
			}
			else
			{
				worker = new Boss(new_id, new_name, new_departid);
			}
			//更新数据到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;
			//保存到文件中
			this->Save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkManager::find_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入想要查询职工的姓名" << endl;
			cin >> name;
			//判断此人是否存在
			bool flag = false;
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" 
						 << this->m_EmpArray[i]->m_id 
						 << "号职工信息如下" << endl;
					flag = true;
					//调用显示查找人员的信息
					this->m_EmpArray[i]->ShowInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}

		}
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkManager::Sort_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int select;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			//声明最小值或者最大值下标
			int minORmax = i;
			for (int j = i + 1;j < this->m_EmpNum;j++)
			{
				//升序
				if (select == 1)
				{
					if (this->m_EmpArray[minORmax]->m_id >this->m_EmpArray[j]->m_id)
					{
						minORmax = j;
					}
				}
				//降序
				else
				{
					if (this->m_EmpArray[minORmax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minORmax = j;
					}
				}
			}
			if (i != minORmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minORmax];
				this->m_EmpArray[minORmax] = temp;
			}
		}
		cout << "排序成功，排序后的结果为：" << endl;
		this->Save();
		this->show_Emp();
	}
}

//清空文件
void WorkManager::Clean_file()
{
	cout << "确认清除文件？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		//删除堆区的每一个职工对象 
		if (this->m_EmpNum != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[]this->m_EmpArray;
			this->m_EmpNum = NULL;
			this->m_EmpNum = 0;
			this->m_FileEmpty = true;
		}
		cout << "清除成功！" << endl;
	}
	system("pause");
	system("cls");
}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}