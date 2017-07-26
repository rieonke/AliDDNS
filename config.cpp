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

#include <rapidjson/document.h>
#include "config.h"


config::ConfigurationTool::ConfigurationTool(const string &filepath){
    this->fileStream = new ifstream(filepath);
    if (this->fileStream == nullptr){
        Logger::console->error("配置文件不存在，请检查配置文件");
    }
}

config::ConfigurationTool::~ConfigurationTool() {

    delete this->fileStream;

}

Configuration config::ConfigurationTool::getConfiguration() {

    std::string content( (std::istreambuf_iterator<char>(* this->fileStream) ),
                         (std::istreambuf_iterator<char>()    ) );

    Document document;
    document.Parse(content.c_str());
    Configuration configuration;
    configuration.AccessKeyId = document["AccessKeyId"].IsNull() ? "" : document["AccessKeyId"].GetString();
    configuration.AccessSecret = document["AccessSecret"].IsNull() ? "" : document["AccessSecret"].GetString();
    configuration.Version = document["Version"].IsNull() ? "" : document["Version"].GetString();
    configuration.Domain = document["Domain"].IsNull() ? "" : document["Domain"].GetString();
    configuration.Target = document["Target"].IsNull() ? "" : document["Target"].GetString();
    configuration.TTL = document["TTL"].IsNull() ? "" : document["TTL"].GetString();
    Logger::console->info("配置文件加载成功");
    return configuration;

}
