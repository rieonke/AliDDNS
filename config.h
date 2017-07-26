/*
 * This file is part of the AliDDNS distribution (https://github.com/rieonke/aliddns).
 * Copyright (c) 2017 Rieon Ke.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALI_DDNS_CONFIG_H
#define ALI_DDNS_CONFIG_H

#include <iostream>
#include <string>
#include <fstream>
#include "rapidjson/rapidjson.h"
#include "configuration.h"
#include "logger.h"

using namespace rapidjson;
using namespace std;
using namespace config;
using namespace utils;

namespace config {

    class ConfigurationTool {

    private:
        Configuration configuration;
        string filepath;
        ifstream *fileStream;

    public:

        explicit ConfigurationTool(const string &filepath);

        Configuration getConfiguration();

        ~ ConfigurationTool();
    };
}


#endif //ALI_DDNS_CONFIG_H
