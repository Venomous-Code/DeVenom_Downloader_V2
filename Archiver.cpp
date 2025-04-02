

#include "Archiver.h"

void PackageInstaller::Archiver::ArchiverInit() {

    archive* a = archive_write_new();
    if (!a) {
        std::cerr << "Error: Could not create archive writer." << std::endl;
    }

    if (archive_write_set_format_pax_restricted(a) != ARCHIVE_OK) {
        std::cerr << "Error setting format: " << archive_error_string(a)
                  << std::endl;
        archive_write_free(a);
    }

    if (archive_write_open_filename(a, "DeVenom_Downloader.tar") != ARCHIVE_OK) {
        std::cerr << "Error opening output file: " << archive_error_string(a)
                  << std::endl;
        archive_write_free(a);
    }

    struct archive_entry* entry = archive_entry_new();
    if (!entry) {
        std::cerr << "Error: Could not create archive entry." << std::endl;
        archive_write_free(a);
    }
    archive_entry_set_pathname(entry, "Data.txt");
    const char* fileData = "Hello, world!";
    size_t fileSize = std::strlen(fileData);
    archive_entry_set_size(entry, fileSize);      // File size in bytes.
    archive_entry_set_filetype(entry, AE_IFREG);  // Regular file.
    archive_entry_set_perm(entry, 0644);          // File permissions.

    if (archive_write_header(a, entry) != ARCHIVE_OK) {
        std::cerr << "Error writing header: " << archive_error_string(a)
                  << std::endl;
        archive_entry_free(entry);
        archive_write_free(a);
    }

    size_t bytesWritten = archive_write_data(a, fileData, fileSize);
    if (bytesWritten < 0) {
        std::cerr << "Error writing data: " << archive_error_string(a)
                  << std::endl;
        archive_entry_free(entry);
        archive_write_free(a);
    }

    if (archive_write_finish_entry(a) != ARCHIVE_OK) {
        std::cerr << "Error finishing entry: " << archive_error_string(a)
                  << std::endl;
    }

    archive_entry_free(entry);

    archive_write_close(a);
    archive_write_free(a);

    std::cout << "Archive created successfully as 'DeVenom_Downloader.tar'." << std::endl;
}
