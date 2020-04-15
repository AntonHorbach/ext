//
// Created by anton on 15.04.2020.
//

#ifndef FILESYSTEM_ENTRYTYPE_HPP
#define FILESYSTEM_ENTRYTYPE_HPP

#include <ostream>
#include <filesystem>

namespace ext::filesystem {

namespace fs = std::filesystem;

enum class EntryType: size_t {
    UNDEFINED, DIR, REG_FL, SOCK, BLK_FL, SYM_LNK, CHR_FL, FIFO, OTH
};

EntryType entry_type(const fs::path& entry_path);

}

#endif //FILESYSTEM_ENTRYTYPE_HPP
