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

#ifndef ALI_DDNS_URLENCODER_H
#define ALI_DDNS_URLENCODER_H

#include <sstream>
#include <string>
#include <iostream>
#include <regex>
#include "osrng.h"
#include "hex.h"
#include "hmac.h"
#include "base64.h"
#include "rapidjson/document.h"
#include "curl/curl.h"

using namespace std;
using namespace CryptoPP;
using namespace rapidjson;

namespace utils {

    class UrlEncoder {

    private:
        static bool isUnreserved(char c);
        static bool isSubDelim(char c);
        static std::string char2hex( char dec );

    public:
        static string percentEncode(const string string);
        static void replaceAll(std::string& str, const std::string& from, const std::string& to);
        static string urlEncode(const string &s, const bool absolute);
        static string urlEncode(const string &s);

    };


}


#endif //ALI_DDNS_URLENCODER_H
