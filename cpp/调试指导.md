# 调试指导v1
***
## 1.Win篇

配置mingw编译器，添加环境变量并且写入task文件，在exe文件生成的情况下即可使用gdb进行调试
## 2.Mac篇
    1. 准备工作
       1. 安装苹果官方开发者工具
       2. 安装以下插件
          1. c/c++
          2. c/c++ command adapter
          3. CodeLLDB
        
    2. 使用方法
       1. shift+commmand+b  编译生成文件
       2. F5 调试刚刚生成的.out文件


