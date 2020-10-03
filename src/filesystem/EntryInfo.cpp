//
// Created by anton on 15.04.2020.
//

#include <EntryInfo.hpp>

namespace ext::filesystem {

    EntryInfo::EntryInfo(const fs::path &entry_path)
        : size(entry_size(entry_path)), perms(fs::status(entry_path).permissions()),
            type(entry_type(entry_path))
    {
        auto canon_entry_path = fs::canonical(entry_path);

        location = canon_entry_path.parent_path();
        name = canon_entry_path.filename();
    }

    EntryInfo::EntryInfo(const fs::path &entry_path, std::error_code &ec)
            : size(entry_size(entry_path, ec)), perms(fs::status(entry_path, ec).permissions()),
                type(entry_type(entry_path))
    {
        if(!ec) {
            auto canon_entry_path = fs::canonical(entry_path, ec);

            if (!ec) {
                location = canon_entry_path.parent_path();
                name = canon_entry_path.filename();
            }
        }
    }

    EntryInfo::EntryInfo(const EntryInfo &entry) = default;
    EntryInfo::EntryInfo(EntryInfo &&entry) noexcept = default;
}
