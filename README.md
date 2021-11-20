# Compilation_principle
山东大学泰山学堂编译原理代码

## 项目功能：本项目实现了简易的在线 IDE 功能

## 项目结构：
### 前后端部分

### 编译器部分

## 项目框架：
### 1.前后端部分：
使用了webpack框架，其中前端的显示使用了react。
### 2.编译器部分：
使用了c++代码
懒得配置makefile或者cmake了，偷懒使用了vscode的task.json。你需要将该项目导入在vscode中，使用task进行运行。


## 运行:
1. 首先需要编译 c++的项目在 zzyOnlineIDE/public/compiler/out 文件夹中需要生成一个main.exe文件
注：需要修改.vscode中 mingw的路径
2. 需要进入根目录,在命令行输入
    `cd zzyOnlineIDE`
3. build一下：
    ` npm run-script build`
4.  运行：
    `npm start`
5. 打开浏览器 输入：
    http://localhost:3000/

## 运行效果与演示