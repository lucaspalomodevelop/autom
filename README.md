# autom
<img src="./readme/img/autom-logo.png">

**IN DEVELOPMENT, NOT READY FOR USE**

autom is a command-line tool for executing shell scripts, independent of the working directory.


## Installation Requirements
- gcc
- make

## Libraries
- [nlohmann/json](https://github.com/nlohmann/json)

## Compilation

1. Clone or download the QuickNote repository.

2. Make sure you have a C++ compiler installed on your system.

3. Make sure you have make installed on your system. 

4. Navigate to the autom directory.

5. Compile the source code:

`$ make`

## Usage

Use the following commands with autom:

- `[script]`: Runs a script if autom has a command with that name.

- `run [script]`: Runs a script if autom doesn't have a command with that name.

- `help`: Shows the help message.

- `ls`: Lists all available scripts.

- `add [script]`: Adds a new script.

- `new [script]`: Adds a new script (alias for add).

- `edit [script]`: Edits an existing script.

- `remove [script]`: Removes an existing script.

- `show [script]`: Shows the content of a script.


## Configuration

The configuration file is located at your home directory: `~/.autom/.automconfig.json`. 


## Contributing

If you encounter any issues, have suggestions for improvements, or would like to propose new features, please feel free to contribute. You can do so by opening an issue in the repository or submitting a pull request with your changes.

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).

## Authors

autom was developed by [lucaspalomodevelop](https://github.com/lucaspalomodevelop).