// Copyright (c) 2020-2021 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_POLICY_FEERATE_H
#define ELECCOIN_POLICY_FEERATE_H

#include <amount.h>
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
    ELE_VB,       //!< Use sat/vB fee rate unit
};

/**
 * Fee rate in electrons per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nElectronsPerK; // unit is electrons-per-1,000-bytes

public:
    /** Fee rate of 0 electrons per kB */
    CFeeRate() : nElectronsPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nElectronsPerK): nElectronsPerK(_nElectronsPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }
    /** Constructor for a fee rate in electrons per kvB (ele/kvB). The size in bytes must not exceed (2^63 - 1).
     *
     *  Passing an nBytes value of COIN (1e8) returns a fee rate in electrons per vB (ele/vB),
     *  e.g. (nFeePaid * 1e8 / 1e3) == (nFeePaid / 1e5),
     *  where 1e5 is the ratio to convert from ECC/kvB to ele/vB.
     *
     *  @param[in] nFeePaid  CAmount fee rate to construct with
     *  @param[in] nBytes    size_t bytes (units) to construct with
     *  @returns   fee rate
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);
    /**
     * Return the fee in electrons for the given size in bytes.
     */
    CAmount GetFee(uint32_t num_bytes) const;
    /**
     * Return the fee in electrons for a size of 1000 bytes
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

#endif //  ELECCOIN_POLICY_FEERATE_H
