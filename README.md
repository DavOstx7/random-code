# Cert Automation

A simple python script for adjusting and validating certificates prototypes and flavors of devices.

## The script works as CLI with the following arguments:

* `-h` -> Show help message
* `--proto` Choose the wanted prototype out of the constant options. Required.
* `--flavor` Choose the wanted flavor out of the constant options.
* `--adjust-mac` Adjust the mac file name to the hard-coded standard.
* `--validate-suffix` Validate the mac file name suffix is valid.
* `--output-dir` The path to the output directory. If no output directory is given, a default one will be created.
* `--source-dir` The path to the source directory. Required.