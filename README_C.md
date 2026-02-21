# Building the C translations

This folder contains C translations of the original shell scripts.

Build:

```sh
make
```

This produces three executables: `git_manager`, `clean_tags`, and `automatic_readme_generator`.

Usage is similar to the shell scripts. Example:

```sh
./git_manager "Commit message"
./git_manager "Commit message" -t -p
./clean_tags
./automatic_readme_generator
```

Notes:
- The programs shell out to `git` and expect to run in a git repository.
- On Windows, build with a POSIX-aware toolchain (Git Bash / MSYS / MinGW).
