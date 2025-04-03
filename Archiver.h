#pragma once
#include <archive.h>
#include <archive_entry.h>
#include <iostream>
#include <string>
#include "Logging.h"

namespace PackageInstaller {
class Archiver {
		public:
    void ArchiverInit();


	   private:
    Logging Logs;
	};

}  // namespace PackageInstaller