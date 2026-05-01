#include <iostream>
#include <string>

class Animal {
public:
    // 构造函数
    Animal() {}

    // 虚函数：支持多态
    virtual void speak() const {
        std::cout << "Animal speaks\n";
    }

    // 非虚函数：不支持多态（静态绑定）
    void identify() const {
        std::cout << "I am an Animal\n";
    }

    // 虚析构函数：确保继承安全
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Dog() {}

    // 重写父类的虚函数
    void speak() const override {
        std::cout << "Dog barks\n";
    }

    // 隐藏了父类的 identify（但因为不是虚函数，父类指针仍会调用父类版本）
    void identify() const {
        std::cout << "I am a Dog\n";
    }

    // Dog 特有的函数
    void fetch() const {
        std::cout << "Dog fetches\n";
    }
};

class Cat : public Animal {
public:
    Cat() {}

    void speak() const override {
        std::cout << "Cat meows\n";
    }

    void scratch() const {
        std::cout << "Cat scratches\n";
    }
};

int main() {
    Dog d;
    Cat c;

    // --- (b) Upcasting (向上转型) ---
    Animal *a1 = &d; // 子类指针转为父类指针
    Animal *a2 = &c;

    // --- (d) 多态测试 ---
    a1->speak();     // 输出: Dog barks (虚函数动态绑定)
    a1->identify();  // 输出: I am an Animal (非虚函数静态绑定)
    
    a2->speak();     // 输出: Cat meows
    a2->identify();  // 输出: I am an Animal

    // --- (c) & (e) Downcasting (向下转型) 与 dynamic_cast ---
    
    // 第一个转换：a1 确实指向 Dog，转换成功
    Dog *d1 = dynamic_cast<Dog *>(a1);
    if (d1 != nullptr) {
        d1->fetch();
    }

    // 第二个转换：a2 指向的是 Cat，无法转为 Dog，转换失败返回 nullptr
    Dog *d2 = dynamic_cast<Dog *>(a2);
    if (d2 != nullptr) {
        d2->fetch();
    } else {
        std::cout << "a2 does not point to a Dog\n";
    }

    return 0;
}