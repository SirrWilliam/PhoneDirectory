#pragma once
#ifndef MACRO_H
#define MACRO_H

/**
 * @brief
 * Iterates over all elements of a fixed-size C array
 * and assigns each element’s address to the given item
 * pointer, simulating a foreach-style loop.
 *
 * @param item
 * Pointer that will reference the current array element.
 *
 * @param array
 * Fixed-size array to iterate over.
 */
#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

 /**
  * @brief
  * Clears the terminal.
  */
#define clrscr() printf("\033[H\033[J");

#endif /* MACRO_H */