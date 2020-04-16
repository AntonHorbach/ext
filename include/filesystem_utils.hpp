//
// Created by anton on 15.04.2020.
//

#ifndef FILESYSTEM_UTILS_HPP
#define FILESYSTEM_UTILS_HPP

#include <filesystem>

namespace ext::filesystem {

    namespace fs = std::filesystem;

    std::size_t entry_size(const fs::path& entry_path);
    std::size_t entry_size(const fs::path& entry_path, std::error_code& ec);
    std::string size_to_str(std::size_t size);
    std::string perms_to_str(const fs::perms& entry_perms);

    template <typename OutIt>
    void dir_items(const fs::path& dir, OutIt&& out) {
        if(fs::exists(dir) && fs::is_directory(dir)) {
            for (auto &item : fs::directory_iterator{dir}) {
                *out++ = item.path().filename();
            }
        }
    }

    template <typename OutIt>
    void recursive_dir_items(const fs::path& dir, OutIt&& out) {
        if(fs::exists(dir) && fs::is_directory(dir)) {
            for(auto& item : fs::recursive_directory_iterator{dir}) {
                *out++ = item.path().filename();
            }
        }
    }

}

#endif //FILESYSTEM_UTILS_HPP
