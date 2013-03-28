C-Brainfuck
===========

Simple brainfuck implementation in C.

Install as a command line program
====

```bash
sudo curl https://raw.github.com/mvader/C-Brainfuck/master/brainfuck.c -o /usr/local/bin/brainfuck.c
sudo gcc -o /usr/local/bin/brainfuck /usr/local/bin/brainfuck.c
sudo rm /usr/local/bin/brainfuck.c
sudo chmod +x /usr/local/bin/brainfuck
```

Usage
====

File input:

```bash
brainfuck my_file
```

Inline brainfuck:

```bash
brainfuck "my brainfuck code"
```
