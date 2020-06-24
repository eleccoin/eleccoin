// Copyright (c) 2009-2010
// Copyright (c) 2009-2018 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_POLICY_FEERATE_H
#define ELECCOIN_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

extern const std::string CURRENCY_UNIT;

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
    /** Constructor for a fee rate in electrons per kB. The size in bytes must not exceed (2^63 - 1)*/
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    /**
     * Return the fee in electrons for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
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
    std::string ToString() const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(nElectronsPerK);
    }
};

#endif //  ELECCOIN_POLICY_FEERATE_H
