#include"Employee.h"
Employee::Employee(int id, string name, int departid)
{
	this->m_id = id;
	this->m_Name = name;
	this->m_DepartId = departid;
}
//显示个人信息
void Employee::ShowInfo()
{
	cout << "职工编号: " << this->m_id
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位编号: " << this->GetDepartName()
		<< "\t岗位职责: 完成经理交给的任务" << endl;
}
//获取岗位名称
string Employee::GetDepartName()
{
	return string("员工");
}