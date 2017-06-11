/*

	JaeHun Ahn <dark_woah@naver.com>

	XLang Main File

*/

#include <stdio.h>

#include <vector>
#include <string>

#include "lexer.hpp"
#include "src_mgr.h"

class CommandLineParser
{
public:
	CommandLineParser() {}
	~CommandLineParser(void) {}

	bool __stdcall Initialize(int cmd_num, char *argv[])
	{
		for (int i = 1; i < cmd_num; i++)
		{
			if (argv[i][0] != '-')
				return false;
			cmd_vec_.emplace_back(argv[i]);
		}
		cmd_num_ = cmd_num - 1;
		return true;
	}

	const char *GetData(int idx) const
	{
		if (cmd_num_ < idx)
			return nullptr;

		return cmd_vec_[idx].c_str();
	}

	int GetDataSize() const { return cmd_num_; }

private:
	int cmd_num_;
	std::vector<std::string> cmd_vec_;
};

int main(int argc, char *argv[])
{
	/*CommandLineParser parser;
	if (!parser.Initialize(argc, argv))
	{
		printf("parser initialize failed \r\n");
		return 1;
	}

	for (int i = 0; i < parser.GetDataSize(); i++)
	{
		printf("%s \r\n", parser.GetData(i));
	}*/

	printf("%s \r\n", argv[1]);
	xlang::SourceManager src_mgr;
	
	if (src_mgr.Open(argv[1]))
	{
		printf("%s \r\n", src_mgr.GetSourceBuffer());
	}

	return 0;
}