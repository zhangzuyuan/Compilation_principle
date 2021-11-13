cmake_minimum_required (VERSION 2.8)
#语法：include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
#它相当于g++选项中的-I参数的作用，也相当于环境变量中增加路径到CPLUS_INCLUDE_PATH变量的作用。
include_directories(include)
# 语法：link_directories(directory1 directory2 ...)
# 它相当于g++命令的-L选项的作用，也相当于环境变量中增加LD_LIBRARY_PATH的路径的作用。
#link_directories("/home/server/third/lib")

# 项目信息
project (src)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 src 子目录

add_subdirectory(LexicalAnalyzer)



# 指定生成目标
add_executable(server ${DIR_SRCS})