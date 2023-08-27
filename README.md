# BAIT 🪤

## The problem

Let's be honest... when using the terminal, there are just a handful of directories where we really do some work on.

Instead of typing, or looking at the history, for our last __cd__ command, why not _catch_ the most active directories in an easy and practical space?

Throw the _bait_ and catch the most used directories.

## Description

__Bait__ is a small CLI tool that _catches_ the current working directory every time you call the command.

You can review yours _catches_ and jump instantaneously to those directories.

The _catches_ are permanent and not tied to a specific session.

_* got some inspiration from [Harpoon](https://github.com/ThePrimeagen/harpoon)._

## Requirements

Linux, bash

Terminal type:

- xterm-256color

## Instalation 

Run the following command:

```sh
$ cd src
$ sudo make install
```

... afterwards, add the this function to the _.bashrc_ file:

```sh
bait() {
  eval $(bait-tool $1 3>&1 1>&2 2>&3)
}
```

