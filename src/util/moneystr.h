// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef ELECCOIN_UTIL_MONEYSTR_H
#define ELECCOIN_UTIL_MONEYSTR_H

#include <attributes.h>
#include <consensus/amount.h>

#include <string>

/* Do not use these functions to represent or parse monetary amounts to or from
 * JSON but use AmountFromValue and ValueFromAmount for that.
 */
std::string FormatMoney(const CAmount n);
/** Parse an amount denoted in full coins. E.g. "0.0034" supplied on the command line. **/
[[nodiscard]] bool ParseMoney(const std::string& str, CAmount& nRet);

#endif // ELECCOIN_UTIL_MONEYSTR_H
