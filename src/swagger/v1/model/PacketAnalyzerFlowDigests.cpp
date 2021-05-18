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


#include "PacketAnalyzerFlowDigests.h"

namespace swagger {
namespace v1 {
namespace model {

PacketAnalyzerFlowDigests::PacketAnalyzerFlowDigests()
{
    m_Frame_lengthIsSet = false;
    m_InterarrivalIsSet = false;
    m_Jitter_ipdvIsSet = false;
    m_Jitter_rfcIsSet = false;
    m_LatencyIsSet = false;
    m_Sequence_run_lengthIsSet = false;
    
}

PacketAnalyzerFlowDigests::~PacketAnalyzerFlowDigests()
{
}

void PacketAnalyzerFlowDigests::validate()
{
    // TODO: implement validation
}

nlohmann::json PacketAnalyzerFlowDigests::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    if(m_Frame_lengthIsSet)
    {
        val["frame_length"] = ModelBase::toJson(m_Frame_length);
    }
    if(m_InterarrivalIsSet)
    {
        val["interarrival"] = ModelBase::toJson(m_Interarrival);
    }
    if(m_Jitter_ipdvIsSet)
    {
        val["jitter_ipdv"] = ModelBase::toJson(m_Jitter_ipdv);
    }
    if(m_Jitter_rfcIsSet)
    {
        val["jitter_rfc"] = ModelBase::toJson(m_Jitter_rfc);
    }
    if(m_LatencyIsSet)
    {
        val["latency"] = ModelBase::toJson(m_Latency);
    }
    if(m_Sequence_run_lengthIsSet)
    {
        val["sequence_run_length"] = ModelBase::toJson(m_Sequence_run_length);
    }
    

    return val;
}

void PacketAnalyzerFlowDigests::fromJson(nlohmann::json& val)
{
    if(val.find("frame_length") != val.end())
    {
        if(!val["frame_length"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["frame_length"]);
            setFrameLength( newItem );
        }
        
    }
    if(val.find("interarrival") != val.end())
    {
        if(!val["interarrival"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["interarrival"]);
            setInterarrival( newItem );
        }
        
    }
    if(val.find("jitter_ipdv") != val.end())
    {
        if(!val["jitter_ipdv"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["jitter_ipdv"]);
            setJitterIpdv( newItem );
        }
        
    }
    if(val.find("jitter_rfc") != val.end())
    {
        if(!val["jitter_rfc"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["jitter_rfc"]);
            setJitterRfc( newItem );
        }
        
    }
    if(val.find("latency") != val.end())
    {
        if(!val["latency"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["latency"]);
            setLatency( newItem );
        }
        
    }
    if(val.find("sequence_run_length") != val.end())
    {
        if(!val["sequence_run_length"].is_null())
        {
            std::shared_ptr<PacketAnalyzerFlowDigestResult> newItem(new PacketAnalyzerFlowDigestResult());
            newItem->fromJson(val["sequence_run_length"]);
            setSequenceRunLength( newItem );
        }
        
    }
    
}


std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getFrameLength() const
{
    return m_Frame_length;
}
void PacketAnalyzerFlowDigests::setFrameLength(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Frame_length = value;
    m_Frame_lengthIsSet = true;
}
bool PacketAnalyzerFlowDigests::frameLengthIsSet() const
{
    return m_Frame_lengthIsSet;
}
void PacketAnalyzerFlowDigests::unsetFrame_length()
{
    m_Frame_lengthIsSet = false;
}
std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getInterarrival() const
{
    return m_Interarrival;
}
void PacketAnalyzerFlowDigests::setInterarrival(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Interarrival = value;
    m_InterarrivalIsSet = true;
}
bool PacketAnalyzerFlowDigests::interarrivalIsSet() const
{
    return m_InterarrivalIsSet;
}
void PacketAnalyzerFlowDigests::unsetInterarrival()
{
    m_InterarrivalIsSet = false;
}
std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getJitterIpdv() const
{
    return m_Jitter_ipdv;
}
void PacketAnalyzerFlowDigests::setJitterIpdv(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Jitter_ipdv = value;
    m_Jitter_ipdvIsSet = true;
}
bool PacketAnalyzerFlowDigests::jitterIpdvIsSet() const
{
    return m_Jitter_ipdvIsSet;
}
void PacketAnalyzerFlowDigests::unsetJitter_ipdv()
{
    m_Jitter_ipdvIsSet = false;
}
std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getJitterRfc() const
{
    return m_Jitter_rfc;
}
void PacketAnalyzerFlowDigests::setJitterRfc(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Jitter_rfc = value;
    m_Jitter_rfcIsSet = true;
}
bool PacketAnalyzerFlowDigests::jitterRfcIsSet() const
{
    return m_Jitter_rfcIsSet;
}
void PacketAnalyzerFlowDigests::unsetJitter_rfc()
{
    m_Jitter_rfcIsSet = false;
}
std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getLatency() const
{
    return m_Latency;
}
void PacketAnalyzerFlowDigests::setLatency(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Latency = value;
    m_LatencyIsSet = true;
}
bool PacketAnalyzerFlowDigests::latencyIsSet() const
{
    return m_LatencyIsSet;
}
void PacketAnalyzerFlowDigests::unsetLatency()
{
    m_LatencyIsSet = false;
}
std::shared_ptr<PacketAnalyzerFlowDigestResult> PacketAnalyzerFlowDigests::getSequenceRunLength() const
{
    return m_Sequence_run_length;
}
void PacketAnalyzerFlowDigests::setSequenceRunLength(std::shared_ptr<PacketAnalyzerFlowDigestResult> value)
{
    m_Sequence_run_length = value;
    m_Sequence_run_lengthIsSet = true;
}
bool PacketAnalyzerFlowDigests::sequenceRunLengthIsSet() const
{
    return m_Sequence_run_lengthIsSet;
}
void PacketAnalyzerFlowDigests::unsetSequence_run_length()
{
    m_Sequence_run_lengthIsSet = false;
}

}
}
}

