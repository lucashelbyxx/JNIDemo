# 设置CMake版本
cmake_minimum_required(VERSION 3.10.2)

# 设置变量
set(jnicpp_src "${CMAKE_SOURCE_DIR}/src")    #src源码路径
set(jnicpp_inc "${CMAKE_SOURCE_DIR}/inc")    #inc头文件路径

# CMake所有内置变量都只能到CMakeLists.txt所在目录路径，下面方式可以获取CMakeLists.txt所在目录的上一级目录路径
string(REGEX REPLACE "(.*)/(.*)" "\\1" CMAKE_UP_PATH  ${PROJECT_SOURCE_DIR})
set(jnilibs_dir "${CMAKE_UP_PATH}/jnilibs")  ##jnilibs目录路径 so/.a


# 1.创建和命名库，本demo里是要生成的库jnidemo.so
# 2.设置要生成的库的属性：STATIC(.a) 或 SHARED(.so)
# 3.设置生成库的源码路径
# 4.可以定义多个库，CMake都会进行编译，Gradle再自动将库打包到Apk
add_library(
        jnidemo    #设置so文件名称
        SHARED     #设置这个so文件为共享
        ${jnicpp_src}/jnidemo.cpp)   #源码路径

#指定需要使用的公共NDK库
find_library(
        log-lib  # 设置路径变量名称
        log)     # 指定需要CMake去搜寻定位的公共NDK库


# 使用add_library命令，通过指定IMPORTED选项表明这是一个要导入的库文件
# 相当于告知CMake,我要链接两个SHARED动态库：aaa、bbb
# 这两句必须在前面，要不然后面的语句不知道aaa、bbb是什么
add_library(aaa SHARED IMPORTED)
add_library(bbb SHARED IMPORTED)

# CMake属性设置函数，IMPORTED_LOCATION 表示设置目标aaa、bbb的文件路径属性
# ${CMAKE_SOURCE_DIR}：表示CMakeLists.txt的当前文件夹路径
# ${ANDROID_ABI}：编译时会自动根据CPU架构去选择相应的库
set_target_properties(aaa
        PROPERTIES
        IMPORTED_LOCATION
        "${jnilibs_dir}/${ANDROID_ABI}/libInterceptOpenXR.so")

set_target_properties(bbb
        PROPERTIES
        IMPORTED_LOCATION
        "${jnilibs_dir}/${ANDROID_ABI}/libMeshingProvider.so")

#链接头文件
target_include_directories(
        jnidemo    #Jni库
        PRIVATE    #对外引用属性
        ${jnicpp_inc})  #头文件路径

#包含头文件
#这个方法与target_include_directories()不同
#设置后，当前目录的所有子目录中的CMakeLists.txt头文件包含都会引用该方法中的变量定义
#include_directories(${jnicpp_inc})

# 指定需要用CMake链接到目标库的库。
# 可以链接多个库，例如在本脚本中定义的库、预构建的第三方库或系统库。
target_link_libraries(
        jnidemo     #指定目标库
        ${log-lib}  # 链接NDK中的log-lib库到目标库
        aaa
        bbb
)