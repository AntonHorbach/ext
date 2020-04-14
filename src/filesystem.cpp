//
// Created by anton on 14.04.2020.
//

#include <filesystem.hpp>

namespace ext::filesystem {

std::string size_to_str(std::size_t size) {
    std::string str_size{};
    std::string size_type{};

    if(size >= 1024 * 1024 * 1024) {
        str_size = std::to_string(static_cast<float>(size) / (1024.f * 1024 * 1024));
        size_type = "GB";
    }
    else if (size >= (1024 * 1024)) {
        str_size = std::to_string(static_cast<float>(size) / (1024.f * 1024));
        size_type = "MB";
    }
    else if (size >= (1024)) {
        str_size = std::to_string(static_cast<float>(size) / 1024.f);
        size_type =  "KB";
    }
    else {
        str_size = std::to_string(static_cast<float>(size));
        size_type = "B";
    }

    str_size.erase(str_size.begin() + str_size.find('.') + 3, str_size.end());
    str_size += size_type;

    return str_size;
}

}
