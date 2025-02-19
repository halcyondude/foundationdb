/*
 * BooleanParam.h
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

#pragma once

#include "flow/Trace.h"

#define FDB_DECLARE_BOOLEAN_PARAM(ParamName)                                                                           \
	class ParamName {                                                                                                  \
		bool value;                                                                                                    \
                                                                                                                       \
	public:                                                                                                            \
		explicit constexpr ParamName(bool value) : value(value) {}                                                     \
		constexpr operator bool() const { return value; }                                                              \
		static ParamName const True, False;                                                                            \
		constexpr void set(bool value) { this->value = value; }                                                        \
	};                                                                                                                 \
	template <>                                                                                                        \
	struct Traceable<ParamName> : std::true_type {                                                                     \
		static std::string toString(ParamName const& value) { return Traceable<bool>::toString(value); }               \
	}

#define FDB_DEFINE_BOOLEAN_PARAM(ParamName)                                                                            \
	ParamName const ParamName::True = ParamName(true);                                                                 \
	ParamName const ParamName::False = ParamName(false)

#define FDB_BOOLEAN_PARAM(ParamName)                                                                                   \
	FDB_DECLARE_BOOLEAN_PARAM(ParamName);                                                                              \
	FDB_DEFINE_BOOLEAN_PARAM(ParamName)
