// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

///!! source code path
///!! not necessary but code macros will work
#define SOURCE_CODE_PATH "C:\\RX\\Plugins\\LearnProject\\QuickStartProj\\QuickStartProj"


#define RXPLUGIN_EXPORTS

// rx-common abstractions
#include "common/rx_common.h"
// std c and std c++17 includes
#include "lib/rx_std.h"
// platform library 
#include "lib/rx_lib.h"
#include "lib/rx_lock.h"
// plugin api includes
#include "version/rx_code_macros.h"
#include "platform_api/rx_api.h"
#include "platform_api/rx_general.h"
#include "platform_api/rx_ports.h"
#include "platform_api/rx_var_types.h"
#include "platform_api/rx_basic_types.h"
#include "protocols/ansi_c/common_c/rx_protocol_handlers.h"
#include "protocols/ansi_c/common_c/rx_packet_decoder.h"

#endif //PCH_H
