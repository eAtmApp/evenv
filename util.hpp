#pragma once

using namespace easy;

struct env_item {
	std::string name;
	std::string path;
/*
	bool operator==(const env_item& other) const {
		return true;
	}*/
};

class evenv
{
private:
	eString _exe_name;
	eString _exe_dir;

	bool	_is_agent_run = false;

	//conda���⻷��
	eVector<env_item> _envs_conda;
	//eStringArray
public:
	evenv()
	{
		_exe_name = process.exe_name().tolower();
		_exe_dir = process.exe_dir().tolower();

		//�ж��Ƿ��������
		//��������:�����в���Ϊȫ·��,��ִ���ļ���Ϊevenv,��ǰĿ¼Ϊ��ִ�г�������Ŀ¼��
		{
			if (_exe_name != "evenv"
				&& _exe_dir.compare_icase(process.cwd()))
			{
				_is_agent_run = true;
			}
		}
	}

	//��ȡconda���⻷��
	bool	read_conda_envs()
	{
		eString conda_env_file = process.get_env("USERPROFILE");
		if (conda_env_file.empty()) conda_env_file = process.get_env("HOMEDRIVE") + process.get_env("USERPROFILE");
		VERIFY(!conda_env_file.empty(), "��ȡ�û��ļ���ʧ��!");
		conda_env_file += "\\.conda\\environments.txt";
		if (!util::is_file_exists(conda_env_file))
		{
			return false;
		}
	}

	//�ж��Ƿ��������
	bool	is_agent_run()
	{
		return _is_agent_run;
	}

	//��event����Ŀ¼�ӽ��̻�������path��ɾ��
	void	del_evenv_envpath()
	{
		eString pathStr = process.get_env("PATH");
		pathStr = delete_evenv_path_string(pathStr);
		process.set_env("PATH", pathStr);
	}

	//��������
	void	run()
	{
		do
		{
			std::cout << "���õ�ǰĿ¼Ĭ�ϻ�������:\r\n";

		} while (true);
	}

private:

	//ɾ�����������ַ����е�evenvĿ¼
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
