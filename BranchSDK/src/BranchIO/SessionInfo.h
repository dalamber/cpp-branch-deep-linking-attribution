// Copyright (c) 2019-21 Branch Metrics, Inc.

#ifndef BRANCHIO_SESSIONINFO_H__
#define BRANCHIO_SESSIONINFO_H__

#include <string>
#include "BranchIO/PropertyManager.h"

namespace BranchIO {

/**
 * (Internal) Session State Information.
 */
class BRANCHIO_DLL_EXPORT SessionInfo : public PropertyManager {
 public:
    /**
     * Default constructor. Loads values from Storage if available.
     */
    SessionInfo();

    ~SessionInfo();

    /**
     * Set the Session Fingerprint ID.
     * @param deviceFingerprint as issued by the Branch server
     * @return This object for chaining builder methods
     */
    SessionInfo& setFingerprintId(const std::string &deviceFingerprint);

    /**
     * Set the Session Identity Id.
     * @param identity as issued by the Branch server
     * @return This object for chaining builder methods
     */
    SessionInfo& setIdentityId(const std::string &identity);

    /**
     * Set the Session Id.
     * @param sessionId as issued by the Branch server
     * @return This object for chaining builder methods
     */
    SessionInfo& setSessionId(const std::string &sessionId);

    SessionInfo& setMetadata(const JSONObject& metadata);

    /**
     * @return true if there is a current session.
     */
    bool hasSessionId() const;

 private:
    SessionInfo& doAddProperty(const char *name, const std::string &value);
};

constexpr const char* const SESSIONSTORAGE = "session";

}  // namespace BranchIO

#endif  // BRANCHIO_SESSIONINFO_H__
