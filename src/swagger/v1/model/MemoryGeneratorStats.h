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
 * MemoryGeneratorStats.h
 *
 * Memory generator statistics
 */

#ifndef MemoryGeneratorStats_H_
#define MemoryGeneratorStats_H_


#include "ModelBase.h"


namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// Memory generator statistics
/// </summary>
class  MemoryGeneratorStats
    : public ModelBase
{
public:
    MemoryGeneratorStats();
    virtual ~MemoryGeneratorStats();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// MemoryGeneratorStats members

    /// <summary>
    /// The intended number of operations performed
    /// </summary>
    int64_t getOpsTarget() const;
    void setOpsTarget(int64_t value);
        /// <summary>
    /// The actual number of operations performed
    /// </summary>
    int64_t getOpsActual() const;
    void setOpsActual(int64_t value);
        /// <summary>
    /// The intended number of bytes read or written
    /// </summary>
    int64_t getBytesTarget() const;
    void setBytesTarget(int64_t value);
        /// <summary>
    /// The actual number of bytes read or written
    /// </summary>
    int64_t getBytesActual() const;
    void setBytesActual(int64_t value);
        /// <summary>
    /// The total amount of time required to perform all operations (in nanoseconds)
    /// </summary>
    int64_t getLatencyTotal() const;
    void setLatencyTotal(int64_t value);
    
protected:
    int64_t m_Ops_target;

    int64_t m_Ops_actual;

    int64_t m_Bytes_target;

    int64_t m_Bytes_actual;

    int64_t m_Latency_total;

};

}
}
}

#endif /* MemoryGeneratorStats_H_ */
