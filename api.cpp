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

#include "api.h"

const string api::AliGeneral::API_ADDRESS = "http://alidns.aliyuncs.com/";
const string api::AliGeneral::IP_CHECK_ADDRESS = "https://api.ipify.org?format=json";
const string api::AliGeneral::PARA_ACTION = "Action";
const string api::AliGeneral::PARA_DOMAINNAME = "DomainName";
const string api::AliGeneral::PARA_VERSION = "Version";
const string api::AliGeneral::DEFAULT_VERSION = "2015-01-09";
const string api::AliGeneral::PARA_ACCESSKEYID = "AccessKeyId";
const string api::AliGeneral::PARA_TIMESTAMP = "Timestamp";
const string api::AliGeneral::PARA_SIGNATUREMETHOD = "SignatureMethod";
const string api::AliGeneral::DEFAULT_SIGNATUREMETHOD = "HMAC-SHA1";
const string api::AliGeneral::PARA_SIGNATUREVERSION = "SignatureVersion";
const string api::AliGeneral::DEFAULT_SIGNATUREVERSION = "1.0";
const string api::AliGeneral::PARA_SIGNATURENONCE = "SignatureNonce";
const string api::AliGeneral::PARA_FORMAT = "Format";
const string api::AliGeneral::PARA_VALUE = "Value";
const string api::AliGeneral::PARA_TTL = "TTL";
const string api::AliGeneral::PARA_RECORDID = "RecordId";
const string api::AliGeneral::DEFAULT_FORMAT = "JSON";
const string api::AliGeneral::PARA_PAGESIZE = "PageSize";
const string api::AliGeneral::PARA_TYPE = "Type";
const string api::AliGeneral::PARA_TARGET = "RR";
const string api::AliGeneral::DEFAULT_TYPE = "A";
const string api::AliGeneral::DEFAULT_PAGESIZE = "500";
const string api::AliGeneral::PARA_QUERYKEYWORD = "RRKeyWord";

string api::AliGeneral::sign(const string toSign) {
    return std::string();
}

bool api::AliGeneral::updateDnsRecord(const string ip, const Configuration configuration) {

    auto record = queryRecords(configuration);
    if (record.id.empty()) {
        addRecord(ip, configuration);
        Logger::console->error("域名记录不存在，已经新建解析记录，记录ID为 {}",record.id);
        return true;
    }

    if (record.value == ip) {
        return true;
    }

    Parameter parameters;

    parameters.insert(ParameterItem(PARA_ACTION, "UpdateDomainRecord"));
    parameters.insert(ParameterItem(PARA_RECORDID, record.id));
    parameters.insert(ParameterItem(PARA_TARGET, configuration.Target));
    parameters.insert(ParameterItem(PARA_TYPE, DEFAULT_TYPE));
    parameters.insert(ParameterItem(PARA_VALUE, ip));
    parameters.insert(ParameterItem(PARA_TTL, configuration.TTL));

    addCommonQueryParameters(parameters, configuration);

    string url = buildUrl(parameters, configuration);

    string result = Curl::get(url);

    Document document;
    document.Parse(result.c_str());
    if (document["RecordId"].IsNull()) {
        Logger::console->error("更新域名解析记录失败！服务器响应为 {}",result);
        return false;
    }

    return true;


}

DomainRecord api::AliGeneral::queryRecords(const Configuration configuration) {

    DomainRecord domainRecord = DomainRecord();

    Parameter parameters;

    parameters.insert(ParameterItem(PARA_ACTION, "DescribeDomainRecords"));
    parameters.insert(ParameterItem(PARA_DOMAINNAME, configuration.Domain));
    parameters.insert(ParameterItem(PARA_QUERYKEYWORD, configuration.Target));
    parameters.insert(ParameterItem(PARA_TYPE, DEFAULT_TYPE));

    addCommonQueryParameters(parameters, configuration);

    string url = buildUrl(parameters, configuration);
    string buffer = Curl::get(url);

    if (buffer.empty()){
        return domainRecord;
    }

    Document document;
    document.Parse(buffer.c_str());

    if (document.IsNull() || !document.IsObject() || document["TotalCount"].IsNull() || document["TotalCount"].GetInt() == 0 ||
        document["DomainRecords"].IsNull()) {
        return domainRecord;
    }

    auto record =  document["DomainRecords"].GetObject()["Record"].GetArray();
    for (auto &v : record) {

        auto obj = v.GetObject();

        if (configuration.Target == obj["RR"].GetString() && DEFAULT_TYPE == obj["Type"].GetString()) {
            domainRecord = {
                    obj["RR"].IsNull() ? std::string() : obj["RR"].GetString(),
                    obj["Status"].IsNull() ? std::string() : obj["Status"].GetString(),
                    obj["Value"].IsNull() ? std::string() : obj["Value"].GetString(),
                    obj["RecordId"].IsNull() ? std::string() : obj["RecordId"].GetString(),
                    obj["Type"].IsNull() ? std::string() : obj["Type"].GetString(),
                    obj["DomainName"].IsNull() ? std::string() : obj["DomainName"].GetString(),
                    obj["Locked"].IsNull() ? false : obj["Locked"].GetBool(),
                    obj["TTL"].IsNull() ? std::string() : obj["TTL"].GetString(),
            };
        }

    }

    return domainRecord;

}

void api::AliGeneral::addCommonQueryParameters(Parameter &parameters, const Configuration configuration) {

    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));

    string uuid = uuid4().str();

    parameters.insert(ParameterItem(PARA_VERSION, DEFAULT_VERSION));
    parameters.insert(ParameterItem(PARA_ACCESSKEYID, configuration.AccessKeyId));
    parameters.insert(ParameterItem(PARA_TIMESTAMP, string(buf)));
    parameters.insert(ParameterItem(PARA_SIGNATUREMETHOD, DEFAULT_SIGNATUREMETHOD));
    parameters.insert(ParameterItem(PARA_SIGNATUREVERSION, DEFAULT_SIGNATUREVERSION));
    parameters.insert(ParameterItem(PARA_SIGNATURENONCE, uuid));
    parameters.insert(ParameterItem(PARA_FORMAT, DEFAULT_FORMAT));
}

string api::AliGeneral::buildUrl(Parameter parameters, const Configuration configuration) {

    const string HTTP_METHOD = "GET";
    const string SEPARATOR = "&";

    stringstream queryParameters;

    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        string key = it->first;
        string value = it->second;
        queryParameters << SEPARATOR << UrlEncoder::percentEncode(key) << "="
                        << UrlEncoder::percentEncode(value);
    }

    stringstream stringToSign;
    auto queryString = static_cast<basic_string<char, char_traits<char>, allocator<char>> &&>(queryParameters.str().erase(
            0, 1));
    stringToSign << HTTP_METHOD << SEPARATOR << UrlEncoder::percentEncode("/") << SEPARATOR
                 << UrlEncoder::percentEncode(queryString);

//    AliGeneral::sign(stringToSign.str()); //TODO

    const string signature = Crypto::hmac(stringToSign.str(), configuration.AccessSecret + "&");

    stringstream finalParameters;

    finalParameters << queryString << "&Signature=" << UrlEncoder::urlEncode(signature, true);

    stringstream url;

    url << AliGeneral::API_ADDRESS << "?" << UrlEncoder::urlEncode(finalParameters.str());

    return url.str();
}


string api::AliGeneral::addRecord(const string ip, const Configuration configuration) {

    Parameter parameters;

    parameters.insert(ParameterItem(PARA_ACTION, "AddDomainRecord"));
    parameters.insert(ParameterItem(PARA_TARGET, configuration.Target));
    parameters.insert(ParameterItem(PARA_TYPE, DEFAULT_TYPE));
    parameters.insert(ParameterItem(PARA_VALUE, ip));
    parameters.insert(ParameterItem(PARA_TTL, configuration.TTL));
    parameters.insert(ParameterItem(PARA_DOMAINNAME, configuration.Domain));

    addCommonQueryParameters(parameters, configuration);

    string url = buildUrl(parameters, configuration);
    string buffer = Curl::get(url);

    Document document;
    document.Parse(buffer.c_str());

    return document["RecordId"].IsNull() ? std::string() : document["RecordId"].GetString();

}


