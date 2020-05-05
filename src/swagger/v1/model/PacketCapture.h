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
 * PacketCapture.h
 *
 * Packet capture; captures packets. 
 */

#ifndef PacketCapture_H_
#define PacketCapture_H_


#include "ModelBase.h"

#include "PacketCaptureConfig.h"
#include <string>

namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// Packet capture; captures packets. 
/// </summary>
class  PacketCapture
    : public ModelBase
{
public:
    PacketCapture();
    virtual ~PacketCapture();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// PacketCapture members

    /// <summary>
    /// Unique capture identifier
    /// </summary>
    std::string getId() const;
    void setId(std::string value);
        /// <summary>
    /// Specifies the unique source of packets for this capture. This id may refer to either a port or an interface. 
    /// </summary>
    std::string getSourceId() const;
    void setSourceId(std::string value);
        /// <summary>
    /// Indicates whether this object is currently capturing packets or not. 
    /// </summary>
    bool isActive() const;
    void setActive(bool value);
        /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<PacketCaptureConfig> getConfig() const;
    void setConfig(std::shared_ptr<PacketCaptureConfig> value);
    
protected:
    std::string m_Id;

    std::string m_Source_id;

    bool m_Active;

    std::shared_ptr<PacketCaptureConfig> m_Config;

};

}
}
}

#endif /* PacketCapture_H_ */