### Exploit
We need to find an input value so that `atoi(input) < 10`.
Then our input is multiplied by 4 so that it to give the number of bytes copied into the `main buffer` of size 40.
So when multiplying our input by 4 it needs to gives us something greater than 40.
With that we can overwrite the `value` variable to get access to a new shell.

### Get access
Our input will be a negative number that overflows to 44 or more.
`int_min * 2` will overflow to zero. So we add `44` to this number and divide it by 4.
Out final number is:
`(-2,147,483,648 * 2 + 44 ) / 4 = -1073741813`
Now the number of bytes copied will be greater than the size of the buffer so we can write the `value` variable.
Our input need to be padded with 40 character and then the word `0x574f4c46` which is the string `FLOW`

```bash
./bonus1 -1073741813 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaFLOW
```