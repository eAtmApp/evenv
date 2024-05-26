#pragma once

using namespace easy;

class evenv
{
private:
	eString _exe_name;
	eString _exe_dir;

	bool	_is_agent_run = false;

	//conda���⻷��
	eStringArray _arr_conda_envs;
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
		_arr_conda_envs.clear();

		eString conda_env_file = process.get_env("USERPROFILE");
		if (conda_env_file.empty()) conda_env_file = process.get_env("HOMEDRIVE") + process.get_env("USERPROFILE");
		VERIFY(!conda_env_file.empty(), "��ȡ�û��ļ���ʧ��!");
		conda_env_file += "\\.conda\\environments.txt";
		if (!util::is_file_exists(conda_env_file))
		{
			console.warn("û���ҵ�conda���⻷���ļ�:{}", conda_env_file);
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
			console.warn("condaû�а�װ���⻷��");
			return false;
		}

		return true;
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
		read_conda_envs();

		do
		{
			console.clear();
			console.log("ѡ��ǰĿ¼({})���⻷��:",process.cwd(true));
			console.log("");
			console.printf(_arr_conda_envs, "{} - (conda){}\r\n", 1);
			console.log("");
			

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
