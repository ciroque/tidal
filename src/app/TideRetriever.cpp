//
// Created by Steve Wagner on 9/23/20.
//

#include <iomanip>
#include <iostream>
#include <utility>

#include "TideRetriever.h"
#include "Time.h"

std::string TideRetriever::Retrieve() {
    std::cout << "TideRetriever::Retrieve" << std::endl;
    return this->Retriever::Retrieve(config->getTideHttpHost(), config->getTideHttpPort(), this->BuildPath());
}

std::string TideRetriever::BuildPath() {
    const auto DATE_LENGTH = 10;
    const auto DATE_FORMAT_STRING = "%Y%m%d";
    time_t *NO_TIMER = NULL;
    time_t ttime = time(NO_TIMER);
    auto local_time = localtime(&ttime);

    char start[DATE_LENGTH];
    char end[DATE_LENGTH];

    strftime(start, DATE_LENGTH, DATE_FORMAT_STRING, local_time);
    local_time->tm_mday += config->getLookAheadDays();
    std::mktime(local_time);
    strftime(end, DATE_LENGTH, DATE_FORMAT_STRING, local_time);

    std::string params = "&begin_date=" + std::string(start)
            + "&end_date=" + std::string(end)
            + "&time_zone=" + config->getTideTimezone()
            + "&station=" + config->getTideStation();

    return config->getTideHttpRootPath() + params;
}

TideRetriever::TideRetriever(AppConfig *config) {
    this->config = config;
}
