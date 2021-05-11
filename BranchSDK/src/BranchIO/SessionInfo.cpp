// Copyright (c) 2019-21 Branch Metrics, Inc.

#include "BranchIO/SessionInfo.h"
#include "BranchIO/Defines.h"
#include "BranchIO/Util/Log.h"
#include "BranchIO/Util/Storage.h"

using std::string;

namespace BranchIO {

    SessionInfo::SessionInfo() {
        // Load these fields from storage if present.
        std::string deviceFingerprint =
            Storage::instance().getString(getPath(SESSIONSTORAGE, Defines::JSONKEY_SESSION_FINGERPRINT));
        std::string identityId =
            Storage::instance().getString(getPath(SESSIONSTORAGE, Defines::JSONKEY_SESSION_IDENTITY));
        std::string requestMetadata =
            Storage::instance().getString(getPath(SESSIONSTORAGE, Defines::JSONKEY_METADATA));

        if (!deviceFingerprint.empty()) {
            doAddProperty(Defines::JSONKEY_SESSION_FINGERPRINT, deviceFingerprint);
        }

        if (!identityId.empty()) {
            doAddProperty(Defines::JSONKEY_SESSION_IDENTITY, identityId);
        }

        try {
            JSONObject metadata = JSONObject::parse(requestMetadata);
            JSONObject temp;
            temp.set(Defines::JSONKEY_METADATA, metadata);
            addProperties(temp);
        }
        catch (...) {

        }
}

SessionInfo::~SessionInfo() = default;

SessionInfo&
SessionInfo::setFingerprintId(const std::string &deviceFingerprint) {
    Storage::instance().setString(getPath(SESSIONSTORAGE, Defines::JSONKEY_SESSION_FINGERPRINT), deviceFingerprint);
    return doAddProperty(Defines::JSONKEY_SESSION_FINGERPRINT, deviceFingerprint);
}

SessionInfo&
SessionInfo::setIdentityId(const std::string &identityId) {
    return doAddProperty(Defines::JSONKEY_SESSION_IDENTITY, identityId);
}

SessionInfo&
SessionInfo::setSessionId(const std::string &sessionId) {
    return doAddProperty(Defines::JSONKEY_SESSION_ID, sessionId);
}

SessionInfo&
SessionInfo::setMetadata(const JSONObject& metadata) {
    Storage::instance().setString(getPath(SESSIONSTORAGE, Defines::JSONKEY_METADATA), metadata.stringify());

    JSONObject temp;
    temp.set(Defines::JSONKEY_METADATA, metadata);
    return static_cast<SessionInfo&>(addProperties(temp));
}

bool
SessionInfo::hasSessionId() const {
    return has(Defines::JSONKEY_SESSION_ID);
}

SessionInfo&
SessionInfo::doAddProperty(const char *name, const std::string &value) {
    addProperty(name, value);
    return *this;
}

}  // namespace BranchIO
