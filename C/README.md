# 概览
## 项目地址
[https://github.com/impact-eintr/LinuxC](https://github.com/impact-eintr/LinuxC)

## c的历史
- 1960 原型A语言->ALGOL语言
- 1963 CPL语言
- 1967 BCPL
- 1970 B语言
- 1973 C语言

## C语言特点
1. 基础性语言
2. 语法简洁 紧凑 方便 灵活(得益于指针)
3. 运算符 数据结构丰富
4. 结构化 模块化编程
5. 移植性好 执行效率高
6. **允许直接对硬件操作**

## 学习建议
1. 概念的正确性
2. 动手能力
3. 主动阅读优秀的程序段
4. 大量练习,编程是技术不是理论

## 学习思路
1. 基本概念
2. 数据类型 运算符 表达式
3. 输入输出
4. 流程控制
5. 数组
6. 指针
7. 函数
8. 构造类型
9. 动态内存管理
10. 常用库函数 
11. 调试工具和调试技巧


## 环境搭建与"Hello world"
## 环境
- 当前测试环境是安装了基于`archlinux`的`manjarolinux`发行版的物理机，大家自己搭建linux环境的话推荐试用或租用云服务器或者尝试`WSL`
- `gcc`版本是 10.2.0
- 编辑器使用`vim`(推荐vim配置[vimplus](https://github.com/chxuan/vimplus))
### "Hello world"
~~~ c
#inlcude <stdio.h>
#include <stdlib.h>

int main(void){
    printf("hello world\n");
    exit(0);
}
~~~

gcc 编译c的源文件过程

~~~ bash
gcc -v
~~~

**C源文件->预处理->编译->汇编->链接->可执行文件**

完整过程
- 预处理
~~~ bash
gcc -E hello.c > hello.i
~~~
- 编译
~~~ bash
gcc -S hello.i 
~~~
- 汇编
~~~ bash
gcc -c hello.s 
~~~
- 链接->可执行文件
~~~ c
gcc hello.o -o hello
~~~

或者
~~~ bash
gcc hello.c -o hello
~~~

又或者
~~~ bash
make hello
~~~

执行
~~~ bash
./hello

hello world
~~~

# 基本概念

## 怎么写代码
### 头文件包含的重要性
在c中，如果没有出现函数原型，就默认函数的返回值是int
~~~ c
#include <stdio.h>
//malloc 处于stdlib.h中，若不写，则默认认为malloc返回为整形
int main()
{
<<<<<<< HEAD
    int *num = malloc(sizeof(int));
    *num = 100;
    printf("%d\n",*num);
=======
    int *num = (int *)malloc(sizeof(int));
>>>>>>> d8201497ccb6ce60411ef4f1d6347921a54e7c22
    return 0;
}
~~~

~~~ bash
hello.c: 在函数‘main’中:
hello.c:5:23: 警告：隐式声明函数‘malloc’ [-Wimplicit-function-declaration]
    5 |     int *num = (int *)malloc(sizeof(int));
          |                       ^~~~~~
          hello.c:5:23: 警告：隐式声明与内建函数‘malloc’不兼容
~~~
- 错误写法

  ```c
  #include <stdio.h>
  int main()
  {
      //没有必要加入（int *）强制转换
      int *num = (int *)malloc(sizeof(int));
      return 0;
  }
  ```

- 正确写法
~~~ c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *num = (int *)malloc(sizeof(int));
    return 0;
}
~~~

**`tips: 1.必须使用-Wall 在C语言中除非GCC所报出的警告是自己非常确认为何产生，并认为可以忽略的，否则必须要对警告进行处理`**

**`2.必须包含所使用函数的所有头文件，-Wall可以看出来`**

**`3.段错误调试方法：首先修好所有warning，再printf大法`**

### 以函数为单位进行编写

要以函数为单位解决问题

在写程序初期，只要是能独立成函数的就独立成函数，写程序后期就可以自己有所经验那些需要那些不需要了。

### 声明部分+实现部分

前部分把各种声明和函数定义写到头部，别写到后部分

### return 0；一定要有

exit(0);和return 0;的区别：在单线程单进程没有区别

return 0;给父进程看的，若没有return 0；最后程序返回的是最后一条语句的返回值

### 适当的多用空格和空行

### 程序中适当的添加注释

可以参考/usr/linux源码中的注释，注释掉某个长段的代码采用#if 0预处理

## 算法：解决问题的方法（可以用流程图，NS图，有限状态机FSM推荐）

## 程序：用某种语言实现算法

## 进程：

## 防止写越界，防止内存泄漏，做到谁打开谁关闭，谁申请谁释放

## 数据类型 运算符 表达式

- 基本类型
  - 数值类型
    - short
    - int
    - long
    - float
    - double
  - 字符类型
  
- 构造类型
  - 数组(不是基本类型)
  - 结构体 struct
  - 共用体 union
  - 枚举类型 enum
  
- 指针类型

- 空类型 void

  `标准C中只规定了int > short,double > float，并没有具体规定各个类型所占的大小`

``` bash
int类型的数据
254 -> unsigned int -> 32bit
(254)10 = (1111 1110)2 = (376)8 = (FE)16

254
B11111110(c不认识这个表示，c语言不支持二进制，只能采用8或者16进制)
0376（以0开头）
0xFE
float类型的数据，存储为
0.xxx * 10 ^ y
31-22 8bit：存储指数y
22-0 bit ： 存储小数xxx
char类型的数据
ASSIC码表
NUL为ASSIC码为0的特殊字符
NULL是一个宏，它在几个标准头文件中定义，0是一个整型常量，'\0'是一个字符常量，而NUL是一个字符常量的名字。这几个术语都不可互换。
1、NULL用于表示什么也不指向，也就是空指针((void *)0)
2、NUL '\0'应该只被用于结束字符串
3、NUL没有被定义于C和C++，它不应该被使用，除非你自己定义它，像：#define nul '\0'
对于有符号的字符类型：其表示范围-128-127，而无符号-256-255
对于默认定义的char变量是有符号还是无符号，这个是未规定，无法确定的。
```


#### 类型转换
``` c
int i;
float f;
doubel d;
char ch;
//不同数据转换有两种方式
//隐式转换和显示转换（强制类型转换）
//隐式转换,会自动提升级别
ch + i -> i 
f -d -> d
(ch + i) - (float -double) -> double
//在‘大’的精度向’小‘的精度转换时，会损失一部分精度，具体损失需要具体分析。
```

#### bool

``` c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//false 代表0 ，非零即为真
int main() {
  bool a = false;
  printf("a = %d\n", a);
  exit(0);
}
```

#### 浮点型的失真问题

``` c++
//float类型并不是一个非常精确的表示类型，其最小分辨率由其存储方式决定
//故float类型无法具体判断是否和某一个数相等，只能判断是否在某一个范围内
//例如 3.0/1.0实际的float可能是3.000001,故需要判断范围
int func(float f) {
  if (f < 0) {
    return -1;
  } else if (fabs(f-0) <= 1e-6) { //无法与0进行比较，故需要这样
    return 0;
  } else {
  return 1;
  }
}
```

####  char

**在iso c中 `char`有无符号是未定义行为**

#### 不同形式的0

``` c++
0(整形) '0'(字符常量) "0"(字符串常量) '\0'(字符常量)
```

#### 输入输出
数据类型要和后续代码中所使用的输入输出要相匹配(小心自相矛盾)

注意前后的输入输出的是否有符号要匹配

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  unsigned int a;
  a = 1 << 31;
  printf("%d", a);
}

```

正确

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  unsigned int a;
  a = 1 << 31;
  printf("%ud", a);
}

```

### 常量与变量
#### 常量：在程序执行过程中值不会发生变化的量
- 整形常量 1 890
- 实型常量 1.2 3.14
- 字符常量 '\t' '\n' '\0' '\015'(8进制) '\x7f' '\018'(错误的表示！！，八进制不大于8)
- 字符串常量 ""（空串） "a" "abXYZ" "abc\n\021\010"(a b c \n \021 \0 1 8)
- 标识常量 ，例如#define
##### 宏的用法
``` c++
#include <stdlib.h>
#include <stdio.h>

#define PI 3.1415926
#define ADD 2+3
// 正确写法
//#define ADD (2+3),故最好加个括号
int main() {
  printf("%f\n", PI);
  printf("%d\n", ADD * ADD);
}

```

``` c++
#include <stdlib.h>
#include <stdio.h>
//带参的define的应用
// 注意a，b都要加上括号，来保证优先级顺序
#define MAX(a,b)	((a) > (b) ? (a): (b))

int main() {
  int a = 3, b = 5;
  printf("%d\n",MAX(a++, b++));
}
//此时b会自增两次，a自增一次
//即 ((a++) > (b++) ? (a++): (b++))
//为了避免这种情况可以采取下面这种

```

``` c++
#include <stdlib.h>
#include <stdio.h>
//带参的define的应用
#define MAX(a,b) ({int A=a,B=b; ((A) > (B) ? (A) : (B));})

int main() {
  int a = 3, b = 5;
  printf("%d\n",MAX(a++, b++));
}
//此时都只会自增一次
```

``` c++
#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) ({typeof(a) A=a,B=b; ((A) > (B) ? (A) : (B));})

int main() {
  int a = 3, b = 5;
  printf("%d\n",MAX(a++, b++));
  printf("%d\n",MAX(a++, b++));
}

```

在程序的预处理阶段，占编译时间，不占运行时间(没有函数调用的消耗)，但不检查语法(比较危险)

对于内核这些需要效率的可以用宏，对于时间不敏感要求稳定的采用函数


#### 变量：保存一些特定的内容，并在程序的执行过程中随时发生变化的量
[存储类型] 数据类型 标识符 = 值
                      TYPE     NAME  = VALUE

存储类型：（extern与前三个不同，不属于定义型的，而是说明型）

- auto 默认 自动分配空间，自动回收

- register 建议型（不会一定放在寄存器中） 寄存器类型 只能定义局部变量，不能定义全局变量，大小有限制，只能定义32位大小的数据类型，比如double就不可以。因为寄存器没有地址，所以一个register类型的变量无法打印出地址查看或使用。

- static 静态型 自动初始化为0值或空值 并且static变量的值有继承性。另外常用来修饰一个变量或者函数(防止当前函数对外扩展)

- extern 说明型，意味不能改变被说明的变量存储类型

  ##### 变量的生命周期和作用范围

  对于auto类型，不会初始化，会随机

  对于static类型，会初始化为0，只会初始化一次，具有继承性，初始化一此后地址就一直不会变了。

  通过static修饰一个函数或者变量，可以防止多个文件全局变量名/全局函数发生冲突，使其作用域仅在本文件内。

  全局变量有副作用，可能某处会不小心改变全局变量的值

``` c
#include <stdlib.h>
#include <stdio.h>

void func() {
  static int x = 1;
  x++;
  printf("%d\n", x);
}

int main() {
  func();
  func();
  func();
}

2
3
4
```

- extern 说明型 意味着不能改变被说明的量的值或类型 可以用来扩展外部变量的作用域
- 在模块化设计时，除非要对外部暴露的接口或者全局变量，否则必须将其声明为static

``` c++
#ifndef EXTERN_H__
#define EXTERN_H__

void func();

#endif
```

``` c++
#include "extern.h"

extern int i; // 不定义 而是引用了其他地方的i
//extern int i = 100;这个是不允许的，extern没有定义功能，只能声明该之
int func() {
  printf("[%s]%d\n", __FUNCTION__, i);
}
```


``` c++
#include "stdlib.h"
#include "stdio.h"
#include "extern.h"

int i = 10;

int main() {
  printf("[%s]%d\n", __FUNCTION__, i);
}
```

### 运算符与表达式

```c
运算符部分：
    1.每个运算符所
    2.结合性
    3.优先级
    4.运算符的特殊
    5.位运算的重要
```

#### 逻辑运算符的短路性
``` c++
#include <stdio.h>
#include <stdlib.h>
//当左边的条件为真的时候才回去判断右边 与运算符
//当左边的表达式为假的时候才会去判断右边 或运算符
int main() {
  int a = 1, b = 2, c = 3, d = 4;
  int m = 1, n = 1;
  
  (m = a > b) && (n = c > d);
  
  printf("m = %d\n n = %d\n", m, n); // m : 0 n : 1
}
```

##### 赋值运算符为自右向左边结合性质

```
a = 6
a -= a *= a += 3;
a最终结果为0
```

#### sizeof（作为运算符而不是函数）

``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("%lu, %lu, %lu, %lu, %lu, %lu, %lu\n",
         sizeof(int),sizeof(short), sizeof(long),
         sizeof(double), sizeof(float), sizeof(char), sizeof(void*));
}

4, 2, 8, 8, 4, 1, 8

```

#### 位运算

- | 按位或
- & 按位与
- ^ 按位异或
- ~ 按位取反

> 应用

将操作数中的第n位置1 其他位不变 **num = num | 1 << n;**
将操作数中的第n位置0 其他位不变 **num = num & ~(1<<n);**
测试第n位: **if(num & (1<<n))**

从一个指定宽度的数中取出某几位：num = num & ((1<<a)|(1<<b))

## IO(标准IO和文件IO)

### 格式化的输入输出：

- printf

#### 变长参数 

`格式字符： %[修饰符]格式符`

格式符号：

![image-20230415111434249](/home/yang/LinuxC/C/image-20230415111434249.png)

修饰符号：

![image-20230415112100267](/home/yang/LinuxC/C/image-20230415112100267.png)

`l的使用：`

```
在计算机的世界中没有单位的数据是没有意义的，会自动当作整数进行处理
1.l修饰 d,o,x,u 指定输出精度为long
2.l修饰e,f,g 指定输出精度为double
3.L修饰如数常量表示该常量为long类型，例如
#define 5G 5*1024*1024*1024
应该为
#define 5G 5LL*1024LL*1024LL*1024LL
对于例如
add (long,long)
传入
add（4L，4L）
```



``` c++
int main() {
  int i = 123;
  printf("%4d\n", i);
  
  float f = 1.23455;
  printf("%.3f\n", f);
  
  char* s= "helloworld";
  printf("%10.5s\n", s);
}
```

#### 刷新缓冲区

`建议每一行之后加上一个\n，方便实时输出从而方便调试或者其他`

缓冲区刷新的条件：

`1.\n	2.缓冲区满了	3.fflush函数`


``` c++
int main() {
  printf("[%s:%d] before while().", __FUNCTION__, __LINE__);
  while(1);
  printf("[%s:%d] after while().", __FUNCTION__, __LINE__);
}
```

正确写法
``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("[%s:%d] before while().]\n", __FUNCTION__, __LINE__);
  // 或者
  //printf("[%s:%d] before while().", __FUNCTION__, __LINE__);
  //fflush(stdout); 
  while(1);
  printf("[%s:%d] after while().", __FUNCTION__, __LINE__);
}

```

- scanf

  **scanf的format不要加多余的字符**

  **使用scanf时空格，回车，tab都表示该值的结束，例如：**

  ```
  scanf("%d%f",&a,&b);
  输入12 3或者 12 tab 3 都表示分别赋值
  同样对于字符串，若输入中带有空格，tab，回车则会只截取空格前面那一段赋值,下面的例子可演示
  ```

  **scanf使用%s非常危险：1.输入空格，tab，回车会截取 2.无法预测输入的长度，可能会溢出数组**

  解决方法是对于scanf的返回值要校验

``` c++
int main() {
  int i;
  scanf("%d", &i);
  printf("%d\n", i);
}
```

> scanf 在使用 `%s` 的时候要特别小心

``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  char S[3];

  scanf("%s", S); // 如果输入 abcdef
  printf("%s", S); // 可能会出现段错误
}

```

> scanf 在循环中使用的时候要特别小心，防止方法是对scanf的返回值进行校验

``` c++
int main() {
  int ret = 0;
  int d = 0;
  
  while(1) {
    ret = scanf("%d, d);
    if (ret == -1) {
      perror("Error");
      break;
    }
    printf("&d\n", d);
  }
  exit(0);
}
```

> 处理换行，getchar接受的输入可能是功能字符，例如回车也会算作getchar的返回值
>
> scanf中的抑制符 * /getchar()吃掉中间产生的回车

``` c++
int main() {
  int i = 0;
  char c = 0;
  //当连续两次以上使用scanf时，下一个scanf会接受到上一个scanf的回车
  //在第二次scanf使用抑制符吃掉这个回车或者用getchar曲调这个回车
  scanf("%d", &i);
  scanf("%*c%c", &c);
  // 或者
  //getchar();
  //scanf("%c", &c);
  printf("i = %d, c = %c", i, c);
}
```

> putchar/getchar

```
返回值都是unsigned int，因为出错时会返回EOF
read as an unsigned char cast to an int or EOF on end of file or error
putchar的参数是int类型
```

> gets/puts(略)

```
gets非常危险，不对缓冲区作任何检查，推荐是使用getline（动态内存,不用给出能接受的最大大小）
或者fgets（静态内存,需要给出能够接受的最大大小）
```



# 流程控制

#### 自然逻辑

流程图画图工具:

windows: 微软的Visio

linux:Dia 流程图画图工具,可以集成到git项目中

推荐每次写程序之前先画一个流程图

> if-else只和最近的一个相匹配,比如说else之和最近的if相匹配,而不是通过类似与python一样调整豫剧的对齐来改变匹配

流程控制的情况一定要完善:

> 1. 对于两种情况A,B: 不要if(A){}else{} 而是 if(A){}else if(B) else,保证流程的完善
> 2. switch中一定要加入default

switch中的case标签需要为常量

**`有限状态机一定是需要用到case语句的.`**

#### 循环

while  do-while for if-goto

`while与do-while的区别:do-while至少执行一次,而while最少执行0次.`

do-while适合于一些你必须执行一次才能判断的情况.例如:

```c
do 
{
	menu();
	scanf();
	if()
	{
		do sth;
	}
}while();
//而不是
menu();
scanf();
while()
{
    do sth;
}
```

`if-goto循环慎用:因为其实现的是无条件的跳转,会破坏模块化编程的结构,且不能跨函数跳转,因为会破坏堆栈.`

#### 典型的死循环

```c
while(1);
for(;;)	
```

#### 辅助的两个关键字

```
break
跳出循环或者switch语句
continue
跳出本次循环
```



# 数组

构造类型 连续存放
## 一维数组
[存储类型] 数据类型 标识符[下标]

### 初始化

- static

``` c++
static int a[10];
```

- {}

``` c++
int a[3] = {1, 2, 3};
int a[3] = {1,}; //a中为1，0，0
//如果是单纯为
int a[3];//此时a中的数据都是未定义，随机的数据
int a[3] = {};//a中数据都为0
```

### 元素引用
- arr[i]
- arr+i

#### 数组名

一个**常量**

``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[3] = {1, 2, 3};
  printf("%ld\n", sizeof(arr));
  // 下面这句是错的
  arr = {4, 5, 6};
  for (int i = 0;i < sizeof(arr)/sizeof(int);i++) {
    printf("%d", *(arr+i));
  }
}

```



### 数组越界
c对数组不进行越界检查，需要格外小心

### 练习

数据排序算法：冒泡，选择法，快速排序

``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fib[10] = {1, 1};

  for (int i = 2;i < 10;i++) {
    fib[i] = fib[i-1]+ fib[i-2];
  }
  for (int i = 0;i < 10;i++) {
    printf("%d ", fib[i]);
  }
}

```


``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[] = {2, 3, 5, 4, 6, 7, 1, 9};
  for (int i = 0;i < sizeof(arr)/sizeof(int);i++) {
    for (int j = 0;j < sizeof(arr)/sizeof(int)-1-i;j++) {
      if(arr[j] > arr[j+1]) {
        int tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
    }
  }
  for (int i = 0;i < sizeof(arr)/sizeof(int);i++) {
    printf("%d ", arr[i]);
  }
}

```

``` c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[] = {3, 2, 5, 4, 9, 7, 1, 6};
  for (int i = 0;i < sizeof(arr)/sizeof(int);i++) {
    int m = i;
    for (int j = i+1;j < sizeof(arr)/sizeof(int);j++) {
      if(arr[j] < arr[m]) {
        m = j;
      }
    }
    if (m != i) {
      int tmp = arr[i];
      arr[i] = arr[m];
      arr[m] = tmp;
    }
  }
  for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
    printf("%d ", arr[i]);
  }
}

```

数组例子：fibonacci数列，排序算法，进制转换

通过删除法求质数

## 二维数组
[存储类型] 数据类型 标识符[行下标][列下标]

```
int a[M][N] = {{1,2,},{3}}
```

``` c++
int main() {
  int a[M][N] = {1, 2, 3, 4, 5};
  int b[][N] = {1, 2, 3, 4, 5};//行可省略
  int c[M][] = {1, 2, 3, 4, 5}; // 错误，列号不可省略
  for (int i = 0;i < M;i++) {
    for (int j = 0;j < N;j++) {
      printf("%d ", *(a+i+j*));
    }
  }
}
```

#### 二维数组的例子

```
1.行列互换
2.求最大值及其所在的位置
3.求各行各列的和
4.矩阵乘法
```



#### 深入理解二维数组

二维数组所有元素仍然是按照一维线性存储的。

1.二维数组中a和a[0]表示的都是第一个元素的地址

a[2][3] = b[3] + c[3]
a[0] = b[0]
a[1] = c[0]


## 字符数组
### 定义以及初始化
[存储类型] char 标识符[]

**注意部分初始化的时候，剩余部分会自动初始化为'\0'**

### IO
scanf 无法获取带有分隔符的字符串(`\t`, `\n`, ` `)


### 常用函数
- strlen & sizeof

  **strlen计算的是数组中遇到第一个'\0'前的大小，sizeof是整个字符串数组的大小。**

- strcpy & strncpy

  **strcpy不会检查des是否能够容纳下src，而strncpy则会指定复制的最多n个字符。**

- strcat & strncat（区别如上所示）

- strcmp & strncmp

  **只比较前n个字符**

> 单词统计

``` c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 1024

int main() {
  char str[STRSIZE] = {};
  fgets(str, STRSIZE, stdin);
  int count= 0, flag = 0;

  for (int i = 0;str[i] != '\0';i++){
    if (str[i] == ' ') {
      flag = 0;
    } else if(!flag) {
      count++;
      flag = 1;
    }
  }
  printf("%d\n", count);
}

```

# 指针

**指针是最节省资源的一种调用函数的方法**

**64位环境 指针类型占用8个字节**
**32位环境 指针类型占用4个字节**

## 变量与地址
变量对某块内存的抽象表示
指针 == 地址 变量名 == 抽象出来的某块空间的别名

## 指针与指针变量

``` c++
int i = 1;
int *p = &i;
int ** q = &p;
```

## 直接访问与间接访问

``` c++
i = 1;
&i = 0x2000;
p = 0x2000;
&p = 0x3000;
*p = 1;
q = 0x3000;
&q = 0x4000;
*q = 0x2000;
**q = 1;
```

## 空指针与野指针

指针一旦定义就要给定地址

## 空类型（任何类型的指针可以赋给他，他也可以赋给任何类型）

``` c++
char *s = "hello";
void *i = s;
// 相当与定义一个存储地址，但是*p此时未定义而已
```

## 定义与初始化的写法


## 指针运算
指针可以进行的运算：& * 关系运算 ++ --

## 指针与数组

### 指针与一维数组

``` c++
#include <stdlib.h>
#include <stdio.h>

int main () {
  int a[3] = {1, 2, 3};
  // a是常量 p是变量
  int *p = a;

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    printf("%p -> %d\n", p+i, *(p+i));
  }
}

```

**`p++` != `p+1`**

``` c++
#include <stdlib.h>
#include <stdio.h>

int main () {
  int a[3];
  int *p = a;

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    scanf("%d", p++);
  }

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    printf("%d\n", *(p++));
  }
}

```

printf("",表达式1,表达式2,....)会从后面开始执行，比如表达式2再执行表达式1

### 指针与二维数组

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  int a[2][3] = {{1, 2, 3},{ 4, 5, 6}};
  int (*p)[3] = a;

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    for (int j = 0;j < sizeof(*a)/sizeof(**a);j++) {
      printf("%d ", *(*(p+i)+j));
    }
  }
}

```

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  int a[2][3] = {{1, 2, 3},{ 4, 5, 6}};
  int *p = &a[0][0];

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    for (int j = 0;j < sizeof(*a)/sizeof(**a);j++) {
      printf("%d ",*(p+(i * sizeof(*a)/sizeof(**a))+j));
    }
  }
}

```

### 字符数组和其指针

------

与上面类似，针对于传入字符的函数，其实质上是传入一个字符的指针，例如

```c
puts(p);	//p可以为一个字符指针
// 又或者
putchar(p);	//p同样可以为一个字符指针
```

bss段常量段不可写入，若尝试写入会段错误

## const与指针

``` c++
const float pi = 3.14; // 常量化变量
// 但是可以通过指针简介的修改pi的值
```

> 先看到指针就是指针 先看到常量就是常量
>
> 看const 和 * 这两个谁在前面
>
> 看const后面是什么，const后面不能改变

- 常量指针 指向的内存不能通过这个指针修改

``` c++
const int* p; //*p即p指向的内存不能改变

int const *p;

char *strcpy(char *restrict dest, const char *src); // src是源字符串 不应该被修改
```

- 指针常量 指向的位置不能变 可以通过这个指针修改内存的值

``` c++

int *const p; //p指针变量的内容不能改变

const int *const p;
```


## 指针数组与数组指针
### 指针数组

``` c++
int *arr[3]//[]的优先级比*高，抽象出来 type name = value；
// 这种定义的看法，哪个优先级高哪个就放在右边，然后按照type name公式来看
```

指针数组排序

``` c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *name[5] = {"golang", "java", "c", "dart", "erlang"};

  int k;
  char *tmp;
  for (int i = 0;i < (sizeof(name)/sizeof(*name))-1;i++) {
    k = i;
    for (int j = i+1;j < (sizeof(name)/sizeof(*name));j++) {
      if (strcmp(name[k], name[j]) > 0) {
        k = j;
      }
    }
    if (k != i) {
      tmp = name[i];
      name[i] = name[k];
      name[k] = tmp;
    }
  }

  for (int i = 0;i < (sizeof(name)/sizeof(*name));i++) {
    printf("%s\n", *(name+i));
  }
}

```

### 数组指针

``` c++
int a[2][3] = {{1, 2, 3},{ 4, 5, 6}};
int (*p)[3] = a;
// 按照TYPE NAME公式可变为 int [3] * p,带括号的反而放在最右边，即为直线一个int [3]类型的数组
// 与int **p; 相区别，按照 TYPE NAME = VALUE；即为指向一个int * 类型的指针
```

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  int a[2][3] = {{1, 2, 3},{ 4, 5, 6}};
  int (*p)[3] = a;

  for (int i = 0;i < sizeof(a)/sizeof(*a);i++) {
    for (int j = 0;j < sizeof(*a)/sizeof(**a);j++) {
      printf("%d ", *(*(p+i)+j));
    }
  }
}

```

## 多级指针
没啥好说的

# 函数

## 函数的定义

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  exit(printf("Hello!\n"));
}

```

```
函数中如果没有指定return语句返回并结束该函数，会以最后一个执行的语句的返回值作为返回
```

`一个进程的返回状态是给他的父进程来看的`

## 函数的传参

- 值传递
- 地址传递
- 全局变量

## 函数的调用
- 嵌套

``` c++
#include <stdlib.h>
#include <stdio.h>

int max(int a, int b, int c) {
  int tmp = a > b ? a : b;
  return tmp > c ? tmp : c;
}

int min(int a, int b, int c) {
  int tmp = a < b ? a : b;
  return tmp < c ? tmp : c;
}

int dist(int a, int b, int c) {
  return max(a, b, c) - min(a, b, c);
}

int main() {
  printf("%d\n", dist(8, 5, 10));
}

```

- 递归

``` c++
#include <stdio.h>
#include <stdlib.h>
// 递进条件
// 结束条件
// 非常难，需要用数学验证表达后，再表示出来
int func(int n) {
  if (n < 0) {
    return -1;
  }
  if (n == 1 || n == 2) {
    return 1;
  }
  return func(n-1) + func(n-2);
}

int main() {
  int n;
  scanf("%d", &n);
  printf("fib %d = %d", n, func(n));
  exit(0);
}

```


``` c++
#include <stdio.h>
#include <stdlib.h>

int func(int n) {
  if (n < 0) {
    return -1;
  }
  if (n == 0 || n == -1) {
    return 1;
  }
  return n * func(n - 1);
}

int main() {
  int n;
  scanf("%d", &n);
  printf("%d! = %d", n, func(n));
  exit(0);
}

```

## 函数与数组

``` c++
#include <stdlib.h>
#include <stdio.h>
// 函数的参数为数组时，一定需要数组的大小
// 注意这里的int *arr 的大小是8个字节 是一个普通的指针不是数组 所以一定要传大小
void printarr(int *arr, int size) {
  for (int i = 0;i < size;i++) {
    printf("%d ", *(arr+i));
  }
  printf("\n");
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  printarr(arr, sizeof(arr)/sizeof(*arr));
}

```

``` c++
#include <stdlib.h>
#include <stdio.h>

void printarr(int *arr, int size) {
  for (int i = 0;i < size;i++) {
    printf("%d ", *(arr+i));
  }
  printf("\n");
}

void printarr2(int (*p)[3], int m , int n) {
    //这里sizeof（p）为8
  for (int i = 0;i < m;i++) {
    for (int j =0;j < n;j++) {
      printf("%4d ", *(*(p+i)+j));
    }
    printf("\n");
  }
}

int main() {
  int arr[][3] = {1, 2, 3, 4, 5, 6};
  printarr2(arr, 2, 3);
}

```

## 函数的指针
- 指针**函数**

  `是一个返回为指针的函数`

  针对某些函数，函数只完成自己的职责，不要越俎代庖，只需要返回指针就可以了，后一步的处理不管。

``` c++
#include <stdio.h>
#include <stdlib.h>

#define M 2
#define N 3

int *findnum(int (*p)[N], int num) {
  if (num > M - 1) {
    return NULL;
  }
  return *(p + num);
}

int main() {
  int arr[M][N] = {{1, 2, 3},{ 4, 5, 6}};

  int *res = findnum(arr, 1);

  for (int i = 0; i < N; i++) {
    printf("%d ", *(res + i));
  }
}

```

- 函数**指针**(指向函数的指针)
`类型 (*指针名)(形参)`

- 函数指针数组
  `类型 (*数组名[下标]) (形参)`

  `上面两者的形式参数都是放在最后面的`

指向指针函数的函数指针数组

``` c++
int *(*funcp[N])(int)
```

实际例子
``` c++
int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
```

# 构造类型
## 结构体
### 产生及意义
描述复杂的数据类型

结构体定义在main函数外

### 类型描述

``` c++
struct node_st{
  type1 name1;
  type2 name2;
  ...
};
```

### 嵌套定义

``` c++
struct day {
  int H;
  int M;
  int S;
};

struct student_st{
  char *name;
  struct day day;
};
```

#### 补充互相嵌套的结构体

```c
struct a;
struct b;
struct b{
struct a *va; //注意这里只能是指针，否则会出现循环定义，编译不通过
};
struct b
{
 struct a *vb; //同理这里只能是指针类型，不能定义为struct a vb;
};
```

### 定义变量 初始化以及成员引用

- 结构体 .引用，针对的是结构体本身

- 结构体指针 ->，针对的是指向结构体的指针

  **指针指向的类型决定了 p+1跳多少个字节**

``` c++

struct A {
  int i;
  char c;
  float f;
};

int main() {
  // TYPE NAME = VALUE;
  struct A a = {123, 'A', 2.22}; // 初始化
  struct A a_ = { .c = 'A', .f = 2.22}; // 部分初始化
  struct A *ap = { .c = 'A', .f = 2.22}; // 部分初始化
  
  printf("%d %c %.2f\n",a.i, a.c, a.f); // 成员引用
  // 123 A 2.22
  printf("%d %c %.2f\n",a_.i, a_.c, a_.f); // 成员引用
  // 0 A 2.22
  printf("%d %c %.2f\n",ap->i, ap->c, ap->f); // 成员引用，针对的是指针
  // 0 A 2.22
}
```

### 占用内存空间大小
`addr % sizeof(type)` 不能整除的话就要继续往下偏移

``` c++
#include <stdio.h>
#include <stdlib.h>

struct A {
  int i;
  char c;
  float f;
};
// 默认会进行四个字节对齐，如果相邻的两个可以合并，则会合并
// 可以使用下面的方法取消对齐 常用于网络通信，防止不同机器环境对齐不一定为四个字节
struct B {
  int i;
  char c;
  float f;
}__attribute__((packed));

int main() {
  struct A a;
  struct B b;

  printf("A = %ld\n", sizeof(a));
  printf("B = %ld\n", sizeof(b));
}

```

#### 结构体传参一般采用指针传参，这样的开销比直接传结构体要小很多。

两个同样定义的结构体可以直接等于来传参

```
struct student p,q;
...
p.id = q.id
p.xx = q.xx
可以直接
p = q
```

## 共用体

### 产生及意义
N选一 多个成员共用一块空间 取最大的成员的类型大小作为共用体的类型大小
### 类型描述

``` c++
union test_un{
  int i;
  float f;
  double d;
  char ch;
};
```

### 嵌套定义
同结构体，共用体 可以互相嵌套，共用体可以嵌套结构体，结构体可以嵌套结构体

###  定义变量 初始化以及成员引用
成员引用：
- u.成员名（u是结构体本身的情况下）
- up->成员名（针对up是结构体指针的情况下）

> 32位的无符号数的高16位和低16位相加

``` c++
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
  uint32_t i = 0x11223344;
  printf("%x\n", (i>>16)+(i&0xFFFF));
}
```

另一种写法
``` c++
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

union {
  struct {
    uint16_t i;
    uint16_t j;
  }x;
  uint32_t y;
}u;
// 通过将同一个内存用不同的划分方式
int main() {
  uint32_t i = 0x11223344;
  printf("%x\n", (i>>16)+(i&0xFFFF));

  u.y = 0x11223344;
  printf("%x\n", u.x.i + u.x.j);
}

```

### 位域

不以字节而以位为单位划分

```c
union
{
	struct
	{
		char a:1;
		char b:2;
		char c:1;
	}x;
	char y;
}w;
// 问如果w.y = 1;此时a，b，c为多少
```



## 枚举

``` c++
enum 标识符{
  成员1;
  ...
};
// 会根据第一个值，依次加一，若不指定则从0开始
// enum 可以看作宏，但是会自增，而且gcc -E 预处理不会和宏一样会替换
```

``` c++
enum day {
  MON = 1,
  TUS,
  WEB,
  THR,
  FRI,
  SAT,
  SUN,
};

int main() {
  enum day a = FRI;
  
  printf("%d\n", a);
}
```

``` c++
enum state {
  RUNNING = 1,
  STOP,
  PAUSE,
};

struct job {
  int id;
  int state;
  time_t start, end;
};

int main() {
  struct job_st job1;
  
  switch(jobs.state) {
    case RUNNING:
      // TODO
      break;
    case STOP:
      // TODO
      break;
    case PAUSE:
      // TODO
      break;
    default:
      // TODO
      abort();
  }
}

```

### **动态内存管理**

------

malloc ralloc realloc free

原则：谁申请谁释放

calloc：申请连续的多个空间：m*n

malloc：申请size_t大小的空间

realloc：扩大已经申请的空间，如果不连续，则会释放之前，移到一个线性的空间去。

```
int * p = malloc();
malloc的返回值为void * ，除非编译器警告，否则不需要强转为(int *)，不用写成
int *p = (int *)malloc();
```

注意malloc和free应该在同一个函数中，否则会内存泄漏

```c
void func(int *p,int n)
{
    p = malloc(n);
    if(p == NULL)
        exit(1);
    return ;
}

int main(void)
{
    int num = 100;
    int *p = NULL;

    func(p,num);
    free(p);
    exit(0);
}
```

注意上面的形参与实参

修改

```c
void func(int **p,int n) //
{
    *p = malloc(n);//
    if(*p == NULL)//
        exit(1);
    return ;
}

int main(void)
{
    int num = 100;
    int *p = NULL;

    func(&p,num);//
    free(p);
    exit(0);
}
```



## typedef

`typedef type typename`

``` c++
typedef int INT

int main() {
  INT i = 9;
}
```

> typedef 和 define 的区别

``` c++
#define IP int *
type int *IP;

int main() {
  // 宏
  IP p, q;
  int *p, q; // 一个int * 一个int
  
  // typedef
  IP p, q;
  int *p, *q; // 两个int *
}
```

> 数组

``` c++
typedef int ARR[6]; // int [6] 改名为 ARR

ARR a; // int a[6];
```

> 结构体

``` c++
typedef struct {
  int i;
  float f;
}NODE, *NODEP;
```

> 函数

``` c++
typedef int *FUNC(int)
```

> 函数指针

``` c++
typedef int* (*FUNCP)(int)
```

# 动态内存管理
- malloc
- calloc
- realloc
- free
**谁申请谁释放**

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  int *ip = malloc(sizeof(int));

  *ip = 1;

  printf("%d\n", *ip);
  free(ip);
}

```

> 动态数组

``` c++
#include <stdlib.h>
#include <stdio.h>

int main() {
  int *p;
  int num = 5;
  p = malloc(num * sizeof(int));

  for (int i = 0;i < num;i++) {
    scanf("%d", p+i);
  }
  for (int i = 0;i < num; i++) {
    printf("%d ", *(p+i));
  }

  printf("\n");
  exit(0);
}

```

> 内存申请与函数传值

``` c++
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void func1(void *p, size_t size) {

  if(p == NULL) {
    return;
  }
  p = malloc(size);
}

void func2(int **p, size_t size) {

  if(*p == NULL) {
    return;
  }
  *p = malloc(size);
}

void *func3(void *p, size_t size) {
  if(p == NULL) {
    return NULL;
  }
  p = malloc(size);
  return p;
}

int main() {
  int num = 100;
  int *p = NULL;

  func1(p, num); // 内存会泄露

  func2(&p, num); // 传递二级指针

  p = func3(p, num); // 将申请的内存返回

  free(p);
  exit(0);
}

```


### free的理解

``` c++
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void func2(int **p, size_t size) {

  if(*p == NULL) {
    return;
  }
  *p = malloc(size);
}

int main() {
  int num = 100;
  int *p = NULL;

  func2(&p, num); // 传递二级指针

  free(p);
  // p = NULL;
  
  *p = 123;
  printf("%d\n", *p); // 这个指针已经是野指针了 
  
  exit(0);
}
```

- free代表着变量p不再拥有原来指向内存空间的引用权限
- free后最好马上将指针置NULL

# Makefile
工程管理 依赖管理

- makefile(用户自定义 更高优先级)
- Makefile(默认)

``` makefile
mytool:main.o tool1.o tool2.o
  gcc main.o tool1.o tool2.o -o mytool

main.o:main.c
  gcc main.c -c -Wall -g -o main.o
tool1.o:tool1.c
  gcc tool1.c -c -Wall -g -o tool1.o
tool2.o:tool2.c
  gcc tool2.c -c -Wall -g -o tool2.o
  
```


``` makefile
OBJS=main.o tool1.o tool2.o
CC=gcc

mytool:$(OBJS)
  $(CC) $(OBJS) -o mytool

main.o:main.c
  $(CC) main.c -c -Wall -g -o main.o
tool1.o:tool1.c
  $(CC) tool1.c -c -Wall -g -o tool1.o
tool2.o:tool2.c
  $(CC) tool2.c -c -Wall -g -o tool2.o
 
clean:
  $(RM) $(OBJS) mytool -r
```

> $^ 表示在上一句依赖关系中被依赖的所有文件
> $@ 表示在上一句依赖关系中依赖项的目标文件

``` makefile
CFLAGS=-Wall -g -c
OBJS=main.o tool1.o tool2.o
CC=gcc

mytool:$(OBJS)
  $(CC) $^ -o $@

main.o:main.c
  $(CC) $^ $(CFLAGS) -o $@
tool1.o:tool1.c
  $(CC) $^ $(CFLAGS) -o $@
tool2.o:tool2.c
  $(CC) $^ $(CFLAGS) -o $@
 
clean:
  $(RM) $(OBJS) mytool -r
```

> % 表示同一个名字

``` makefile
CFLAGS=-Wall -g -c
OBJS=main.o tool1.o tool2.o
CC=gcc

mytool:$(OBJS)
  $(CC) $^ -o $@

%.o:%.c
  $(CC) $^ $(CFLAGS) -o $@
 
clean:
  $(RM) $(OBJS) mytool -r
```

