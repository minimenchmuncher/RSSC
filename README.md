# R Wrapper for Sam Simulation Core (RSSC)

From [https://sam.nrel.gov](https://sam.nrel.gov):

> NREL's System Advisor Model (SAM) is a performance and financial model designated to facilitate decision making for people involved in the renewable energy industry.

In short, SAM is an exceptionally powerful and useful tool for modeling a variety of renewable energy systems under various financial structures. The Sam Simulation Core itself is a free, but closed-source precombiled library. NREL provides support, direction, and examples of how to interface with this library using a variety of programming languages on their [SDK website](https://sam.nrel.gov/sdk), but does not include R.

## Installation

Currently, Windows and Linux are the supported OSes, MacOS will be more fully supported soon (although you may try, and if you do, make a PR with any edits you made!). In the past SAM has been offered only as a pre-compilied library, they have since gone [open-source](https://github.com/NREL/SAM). The instructions that follow involve utilizing the pre-compiled binary. Until such a time as that changes, this package will not be available on CRAN.

In order to get started, you must register with NREL as a software developer at [https://sam.nrel.gov/sdk](https://sam.nrel.gov/sdk). Download the SDK, and note the download location.

Theoretically, the whole SDK is not necessary, only the binary and its associated header file. The binary itself is also distributed through the SAM program, obviating the need to download the SDK.

It is, at this point, not recommended to install this package using `devtools::install_github()`. Please see OS specific details for installation instructions. If you encounter issues in installation, raise an issue on this github page.

### Linux
1. After you have downloaded the SAM SDK, `git clone` this repository.
2. Next, copy the header file `sscapi.h` somewhere that makes sense (for example `/usr/include` or
   `/usr/local/include`)
3. And also copy the actual library `ssc.so` somewhere that makes sense (for example `/usr/lib` or
   `/usr/local/lib`)
4. Build

As a note, this package uses `autoconf` to generate the configure script as opposed to using "anticonf"/`pkg-config` (see `xml2` for a good example). Since the library and header file must be installed manually this option does not seem to work at this time.

### Windows

1. After you have downloaded the SAM SDK, `git clone` this repository.
2. Edit `src/Makevars.win` to reflect your library and header file locations. By default,
   they point to `C:\SAM\sam-sdk-2017-1-17-r4\sscapi.h` for the header file and
   `C:\SAM\sam-sdk-2017-1-17-r4\win(32|64)\ssc.dll` as the library.
3. Build
4. Test - run `RSSC::R_ssc_build_info()`

This will be revised shortly.

### Mac

This has not yet been attempted. It ought to work the same as the Linux instructions above. Be aware you'll need XCode at a minimum for compiling. The package has only been tested using `g++` on linux and Windows (through `Rtools`). Furthermore, the linux version (hence possibly the mac version as well) requires linking to `libdl` in addition to `ssc`, you need to make sure that is find-able.

Lastly, on account of the way `ssc` was distributed, you'll need to edit the provided `configure.ac` file so it finds the mac `ssc.dylib` instead of a linux `ssc.so`. Again, if you have questions or have done a successful install on a mac, do a pull request of your changes.

## To Do

This package is by no means fully developed. Currently, it can load the library, and display the build info.

### Modules
There is a template for the R side of the `pvwattsv5` module and a data structure using an S3 class. The presumption is that various modules need to be implemented individually. Writing a (R)C++ wrapper for this module is the first order of business.

### R Classes
Currently there exists a template for the `pvwattsv5` class in `inst/classes.yml`, as well as a few tests for instantiating instances of that class.

### Other issues
The architecture is currently in-flux, and no final design decisions have been made. The library itself makes some assumptions about organization. Generally, it creates a data container and fills it with values and other data structures, runs a module on that data structure (the same structure is used for inputs and outputs), and returns that data structure with the output attributes. However, the code doesn't enforce strong requirements that the data structure passed in is of the correct format.

The overall design approach taken to this point is that the user will provide the correct inputs to create the data object for the module they wish to run, then call a generic which, via method dispatch will find the correct method that corresponds to that object.

The reason this architecture was chosen instead of a less strongly-typed one is for the convenience of the user and the difficulty in debugging code reliant on a precompiled library, and that only partial tracebacks are possible should errors arise.

The flip side is that this creates some extra overhead and longer call stacks.
