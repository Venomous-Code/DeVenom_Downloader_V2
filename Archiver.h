#pragma once
#include <archive.h>
#include <archive_entry.h>
#include <iostream>
#include <string>
#include "Logging.h"
#include <filesystem>
#include <fstream>
#include <tuple>
#include <vector>

namespace PackageInstaller {
class Archiver {
		public:
    void ArchiverInit(const char* archiveName,
                      unsigned int fileType);



	   private:
    Logging Logs;
	std::vector<std::string> allFilesData;
    std::vector<size_t> allFilesSizes;
     std::vector<std::string> FilesNames;

	std::tuple<std::vector<std::string>, std::vector<size_t>,std::vector<std::string>> AddDirectoryToArchive();

	};

}  // namespace PackageInstaller