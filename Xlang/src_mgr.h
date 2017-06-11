/*

	JaeHun Ahn 안재훈 <dark_woah@naver.com>

	XLang Src_mgr.h

	소스코드 매니저

*/

#ifndef SRC_MGR_H
#define SRC_MGR_H

#include <vector>
#include <memory>

namespace xlang
{
	class SourceManager
	{
	public:
		SourceManager() {}
		~SourceManager() {}

		bool Open(const char *src_path)
		{
			FILE *fp;
			if(fopen_s(&fp, src_path, "r"))
			{
				return false;
			}

			std::shared_ptr<FILE> file_closer(fp, [](FILE *f) {::fclose(f); });

			fseek(fp, 0, SEEK_END);
			int file_size = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			src_contents_.reserve(file_size);
			if (!fread_s(&src_contents_[0], file_size, 1, file_size, fp))
			{
				printf("11 \r\n");
				return false;
			}
			return true;
		}

		unsigned char *GetSourceBuffer()
		{
			return &src_contents_[0];
		}

	private:
		std::vector<unsigned char> src_contents_;
	};
}



#endif // SRC_MGR_H
