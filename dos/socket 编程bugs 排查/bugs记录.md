#### bugs记录

**bug1**:Bind socket failed;

原因:

```
if((socket == socket(...))<0) 其中==改成=
```

**bug2**:

```
terminate called after throwing an instance of 'std::bad_function_call'
  what():  bad_function_call
buildexe.sh: 行 3:  5114 已放弃               (核心已转储) ./chatserver
```

原因:

