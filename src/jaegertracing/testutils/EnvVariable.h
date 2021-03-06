/*
 * Copyright (c) 2019 The Jaeger Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JAEGERTRACING_TESTUTILS_ENVVARIABLE_H
#define JAEGERTRACING_TESTUTILS_ENVVARIABLE_H

#include <string>

namespace jaegertracing {
namespace testutils {
namespace EnvVariable {

inline void setEnv(const char *variable, const char *value) {
#ifdef WIN32
  _putenv_s(variable, value);
#else
  setenv(variable, value, true);
#endif
}

inline void resetEnv() {
    setEnv("JAEGER_AGENT_HOST", "");
    setEnv("JAEGER_AGENT_PORT", "");
    setEnv("JAEGER_ENDPOINT", "");
    setEnv("JAEGER_REPORTER_MAX_QUEUE_SIZE", "");
    setEnv("JAEGER_REPORTER_FLUSH_INTERVAL", "");
    setEnv("JAEGER_REPORTER_LOG_SPANS", "");
    setEnv("JAEGER_SAMPLER_PARAM", "");
    setEnv("JAEGER_SAMPLER_TYPE", "");
    setEnv("JAEGER_SERVICE_NAME", "");
    setEnv("JAEGER_TAGS", "");
    setEnv("JAEGER_DISABLED", "");
}

}  // namespace EnvVariable
}  // namespace testutils
}  // namespace jaegertracing

#endif  // JAEGERTRACING_TESTUTILS_ENVVARIABLE_H
