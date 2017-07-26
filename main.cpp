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

#include <iostream>
#include <map>
#include "api.h"
#include "config.h"
#include "ipchecker.h"
#include "logger.h"

using namespace std;
using namespace api;
using namespace config;
using namespace utils;


int main() {

    IpResult last;
    ConfigurationTool tool("./config.json");
    Configuration configuration = tool.getConfiguration();

    shared_ptr<logger> console = Logger::console;

    bool flag = true;

    console->info("欢迎使用阿里云动态域名解析工具");

    while (flag){

        IpResult result = IpChecker::check();
        if (result.ip.empty() || result.ip == last.ip){
            continue;
        }

        if (last.ip.empty()){
            console->info("开始将记录解析为: {}",result.ip);
        }else {
            console->info("监测到IP地址已经改变，开始更新解析记录,原地址为: {}, 新地址为: {}",last.ip,result.ip);
        }
        last.ip = result.ip;
        AliGeneral::updateDnsRecord(result.ip,configuration);

    }

}