#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Базовий клас для всіх підписок (Продукт)
class Subscription {
public:
    double monthlyFee;
    int minPeriod;
    vector<string> channels;

    // Віртуальний деструктор необхідний у C++ для правильного видалення дочірніх об'єктів
    virtual ~Subscription() {}

    // Метод для виводу інформації
    void printDetails() {
        cout << "Щомісячна плата: " << monthlyFee << " грн" << endl;
        cout << "Мінімальний період: " << minPeriod << " міс." << endl;
        cout << "Канали та можливості: ";
        for (const string& channel : channels) {
            cout << channel << ", ";
        }
        cout << "\n--------------------------------------------------" << endl;
    }
};

// 2. Конкретні підписки (Concrete Products)
class DomesticSubscription : public Subscription {
public:
    DomesticSubscription() {
        monthlyFee = 150.0;
        minPeriod = 1;
        channels = {"1+1", "ICTV", "Новий канал"};
    }
};

class EducationalSubscription : public Subscription {
public:
    EducationalSubscription() {
        monthlyFee = 100.0;
        minPeriod = 6;
        channels = {"Discovery", "National Geographic", "History Channel"};
    }
};

class PremiumSubscription : public Subscription {
public:
    PremiumSubscription() {
        monthlyFee = 400.0;
        minPeriod = 12;
        channels = {"Всі канали Domestic та Educational", "Netflix", "4K якість без реклами"};
    }
};

// 3. Базовий клас творця (Creator)
class PurchaseChannel {
public:
    virtual ~PurchaseChannel() {}
    
    // Це наш Фабричний метод! 
    // '= 0' означає, що метод "чисто віртуальний", тобто дочірні класи зобов'язані його написати.
    virtual Subscription* createSubscription(string type) = 0;
};

// 4. Конкретні творці (Concrete Creators)
class WebSite : public PurchaseChannel {
public:
    Subscription* createSubscription(string type) override {
        cout << "Обробка запиту через Вебсайт..." << endl;
        if (type == "Domestic") return new DomesticSubscription();
        if (type == "Educational") return new EducationalSubscription();
        if (type == "Premium") return new PremiumSubscription();
        return nullptr;
    }
};

class MobileApp : public PurchaseChannel {
public:
    Subscription* createSubscription(string type) override {
        cout << "Обробка запиту через Мобільний додаток..." << endl;
        if (type == "Domestic") return new DomesticSubscription();
        if (type == "Educational") return new EducationalSubscription();
        if (type == "Premium") return new PremiumSubscription();
        return nullptr;
    }
};

class ManagerCall : public PurchaseChannel {
public:
    Subscription* createSubscription(string type) override {
        cout << "Менеджер приймає дзвінок та оформлює підписку вручну..." << endl;
        if (type == "Domestic") return new DomesticSubscription();
        if (type == "Educational") return new EducationalSubscription();
        if (type == "Premium") return new PremiumSubscription();
        return nullptr;
    }
};

// 5. Головний метод програми (клієнтський код)
int main() {
    // Встановлюємо підтримку кирилиці в консолі (для Windows)
    setlocale(LC_ALL, "Ukrainian");

    cout << "=== Система придбання підписок ===\n" << endl;

    // Створюємо канали продажу
    PurchaseChannel* webSite = new WebSite();
    PurchaseChannel* mobileApp = new MobileApp();
    PurchaseChannel* managerCall = new ManagerCall();

    // Купуємо підписки
    Subscription* mySub1 = webSite->createSubscription("Domestic");
    if (mySub1) mySub1->printDetails();

    Subscription* mySub2 = mobileApp->createSubscription("Educational");
    if (mySub2) mySub2->printDetails();

    Subscription* mySub3 = managerCall->createSubscription("Premium");
    if (mySub3) mySub3->printDetails();

    // В C++ дуже важливо прибирати за собою пам'ять!
    delete mySub1;
    delete mySub2;
    delete mySub3;
    delete webSite;
    delete mobileApp;
    delete managerCall;

    return 0;
}