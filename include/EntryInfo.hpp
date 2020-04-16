//
// Created by anton on 15.04.2020.
//

#ifndef FS_ENTRYINFO_HPP
#define FS_ENTRYINFO_HPP

#include <filesystem>

#include <EntryType.hpp>
#include <filesystem_utils.hpp>

namespace ext::filesystem {

struct EntryInfo {
    std::filesystem::path location;
    std::string name;
    std::size_t size;
    fs::perms perms;
    EntryType type;

    explicit EntryInfo(const fs::path& entry_path);
    EntryInfo(const fs::path& entry_path, std::error_code& ec);
    EntryInfo(const EntryInfo& entry);
    EntryInfo(EntryInfo&& entry) noexcept;
};

template <typename OutIt>
void dir_entries_info(const fs::path& dir, OutIt&& out) {
    if(fs::exists(dir) && fs::is_directory(dir)) {
        for(auto& entry : fs::directory_iterator{dir}) {
            *out++ = EntryInfo(entry.path());
        }
    }
}

template <typename OutIt>
void recursive_dir_entries_info(const fs::path& dir, OutIt&& out) {
    if(fs::exists(dir) && fs::is_directory(dir)) {
        for(auto& entry : fs::recursive_directory_iterator{dir}) {
            *out++ = EntryInfo(entry.path());
        }
    }
}

}

#endif //FS_ENTRYINFO_HPP
