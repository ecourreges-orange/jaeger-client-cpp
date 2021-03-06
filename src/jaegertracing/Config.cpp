/*
 * Copyright (c) 2017 Uber Technologies, Inc.
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

#include "jaegertracing/Config.h"
#include "jaegertracing/samplers/Config.h"
#include "jaegertracing/utils/EnvVariable.h"

namespace jaegertracing {

constexpr const char* Config::kJAEGER_SERVICE_NAME_ENV_PROP;
constexpr const char* Config::kJAEGER_TAGS_ENV_PROP;
constexpr const char* Config::kJAEGER_JAEGER_DISABLED_ENV_PROP;

void Config::fromEnv()
{
    const auto disabled =
        utils::EnvVariable::getBoolVariable(kJAEGER_JAEGER_DISABLED_ENV_PROP);
    if (disabled.first) {
        _disabled = disabled.second;
    }

    const auto serviceName =
        utils::EnvVariable::getStringVariable(kJAEGER_SERVICE_NAME_ENV_PROP);
    if (!serviceName.empty()) {
        _serviceName = serviceName;
    }

    const auto tags =
        utils::EnvVariable::getStringVariable(kJAEGER_TAGS_ENV_PROP);
    if (!tags.empty()) {
        std::string tag;
        std::istringstream tagsStream(tags);
        while (std::getline(tagsStream, tag, ',')) {

            std::istringstream tagStream(tag);

            std::string tagKey;
            std::string tagValue;
            if (std::getline(tagStream, tagKey, '=')) {
                std::getline(tagStream, tagValue, '=');
                if (std::getline(tagStream, tagValue, '=')) {
                    // error, should be logged somewhere
                    std::cerr << "wrong format in tag " << tagKey
                    << " of env var " << kJAEGER_TAGS_ENV_PROP
                    << ", it can not contain an =\n";
                }
                else {
                    _tags.emplace_back(tagKey, tagValue);
                }
            }
        }
    }
    _reporter.fromEnv();
    _sampler.fromEnv();
}

}  // namespace jaegertracing
