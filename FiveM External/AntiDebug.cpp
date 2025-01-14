#include "AntiDebug.h"

bool isDebuggerPresent() {
#ifdef _WIN32
    return IsDebuggerPresent();
#else
    return false;
#endif
}
