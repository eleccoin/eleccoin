// Copyright (c) 2020-2021 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <policy/feerate.h>

#include <tinyformat.h>

CFeeRate::CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes)
{
    const int64_t nSize{num_bytes};

    if (nSize > 0) {
        nElectronsPerK = nFeePaid * 1000 / nSize;
    } else {
        nElectronsPerK = 0;
    }
}

CAmount CFeeRate::GetFee(uint32_t num_bytes) const
{
    const int64_t nSize{num_bytes};

    CAmount nFee = nElectronsPerK * nSize / 1000;

    if (nFee == 0 && nSize != 0) {
        if (nElectronsPerK > 0) nFee = CAmount(1);
        if (nElectronsPerK < 0) nFee = CAmount(-1);
    }

    return nFee;
}

std::string CFeeRate::ToString(const FeeEstimateMode& fee_estimate_mode) const
{
    switch (fee_estimate_mode) {
    case FeeEstimateMode::ELE_VB: return strprintf("%d.%03d %s/vB", nElectronsPerK / 1000, nElectronsPerK % 1000, CURRENCY_ATOM);
    default:                      return strprintf("%d.%08d %s/kvB", nElectronsPerK / COIN, nElectronsPerK % COIN, CURRENCY_UNIT);
    }
}
