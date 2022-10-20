# Classroom
### Environment requirement

```
Linux
mysql
mysql++
cmake
```



### cmake

```shell
cmake -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" -S ./ -B ./cmake-build-debug-
cd cmake-build-debug
cmake --build .
```



### sql

```
sorry!
编码仓促，你可能需要修改数据库连接配置（ip、密码、数据库名、mysql端口）：src/system/frontend.h

数据库文件：
./oom.sql
```



### server-setup

```shell
./oom_classroom_server
```



### client-setup

```
./oom_classroom_client
```



