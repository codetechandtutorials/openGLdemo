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

const char* get_current_time()
{
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::string realTime = std::ctime(&now);

	// The 25th character has a '\n' which we do not want so we do this
        realTime[24] = NULL;

	return realTime.c_str();
}

#ifdef _DEBUG
template<typename... args>
void write_log(const char* msg, args&&... argv)
{
	std::ofstream logs;
	logs.open("our_log.txt", std::ofstream::app | std::ofstream::out);
	
	logs << "[" << get_current_time() << "] " << msg;
	(logs << ... << argv);
	logs << '\n';
	logs.close();
}
#else
template<typename... args>
void write_log(const char* msg, args&&... argv)
{
}
#endif
