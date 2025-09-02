# DataStructure

简洁易用的数据结构实现仓库（C 语言）

## 项目概览

本仓库收集了一系列数据结构的 C 语言实现，包括但不限于：

- 单链表（EasySingleLinkedList）
- 动态数组（DynamicArray）
- 双向链表（DoublyLinkedList）
- 双向循环链表（DoublyCircularLinkedList）
- 顺序栈（SequentialStack）

所有数据结构模块均以纯 C 实现，代码结构清晰，易于理解与移植。

## 目录结构示例

```
DataStructure/
├── EasySingleLinkedList/         # 单链表实现
├── DynamicArray/                 # 动态数组
├── DoublyLinkedList/             # 双向链表
├── DoublyCircularLinkedList/     # 双向循环链表
├── SequentialStack/              # 顺序栈
├── LICENSE                       # MIT 许可文件
└── README.md                     # 本说明文档
```

## 特性与优势

- **纯 C 语言实现**：无第三方依赖，轻量且便于移植  
- **模块化设计**：每种数据结构管理在独立目录下，清晰直观  
- **适合学习与教学**：适用于自学、教学案例、快速集成  

## 使用方式

以动态数组为例，可参考以下方式使用：

```c
#include "DynamicArray/dynamic_array.h"

int main() {
    DynamicArray *arr = da_create(10);
    da_push_back(arr, 42);
    printf("Element at index 0: %d\n", da_get(arr, 0));
    da_destroy(arr);
    return 0;
}
```

> 说明：请根据实际项目中的接口和函数名做对应替换。

## 许可证

本项目采用 MIT 许可证授权，具体详见 [LICENSE](LICENSE) 文件。

## 作者与致谢

代码源自 Bilibili UP 主 **[Micro_Frank](https://space.bilibili.com/19658621)** 的教学视频，由其针对数据结构课程中“被吐槽”的实现进行了重写和优化。  
在此衷心感谢 Micro_Frank 的公开授课与讲解，若你喜欢他的教学风格或内容，欢迎访问其 Bilibili 频道查看更多精彩内容。