
# Tiler

This repository contains a simple C application that tiles PPM images.


## Build

This application can be built by simply running the ```make``` command from within this directory.


## Usage

The tiler can be run using the following command.

```./tiler <input> <cores> <display> <width> (<height>)```

The parameters that follow apply.

+ Input   - a PPM image to tile.
+ Input   - base name for output PPM, <tile#>-<output>.ppm.
+ Cores   - the number of cores to utilize for this parallel operation.
+ Display - 0 for timing, 1 for full report.
+ Width   - tile width, use alone for square tiles.
+ Height  - tile height if rectangular tiles are desired.

Example:  ```./tiler input.ppm 4 1 224```

Example:  ```./tiler input.ppm 4 1 2448 2050```


## Conversion

One may convert to and from PPM images using the Unix terminal command:

```convert <filenameIn>.<extensionIn> <filenameOut>.<extensionOut>```
