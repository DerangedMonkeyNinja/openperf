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
 * BulkStartCapturesResponse.h
 *
 * 
 */

#ifndef BulkStartCapturesResponse_H_
#define BulkStartCapturesResponse_H_


#include "ModelBase.h"

#include <vector>
#include "PacketCaptureResult.h"

namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// 
/// </summary>
class  BulkStartCapturesResponse
    : public ModelBase
{
public:
    BulkStartCapturesResponse();
    virtual ~BulkStartCapturesResponse();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// BulkStartCapturesResponse members

    /// <summary>
    /// List of capture results
    /// </summary>
    std::vector<std::shared_ptr<PacketCaptureResult>>& getItems();
    
protected:
    std::vector<std::shared_ptr<PacketCaptureResult>> m_Items;

};

}
}
}

#endif /* BulkStartCapturesResponse_H_ */