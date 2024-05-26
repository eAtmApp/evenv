// eVirtualEnv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <easylib.h>
#include "evenv.hpp"
#include <type_traits>

evenv ev;

/*
std::ostream& operator<<(std::ostream& os, const env_item& d)
{
	return os << "XXX";
}*/


int main()
{
	ev.del_evenv_envpath();

	//static_assert(is_equality_comparable<env_item>::value, "不支持流");

	console.log("进入evenv...");
	if (ev.is_agent_run())
	{
		console.log("代理运行...");
		ev.del_evenv_envpath();
		VERIFY(0, "代理运行.");
	}
	else {
		console.log("正常运行");
	}

	process.auto_proxy_input([](eString& cmdStr)
		{

			return true;
		});

	return 0;
}

