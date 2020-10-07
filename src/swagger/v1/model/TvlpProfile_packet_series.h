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
 * TvlpProfile_packet_series.h
 *
 * TVLP Profile for Packet generators configuration
 */

#ifndef TvlpProfile_packet_series_H_
#define TvlpProfile_packet_series_H_


#include "ModelBase.h"

#include "PacketGeneratorConfig.h"
#include <string>

namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// TVLP Profile for Packet generators configuration
/// </summary>
class  TvlpProfile_packet_series
    : public ModelBase
{
public:
    TvlpProfile_packet_series();
    virtual ~TvlpProfile_packet_series();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// TvlpProfile_packet_series members

    /// <summary>
    /// Specifies the unique target for packets from this generator. This id may refer to either a port or an interface id. 
    /// </summary>
    std::string getTargetId() const;
    void setTargetId(std::string value);
        /// <summary>
    /// Length of a current operation in ns
    /// </summary>
    int64_t getLength() const;
    void setLength(int64_t value);
        /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketGeneratorConfig> getConfig() const;
    void setConfig(std::shared_ptr<PacketGeneratorConfig> value);
    
protected:
    std::string m_Target_id;

    int64_t m_Length;

    std::shared_ptr<PacketGeneratorConfig> m_Config;

};

}
}
}

#endif /* TvlpProfile_packet_series_H_ */