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

#ifndef ALI_DDNS_CURL_H
#define ALI_DDNS_CURL_H

#include <string>
#include <iostream>
#include "curl/curl.h"
#include "logger.h"

using namespace std;

namespace utils {
    class Curl {
    private:
        static size_t writer(char *data, size_t size, size_t nmemb, std::string *writerData);

    public:
        static string get(const string url);
    };
}


#endif //ALI_DDNS_CURL_H
