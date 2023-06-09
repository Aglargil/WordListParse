# 需求
词表程序：

在我们的开发任务中，最常见的一项工作就是解析并读取各种词表文件，请设计并实现一个通用的词表解析读取工具类(一个或者几个class/struct组成)，解析并读取如下形式的词表: 

    <col1>\t<col2>\t...\t<coln>

每一行都是一条记录，每一列可能的类型包括: 

   * int
   * float
   * char *
   * 形如num:item1,item2,item3的数组（可以理解为T[num]的数组，T是用户给出某种build-in类型）
   * 其他用户自定义类型(需要灵活支持多种自定义类型)

每一列的数据中均不包含\t字符，每一行以\n结尾。

要求: 

    1. 对于非用户自定义类型，封装解析行为；用户自定义类型，调用用户给出的parse函数（从string翻译成用户struct)完成
         * 提示，要将string翻译为内部类型或用户自定义类型，而不是简单的字符串切分。
    2. 用户能通过某些形式，定制这个词表的结构，指明每一列的类型是什么
    3. 用户能逐行读取这个词表的信息，即按序读取每一行，然后能解析出这一行中的每一列内容
         * 提示，实现line by line的解析功能即可，不要求把整个词表存储到内存中（感兴趣的话也可以搞搞）  
         * 要求提供获取数据的接口，而不是仅仅打印出来   
    4. 容错采用出错则报警并跳过整行记录的方式，但不论输入任何错误数据，程序不能出core
    5. API设计友好，做到自解释
    6. 代码严格遵守百度编码规范
    7. 代码的可读性和可维护性好 
    8. 使用常用日志库规范日志输出
    9. 完成相应的单元测试和使用demo, 你的代码必须可编译， Demo可运行， 单元测试有效而且通过;
         * 提示，demo也要符合编码规范，:-)
         * 单元测试必须使用GTest

# 功能实现
## 类图
定义一个抽象的`basePaser`, 一个模板类`Paser<T>`继承于`basePaser`

`WordListParse`维护一个`vector<BaseParser*>`

![](https://cdn.nlark.com/yuque/__puml/bd5f2f090f7f32ee261d85d449683cf4.svg)

## 顺序图
调用`WordListParse::parse(line)`最终会调用模版函数`parse`

模版函数`parse`目前有三个全特化版本, 分别可以处理三个基本的数据类型
- `parse(const std::string& input, int& output)`
- `parse(const std::string& input, float& output)`
- `parse(const std::string& input, std::string& output)`

同时还有一个针对`vector`类型的`parse`, 其中嵌套调用了`parse`, 方便进行`vector`类型的数据解析
- `template<typename T> inline bool parse(const std::string& input, std::vector<T>& output)`

最后是最基本的模版函数`parse`, 被调用会返回`false`, 提醒用户对相对应类型的`parse`进行特化
- `template<typename T> inline bool parse(const std::string& input, T& output)`

![](https://cdn.nlark.com/yuque/__puml/b0f422990faeb5ea9af38be5f39b9cae.svg)

# 使用教程


## 分隔符的作用
- `\t` 用于分割每一列
- `,` 用于分割`vector`类型元素的每一项
- `|` 用户自定义分隔符, 用于分割`CustomerData`的每一项

### 自定义类型

```cpp
struct CustomerData {
    int a;
    float b;
};
struct EmbedData {
    CustomerData data;
    std::string str;
};
```

## 自定义`parse()`
每个自定义类型需要有自己唯一的自定义分隔符, 这里的`CustomerData`使用`|`, `EmbedData`使用`~`

```cpp
template<>
inline bool parse(const std::string& input, CustomerData& output) {
    auto word_parse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.a);
        } else if (index == 1) {
            parse(word, output.b);
        }

        return true;
    };
    return read_line(input, '|', word_parse);
}

template<>
inline bool parse(const std::string& input, EmbedData& output) {
    auto word_parse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.data);
        } else if (index == 1) {
            parse(word, output.str);
        }

        return true;
    };
    return read_line(input, '~', word_parse);
}

```