# uC LibC for hobbyist OSs

uC is a lightweight and tiny implementation of Libc.

adam@DESKTOP-GP45GMR:~/microC$ ls -lh out/mc/libs/*
-rw-r--r-- 1 adam adam 14K Nov 15 10:45 out/mc/libs/micro_c.a
-rwxr-xr-x 1 adam adam 17K Nov 15 10:45 out/mc/libs/micro_c.so
adam@DESKTOP-GP45GMR:~/microC$ ls -lh test_linux/out/mc/libs/*
-rw-r--r-- 1 adam adam 21K Nov 15 10:33 test_linux/out/mc/libs/micro_c.a
-rwxr-xr-x 1 adam adam 22K Nov 15 10:33 test_linux/out/mc/libs/micro_c.so
adam@DESKTOP-GP45GMR:~/microC$

### After tests

#### Empty helper
- micro_c.a  (Static): 14KB
- micro_c.so (Shared): 17KB

#### For linux
- micro_c.a  (Static): 21K
- micro_c.so (Shared): 22K
