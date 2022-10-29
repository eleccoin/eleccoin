// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_POLICY_FEERATE_H
#define ELECCOIN_POLICY_FEERATE_H

#include <consensus/amount.h>
#include <serialize.h>

#include <string>

const std::string CURRENCY_UNIT = "ECC"; // One formatted unit
const std::string CURRENCY_ATOM = "ELE"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    ECC_KVB,      //!< Use ECC/kvB fee rate unit
    ELE_VB,       //!< Use ele/vB fee rate unit
};

/**
 * Fee rate in electrons per kilovirtualbyte: CAmount / kvB
 */
class CFeeRate
{
private:
    /** Fee rate in ele/kvB (electrons per 1000 virtualbytes) */
    CAmount nElectronsPerK;

public:
    /** Fee rate of 0 electrons per kB */
    CFeeRate() : nElectronsPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nElectronsPerK): nElectronsPerK(_nElectronsPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }

    /**
     * Construct a fee rate from a fee in electrons and a vsize in vB.
     *
     * param@[in]   nFeePaid    The fee paid by a transaction, in electrons
     * param@[in]   num_bytes   The vsize of a transaction, in vbytes
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);

    /**
     * Return the fee in electrons for the given vsize in vbytes.
     * If the calculated fee would have fractional electrons, then the
     * returned fee will always be rounded up to the nearest electron.
     */
    CAmount GetFee(uint32_t num_bytes) const;

    /**
     * Return the fee in electrons for a vsize of 1000 vbytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK < b.nElectronsPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK > b.nElectronsPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK == b.nElectronsPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK <= b.nElectronsPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK >= b.nElectronsPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nElectronsPerK != b.nElectronsPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nElectronsPerK += a.nElectronsPerK; return *this; }
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::ECC_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nElectronsPerK); }
};

#endif // ELECCOIN_POLICY_FEERATE_H
