# How to

```shell
$ make
$ eval $(.bin/poc.o 3>&1 1>&2 2>&3)
```

__stderr__ and __stdout__ switch position.

This will change the current directory as defined in the code.
