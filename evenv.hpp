#pragma once

using namespace easy;

class evenv
{
private:
	eString _exe_name;
	eString _exe_dir;

	bool	_is_agent_run = false;

	//conda虚拟环境
	eStringArray _arr_conda_envs;
public:
	evenv()
	{
		_exe_name = process.exe_name().tolower();
		_exe_dir = process.exe_dir().tolower();

		//判断是否代理运行
		//正常运行:命令行参数为全路径,可执行文件名为evenv,当前目录为可执行程序所在目录的
		{
			if (_exe_name != "evenv"
				&& _exe_dir.compare_icase(process.cwd()))
			{
				_is_agent_run = true;
			}
		}
	}

	//读取conda虚拟环境
	bool	read_conda_envs()
	{
		_arr_conda_envs.clear();

		eString conda_env_file = process.get_env("USERPROFILE");
		if (conda_env_file.empty()) conda_env_file = process.get_env("HOMEDRIVE") + process.get_env("USERPROFILE");
		VERIFY(!conda_env_file.empty(), "获取用户文件夹失败!");
		conda_env_file += "\\.conda\\environments.txt";
		if (!util::is_file_exists(conda_env_file))
		{
			console.warn("没有找到conda虚拟环境文件:{}", conda_env_file);
			return false;
		}
		
		eString bodyStr=util::read_file(conda_env_file);
		if (bodyStr.empty())
		{
			return true;
		}
		bodyStr.replaceAll("\r", "");
		_arr_conda_envs=bodyStr.split_string("\n", true);

		if (_arr_conda_envs.empty())
		{
			console.warn("conda没有安装虚拟环境");
			return false;
		}

		return true;
	}

	//判断是否代理运行
	bool	is_agent_run()
	{
		return _is_agent_run;
	}

	//将event所在目录从进程环境变量path中删除
	void	del_evenv_envpath()
	{
		eString pathStr = process.get_env("PATH");
		pathStr = delete_evenv_path_string(pathStr);
		process.set_env("PATH", pathStr);
	}

	//运行命令
	void	run()
	{
		read_conda_envs();

		do
		{
			console.clear();
			console.log("选择当前目录({})虚拟环境:",process.cwd(true));
			console.log("");
			console.printf(_arr_conda_envs, "{} - (conda){}\r\n", 1);
			console.log("");
			

		} while (true);
	}

private:

	//删除环境变量字符串中的evenv目录
	eString	delete_evenv_path_string(eString& pathStr)
	{
		eString exeDir = process.exe_dir().tolower();

		auto pathItems = pathStr.split_string(";");
		eStringArray arrayItems;
		pathItems.forEach([&](eString& oldStr)
			{
				if (oldStr.empty()) return;

				eString tmpStr(oldStr);
				tmpStr.tolower();
				tmpStr.replaceAll("\\\\", "\\");
				tmpStr.replaceAll("/", "\\");
				if (tmpStr.back() != '\\') tmpStr += "\\";

				if (exeDir != tmpStr)
				{
					arrayItems.push_back(oldStr);
				}

			});

		return arrayItems.join(";");
	}
};
