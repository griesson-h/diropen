# diropen
a silly CLI file manager for linux

## Note
This is my very first project and it was not made for real use

## Installation
Install git via your package manager
```bash
sudo pacman -S git # for arch-based linux distribution
sudo apt install git # for debian based one
```
then clone the repository
```bash
git clone https://github.com/griesson-h/diropen.git
```
To install you can use Makefile
```bash
cd diropen
make
```
or manually
```bash
cd diropen
gcc -o diropen diropen.c
sudo cp diropen /bin/
```
To run just type diropen
```bash
diropen
```

## Usage
To open a directory type the directory name (the name must not have spaces in it because I haven't fixed this yet)

To execute a file type &exe&

To create an empty file type &createafile&

To open/create a file via nano type &nano& (be sure you have it installed)

To open/create a file via vim type &vim& (be sure you have it installed)

