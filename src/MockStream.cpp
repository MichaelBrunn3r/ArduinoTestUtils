#include "MockStream.h"
#include <cstring>

namespace ArduinoTestUtils {
        //////////////////
        // Constructors //
        //////////////////

        MockStream::MockStream() : MockStream("") {}

        MockStream::MockStream(String str) {
            setTimeout(0);
            setString(str);
        }

        MockStream::MockStream(const char* cstr) {
            setTimeout(0);
            mStr = String(cstr);
            mCstr = mStr.c_str();
        }

        ///////////////////////////
        // Stream Implementation //
        ///////////////////////////

        int MockStream::available() {
            if(*mCstr == 0) return 0;
            long charsRead = mCstr - mStr.c_str(); 
            return mStr.length() - charsRead;
        }

        int MockStream::read() {
            return *mCstr == 0 ? -1 : (unsigned char)*mCstr++;
        }

        int MockStream::peek() {    
            return *mCstr == 0 ? -1 : (unsigned char)*mCstr;
        }

        size_t MockStream::write(uint8_t) {
            return 1;
        }

        /////////////
        // Methods //
        /////////////

        void MockStream::setString(String str) {
            mStr = str;
            mCstr = mStr.c_str();
        }

        String MockStream::peekString() {
            return String(mCstr);
        }

        ///////////////
        // Operators //
        ///////////////

        MockStream& MockStream::operator= (const MockStream& other) {
            mStr = other.mStr;
            mCstr = mStr.c_str();
            return *this;
        }
} // ArduinoTestUtils
