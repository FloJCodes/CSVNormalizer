# CSVNormalizer

CSVNormalizer is a C++ command-line tool for parsing, validating, and normalizing CSV files. It allows you to process CSV data with configurable delimiters, validate rows, and optionally remove rows with errors before writing the output to a file.

## Features

- **Custom Delimiters**: Specify the delimiter used in your CSV files.
- **Validation**: Detect rows that do not conform to expected format/validation rules.
- **Error Row Removal**: Optionally remove rows with errors from the output.
- **Console and File Output**: Preview parsed/validated data in the console or write results to a new file.
- **Robust Error Handling**: Clearly reports file access and parsing errors.

## Getting Started

### Prerequisites

- A C++17 (or later) compiler
- CMake (recommended for building)
- Standard C++ libraries

### Building

Assuming you have all source files (`main.cpp`, `io.hpp`, `parser.hpp`, etc.) in your project folder:

1. Create a `CMakeLists.txt` (example below):

    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(CSVNormalizer)

    set(CMAKE_CXX_STANDARD 17)

    add_executable(CSVNormalizer main.cpp parser.cpp io.cpp)
    ```

2. Build the project:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. The executable `CSVNormalizer` will be created in the `build` directory.

### Usage

```
CSVNormalizer <input.csv> <output.csv> [--delimiter <char>] [--remove-error-rows]
```

#### Parameters

- `<input.csv>`: Path to the input CSV file.
- `<output.csv>`: Path to the output CSV file.
- `--delimiter <char>`: (Optional) Specify a custom delimiter character. Default is `,`.
- `--remove-error-rows`: (Optional) If set, rows that fail validation will be excluded from the output.

#### Examples

Parse a CSV file using the default delimiter and include all rows (even those with errors):

```
./CSVNormalizer customers.csv cleaned.csv
```

Parse a CSV file with semicolon as delimiter and remove erroneous rows:

```
./CSVNormalizer customers.csv cleaned.csv --delimiter ";" --remove-error-rows
```

### Output

The program prints configuration and progress messages to the console. If errors are detected, they are displayed. The normalized/validated CSV is written to the specified output file.

## Project Structure

- `main.cpp`: Contains the main application logic and command-line interface.
- `parser.hpp`/`parser.cpp`: Handles CSV parsing and validation.
- `io.hpp`/`io.cpp`: Contains CSV writing utilities.
- `data/`: Sample CSV files (for development/testing).

## Extending

- Implement additional validation logic in `parser.cpp`.
- Support for more output formats can be added in `io.cpp`.
- Improve error reporting for specific column formats.

## Author

Developed by [FloJCodes](https://github.com/FloJCodes)
