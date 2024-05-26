// eVirtualEnv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <easylib.h>
#include "evenv.hpp"

evenv ev;

int main()
{
	//控制台窗口不显示时间
	console.set_console_time(false);

/*
	if (ev.is_agent_run())
	{
		ev.del_evenv_envpath();
		VERIFY(0, "代理运行.");
	}
	else {
		console.log("正常运行");
	}*/

	ev.run();

	process.auto_proxy_input([](eString& cmdStr)
		{

			return true;
		});

	return 0;
}

