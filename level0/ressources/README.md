### Brief
We can see that this program start with a main function taking one argument

### Exploit
For this program there is not really an exploit but rather you need to understand what the function does.
First it will pass the first argument of the program to atoi.
Then it will test the result to see if it's equal to 423.
If it's equal it will set the parameter needed to run a new shell with the permission of level1.
If it's not equal it just print out an error message.

### How to do it
```bash
# So to be able to access the next level you will do:
./level0 423
# With this you get access to a new shell with the permission to access the flag.
cat /home/user/level1/.pass
```
