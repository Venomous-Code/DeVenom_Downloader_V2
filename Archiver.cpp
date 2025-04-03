

#include "Archiver.h"

void PackageInstaller::Archiver::ArchiverInit() {

    archive* archiveWriter = archive_write_new();
    if (!archiveWriter) {
        Logs.CustomLogger("FAILED TO INITIALIZE THE ARCHIVE.",spdlog::level::critical);
    }

    if (archive_write_set_format_pax_restricted(archiveWriter) != ARCHIVE_OK) {
        Logs.CustomLogger("ERROR SETTING FORMAT. ",
                          spdlog::level::critical);
        std::cerr<< archive_error_string(archiveWriter)<< std::endl;
        archive_write_free(archiveWriter);
    }

    if (archive_write_open_filename(archiveWriter, "DeVenom_Downloader.tar") !=
        ARCHIVE_OK) {
        Logs.CustomLogger("ERROR OPENING OUTPUT FILE. ",
                          spdlog::level::critical);
        std::cerr << archive_error_string(archiveWriter) << std::endl;
        archive_write_free(archiveWriter);
    }

    struct archive_entry* entry = archive_entry_new();
    if (!entry) {
        Logs.CustomLogger("COULD NOT CREATE ARCHIVE ENTRY ",
                          spdlog::level::critical);
        archive_write_free(archiveWriter);
    }
    archive_entry_set_pathname(entry, "data.txt");
    const char* filedata = "hello, world!";
    size_t filesize = std::strlen(filedata);
    archive_entry_set_size(entry, filesize);      // file size in bytes.
    archive_entry_set_filetype(entry, AE_IFREG);  // regular file.
    archive_entry_set_perm(entry, 0644);          // file permissions.

    if (archive_write_header(archiveWriter, entry) != ARCHIVE_OK) {
        Logs.CustomLogger("ARCHIVE HEADER ERROR.",
                          spdlog::level::critical);
        std::cerr << archive_error_string(archiveWriter) << std::endl;
        archive_entry_free(entry);
        archive_write_free(archiveWriter);
    }

    size_t byteswritten = archive_write_data(archiveWriter, filedata, filesize);
    if (byteswritten < 0) {
        Logs.CustomLogger("FAILED TO WRITE DATA TO ARCHIVE.",
                          spdlog::level::critical);
        std::cerr << archive_error_string(archiveWriter) << std::endl;
        archive_entry_free(entry);
        archive_write_free(archiveWriter);
    }

    if (archive_write_finish_entry(archiveWriter) != ARCHIVE_OK) {
        Logs.CustomLogger("FAILED TO TERMINATE THE ARCHIVE ENTRY. ",
                          spdlog::level::critical);
        std::cerr << archive_error_string(archiveWriter) << std::endl;
    }

    archive_entry_free(entry);

    archive_write_close(archiveWriter);
    archive_write_free(archiveWriter);

    Logs.CustomLogger("ARCHIVE CREATED SUCCESSFULLY AS 'DeVenom_Downloader.tar' .",
                      spdlog::level::info);
}

//void PackageInstaller::Archiver::ArchiverInit() {
//    archive* archiveWriter = archive_write_new();
//    if (archiveWriter != ARCHIVE_OK) {
//        Logs.CustomLogger("FAILED TO INITIALIZE THE ARCHIVE.",
//                          spdlog::level::critical);
//        archive_write_close(archiveWriter);
//        archive_write_free(archiveWriter);
//    }
//
//    if (archive_write_set_bytes_per_block(archiveWriter, 4194304) !=
//        ARCHIVE_OK) {
//        Logs.CustomLogger("SETTING BYTES PER BLOCK NOT SUPPORTED.");
//        archive_write_close(archiveWriter);
//        archive_write_free(archiveWriter);    
//    }
//
//    if (archive_write_add_filter_none(archiveWriter) != ARCHIVE_OK) {
//        Logs.CustomLogger(
//            "AN UNEXPECTED ERROR OCCURED DURING THE FILTER FUNCTION.");
//        archive_write_close(archiveWriter);
//        archive_write_free(archiveWriter);  
//    }
//
//
//}