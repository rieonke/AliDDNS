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

#ifndef ALI_DDNS_IPCHECKER_H
#define ALI_DDNS_IPCHECKER_H

#include <iostream>
#include "rapidjson/document.h"
#include "curl.h"
using namespace std;
using namespace rapidjson;
using namespace utils;

struct IpResult {
    string  ip;
};

namespace utils {

    class IpChecker {

    private:

        static const string API_ADDRESS;

    public:
        static IpResult check();
    };

}

#endif //ALI_DDNS_IPCHECKER_H
