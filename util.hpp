#pragma once

using namespace easy;

class evenv
{
private:

public:
	evenv()
	{

	}
	//判断是否代理运行
	//以下情况为正常运行:
	//*******************命令行参数为全路径
	//*******************可执行文件名为evenv
	//*******************当前目录为可执行程序所在目录的
	bool	is_agent_run()
	{
		eString extName = process.exe_name().tolower();
		if (extName == "evenv") return false;

		eString exeDir = process.exe_dir();
		eString curDir = process.cwd();
		if (exeDir.compare_icase(curDir)) return false;

		return false;
	}

	//将event所在目录从进程环境变量path中删除
	void	del_evenv_envpath()
	{
		eString pathStr = process.get_env("PATH");
		auto pathItems = pathStr.split(";");
		process.set_env("PATH", pathStr);
	}

private:
	eString	deleteCwdPath(eString &pathStr)
	{

	}
};
