# ppsh — Custom Shell

ppsh is a custom shell implementation with extended capabilities for process management and file handling.

## Features

- When an error occurs while launching a file, ppsh automatically attempts to restart it up to 4 more times.
- The shell includes custom implementations of the following commands:
  - ls — list directory contents
  - cat — display file contents
  - killall — terminate processes by name
  - nice — set process priority
  - utils — a set of utility functions
  - cd — change the current working directory

