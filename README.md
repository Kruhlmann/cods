# cods - C API for manipulating ODS documents

## Running tests

The following programs are required for running tests:

```
gcc
make
```

To run the tests:

```sh
make
./test
```

## Development

A make target `make compile_commands` is available for generating the `.clangd`
folder used by the clangd language server. This requires you to have `bear`
installed and running `make clean && bear make` to update these files.
