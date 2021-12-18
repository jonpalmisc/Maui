# Maui

Maui is an open source desktop application providing a user interface for the
free [Wolfram Engine](https://www.wolfram.com/engine/).

<div align="center">
  <img src="docs/ui.png" width="512">
  <br/>
</div>

## Building

Maui has two main dependencies: [Qt](https://www.qt.io/product/qt6) and the WSTP
C API. Both are required to build and run Maui. The WSTP C API is included with
the [Wolfram Engine](https://www.wolfram.com/engine/) which is free for
personal use.

With both of these dependencies installed, simply use CMake to generate the
appropriate build environment, then build Maui:

```sh
cmake -S . -B build -DWSTP_API_PATH="..." # -GNinja
cmake --build build
```

If the WSTP headers and libraries are already in your system paths (which is
unlikely), then passing the `-DWSTP_API_PATH` option to CMake is not needed.

## Contributing

Contributions are welcome! All code is formatted with `clang-format` using the
built-in "WebKit" preset; please ensure your code is formatted when submitting
a pull request.

## License

Copyright &copy; 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
