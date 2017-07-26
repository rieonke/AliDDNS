/* * This file is part of the AliDDNS distribution (https://github.com/rieonke/aliddns). * Copyright (c) 2017 Rieon Ke. * * This program is free software: you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation, version 3. * * This program is distributed in the hope that it will be useful, but * WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU * General Public License for more details. * * You should have received a copy of the GNU General Public License * along with this program. If not, see <http://www.gnu.org/licenses/>. */

#ifndef ALI_DDNS_LOGGER_H
#define ALI_DDNS_LOGGER_H

#include <memory>
#include "spdlog/spdlog.h"

using namespace spdlog;
using namespace std;

namespace utils {

    class Logger {
    private:
        static shared_ptr<logger> init();

    public:
        const static shared_ptr<logger> console;

    };
}


#endif //ALI_DDNS_LOGGER_H
