# AntiShiftDelete
## 简介
AntiShiftDelete是一个Shell Extension，它的功能是禁用 永久删除(Shift+Delete) 快捷键。
有一些人（包括我自己）都惯用永久删除快捷键，从来不把文件删到回收站。然而，这并不是什么好习惯，如果我们删错了文件，这会给我们带来很多麻烦，反复做无用功……
AntiShiftDelete扩展便是帮助我们摆脱这个坏习惯的有力助手！安装这个扩展之后，当我们再次使用Shift+Delete快捷键删除文件时，资源管理器不会删除文件，而是会发出一声提示音，提醒你使用正常的删除功能。

## 原理
AntiShiftDelete使用了微软Detours库来Hook资源管理其内部的删除方法。所以，AntiShiftDelete需要是一个Shell Extension，因为Shell Extension会被资源管理器自动加载。

### Shell Extension
Shell Extension有很多种，不过为了让explorer.exe尽快加载插件，我选择使用 [IconOverlayHandler](https://docs.microsoft.com/en-us/windows/win32/shell/how-to-implement-icon-overlay-handlers) (实现 [IShellIconOverlayIdentifier](https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishelliconoverlayidentifier))，因为这种扩展可以在explorer.exe启动时直接加载。

### Hook
Microsoft Detours 库使用起来很方便，我也不打算多说。在资源管理器Hook的方法倒是挺有趣的。
在 Windows Vista, 7, 8, 8.1, 10 和对应的服务器版本中， explorer.exe不会直接调用WindowsAPI来操作文件而是使用FileOperation这个COM组件来操作文件。AntiShiftDelete便是Hook了FileOperation的虚函数达到阻止永久删除的目的。

## 兼容性
理论上，Windows Vista及以上版本x86和x64还有对应的服务器版本，都能使用这个扩展。但是我不确定是否真的能兼容这么多……

桌面版本: Windows Vista, Windows 7, Windows 8, Windows 8.1, Windows 10
服务器版本: Server 2008, Server 2008 R2, Server 2012, Server 2012 R2, Server 2016