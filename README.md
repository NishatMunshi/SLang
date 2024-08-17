# SLang: Simple Language
This is a test programming language. I don't know where it will end up.
- I have 3 ideas:
    - a compiled language
    - an interpreted language
    - a hardware description language

PS: Ok I don't think a hardware description language is the way to go.
Let's get rid of it:
- New ideas:
   - a compiled language
   - an interpreted language

PPS: Ok I now have decided what to do.

## slc
`slc` (abbreviation for "**simple language compiler**") is going to be the compiler for the compiled and assembled programming language named "**SLang**" (abbreviation for "**Simple Language**")

## Principle
As the name "**SLang**" suggests, it is only a simple language intended for learning about compilers. `slc` does not do any optimizations to the source code and only compiles it as it is. This is not going to change in the future because that will defeat the entire purpose of the language.

### SLang source file extension: `.sl`

## Supported Platforms

currently only supporting **linux**

## How To Build
### **step 1**: install dependencies
```console
$ sudo apt install gcc make
```
### **step 2**: compile `slc`  itself
```console
$ make -j -B -C slc/
```

## How To Run
```console
$ <path_to_slc> <source_filename> <output_filename>
```
When you first build `slc`, it will be located in `./slc/bin/`\
Output file is an assembly file

## Future Plans

I want to add interperting behavior to the compiler as well. (making it a **compreter**).

> [!WARNING]
> This behavior is unimplemented. Keep your expectations low.
### to compile
```console
$ <path_to_slc> -com <source_filename> <output_assembly_filename>
```
### to interpret

```console
$ <path_to_slc> -int <source_filename>
```