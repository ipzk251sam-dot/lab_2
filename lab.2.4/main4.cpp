#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Створюємо клас Virus
class Virus {
public:
    double weight;
    int age;
    string name;
    string species;
    vector<Virus*> children; // Масив дітей (вказівники на інші віруси)

    // Конструктор для зручного створення віруса
    Virus(double w, int a, string n, string s) {
        weight = w;
        age = a;
        name = n;
        species = s;
    }

    // Деструктор (обов'язково в C++, щоб видалити всіх дітей з пам'яті)
    ~Virus() {
        for (Virus* child : children) {
            delete child;
        }
    }

    // Метод для додавання дитини
    void addChild(Virus* child) {
        children.push_back(child);
    }

    // ---------------------------------------------------------
    // 3 & 4. ПАТЕРН ПРОТОТИП: Метод клонування (Глибока копія)
    // ---------------------------------------------------------
    Virus* clone() {
        // Створюємо новий вірус з такими ж базовими характеристиками
        Virus* copy = new Virus(weight, age, name, species);
        
        // Клонуємо ВСІХ дітей рекурсивно (це і є 4-й пункт завдання!)
        for (Virus* child : children) {
            copy->addChild(child->clone()); 
        }
        
        return copy; // Повертаємо готового клона
    }

    // Допоміжний метод для красивого виводу сімейного дерева на екран
    void printTree(int level = 0) {
        string indent(level * 4, ' '); // Відступи для ієрархії
        cout << indent << "-> Вірус: " << name << " (Вид: " << species 
             << ", Вік: " << age << ", Вага: " << weight << ")\n";
        
        for (Virus* child : children) {
            child->printTree(level + 1); // Виводимо дітей з більшим відступом
        }
    }
};

// =========================================================
// 5. ГОЛОВНИЙ МЕТОД (Клієнтський код)
// =========================================================
int main() {
    // Встановлюємо кирилицю для консолі
    setlocale(LC_ALL, "Ukrainian");

    cout << "=== Патерн Прототип (Prototype) ===\n\n";

    // 2. Створюємо сімейство вірусів (3 покоління)
    cout << "[ Створення оригінального сімейства вірусів... ]\n";
    
    // Покоління 1 (Дідусь)
    Virus* grandParent = new Virus(1.5, 10, "Дельта-Прайм", "Covid");
    
    // Покоління 2 (Батьки)
    Virus* parent1 = new Virus(1.2, 5, "Дельта-А", "Covid");
    Virus* parent2 = new Virus(1.3, 4, "Дельта-Б", "Covid");
    
    // Покоління 3 (Діти/Онуки)
    Virus* child1 = new Virus(0.5, 1, "Омікрон-1", "Covid");
    Virus* child2 = new Virus(0.6, 2, "Омікрон-2", "Covid");

    // Вибудовуємо ієрархію: додаємо дітей батькам
    parent1->addChild(child1);
    parent1->addChild(child2);
    
    // Додаємо батьків дідусю
    grandParent->addChild(parent1);
    grandParent->addChild(parent2);

    cout << "Оригінальне дерево:\n";
    grandParent->printTree();

    // 3. КЛОНУВАННЯ
    cout << "\n[ Клонування головного віруса (Дідуся)... ]\n";
    Virus* clonedFamily = grandParent->clone();

    // Щоб довести, що клонування пройшло успішно і це ДІЙСНО незалежна копія, 
    // змінимо ім'я клону-дідуся та одного з його клонів-онуків.
    clonedFamily->name = "КЛОН-Дельта-Прайм";
    clonedFamily->children[0]->children[0]->name = "КЛОН-Омікрон-1";

    cout << "Дерево клонів (після мутації імені):\n";
    clonedFamily->printTree();

    cout << "\nПеревіряємо оригінальне дерево ще раз (воно не мало змінитись!):\n";
    grandParent->printTree();

    // Очищення пам'яті (деструктор автоматично видалить всіх дітей всередині)
    delete grandParent;
    delete clonedFamily;

    return 0;
}