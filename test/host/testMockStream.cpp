#include <catch.hpp>

#include <vector>
#include <iostream>
#include <utility>

#define private public
#define protected public
    #include <MockStream.h>
#undef private
#undef protected

using namespace ArduinoTestUtils; 

TEST_CASE("::read") {
    std::vector<std::tuple<const char*, int>> tests {
        {"", -1},
        {"a", 97},
        {"äöü", 195},
    };

    for(unsigned int testIdx=0; testIdx<tests.size(); testIdx++) {
        const char* str = std::get<0>(tests.at(testIdx));
        int expectedVal = std::get<1>(tests.at(testIdx));
        String strAfterExec = String(String(std::get<0>(tests.at(testIdx))).c_str()+1);

        MockStream stream(str);
        REQUIRE(stream.read() == expectedVal);
        CHECK_THAT(stream.readString().c_str(), Catch::Equals(strAfterExec.c_str()));
    }
}

TEST_CASE("::peek") {
    std::vector<std::tuple<String, int>> tests {
        {"", -1},
        {"a", 97},
        {"äöü", 195},
    };

    for(unsigned int testIdx=0; testIdx<tests.size(); testIdx++) {
        String str = std::get<0>(tests.at(testIdx));
        int expectedVal = std::get<1>(tests.at(testIdx));
        String strAfterExec = String(std::get<0>(tests.at(testIdx)));

        MockStream stream(str);
        REQUIRE(stream.peek() == expectedVal);
        CHECK_THAT(stream.readString().c_str(), Catch::Equals(strAfterExec.c_str()));
    }
}

TEST_CASE("::available()") {
    std::vector<std::tuple<const char*, int, int, const char*>> tests {
        {"", 0, 0, ""},
        {"aString", 0, 7, "aString"},
        {"aString", 3, 4, "ring"},
    };

    for(unsigned int testIdx=0; testIdx<tests.size(); testIdx++) {
        const char* str = std::get<0>(tests.at(testIdx));
        int readsBeforeExec = std::get<1>(tests.at(testIdx));
        int expectedVal = std::get<2>(tests.at(testIdx));
        const char* strAfterExec = std::get<3>(tests.at(testIdx));

        MockStream stream(str);

        for(int i=0; i<readsBeforeExec; i++) stream.read();

        REQUIRE(stream.available() == expectedVal);
        CHECK_THAT(stream.peekString().c_str(), Catch::Equals(strAfterExec));
    }
}

TEST_CASE("::readString") {
    std::vector<std::tuple<const char*, const char*>> tests {
        {"", ""},
        {"aString", "aString"},
        {"äöü", "äöü"},
    };

    for(unsigned int testIdx=0; testIdx<tests.size(); testIdx++) {
        const char* str = std::get<0>(tests.at(testIdx));
        const char* readStr = std::get<1>(tests.at(testIdx));

        MockStream stream(str);
        CHECK_THAT(stream.readString().c_str(), Catch::Equals(readStr));
    }
}

TEST_CASE("::peekString") {
    std::vector<std::tuple<const char*, int, const char*>> tests {
        {"", 0, ""},
        {"aString", 0, "aString"},
        {"aString", 3, "ring"},
    };

    for(unsigned int testIdx=0; testIdx<tests.size(); testIdx++) {
        const char* str = std::get<0>(tests.at(testIdx));
        int readsBeforeExec = std::get<1>(tests.at(testIdx));
        const char* strAfterExec = std::get<2>(tests.at(testIdx));

        MockStream stream(str);

        for(int i=0; i<readsBeforeExec; i++) stream.read();

        CHECK_THAT(stream.peekString().c_str(), Catch::Equals(strAfterExec));
    }
}