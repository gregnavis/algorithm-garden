Algorithm Garden
================

This repository contains algorithms of all sort implemented in C. The goal of
the project is to learn and understand the details of the algorithms. I won't
produce production-quality library code here. However one of my goals is to
produce code that is free of undefined behaviour.

Feel free to suggest an algorithm to implement!

Usage
-----

Clone the repository and issue `make` in the root directory. Now you can run
individual algorithms (e.g. `sorting/selection-sort`) to output some
measurements.

Sorting
-------

The algorithms that are currently implemented are:

  * selection sort
  * insertion sort
  * bubble sort
  * heapsort
  * quicksort
  * counting sort
  * radix sort

Each sorting algorithm is run multiple times on inputs of different sizes and
otuputs two rows for each iteration:

  * the size of the input array
  * 10 samples of time measurements made for arrays of the size above
