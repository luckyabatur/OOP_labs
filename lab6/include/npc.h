#pragma once
#include <string>

class Visitor; // Предварительное объявление

// Базовый класс для всех NPC
class NPC
{
protected:
    std::string m_name;
    double m_x, m_y; // координаты в диапазоне [0..500]
public:
    NPC(const std::string& name, double x, double y)
            : m_name(name), m_x(x), m_y(y) {}
    virtual ~NPC() = default;

    const std::string&  getName() const { return m_name; }
    double getX() const { return m_x; }
    double getY() const { return m_y; }

    // Чисто виртуальная функция: тип NPC
    virtual std::string getType() const = 0;

    // Метод для визитора (бой)
    virtual void accept(Visitor& v, NPC& other) = 0;
};

// =============== Три подкласса ===============

// Медведь (Bear)
class Bear : public NPC
{
public:
    Bear(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Bear"; }
    void accept(Visitor& v, NPC& other) override;
};

// Оборотень (Werewolf)
class Werewolf : public NPC
{
public:
    Werewolf(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Werewolf"; }
    void accept(Visitor& v, NPC& other) override;
};

// Разбойник (Rogue)
class Rogue : public NPC
{
public:
    Rogue(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Rogue"; }
    void accept(Visitor& v, NPC& other) override;
};

