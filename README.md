# RoboarchNG
## Roboarch is a really stupid and simple CPU ISA i came up with one night and decided to write a VM and "assembler" for it.

### roboarchvm
Usage: ./roboarchvm bytecode (memsize) (output)

There is currently no way to get output from it other than the output file, which writes the entire memory of the vm (minus any trailing 0s).


### roboarchasm
Usage: ./roboarchasm input output
