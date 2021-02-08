// Copyright (c) 2020-2021 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <policy/feerate.h>

#include <tinyformat.h>

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nBytes_)
{
    assert(nBytes_ <= uint64_t(std::numeric_limits<int64_t>::max()));
    int64_t nSize = int64_t(nBytes_);

    if (nSize > 0)
        nElectronsPerK = nFeePaid * 1000 / nSize;
    else
        nElectronsPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nBytes_) const
{
    assert(nBytes_ <= uint64_t(std::numeric_limits<int64_t>::max()));
    int64_t nSize = int64_t(nBytes_);

    CAmount nFee = nElectronsPerK * nSize / 1000;

    if (nFee == 0 && nSize != 0) {
        if (nElectronsPerK > 0)
            nFee = CAmount(1);
        if (nElectronsPerK < 0)
            nFee = CAmount(-1);
    }

    return nFee;
}

std::string CFeeRate::ToString(const FeeEstimateMode& fee_estimate_mode) const
{
    return strprintf("%d.%08d %s/kB", nElectronsPerK / COIN, nElectronsPerK % COIN, CURRENCY_UNIT);
}
