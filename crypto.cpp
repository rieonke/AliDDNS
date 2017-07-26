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

#include "crypto.h"

string utils::Crypto::hmac(const string original, const string hkey) {

    SecByteBlock key(hkey.length());
    std::copy(hkey.begin(),hkey.end(),key.data());

    string mac, encoded;

    encoded.clear();
    StringSource ss1(key, key.size(), true,
                     new HexEncoder(
                             new StringSink(encoded)
                     ) // HexEncoder
    ); // StringSource

    try {
        HMAC<SHA1> hmac(key, key.size());

        StringSource ss2(original, true,
                         new HashFilter(hmac,
                                        new StringSink(mac)
                         ) // HashFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }

    encoded.clear();
    StringSource ss3(mac, true,
                     new Base64Encoder(
                             new StringSink(encoded)
                     ) // HexEncoder
    ); // StringSource

    return encoded;
}

string utils::Crypto::base64(const string original) {
    byte decoded[original.length()];
    std::copy(original.begin(),original.end(),decoded);
    string encoded;

    Base64Encoder encoder;
    encoder.Put(decoded, sizeof(decoded));
    encoder.MessageEnd();

    word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((byte*)encoded.data(), encoded.size());
    }

    cout << encoded << endl;
    return encoded;
    return std::string();
}

