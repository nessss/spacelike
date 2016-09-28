/* Attribute for output
 */

#ifndef OUTPUT_ATTRIBUTE_H
#define OUTPUT_ATTRIBUTE_H 

#include <ncurses.h>

namespace OutputAttribute{
    extern unsigned int normal;
    extern unsigned int standout;
    extern unsigned int underline;
    extern unsigned int reverse;
    extern unsigned int blink;
    extern unsigned int dim;
    extern unsigned int bold;
    extern unsigned int protect;
    extern unsigned int invis;
    extern unsigned int altCharSet;
    extern unsigned int charText;
}

#endif /* ifndef OUTPUT_ATTRIBUTE_H */
