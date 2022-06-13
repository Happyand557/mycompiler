## 完成的功能

1. 可以实现sysy文法的识别
2. 可以生成抽象语法树
3. 可以生成符号表文件
4. 可以生成实验老师要求的ir
5. 划分基本块

## 依赖

1. g++
2. make
3. graphviz

## 运行

1. 进入mycompiler文件夹
2. make
3. ```
   ./build/minic -s -o 符号表文件 源文件
   ./build/minic -i -o ir文件 源文件
   ./build/minic -a -o 抽象语法树文件 源文件
   ./build/minic -c 函数名 -o 基本块文件 源文件
   ```
4. ```shell
   #自动化测试脚本使用
   bash minicrun.sh
   #删除自动测试产生的文件
   bash clean.sh
   ```
