#include <iostream>
#include <cstring> 

using namespace std;

class String {
public:
    // 1. 构造函数
    String(const char* str = NULL);
    
    // 2. 拷贝构造函数
    String(const String& other);
    
    // 3. 析构函数
    ~String(void);
    
    // 4. 赋值运算符重载
    String& operator=(const String& other);

    void print() const {
        if (m_data) {
            cout << m_data << endl;
        }
    }

private:
    char *m_data; // 用于保存字符串
};

// 1. 普通构造函数
String::String(const char* str) {
    if (str == NULL) {
        // 如果传入 NULL，分配一个字节存储 '\0'，确保 m_data 不为空指针
        m_data = new char[1];
        *m_data = '\0';
    } else {
        // 分配长度 + 1 (为了结束符 '\0')
        int length = strlen(str);
        m_data = new char[length + 1];
        strcpy(m_data, str);
    }
}

// 2. 拷贝构造函数 (深拷贝)
String::String(const String& other) {
    // 获取源字符串长度
    int length = strlen(other.m_data);
    // 分配新内存
    m_data = new char[length + 1];
    // 拷贝内容
    strcpy(m_data, other.m_data);
}

// 3. 析构函数
String::~String(void) {
    if (m_data != NULL) {
        delete[] m_data; // 释放数组内存
        m_data = NULL;   // 避免野指针
    }
}

// 4. 赋值函数 
String& String::operator=(const String& other) {
    // 第一步：检查自赋值 (例如 a = a)
    if (this == &other) {
        return *this;
    }

    // 第二步：释放原有的内存资源
    delete[] m_data;

    // 第三步：分配新内存并拷贝 (深拷贝)
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy(m_data, other.m_data);

    // 第四步：返回本对象的引用
    return *this;
}

int main(void) {
    cout << "--- 测试构造函数 ---" << endl;
    String str1("Hello World");
    cout << "str1: ";
    str1.print();

    String str2; // 测试默认参数 NULL
    cout << "str2 (Empty): "; 
    str2.print(); // 应该输出空行

    cout << "\n--- 测试拷贝构造函数 ---" << endl;
    String str3(str1);
    cout << "str3 (Copy of str1): ";
    str3.print();

    cout << "\n--- 测试赋值运算符 ---" << endl;
    String str4;
    str4 = str1; // 赋值
    cout << "str4 (Assigned from str1): ";
    str4.print();

    cout << "\n--- 测试连续赋值 ---" << endl;
    String str5;
    String str6;
    str6 = str5 = str1;
    cout << "str5: "; str5.print();
    cout << "str6: "; str6.print();
    
    cout << "\n--- 测试自赋值 ---" << endl;
    str1 = str1;
    cout << "str1 after self-assignment: ";
    str1.print();

    return 0;
}