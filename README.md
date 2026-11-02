# staff-manage-system
基于cpp多态的职工管理系统
# 基于C++多态的职工管理系统
黑马C++学习项目，面向对象综合练手项目

## 📖 项目简介
本系统使用C++实现，利用继承、抽象类、多态区分三类职工：普通员工、经理、老板。
- 普通员工：完成经理分配的任务
- 经理：接收老板任务，向下分配任务给员工
- 老板：统筹管理公司全部事务

数据持久化保存到 `staff.txt`，程序重启数据不丢失。

## ✨ 功能清单
- 1. 退出管理程序
- 2. 批量添加职工信息
- 3. 展示全部职工信息
- 4. 按职工编号删除职工
- 5. 按职工编号修改信息
- 6. 按编号 / 姓名查找职工
- 7. 按职工编号升序/降序排序
- 8. 清空文件（二次确认，防止误删）

## 🛠️ 技术要点
- 面向对象：类、继承、纯虚函数（抽象基类）、多态
- STL：vector 容器存储职工指针
- 文件IO：ifstream / ofstream 读写文本文件
- 算法：查找、删除、sort排序
- 菜单交互，循环选择功能

## 📂 项目结构
staff-manage-system/

├── README.md

├── worker.h

├── worker.cpp

├── workManager.h

├── workManager.cpp

└── main.cpp

## 🚀 编译运行
```bash
g++ main.cpp worker.cpp workManager.cpp -o staff.exe
./staff.exe

## 💻 开发环境
- VS Code + MinGW-w64 (g++)
- Git & GitHub
