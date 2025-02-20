#pragma once
#include <string>

class Visitor;

class NPC
{
protected:
    std::string m_name;
    double m_x, m_y;
    bool   m_dead{false};

public:
    NPC(const std::string& name, double x, double y)
            : m_name(name), m_x(x), m_y(y) {}
    virtual ~NPC() = default;

    const std::string& getName() const { return m_name; }
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    bool   isDead() const { return m_dead; }
    void   kill() { m_dead = true; }

    virtual std::string getType() const = 0;
    virtual void accept(Visitor& v, NPC& other) = 0;

    virtual double getMoveDistance() const = 0;
    virtual double getKillDistance() const = 0;

    void moveRandom();
};

class Bear : public NPC
{
public:
    using NPC::NPC;
    std::string getType() const override { return "Bear"; }
    void accept(Visitor& v, NPC& other) override;

    double getMoveDistance() const override { return 5.0; }
    double getKillDistance() const override { return 10.0; }
};

class Werewolf : public NPC
{
public:
    using NPC::NPC;
    std::string getType() const override { return "Werewolf"; }
    void accept(Visitor& v, NPC& other) override;

    double getMoveDistance() const override { return 40.0; }
    double getKillDistance() const override { return 5.0; }
};

class Rogue : public NPC
{
public:
    using NPC::NPC;
    std::string getType() const override { return "Rogue"; }
    void accept(Visitor& v, NPC& other) override;

    double getMoveDistance() const override { return 10.0; }
    double getKillDistance() const override { return 10.0; }
};
