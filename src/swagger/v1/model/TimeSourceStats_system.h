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
 * TimeSourceStats_system.h
 *
 * System statistics
 */

#ifndef TimeSourceStats_system_H_
#define TimeSourceStats_system_H_


#include "ModelBase.h"


namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// System statistics
/// </summary>
class  TimeSourceStats_system
    : public ModelBase
{
public:
    TimeSourceStats_system();
    virtual ~TimeSourceStats_system();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// TimeSourceStats_system members

    /// <summary>
    /// Number of times the system clock has been polled
    /// </summary>
    int64_t getPollCount() const;
    void setPollCount(int64_t value);
        /// <summary>
    /// Current system poll period, in seconds
    /// </summary>
    int64_t getPollPeriod() const;
    void setPollPeriod(int64_t value);
    
protected:
    int64_t m_Poll_count;

    int64_t m_Poll_period;

};

}
}
}

#endif /* TimeSourceStats_system_H_ */