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

#include "urlencoder.h"

string utils::UrlEncoder::urlEncode(const string &s) {

    std::stringstream escaped;

    std::string::const_iterator itStr = s.begin();
    for (; itStr != s.end(); ++itStr)
    {
        char c = *itStr;

        // Unreserved chars - never percent-encoded
        if (isUnreserved(c) || isSubDelim(c))
        {
            escaped << c;
            continue;
        }

        escaped << '%' << char2hex(c);
    }

    return escaped.str();
}
string utils::UrlEncoder::urlEncode(const string &s, const bool absolute) {

    std::stringstream escaped;

    std::string::const_iterator itStr = s.begin();
    for (; itStr != s.end(); ++itStr)
    {
        char c = *itStr;

        if (isUnreserved(c) || (absolute == false && isSubDelim(c)))
        {
            escaped << c;
            continue;
        }

        if (c != '\n')
            escaped << '%' << char2hex(c);
    }

    return escaped.str();
}

bool utils::UrlEncoder::isUnreserved(char c) {
    switch (c)
    {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':

        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z':

        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z':

        case '-': case '.': case '_': case '~':
            return true;

        default:
            return false;
    }
}

bool utils::UrlEncoder::isSubDelim(char c) {
    switch (c)
    {
        case '!': case '$': case '&': case '\'': case '(':
        case ')': case '*': case '+': case ',':  case ';':
        case '=':
        case '%':
            return true;

        default:
            return false;
    }
}

std::string utils::UrlEncoder::char2hex( char dec ) {

    auto dig1 = static_cast<char>((dec & 0xF0) >> 4);
    auto dig2 = static_cast<char>(dec & 0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48 in ascii
    if (10<= dig1 && dig1<=15) dig1+=65-10; //A,65 in ascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=65-10;

    std::string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

string utils::UrlEncoder::percentEncode(const string s) {
    if (s.length() < 1) return "";
    string str = urlEncode(s, true);
    replaceAll(str,"+","%20");
    replaceAll(str,"*","%2A");
    replaceAll(str,"%7E","~");
    replaceAll(str,"%0A","");
    return str;

}

void utils::UrlEncoder::replaceAll(std::string &str, const std::string &from, const std::string &to) {

    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


