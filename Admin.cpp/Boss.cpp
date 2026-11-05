#include"Boss.h"
Boss::Boss(int id, string name, int departid)
{
	this->m_id = id;
	this->m_Name = name;
	this->m_DepartId = departid;
}
//显示个人信息
void Boss::ShowInfo()
{
	cout << "职工编号: " << this->m_id
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位编号: " << this->GetDepartName()
		<< "\t岗位职责: 管理公司事务" << endl;
}
//获取岗位名称
string Boss::GetDepartName()
{
	return string("老板");
}