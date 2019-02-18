# Debug Logging Wrapper
I put this wrapper together for an ESP32 project that I'm working on and it has been hugely helpful for me. Basically I have a pretty complex project with 50+ source files/headers. Each .c file gets its own log configuration struct as a static global, then all logging is done throught the LOGX macros. It makes it flexible enought that I can have a macro per file to disable debug output OR globally disable all ouputs. The version I'm sharing here is a little more simple than that so you can tailor it to your needs. I thought I'd share it in case it would be helpful for someone else!

EDIT: github doesn't seem to support HTML in markdown files, so the colors are not showing up correctly in output logs examples, but it IS colored when using this to print logs in MacOS terminal. I'm not sure about Windows compatibility, so if someone wants to test and either add Issues or PRs feel free!

## Example 1: ERROR Logging
For quick formatted, color coded logging, the easiest way is to use the LOGX wrappers. For more flexibility, you can add your own debug_log_base macro or use the function directly (though the macros help reduce the lengthy function call greatly).
```C
static debug_log_cfg_t log =
{
    DEBUG_LOG_LEVEL_ERROR,
    false,
};

static void test_func( bool isGood )
{
    if( !isGood )
    {
        LOGE( &log, "THIS IS AN ERROR" );
    }
}
```

When test_func( false ) is called, you should get the following terminal output:

<p style="color:red">E main.c : app_main (15)- THIS IS AN ERROR</p>

The ouput is automatically colored, the filenane, line number and function name are added and a newline character is appended to the end.


## Other LOGX() Functionality
The other LOGX functions produce similar output:

<p style="color:red">E main.c : app_main (15)- THIS IS AN ERROR (using LOGE())</p>
<p style="color:yellow">W main.c : app_main (15)- THIS IS A WARNING (using LOGW())</p>
<p style="color:green">I main.c : app_main (15)- THIS IS INFO (using LOGI())</p>
<p style="color:blue">D main.c : app_main (15)- THIS IS DEBUG (using LOGD())</p>

Keep in mind that the DEBUG_LOG_LEVEL set in the debug_log_cfg struct is heirarchical meaning if it is set to ...ERROR only LOGE statements are output. If it is set to ...INFO, LOGE, LOGW and LOGI statements are output. Higher debug levels will display all lower logs as well. ...NONE will disable all LOGX() output

## Example 2: Raw Logging
There are some instances where the formatted logging provides more information than you need (eg. wanting to print hex bytes from an array on a single line). For this you can use the LOG() macro or the debug_log_raw() function. Remember that this requires the debug_log_cfg logRaw member to be true for it to output.

```C
static debug_log_cfg_t log =
{
    DEBUG_LOG_LEVEL_NONE,
    true,
};

static void test_func( void )
{
    char testString[] = "ThisIsATest";
    for( i = 0; i < 10; i++ )
    {
        LOG( &log, "%02x", testString[i] );
    }
    LOG( &log, "\n", );
}
```

The output should be:
5468697349734154657374

## Example 3: Changing Log Levels On-The-Fly
The debug_log_cfg struct allows you to change the log level on the fly. For embedded systems, this means you can disable debug output in a production product, and re-enable it in the field to debug.

```C
static debug_log_cfg_t log =
{
    DEBUG_LOG_LEVEL_NONE,
    false,
};

static void test_func( bool isGood )
{
    if( !isGood )
    {
        LOGE( &log, "THIS IS AN ERROR" );

        log.genLogLevel = DEBUG_LOG_LEVEL_ERROR;

        LOGE( &log, "THIS IS AN ERROR" );
    }
}
```

When test_func( false ) is called, you should get the following terminal output:

<p style="color:red">E main.c : app_main (15)- THIS IS AN ERROR</p>

Note that this is the second line that printed. The first line didn't because log.genLogLevel was set to DEBUG_LOG_LEVEL_NONE when it was called.
