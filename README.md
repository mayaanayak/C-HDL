# CS128 Final Project - C++HDL
**Created by Sam Ruggerio, Maya Nayak, and Nicholas Park**

Do

```bash
$ git clone https://github.com/cs128-2021c/final-project-templating-is-turing-complete
```
to get a copy of the repository. 

## Description
Our project is a CLI wiring and simulator for logical circuits. Users can send commands to create and wire components, simulate using sets of inputs, and save and load schematics.

## Building and Running the CLI program

Run the following commands:
```bash
$ make clean
$ make
$ ./bin/exec
```

## Building and Running the test suite
Run the following commands:
```bash
$ make clean
$ make tests
$ ./bin/tests
```

## Using the CLI program

C++HDL supports feed-forward wiring and simulation. Feedback schematics are not supported due to the lack of time features in simulation. Feedback wiring behavior is undefined.

`help` Will display a general purpose help message for all commands.
```
> help
```

`save` and `load` will convert the user's schematic into a human-readable file, and can then read the file back into a working schematic. Using `load` will clear any working schematic the user created within the program.

```
> save <filename>
> load <filename>
```

A schematic has three major module types:

`register` - The working schematic's input wires. These modules have their states set to user input on simulation.

`monitor` - The working schematic's output wires. These modules' state will be displayed on completion of emulation.

Logic Gates - Dynamic input size modules that perform their logical operation on their inputs, then broadcast it to their outputs. Valid modules are `and or not nor nand xor`.


`add` and `delete` will create and remove modules from the working schematic respectively. `<module>` must be `register, monitor, and, or, not, nor, nand, xor`. The program prevents repetition of names.

```
> add <module> <name>
> delete <name>
```

`wire` and `unwrite` will create and remove a connection from `<name_one>` to `<name_two>`. Registers cannot have inputs, and monitors cannot have outputs. It also forbids the same module attaching itself multiple times to another module.

```
> wire <name_one> <name_two>
> unwire <name_one> <name_two>
```

`list` will list out the created modules in the working schematic. It can be used without a parameter, but adding a parameter will make it list only one major set of modules.

```
> list [registers/modules/monitors/all]
```

`clear` will remove all modules in the working schematic.

```
> clear
```

`run` will assign inputs to every register, and then simulate the working schematic. Every register must be assigned an input, either 1 or 0.

```
> run <register name> <1/0> [additional registers...]
```

For example, if I have the registers r1..r4, then if I want to set the binary input 9:

```
> run r1 1 r2 0 r3 0 r4 1
```
