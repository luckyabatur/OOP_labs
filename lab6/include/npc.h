#pragma once
#include <string>

class Visitor;


class NPC
{
protected:
    std::string m_name;
    double m_x, m_y;
public:
    NPC(const std::string& name, double x, double y)
            : m_name(name), m_x(x), m_y(y) {}
    virtual ~NPC() = default;

    const std::string&  getName() const { return m_name; }
    double getX() const { return m_x; }
    double getY() const { return m_y; }


    virtual std::string getType() const = 0;


    virtual void accept(Visitor& v, NPC& other) = 0;
};


class Bear : public NPC
{
public:
    Bear(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Bear"; }
    void accept(Visitor& v, NPC& other) override;
};


class Werewolf : public NPC
{
public:
    Werewolf(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Werewolf"; }
    void accept(Visitor& v, NPC& other) override;
};


class Rogue : public NPC
{
public:
    Rogue(const std::string& name, double x, double y)
            : NPC(name, x, y) {}

    std::string getType() const override { return "Rogue"; }
    void accept(Visitor& v, NPC& other) override;
};

