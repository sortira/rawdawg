# RawDawg : A lightweight (header-only) machine learning library 

© Team MikeHawk : Aritro Shome, SK Asif Tanvir, Vedanta Saha, Prayas Sinha

## What is RawDawg?

RawDawg is a _lightweight_, _header-only_ machine learning library written purely in C with no dependencies other than the standard library. This includes (and is not limited to) : 

-   Matrix and vector operations
-   A simple interface to read/write to csv files
-   Basic machine learning algorithms like : linear regression on n variables, softmax regression, logistic regression, k-nearest neighbours, k-means clustering, single perceptron classifier, multilayer perceptron classifier, support vector machines, dbscan, etc.

## Why RawDawg?

Any given day, raw C gives you exponentially greater performance gains as opposed to Python, hence RawDawg provides a lightweight yet performant machine learning library that can be used for demos.

Apart from this, from an educational standpoint, C is a language which we and many educators in the CS field believe should be learnt and mastered by everyone for true grasp over the concepts involved. Moreover, the field of machine learning and artificial intelligence is one of interest to many students hence this library brings the best of both worlds. 

## Usage instructions

- copy the folders except `test` inside a folder called `rawdawg` and make sure it is included while compiling your programs.

## For Developers

- the `alg` folder contains the implementations of the ML algorithms.
- the `math` folder contains the mathematical utilities including vector, matrix, tensor operations.
- the `exec` folder contains all the CSV operations and other executing related operations.
- the `test` folder contains tests of the functionalities provided in the above three folders.