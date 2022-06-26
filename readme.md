# WSL2Tool

用于在windows中快速调用wsl2的命令的小工具

## 功能

- 将windows绝对路径作为命令参数时自动转译（相对路径由wsl2原生支持）
- 创建wsl指令到windows指令的映射
- 调用wsl2命令的输出将会自动转义 ***测试性**



## 如何使用

需要自行使用`msvc`或`gcc+mingw`进行编译。

仅在msvc + vs2022 + wsl2(ubuntu20.02tls)中勉强测试通过。

输入`wsl2tool.exe`以获取帮助。

### 调用wsl2指令

若传入的第一个参数不为 `~`时，将解析传入的windows路径并转义并正常调用wsl，例如`wsl2tool git clone https://github.com/dangjinghao/wsl2tool.git D:\wsl2tool  `将会自动转义，并最终转化为wsl可识别的目录格式:`wsl2tool git clone https://github.com/dangjinghao/wsl2tool.git /mnt/d/wsl2tool`。

### 创建指令映射

**注意，为了能正常使用此功能，请将本程序所在路径放在环境变量中**

`wsl2tool`提供了创建和删除指令映射的方式

```
 ~ [action: create/delete/create_map] [...]
[action:create] [wsl_command] --- create linux command on windows
[action:create_map] [nickname] [wsl_command] --- create nickname of linux command on windows
[action:delete] [wsl_command/nickname] --- delete linux command by name or nickname
```

例如，当我想要调用wsl2系统中的git，并且不想直接使用`wsl git`时，可以执行`wsl2tool ~ create git`，此时本程序会，如果此时已将本程序所在路径添加入环境变量，则可在全局使用`git`指令来调用wsl中的`git`，此指令本质为调用`wsl2tool git`的脚本，这意味着调用此指令的参数中，所有**windows绝对路径将会被自动转译**。

此外，本程序还提供了另一个功能，`create_map`指令类似于linux中的alias，允许你在windows中创建wsl2中的程序别名，例如运行`wsl2tool ~ create_map lgcc gcc`将在程序所在路径创建一个名为lgcc.cmd文件，随后可以使用lgcc来调用wsl中的gcc命令。

值得注意的是，此功能的设计初衷是防止两个系统中相同命令名称冲突直接调用时的冲突，例如在windows中存在mingw-w64+gcc的环境，和在wsl2(ubuntu)中存在gcc，虽然可以通过调用命令的后缀进行区分(gcc.cmd与gcc.exe)，但为了将两者的调用方式快速区分开，还是编写了此功能。这意味着**create_map功能不支持将参数映射**，例如`wsl2tool ~ create_map ll ls -l`指令，此类映射是不支持的。 

### 转义wsl2程序输出

*测试性*

当使用wsl2tool替代wsl程序作为调用wsl2内程序时，wsl2tool程序会修改wsl2程序的输出，同样是将wsl2路径转义为windows路径。