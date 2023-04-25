<br/>
<p align="center">
    <img src="https://github.com/chrisdelmoro/42cursus/blob/main/badges/libftm.png" alt="Logo" width="150" height="150">

  <p align="center">
    A C library, the first assignment from 42's cursus.
    <br/>
    <img src="https://img.shields.io/badge/Mandatory-OK-brightgreen"/>
    <img src="https://img.shields.io/badge/Bonus-OK-brightgreen"/>
    <img src="https://img.shields.io/badge/Final%20Score-125-blue"/>
  </p>
</p>

# Libft

## Introduction
Libft is the very first project of the 42 cursus. In it, we are expected to write several functions that will help us throughout the majority of the fundamentals track. In it we will find functions to deal with characters, strings, numbers, memory allocation and treatment, as well as functions to deal with linked lists. This repo contain my original libft project but with aditional functions as well as two subsequent projects that are useful for other projects of the cursus.

## Division of the project
* **First Part:** A set of functions from the  libc. The functions are expected to have the same prototypes and implement the same behaviors as the originals. They must comply with the way they are defined in their  man. The only difference is their names.
* **Second Part:** A set of functions that are either not in the  libc, or that are part of it but in a different form.
* **Bonus Part:** A set of functions that are used to manipulate linked lists.
* **Aditional Functions:** Functions that I deemed useful to use as well as the get_next_line and ft_printf project.

## Makefile
| Command | Usage |
| --- | --- |
| `make` | creates .o files for all functions as well as the main library file, libft.a |
| `make clean` | removes the .o files used to create the library |
| `make fclean` | removes the .o & .a files |
| `make re` | removes all .o & .a files then remakes them |
