/**
 * @file    debug_log.c
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

#include "debug_log.h"

//======================================================================
// Dependencies
//======================================================================

// Standard C Libraries
#include <stdio.h>
#include <stdarg.h>




//======================================================================
// Public Types
//======================================================================

void _logRaw( const char *format, va_list args )
{
    vprintf( format, args );
}

void debug_log_base( debug_log_cfg_t *cfg, debug_log_level_t logLevel, char *colorCode, char *logID, const char *file, const char* function, int line, const char *format, ... )
{
    if( cfg->genLogLevel >= logLevel )
    {
        va_list args;
        va_start( args, format );

        printf( "%s%s %s : %s (%d)- ", colorCode, logID, file, function, line);
        _logRaw( format, args );
        printf( ANSI_COLOR_RESET "\n" );
        fflush( stdout );

        va_end( args );
    }
}

void debug_log_raw( debug_log_cfg_t *cfg, const char *format, ... )
{
    if( cfg-> logRaw )
    {
        va_list args;
        va_start( args, format );
        vprintf( format, args );
        fflush( stdout );
        va_end( args );
    }
}