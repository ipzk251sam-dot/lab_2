#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================
// 1. ПРОДУКТ (Сам персонаж, якого ми будуємо)
// =========================================================
class Character {
public:
    string type; // Герой чи Ворог
    string name = "Безіменний";
    int height = 0;
    string bodyBuild = "Звичайна";
    string hairColor = "Лисий";
    string eyeColor = "Карі";
    string clothes = "Лохміття";
    vector<string> inventory;
    vector<string> deeds; // Список справ (добрих або злих)

    // Метод для красивого виводу персонажа на екран
    void showInfo() {
        cout << "--- " << type << ": " << name << " ---\n";
        cout << "Зріст: " << height << " см | Статура: " << bodyBuild << "\n";
        cout << "Очі: " << eyeColor << " | Волосся: " << hairColor << "\n";
        cout << "Одяг: " << clothes << "\n";
        
        cout << "Інвентар: ";
        if (inventory.empty()) cout << "Порожньо";
        for (const string& item : inventory) cout << item << ", ";
        
        cout << "\nІсторія справ:\n";
        if (deeds.empty()) cout << "  Ще нічого не зробив.\n";
        for (const string& deed : deeds) cout << "  * " << deed << "\n";
        cout << "--------------------------------------\n\n";
    }
};

// =========================================================
// 2. ІНТЕРФЕЙС БУДІВЕЛЬНИКА
// =========================================================
class ICharacterBuilder {
public:
    virtual ~ICharacterBuilder() {}
    
    // Зверни увагу: методи повертають посилання на будівельника. 
    // Саме це робить інтерфейс "текучим" (fluent)!
    virtual ICharacterBuilder& setName(string name) = 0;
    virtual ICharacterBuilder& setHeight(int height) = 0;
    virtual ICharacterBuilder& setBodyBuild(string build) = 0;
    virtual ICharacterBuilder& setHairColor(string color) = 0;
    virtual ICharacterBuilder& setEyeColor(string color) = 0;
    virtual ICharacterBuilder& setClothes(string clothes) = 0;
    virtual ICharacterBuilder& addInventoryItem(string item) = 0;
    
    virtual Character* build() = 0;
};

// =========================================================
// 3. КОНКРЕТНИЙ БУДІВЕЛЬНИК: Герой
// =========================================================
class HeroBuilder : public ICharacterBuilder {
private:
    Character* character;
public:
    HeroBuilder() { reset(); }
    void reset() { 
        character = new Character(); 
        character->type = "Герой"; 
    }

    // Реалізація текучого інтерфейсу
    HeroBuilder& setName(string name) override { character->name = name; return *this; }
    HeroBuilder& setHeight(int height) override { character->height = height; return *this; }
    HeroBuilder& setBodyBuild(string build) override { character->bodyBuild = build; return *this; }
    HeroBuilder& setHairColor(string color) override { character->hairColor = color; return *this; }
    HeroBuilder& setEyeColor(string color) override { character->eyeColor = color; return *this; }
    HeroBuilder& setClothes(string clothes) override { character->clothes = clothes; return *this; }
    HeroBuilder& addInventoryItem(string item) override { character->inventory.push_back(item); return *this; }

    // Унікальний метод тільки для Героя
    HeroBuilder& addGoodDeed(string deed) {
        character->deeds.push_back("Добра справа: " + deed);
        return *this;
    }

    Character* build() override {
        Character* result = character;
        reset(); // Готуємо будівельника до створення наступного героя
        return result;
    }
};

// =========================================================
// 4. КОНКРЕТНИЙ БУДІВЕЛЬНИК: Ворог
// =========================================================
class EnemyBuilder : public ICharacterBuilder {
private:
    Character* character;
public:
    EnemyBuilder() { reset(); }
    void reset() { 
        character = new Character(); 
        character->type = "Злодій"; 
    }

    EnemyBuilder& setName(string name) override { character->name = name; return *this; }
    EnemyBuilder& setHeight(int height) override { character->height = height; return *this; }
    EnemyBuilder& setBodyBuild(string build) override { character->bodyBuild = build; return *this; }
    EnemyBuilder& setHairColor(string color) override { character->hairColor = color; return *this; }
    EnemyBuilder& setEyeColor(string color) override { character->eyeColor = color; return *this; }
    EnemyBuilder& setClothes(string clothes) override { character->clothes = clothes; return *this; }
    EnemyBuilder& addInventoryItem(string item) override { character->inventory.push_back(item); return *this; }

    // Унікальний метод тільки для Ворога
    EnemyBuilder& addEvilDeed(string deed) {
        character->deeds.push_back("Злодіяння: " + deed);
        return *this;
    }

    Character* build() override {
        Character* result = character;
        reset();
        return result;
    }
};

// =========================================================
// 5. ДИРЕКТОР (Керує будівельниками для типових рецептів)
// =========================================================
class Director {
public:
    // Директор знає, як створити стандартного воїна
    void makeStandardWarrior(ICharacterBuilder& builder) {
        builder.setHeight(185)
               .setBodyBuild("М'язиста")
               .setClothes("Сталеві обладунки")
               .addInventoryItem("Меч")
               .addInventoryItem("Щит");
    }

    // Директор знає, як створити стандартного мага-лиходія
    void makeDarkMage(ICharacterBuilder& builder) {
        builder.setHeight(170)
               .setBodyBuild("Худорлява")
               .setClothes("Чорна мантія")
               .setEyeColor("Червоні")
               .addInventoryItem("Посох темряви");
    }
};

// =========================================================
// 6. ГОЛОВНИЙ МЕТОД
// =========================================================
int main() {
    setlocale(LC_ALL, "Ukrainian");

    cout << "=== Патерн Будівельник (Builder) ===\n\n";

    Director director;
    HeroBuilder heroBuilder;
    EnemyBuilder enemyBuilder;

    // ---------------------------------------------------------
    // Створюємо Героїню Мрії (використовуючи Директора + ручні налаштування)
    // ---------------------------------------------------------
    director.makeStandardWarrior(heroBuilder); // Беремо базу воїна
    
    // Додаємо специфічні деталі завдяки текучому інтерфейсу
    heroBuilder.setName("Артеміда")
               .setHairColor("Руде")
               .setEyeColor("Зелені")
               .addInventoryItem("Чарівний лук")
               .addGoodDeed("Врятувала ліс від пожежі")
               .addGoodDeed("Нагодувала бездомного дракончика");
               
    Character* myDreamHero = heroBuilder.build();

    // ---------------------------------------------------------
    // Створюємо Найзапеклішого Ворога
    // ---------------------------------------------------------
    director.makeDarkMage(enemyBuilder); // Беремо базу темного мага
    
    enemyBuilder.setName("Волан-де-Морт")
                .setHairColor("Лисий")
                .addEvilDeed("Викрав печиво у студентів")
                .addEvilDeed("Захопив університетську їдальню");
                
    Character* myArchEnemy = enemyBuilder.build();

    // ---------------------------------------------------------
    // Виводимо результати
    // ---------------------------------------------------------
    cout << "[ Створено Героїню ]\n";
    myDreamHero->showInfo();

    cout << "[ Створено Ворога ]\n";
    myArchEnemy->showInfo();

    // Прибираємо за собою
    delete myDreamHero;
    delete myArchEnemy;

    return 0;
}