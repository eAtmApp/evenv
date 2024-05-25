// eVirtualEnv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <easylib.h>
#include "util.hpp"

evenv ev;

int main()
{
	ev.del_evenv_envpath();
	if (ev.is_agent_run())
	{

	}

	return 0;
}

