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
    EntryType type;

    explicit EntryInfo(const fs::path& entry_path);
    EntryInfo(const fs::path& entry_path, std::error_code& ec);
    EntryInfo(const EntryInfo& entry);
    EntryInfo(EntryInfo&& entry) noexcept;
};

}

#endif //FS_ENTRYINFO_HPP
