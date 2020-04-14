#ifndef FILESYSTEM_FILESYSTEM_HPP
#define FILESYSTEM_FILESYSTEM_HPP

#include <ostream>
#include <filesystem>

namespace ext::filesystem {

void write_entry_info(std::ostream& stream, const std::filesystem::path& entry_path);
std::size_t entry_size(const std::filesystem::path& entry_path);
std::string size_to_str(std::size_t size);

}

#endif //FILESYSTEM_FILESYSTEM_HPP
