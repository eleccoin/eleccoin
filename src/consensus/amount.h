// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_CONSENSUS_AMOUNT_H
#define ELECCOIN_CONSENSUS_AMOUNT_H

#include <cstdint>

/** Amount in electrons (Can be negative) */
typedef int64_t CAmount;

/** The amount of electrons in one ECC. */
static constexpr CAmount COIN = 100000000;

/** No amount larger than this (in electron) is valid.
 *
 * Note that this constant is *not* the total money supply, which in Eleccoin
 * currently happens to be less than 21,000,000 ECC for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static constexpr CAmount MAX_MONEY = 22000000 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

#endif // ELECCOIN_CONSENSUS_AMOUNT_H
