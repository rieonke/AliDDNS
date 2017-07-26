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

#ifndef ALI_DDNS_CRYPTO_H
#define ALI_DDNS_CRYPTO_H

#include <sstream>
#include <string>
#include <iostream>
#include "osrng.h"
#include "hex.h"
#include "hmac.h"
#include "base64.h"
#include "rapidjson/document.h"
#include "curl/curl.h"

using namespace std;
using namespace CryptoPP;
namespace utils {

    class Crypto {

    public:
        static string hmac(const string original, const string hkey);

        static string base64(const string original);
    };

}


#endif //ALI_DDNS_CRYPTO_H
