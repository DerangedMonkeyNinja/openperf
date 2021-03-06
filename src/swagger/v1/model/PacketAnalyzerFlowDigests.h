/**
* OpenPerf API
* REST API interface for OpenPerf
*
* OpenAPI spec version: 1
* Contact: support@spirent.com
*
* NOTE: This class is auto generated by the swagger code generator program.
* https://github.com/swagger-api/swagger-codegen.git
* Do not edit the class manually.
*/
/*
 * PacketAnalyzerFlowDigests.h
 *
 * Result digests for flows
 */

#ifndef PacketAnalyzerFlowDigests_H_
#define PacketAnalyzerFlowDigests_H_


#include "ModelBase.h"

#include "PacketAnalyzerFlowDigestResult.h"

namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// Result digests for flows
/// </summary>
class  PacketAnalyzerFlowDigests
    : public ModelBase
{
public:
    PacketAnalyzerFlowDigests();
    virtual ~PacketAnalyzerFlowDigests();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// PacketAnalyzerFlowDigests members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getFrameLength() const;
    void setFrameLength(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool frameLengthIsSet() const;
    void unsetFrame_length();
    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getInterarrival() const;
    void setInterarrival(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool interarrivalIsSet() const;
    void unsetInterarrival();
    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getJitterIpdv() const;
    void setJitterIpdv(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool jitterIpdvIsSet() const;
    void unsetJitter_ipdv();
    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getJitterRfc() const;
    void setJitterRfc(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool jitterRfcIsSet() const;
    void unsetJitter_rfc();
    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getLatency() const;
    void setLatency(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool latencyIsSet() const;
    void unsetLatency();
    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketAnalyzerFlowDigestResult> getSequenceRunLength() const;
    void setSequenceRunLength(std::shared_ptr<PacketAnalyzerFlowDigestResult> value);
    bool sequenceRunLengthIsSet() const;
    void unsetSequence_run_length();

protected:
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Frame_length;
    bool m_Frame_lengthIsSet;
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Interarrival;
    bool m_InterarrivalIsSet;
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Jitter_ipdv;
    bool m_Jitter_ipdvIsSet;
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Jitter_rfc;
    bool m_Jitter_rfcIsSet;
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Latency;
    bool m_LatencyIsSet;
    std::shared_ptr<PacketAnalyzerFlowDigestResult> m_Sequence_run_length;
    bool m_Sequence_run_lengthIsSet;
};

}
}
}

#endif /* PacketAnalyzerFlowDigests_H_ */
