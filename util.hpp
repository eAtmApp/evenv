#pragma once

using namespace easy;

class evenv
{
private:

public:
	evenv()
	{

	}
	//�ж��Ƿ��������
	//�������Ϊ��������:
	//*******************�����в���Ϊȫ·��
	//*******************��ִ���ļ���Ϊevenv
	//*******************��ǰĿ¼Ϊ��ִ�г�������Ŀ¼��
	bool	is_agent_run()
	{
		eString extName = process.exe_name().tolower();
		if (extName == "evenv") return false;

		eString exeDir = process.exe_dir();
		eString curDir = process.cwd();
		if (exeDir.compare_icase(curDir)) return false;

		return false;
	}

	//��event����Ŀ¼�ӽ��̻�������path��ɾ��
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
