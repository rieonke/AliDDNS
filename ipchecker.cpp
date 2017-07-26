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

#include "ipchecker.h"

const string utils::IpChecker::API_ADDRESS = "https://api.ipify.org?format=json";

IpResult utils::IpChecker::check() {
    IpResult result = IpResult();

    string buffer = Curl::get(API_ADDRESS);

    if (buffer.empty()){
        return result;
    }

    Document document;
    document.Parse(buffer.c_str());

    result = {
            document["ip"].IsNull() ? "" : document["ip"].GetString()
    };

    return result;

}

