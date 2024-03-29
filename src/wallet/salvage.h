// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_WALLET_SALVAGE_H
#define ELECCOIN_WALLET_SALVAGE_H

#include <fs.h>
#include <streams.h>

struct bilingual_str;

namespace wallet {
bool RecoverDatabaseFile(const fs::path& file_path, bilingual_str& error, std::vector<bilingual_str>& warnings);
} // namespace wallet

#endif // ELECCOIN_WALLET_SALVAGE_H
