#pragma once

#include <Stream.h>
#include <Arduino.h>
#include <WString.h>

namespace ArduinoTestUtils {
        class MockStream : public Stream {
            public:
                MockStream();
                MockStream(String str);
                MockStream(const char* cstr);

                // Stream Implementation
                int available();
                int read();
                int peek();
                size_t write(uint8_t);

                void setString(String str);
                String peekString();

                MockStream& operator= (const MockStream& other); 

            private:
                String mStr;
                const char* mCstr;
        };    
} // ArduinoTestUtils
