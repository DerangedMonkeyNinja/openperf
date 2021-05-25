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
 * TimeKeeperState.h
 *
 * TimeKeeper internal state information
 */

#ifndef TimeKeeperState_H_
#define TimeKeeperState_H_


#include "ModelBase.h"


namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// TimeKeeper internal state information
/// </summary>
class  TimeKeeperState
    : public ModelBase
{
public:
    TimeKeeperState();
    virtual ~TimeKeeperState();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// TimeKeeperState members

    /// <summary>
    /// The time counter frequency as measured by the interval between the two best timestamp exchanges with the time source over the past two hours, in Hz. 
    /// </summary>
    int64_t getFrequency() const;
    void setFrequency(int64_t value);
    bool frequencyIsSet() const;
    void unsetFrequency();
    /// <summary>
    /// The estimated error of the time counter frequency measurement, in Parts Per Billion (PPB). 
    /// </summary>
    int64_t getFrequencyError() const;
    void setFrequencyError(int64_t value);
    bool frequencyErrorIsSet() const;
    void unsetFrequency_error();
    /// <summary>
    /// The time counter frequency as measured by the interval between the two best timestamp exchanges with the time source over the past hour, in Hz. This value is used to help determine time stamp error due to time counter frequency drift. 
    /// </summary>
    int64_t getLocalFrequency() const;
    void setLocalFrequency(int64_t value);
    bool localFrequencyIsSet() const;
    void unsetLocal_frequency();
    /// <summary>
    /// The estimated error of the local time counter frequency measurement, int Parts Per Billion (PPB). 
    /// </summary>
    int64_t getLocalFrequencyError() const;
    void setLocalFrequencyError(int64_t value);
    bool localFrequencyErrorIsSet() const;
    void unsetLocal_frequency_error();
    /// <summary>
    /// The offset applied to time counter derived timestamp values, in seconds.  This value comes from the system host clock. 
    /// </summary>
    double getOffset() const;
    void setOffset(double value);
        /// <summary>
    /// The time keeper is considered to be synced to the time source if a clock offset, theta, has been calculated and applied within the past 20 minutes. 
    /// </summary>
    bool isSynced() const;
    void setSynced(bool value);
        /// <summary>
    /// The calculated correction to apply to the offset, based on the measured time counter frequency and time source timestamps. 
    /// </summary>
    double getTheta() const;
    void setTheta(double value);
    bool thetaIsSet() const;
    void unsetTheta();

protected:
    int64_t m_Frequency;
    bool m_FrequencyIsSet;
    int64_t m_Frequency_error;
    bool m_Frequency_errorIsSet;
    int64_t m_Local_frequency;
    bool m_Local_frequencyIsSet;
    int64_t m_Local_frequency_error;
    bool m_Local_frequency_errorIsSet;
    double m_Offset;

    bool m_Synced;

    double m_Theta;
    bool m_ThetaIsSet;
};

}
}
}

#endif /* TimeKeeperState_H_ */
