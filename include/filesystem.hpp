#ifndef FILESYSTEM_FILESYSTEM_HPP
#define FILESYSTEM_FILESYSTEM_HPP

#include <ostream>
#include <filesystem>

#include <EntryType.hpp>

namespace ext::filesystem {
    
namespace fs = std::filesystem;

std::size_t entry_size(const fs::path& entry_path);
std::size_t entry_size(const fs::path& entry_path, std::error_code& ec);
std::string size_to_str(std::size_t size);

template <typename OutIt>
void dir_items(const fs::path& dir, OutIt&& out) {
    if(fs::exists(dir) && fs::is_directory(dir)) {
        for (auto &item : fs::directory_iterator{dir}) {
            *out++ = item.path().filename();
        }
    }
}

}

#endif //FILESYSTEM_FILESYSTEM_HPP
