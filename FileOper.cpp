#include <iostream>
#include <stdio.h>
#include <iostream>
#include "FileOper.h"
#include <ctype.h>

using namespace std;

string user_input;
string password = "84265";

int main(void)
{
	cout << "[智能函数运算训练工具]\t版本号：v-19.12.12" << endl;
	cout << "(c)2019 Cardinal Organization。保留所有权利。" << endl;
	cout << "Powered By Voidmatrix\tData:2019.12" << endl;

	cout << "\n请在下方输入所需计算的表达式，以 [;] 结尾：" << endl << "\n>>>";
	cin >> user_input;
	while (user_input != password)
	{
		cout << "\n输入格式错误，请尝试重新输入 ！" << endl << "\n>>>";
		cin >> user_input;
	}

	cout << "\n通过验证 ！" << endl;
	system("cls");

	cout << "\t<<<    指令索引    >>>\t" << endl;
	cout << "1.将PackageData.bin文件内容解包至./data/目录下；\n" << endl;
	cout << "2.将./data/目录下所有文件打包至PackageData.bin文件；\n" << endl;
	cout << "3.将./data/目录下所有文件删除；\n" << endl;
	cout << "4.退出程序 [将自动清空./data/目录]\n" << endl;
	cout << "9.获取全部指令介绍\n" << endl;
	
	while (user_input != "4")
	{
		cout << "\n>>>";
		cin >> user_input;

		if (user_input == "1")
		{
			cout << "\n请确认此操作会将./data/下现有内容覆盖，是否继续 ？\n\tY.继续\tN.取消" << endl << "\n";
			string confirm_input;
			cin >> confirm_input;
			if (confirm_input == "Y" || confirm_input == "y")
			{
				read_files_info();
				unpack_files();
			}
			else
			{
				continue;
			}	
		}
		else if (user_input == "2")
		{
			cout << "\n请确认./data/目录下文件为所要进行打包文件，是否继续 ？\n\tY.继续\tN.取消" << endl << "\n";
			string confirm_input;
			cin >> confirm_input;
			if (confirm_input == "Y" || confirm_input == "y")
			{
				get_all_files();
				package_files();
				write_files_info();
			}
			else
			{
				continue;
			}	
		}
		else if (user_input == "3")
		{
			cout << "\n请确认./data/目录下所有文件都将被删除，是否继续 ？\n\tY.继续\tN.取消" << endl << "\n";
			string confirm_input;
			cin >> confirm_input;
			if (confirm_input == "Y" || confirm_input == "y")
			{
				delete_files();
			}
			else
			{
				continue;
			}
		}
		else if (user_input == "4")
		{
			delete_files();
			break;
		}
		else if (user_input == "9")
		{
			cout << "\t<<<    指令索引    >>>\t" << endl;
			cout << "1.将PackageData.bin文件内容解包至./data/目录下；\n" << endl;
			cout << "2.将./data/目录下所有文件打包至PackageData.bin文件；\n" << endl;
			cout << "3.将./data/目录下所有文件删除；\n" << endl;
			cout << "4.退出程序 [将自动清空./data/目录]\n" << endl;
			cout << "9.获取全部指令介绍\n" << endl;
		}
		else
		{
			cout << "\n输入有误，尝试重新输入 [输入数字 '9' 获取全部指令介绍]" << endl;
		}
	}
}