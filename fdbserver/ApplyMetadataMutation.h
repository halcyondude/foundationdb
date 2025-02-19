/*
 * ApplyMetadataMutation.h
 *
 * This source file is part of the FoundationDB open source project
 *
 * Copyright 2013-2018 Apple Inc. and the FoundationDB project authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FDBSERVER_APPLYMETADATAMUTATION_H
#define FDBSERVER_APPLYMETADATAMUTATION_H
#pragma once

#include "fdbclient/BackupAgent.actor.h"
#include "fdbclient/MutationList.h"
#include "fdbclient/Notified.h"
#include "fdbclient/SystemData.h"
#include "fdbserver/IKeyValueStore.h"
#include "fdbserver/LogProtocolMessage.h"
#include "fdbserver/LogSystem.h"
#include "fdbserver/ProxyCommitData.actor.h"

inline bool isMetadataMutation(MutationRef const& m) {
	// FIXME: This is conservative - not everything in system keyspace is necessarily processed by
	// applyMetadataMutations
	if (m.type == MutationRef::SetValue) {
		return m.param1.size() && m.param1[0] == systemKeys.begin[0] &&
		       !m.param1.startsWith(nonMetadataSystemKeys.begin);
	} else if (m.type == MutationRef::ClearRange) {
		return m.param2.size() > 1 && m.param2[0] == systemKeys.begin[0] &&
		       !nonMetadataSystemKeys.contains(KeyRangeRef(m.param1, m.param2));
	} else {
		return false;
	}
}

Reference<StorageInfo> getStorageInfo(UID id,
                                      std::map<UID, Reference<StorageInfo>>* storageCache,
                                      IKeyValueStore* txnStateStore);

void applyMetadataMutations(SpanID const& spanContext,
                            ProxyCommitData& proxyCommitData,
                            Arena& arena,
                            Reference<ILogSystem> logSystem,
                            const VectorRef<MutationRef>& mutations,
                            LogPushData* pToCommit,
                            bool& confChange,
                            Version version,
                            Version popVersion,
                            bool initialCommit);
void applyMetadataMutations(SpanID const& spanContext,
                            const UID& dbgid,
                            Arena& arena,
                            const VectorRef<MutationRef>& mutations,
                            IKeyValueStore* txnStateStore);

#endif
