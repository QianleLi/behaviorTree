//
// Created by Qianle Li on 2021/10/11.
//

#ifndef BV75PROJECT_BT_COMMON_H
#define BV75PROJECT_BT_COMMON_H

#include "basic_types.h"
#include "vec.h"

using Path = std::vector<Point_2f>;
using rcpp = std::vector<std::pair<Path, Path>>;

// TODO 目前首要任务是用BT取代动作栈
namespace BT
{
// Navigation task type
enum TaskType_
{
    TARGET = 0,
    CPP,
    WALL,
    NOPASS
};

//template <>
//inline Point_2f convertFromString<Point_2f>(StringView str)
//{
//    printf("Converting Point_2f: \"%s\"\n", str.data());
//
//    // real numbers separated by semicolons
//    auto parts = splitString(str, ';');
//    if (parts.size() != 2)
//    {
//        printf("Point_2f convert from string INVALID INPUT!!! size: %d \n", parts.size());
//    }
//    else
//    {
//        Point_2f output;
//        output.x = convertFromString<float>(parts[0]);
//        output.y = convertFromString<float>(parts[1]);
//        printf("Point_2f convert from string: (%f, %f)\n", output.x, output.y);
//        return output;
//    }
//}
//
//template <>
//Path convertFromString<Path>(StringView str)
//{
//    auto parts = splitString(str, ';');
//    Path output;
//    output.reserve(parts.size());
//    for (const StringView& part : parts)
//    {
//        char* end;
//        output.push_back(convertFromString<Point_2f>(part));
//    }
//    return output;
//}
//
//template <>
//std::pair<Path, Path> convertFromString<std::pair<Path, Path>>(StringView str)
//{
//    auto parts = splitString(str, ';');
//    std::pair<Path, Path> output;
//    if (parts.size() != 2)
//    {
//        printf("std::pair<Path, Path> convert from string INVALID INPUT!!! size: %d \n",
//               parts.size());
//    }
//    else
//    {
//        output =
//            std::make_pair(convertFromString<Path>(parts[0]), convertFromString<Path>(parts[1]));
//        return output;
//    }
//}
//
//template <>
//rcpp convertFromString<rcpp>(StringView str)
//{
//    auto parts = splitString(str, ';');
//    rcpp output;
//    output.reserve(parts.size());
//    for (const StringView& part : parts)
//    {
//        output.push_back(convertFromString<std::pair<Path, Path>>(part));
//    }
//    return output;
//}

}   // namespace BT

#endif   // BV75PROJECT_BT_COMMON_H
