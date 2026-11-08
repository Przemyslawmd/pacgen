
#pragma once

#include "defines/errors.h"

class ErrorStorage
{
public:
    static void putError(ErrorCode error)
    {
        if (isLocked) {
            return;
        }
        errorCode = error;
        isLocked = true;
    }

    static ErrorCode getError()
    {
        ErrorCode temp = errorCode;
        isLocked = false;
        errorCode = ErrorCode::OK;
        return temp;
    }

private:
    inline static ErrorCode errorCode;
    inline static bool isLocked = false;
};

