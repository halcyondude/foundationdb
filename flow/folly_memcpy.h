/*
 * folly_memcpy.h
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

#ifndef FLOW_FOLLY_MEMCPY_H
#define FLOW_FOLLY_MEMCPY_H
#pragma once

#if (defined(__linux__) || defined(__FreeBSD__)) && defined(__AVX__)

extern "C" {
void* folly_memcpy(void* dst, const void* src, uint32_t length);
}

#endif // linux or bsd and avx

#endif
