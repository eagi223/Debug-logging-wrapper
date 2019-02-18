/**
 * @file    debug_log.h
 * @author  Ethan Gibson (ethan@gibsondevlab.com)
 * @date    2019-02-18
 *
 * @brief   Simple printf wrapper
 *
 * A printf wrapper that expands the functionality to color code terminal output and adds on-the-fly enable/disable
 * of logs.
 *
 * @copyright Copyright Gibson Dev Lab(c) 2019
 */

#ifndef DEBUG_LOG_H_
#define DEBUG_LOG_H_

//======================================================================
// Dependencies
//======================================================================

// Standard C Libraries
#include <stdbool.h>

// Local
#include "helpers.h"



//======================================================================
// Public Types
//======================================================================

typedef enum
{
    DEBUG_LOG_LEVEL_NONE,
    DEBUG_LOG_LEVEL_ERROR,
    DEBUG_LOG_LEVEL_WARN,
    DEBUG_LOG_LEVEL_INFO,
    DEBUG_LOG_LEVEL_DEBUG,
} debug_log_level_t;

typedef struct
{
    debug_log_level_t genLogLevel;
    bool logRaw;
} debug_log_cfg_t;




//======================================================================
// Public Functions
//======================================================================

/**
 * @brief   General output logging function
 *
 * This wraps printf, but adds color coding and some useful debug text to indicate what file,
 * function and line triggered the print. This should mainly be used through the macros below
 * for guaranteed structure and consistency.
 *
 * @param   cfg         Struct containing trace level and flags to determine whether output is necessary
 * @param   logLevel    Log level to check cfg against
 * @param   colorCode   Color code
 * @param   logID       The string/character that will display at the very beginning of each line
 * @param   file        The file name to display in the log output
 * @param   function    The function name to display in the log output
 * @param   line        The line number to display in the log output
 * @param   format      String to print including any variable placeholders for optional arguments
 * @param   ...         Variable number of arguments to insert into print string
 */
void debug_log_base( debug_log_cfg_t *cfg, debug_log_level_t logLevel, char *colorCode, char *logID, const char *file, const char* function, int line, const char *format, ... );


/**
 * @brief   Raw logging wrapper
 *
 * Wraps printf with the ability to disable output on the fly using the debug_log_cfg struct passed in
 *
 * @param   cfg     Struct containing the trace level and flags to determine whether output is necessary
 * @param   format  String to print including any variable placeholders for optional arguments
 * @param   ...     Variable number of arguments to insert into print string
 */
void debug_log_raw( debug_log_cfg_t *cfg, const char *format, ... );



//======================================================================
// Public Macros
//======================================================================

// ANSI colors for terminal output
#define ANSI_COLOR_RED     "\x1b[0;31m"
#define ANSI_COLOR_GREEN   "\x1b[0;32m"
#define ANSI_COLOR_YELLOW  "\x1b[0;33m"
#define ANSI_COLOR_BLUE    "\x1b[0;34m"
#define ANSI_COLOR_MAGENTA "\x1b[0;35m"
#define ANSI_COLOR_CYAN    "\x1b[0;36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BG_CYAN       "\x1b[0;100m"

// The following LOGX wrappers add simple calls for common log types that auto fill mode of the parameters for debug_log_base
#define LOGE( logInfo, format, ... )    debug_log_base( logInfo, DEBUG_LOG_LEVEL_ERROR, ANSI_COLOR_RED, "E", __FILENAME__, __func__, __LINE__, format, ##__VA_ARGS__ )
#define LOGW( logInfo, format, ... )    debug_log_base( logInfo, DEBUG_LOG_LEVEL_WARN, ANSI_COLOR_YELLOW, "W", __FILENAME__, __func__, __LINE__, format, ##__VA_ARGS__ )
#define LOGI( logInfo, format, ... )    debug_log_base( logInfo, DEBUG_LOG_LEVEL_INFO, ANSI_COLOR_GREEN, "I", __FILENAME__, __func__, __LINE__, format, ##__VA_ARGS__ )
#define LOGD( logInfo, format, ... )    debug_log_base( logInfo, DEBUG_LOG_LEVEL_DEBUG, ANSI_COLOR_BLUE, "D", __FILENAME__, __func__, __LINE__, format, ##__VA_ARGS__ )

#define LOG( logInfo, format, ... )     debug_log_raw( logInfo, format, ##__VA_ARGS__ )

#endif /* DEBUG_LOG_H_ */
