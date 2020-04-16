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
 * BlockFile.h
 *
 * Block file
 */

#ifndef BlockFile_H_
#define BlockFile_H_


#include "ModelBase.h"

#include <string>

namespace swagger {
namespace v1 {
namespace model {

/// <summary>
/// Block file
/// </summary>
class  BlockFile
    : public ModelBase
{
public:
    BlockFile();
    virtual ~BlockFile();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// BlockFile members

    /// <summary>
    /// Unique file identifier
    /// </summary>
    std::string getId() const;
    void setId(std::string value);
        /// <summary>
    /// Size of test file (in bytes)
    /// </summary>
    int64_t getFileSize() const;
    void setFileSize(int64_t value);
        /// <summary>
    /// Percentage of initialization completed so far
    /// </summary>
    int32_t getInitPercentComplete() const;
    void setInitPercentComplete(int32_t value);
        /// <summary>
    /// Resource pathname
    /// </summary>
    std::string getPath() const;
    void setPath(std::string value);
        /// <summary>
    /// State of resource
    /// </summary>
    std::string getState() const;
    void setState(std::string value);
    
protected:
    std::string m_Id;

    int64_t m_File_size;

    int32_t m_Init_percent_complete;

    std::string m_Path;

    std::string m_State;

};

}
}
}

#endif /* BlockFile_H_ */
