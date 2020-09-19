# lwgps

# 1. 介绍

此项目是完成开源的lwgps与rt-thread的匹配。

原工程地址：[https://github.com/MaJerle/lwgps](https://github.com/MaJerle/lwgps)

## 1.1 许可证

lwgps移植包及lwgps遵循 MIT 许可。

# 2. 如何使用lwgps

使用lwgps package 需要先使用 `pkgs --upgrade` 更新包列表

然后在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    miscellaneous packages --->
        [*] lwgps: Lightweight GPS NMEA parser --->
            (0)   Enables double precision for floating point values
            (0)   Enables status reporting callback
            (1)   Enables `GGA` statement parsing
            (1)   Enables `GSA` statement parsing
            (1)   Enables `RMC` statement parsing
            (1)   Enables `GSV` statement parsing
            (0)   Enables detailed parsing of each satellite
            (0)   Enables parsing and generation of PUBX (uBlox) messages
            (0)   Enables parsing and generation of PUBX (uBlox) TIME messages
                  Version
```

然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

# 3、联系方式 & 感谢

* 维护：orange2348
* 主页：<https://github.com/orange2348>
* 邮箱：<orange2348@163.com>