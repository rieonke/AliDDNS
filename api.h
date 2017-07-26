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

#ifndef ALI_DDNS_ALIAPI_H
#define ALI_DDNS_ALIAPI_H


#include <string>
#include <sstream>
#include <map>
#include <ctime>
#include "configuration.h"
#include "curl.h"
#include "urlencoder.h"
#include "sole.hpp"
#include "crypto.h"
#include "rapidjson/rapidjson.h"
#include "logger.h"

typedef map<string, string> Parameter;
typedef pair<string, string> ParameterItem;

struct DomainRecord {
    string target;
    string status;
    string value;
    string id;
    string type;
    string name;
    bool locked;
    string ttl;
};

using namespace std;
using namespace sole;
using namespace config;
using namespace utils;

namespace api {
    class AliGeneral {

    public:
        static const string API_ADDRESS;
        static const string IP_CHECK_ADDRESS;
        static const string PARA_ACTION;
        static const string PARA_DOMAINNAME;
        static const string PARA_VERSION;
        static const string PARA_ACCESSKEYID;
        static const string PARA_TIMESTAMP;
        static const string PARA_SIGNATUREMETHOD;
        static const string PARA_SIGNATUREVERSION;
        static const string PARA_SIGNATURENONCE;
        static const string PARA_PAGESIZE;
        static const string PARA_QUERYKEYWORD;
        static const string PARA_TYPE;
        static const string PARA_RECORDID;
        static const string PARA_TARGET;
        static const string PARA_FORMAT;
        static const string PARA_TTL;
        static const string PARA_VALUE;
        static const string DEFAULT_FORMAT;
        static const string DEFAULT_TYPE;
        static const string DEFAULT_VERSION;
        static const string DEFAULT_SIGNATUREVERSION;
        static const string DEFAULT_SIGNATUREMETHOD;
        static const string DEFAULT_PAGESIZE;

        static string sign(const string toSign);

        static bool updateDnsRecord(const string ip, const Configuration configuration);

        static DomainRecord queryRecords(const Configuration configuration);

        static void addCommonQueryParameters(Parameter &parameters, const Configuration configuration);

        static string buildUrl(Parameter parameter, const Configuration configuration);

        static string addRecord(const string ip, const Configuration configuration);
    };
}


#endif //ALI_DDNS_ALIAPI_H
