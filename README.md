# Compilation_principle
山东大学泰山学堂编译原理代码

## 项目功能：本项目实现了简易的在线 IDE 功能

## 设计思路：
    1.我们通过 c++项目实现编译器 功能，生成exe文件 
    2.我们通过客户端 向服务端请求数据，来进行修改source.code 执行exe文件，生成我们所需要的json存于虚拟的服务端中（这里我直接存在一个文件夹中）
    3.客户端发出请求数据指令，读取json文件，并且显示 。

## 项目结构：

### 前端部分 client
    共有四个界面: index，lexical，parser，run。
    index界面是写代码的界面
    lexical是显示词法分析的界面
    parser是显示语法分析的界面
    run 是生成的指令运行的界面

#### views：
    是每个界面的class 负责显示不同界面 

#### component：
    是对应每个界面的组件

### 后端部分 server
    当服务器收到前端代码将其保存在source.code中，然后执行exe文件（这里需要顺序执行，折磨死我了）

#### 

### 编译器部分

#### 项目框架

#### 实现功能

#### 实现原理

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

### index界面：
    在该界面书写代码，写完点击提交按钮，进行下一步操作
![image](https://github.com/zhangzuyuan/Compilation_principle/blob/master/image/index.png)

### receive界面：
    如果你的代码没有问题那么就会跳转到该界面
![image](https://github.com/zhangzuyuan/Compilation_principle/blob/master/image/receive.png)

### lexical界面：
    这是词法分析界面，你可以看到词法分析相关结果
![image](https://github.com/zhangzuyuan/Compilation_principle/blob/master/image/lexical.png)

### parser界面：
    这是语法分析界面，你可以看到语法分析相关结果
![image](https://github.com/zhangzuyuan/Compilation_principle/blob/master/image/parser.png)

### run界面：
    这是生成了相关指令后的程序运行界面，可以一步步的运行程序
![image](https://github.com/zhangzuyuan/Compilation_principle/blob/master/image/run.png)

## 致谢:
    xczhw 的帮助和设计思路的提供。