### Exploit
Here we see that our argument is passed to the `atoi` function.
A buffer is filled with what is in the file `/home/user/end/.pass`.
Then the result is used as an index to put a `\0` in the buffer.

So we need to find as string that will be used as an index to end the `main buffer` and is identical to the `main buffer`.
There is a string that just do that: `''`.
In fact the empty string will result to `0` when called with `atoi`.
So the `main buffer` will only be an empty string and the result of `strcmp` will be `0`.

### Get access
```bash
./bonus3 ""
```