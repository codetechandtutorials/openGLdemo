#pragma once
#include <string>
#include <fstream>

const char* extract_prog_name(const char* full)
{
	std::string p1 = full;
	static std::string p2;
	p2.clear();
	p2 = p1.substr(
		p1.find_last_of("/\\") + 1,  // from after last slash
		(p1.length() - p1.find_last_of("/\\")) - (p1.length() - (p1.find_last_of(".")) + 1)  // up to last dot
	);
	return p2.c_str();
}

#ifdef _DEBUG
void write_log(const char* msg)
{
	std::ofstream logs;
	logs.open("our_log.txt", std::ofstream::app | std::ofstream::out);
	logs << msg << '\n';
	logs.close();
}
#else
void write_log(const char* msg)
{
}
#endif