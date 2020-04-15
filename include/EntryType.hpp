//
// Created by anton on 15.04.2020.
//

#ifndef FILESYSTEM_ENTRYTYPE_HPP
#define FILESYSTEM_ENTRYTYPE_HPP

#include <ostream>
#include <filesystem>

namespace ext::filesystem {

namespace fs = std::filesystem;

enum class EntryType: char {
    UNDEFINED = '?', DIR = 'd', REG_FL = 'f', SOCK = 's', BLK_FL = 'b', SYM_LNK = 'l',
    CHR_FL = 'c', FIFO = 'p', OTH = 'o'
};

std::ostream& operator<<(std::ostream& stream, EntryType type);

EntryType entry_type(const fs::path& entry_path);

}

#endif //FILESYSTEM_ENTRYTYPE_HPP
