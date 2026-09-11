# Weather Forecast Application

A C++ desktop Weather Forecast Application built with **Qt 6**. The
project uses a Qt GUI together with HTTP/API communication, JSON
parsing, weather data handling, and Qt Charts.

## Project Structure

-   `main.cpp` --- application entry point
-   `mainWindow.cpp / mainWindow.h` --- main GUI window
-   `Cities.cpp / Cities.h` --- city-related functionality
-   `Curl.cpp / Curl.h` --- HTTP/API communication
-   `CurlAbstract.cpp / CurlAbstract.h` --- Curl abstraction
-   `Data.cpp / Data.h` --- weather/data handling
-   `DataAbstract.cpp / DataAbstract.h` --- data abstraction
-   `Rapidjson.cpp / Rapidjson.h` --- JSON parsing
-   `RapidjsonAbstract.cpp / RapidjsonAbstract.h` --- JSON parsing
    abstraction
-   `Makefile` --- builds the application
-   `WeatherForecastApplication.pro` --- Qt project file

## Requirements

Ubuntu/Linux with:

-   `g++`
-   `make`
-   Qt 6
-   Qt Charts
-   Qt Widgets / GUI
-   `libcurl`
-   RapidJSON
-   required Qt/OpenGL libraries

## Build

Open a normal Ubuntu Terminal:

``` bash
cd ~/SWE/cpp_projects/Weather_Forecast_Application
```

Then build:

``` bash
make -j$(nproc)
```

If the build succeeds, the executable is:

``` text
WeatherForecastApplication
```

## Run

### Recommended run command

On this machine, VS Code is installed as a Snap. Its environment can
cause the executable to load incompatible Snap libraries.

Use this command to run the application with a clean environment:

``` bash
env -i \
PATH=/usr/bin:/bin \
HOME="$HOME" \
DISPLAY="$DISPLAY" \
XAUTHORITY="$XAUTHORITY" \
XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" \
./WeatherForecastApplication
```

### Build + Run

``` bash
cd ~/SWE/cpp_projects/Weather_Forecast_Application
make -j$(nproc)
env -i \
PATH=/usr/bin:/bin \
HOME="$HOME" \
DISPLAY="$DISPLAY" \
XAUTHORITY="$XAUTHORITY" \
XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" \
./WeatherForecastApplication
```

### One-line run command

``` bash
env -i PATH=/usr/bin:/bin HOME="$HOME" DISPLAY="$DISPLAY" XAUTHORITY="$XAUTHORITY" XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" ./WeatherForecastApplication
```

## Why `env -i`?

The normal:

``` bash
./WeatherForecastApplication
```

can fail in the Snap VS Code environment with an error such as:

``` text
symbol lookup error:
/snap/core20/current/lib/x86_64-linux-gnu/libpthread.so.0:
undefined symbol: __libc_pthread_init
```

The clean `env -i` command prevents the application's environment from
inheriting problematic Snap-related variables and explicitly keeps the
variables needed by the GUI:

-   `PATH` --- finds system commands
-   `HOME` --- user's home directory
-   `DISPLAY` --- connects the Qt GUI to the display
-   `XAUTHORITY` --- X11 authentication
-   `XDG_RUNTIME_DIR` --- desktop runtime directory

## Quick Workflow

``` bash
cd ~/SWE/cpp_projects/Weather_Forecast_Application
make -j$(nproc)
env -i PATH=/usr/bin:/bin HOME="$HOME" DISPLAY="$DISPLAY" XAUTHORITY="$XAUTHORITY" XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" ./WeatherForecastApplication
```

## Troubleshooting

### `libpthread.so.0: undefined symbol: __libc_pthread_init`

Use the clean-environment run command:

``` bash
env -i \
PATH=/usr/bin:/bin \
HOME="$HOME" \
DISPLAY="$DISPLAY" \
XAUTHORITY="$XAUTHORITY" \
XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" \
./WeatherForecastApplication
```

Do not change the source code or Makefile just because this runtime
error appears.

### GUI does not open

Check:

``` bash
echo "$DISPLAY"
echo "$XAUTHORITY"
echo "$XDG_RUNTIME_DIR"
```

Then run the application with the clean-environment command.

## Clean Build

If the Makefile has a `clean` target:

``` bash
make clean
make -j$(nproc)
```

Then run the executable with the command above.

## Development Workflow

1.  Open the project in VS Code.
2.  Edit the C++ files.
3.  Open a terminal.
4.  Build with `make -j$(nproc)`.
5.  Run with the clean `env -i` command.
6.  Repeat after changes.
