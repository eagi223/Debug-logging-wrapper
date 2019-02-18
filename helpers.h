/**
 * @file    helpers.h
 * @author  Ethan Gibson (ethan@gibsondevlab.com)
 * @date    2019-02-18
 *
 * @brief   Helper functions and macros
 *
 * @copyright Copyright Gibson Dev Lab(c) 2019
 */

#ifndef HELPERS_H_
#define HELPERS_H_

#include <string.h>

// Copied from https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
// Tested on OSX, so may need to be changed for Windows
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#endif /* HELPERS_H_ */