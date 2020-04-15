//
// Created by anton on 14.04.2020.
//

#include <filesystem.hpp>

#include <numeric>

namespace ext::filesystem {

    std::string size_to_str(std::size_t size) {
        std::string str_size{};
        std::string size_type{};

        if (size >= (1000 * 1000 * 1000)) {
            str_size = std::to_string(static_cast<float>(size) / (1000.f * 1000 * 1000));
            size_type = "GiB";
        } else if (size >= (1000 * 1000)) {
            str_size = std::to_string(static_cast<float>(size) / (1000.f * 1000));
            size_type = "MiB";
        } else if (size >= (1000)) {
            str_size = std::to_string(static_cast<float>(size) / 1000.f);
            size_type = "KiB";
        } else {
            str_size = std::to_string(static_cast<float>(size));
            size_type = "B";
        }

        str_size.erase(str_size.begin() + str_size.find('.') + 3, str_size.end());
        str_size += size_type;

        return str_size;
    }

    std::size_t entry_size(const fs::path &entry_path) {
        if (!fs::exists(entry_path)) {
            return 0;
        }

        if (!fs::is_directory(entry_path)) {
            return fs::file_size(entry_path);
        }

        return std::accumulate(fs::directory_iterator{entry_path}, {}, 0,
                               [](size_t sum, const fs::directory_entry &ent) {
                                   return sum + entry_size(ent);
                               }
        );
    }

    std::size_t entry_size(const std::filesystem::path &entry_path, std::error_code &ec) {
        if (!fs::exists(entry_path)) {
            return 0;
        }

        std::size_t size = 0;
        if (!fs::is_directory(entry_path)) {
            size = fs::file_size(entry_path, ec);
        } else {
            size = std::accumulate(fs::directory_iterator{entry_path}, {}, 0,
                                   [](size_t sum, const fs::directory_entry &ent) {
                                       return sum + entry_size(ent);
                                   }
            );
        }

        return (ec ? size : 0);
    }

}
