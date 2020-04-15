//
// Created by anton on 15.04.2020.
//

#include <EntryType.hpp>

namespace ext::filesystem {

    EntryType entry_type(const fs::path &entry_path) {
        if (!fs::exists(entry_path)) return EntryType::UNDEFINED;
        else if (fs::is_directory(entry_path)) return EntryType::DIR;
        else if (fs::is_regular_file(entry_path)) return EntryType::REG_FL;
        else if (fs::is_socket(entry_path)) return EntryType::SOCK;
        else if (fs::is_block_file(entry_path)) return EntryType::BLK_FL;
        else if (fs::is_symlink(entry_path)) return EntryType::SYM_LNK;
        else if (fs::is_character_file(entry_path)) return EntryType::CHR_FL;
        else if (fs::is_fifo(entry_path)) return EntryType::FIFO;
        else if (fs::is_other(entry_path)) return EntryType::OTH;
    }

    std::ostream &operator<<(std::ostream &stream, EntryType type) {
        return stream << static_cast<char>(type);
    }

}
