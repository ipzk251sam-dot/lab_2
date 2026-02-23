#include <iostream>
#include <string>

using namespace std;

// =========================================================
// 1. АБСТРАКТНІ ПРОДУКТИ (Загальні назви техніки)
// =========================================================
class Laptop { public: virtual void show() = 0; virtual ~Laptop() {} };
class Netbook { public: virtual void show() = 0; virtual ~Netbook() {} };
class EBook { public: virtual void show() = 0; virtual ~EBook() {} };
class Smartphone { public: virtual void show() = 0; virtual ~Smartphone() {} };


// =========================================================
// 2. КОНКРЕТНІ ПРОДУКТИ (Техніка конкретних брендів)
// =========================================================

// --- Сім'я IProne ---
class IProneLaptop : public Laptop { public: void show() override { cout << "  - Ноутбук вiд IProne (дорого і стильно)\n"; } };
class IProneNetbook : public Netbook { public: void show() override { cout << "  - Нетбук вiд IProne\n"; } };
class IProneEBook : public EBook { public: void show() override { cout << "  - Електронна книга вiд IProne\n"; } };
class IProneSmartphone : public Smartphone { public: void show() override { cout << "  - Смартфон IProne (з відкушеним яблуком)\n"; } };

// --- Сім'я Kiaomi ---
class KiaomiLaptop : public Laptop { public: void show() override { cout << "  - Ноутбук вiд Kiaomi (топ за свої гроші)\n"; } };
class KiaomiNetbook : public Netbook { public: void show() override { cout << "  - Нетбук вiд Kiaomi\n"; } };
class KiaomiEBook : public EBook { public: void show() override { cout << "  - Електронна книга вiд Kiaomi\n"; } };
class KiaomiSmartphone : public Smartphone { public: void show() override { cout << "  - Смартфон Kiaomi\n"; } };

// --- Сім'я Balaxy ---
class BalaxyLaptop : public Laptop { public: void show() override { cout << "  - Ноутбук вiд Balaxy\n"; } };
class BalaxyNetbook : public Netbook { public: void show() override { cout << "  - Нетбук вiд Balaxy\n"; } };
class BalaxyEBook : public EBook { public: void show() override { cout << "  - Електронна книга вiд Balaxy\n"; } };
class BalaxySmartphone : public Smartphone { public: void show() override { cout << "  - Смартфон Balaxy (з крутим екраном)\n"; } };


// =========================================================
// 3. АБСТРАКТНА ФАБРИКА
// =========================================================
class DeviceFactory {
public:
    virtual Laptop* createLaptop() = 0;
    virtual Netbook* createNetbook() = 0;
    virtual EBook* createEBook() = 0;
    virtual Smartphone* createSmartphone() = 0;
    virtual ~DeviceFactory() {}
};


// =========================================================
// 4. КОНКРЕТНІ ФАБРИКИ БРЕНДІВ
// =========================================================
class IProneFactory : public DeviceFactory {
public:
    Laptop* createLaptop() override { return new IProneLaptop(); }
    Netbook* createNetbook() override { return new IProneNetbook(); }
    EBook* createEBook() override { return new IProneEBook(); }
    Smartphone* createSmartphone() override { return new IProneSmartphone(); }
};

class KiaomiFactory : public DeviceFactory {
public:
    Laptop* createLaptop() override { return new KiaomiLaptop(); }
    Netbook* createNetbook() override { return new KiaomiNetbook(); }
    EBook* createEBook() override { return new KiaomiEBook(); }
    Smartphone* createSmartphone() override { return new KiaomiSmartphone(); }
};

class BalaxyFactory : public DeviceFactory {
public:
    Laptop* createLaptop() override { return new BalaxyLaptop(); }
    Netbook* createNetbook() override { return new BalaxyNetbook(); }
    EBook* createEBook() override { return new BalaxyEBook(); }
    Smartphone* createSmartphone() override { return new BalaxySmartphone(); }
};


// =========================================================
// 5. ГОЛОВНИЙ МЕТОД (Клієнтський код)
// =========================================================
int main() {
    // Встановлюємо кирилицю
    setlocale(LC_ALL, "Ukrainian");

    cout << "=== Система замовлення техніки (Абстрактна фабрика) ===\n\n";

    // 1. Створюємо фабрику IProne і випускаємо їхню техніку
    cout << "[ Замовлення партії техніки IProne ]\n";
    DeviceFactory* iproneFactory = new IProneFactory();
    Laptop* mac = iproneFactory->createLaptop();
    Smartphone* iphone = iproneFactory->createSmartphone();
    mac->show();
    iphone->show();

    // 2. Створюємо фабрику Kiaomi
    cout << "\n[ Замовлення партії техніки Kiaomi ]\n";
    DeviceFactory* kiaomiFactory = new KiaomiFactory();
    Smartphone* xiaomiPhone = kiaomiFactory->createSmartphone();
    Netbook* xiaomiNetbook = kiaomiFactory->createNetbook();
    xiaomiPhone->show();
    xiaomiNetbook->show();

    // 3. Створюємо фабрику Balaxy
    cout << "\n[ Замовлення партії техніки Balaxy ]\n";
    DeviceFactory* balaxyFactory = new BalaxyFactory();
    EBook* samsungBook = balaxyFactory->createEBook();
    samsungBook->show();

    // Прибираємо за собою пам'ять (обов'язково в C++)
    delete mac; delete iphone; delete iproneFactory;
    delete xiaomiPhone; delete xiaomiNetbook; delete kiaomiFactory;
    delete samsungBook; delete balaxyFactory;

    return 0;
}