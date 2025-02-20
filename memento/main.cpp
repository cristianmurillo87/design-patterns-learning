/*
 * Memento Design Pattern
 *
 * The Memento pattern provides the ability to restore an object to its previous state.
 * It is useful for implementing undo mechanisms.
 * In this example, the Memento class stores the state of the BankAccount and BankAccount2 classes,
 * allowing for the restoration of their state at a later time.
 */

#include <iostream>
#include <vector>
#include <memory>

class Memento
{
    int balance;
public:
    Memento(int balance): balance(balance) {}

    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
    int balance{0};

    Memento deposit(int amount)
    {
        balance += amount;
        return Memento{balance};
    }

    void restote(const Memento& m)
    {
        balance = m.balance;
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account)
    {
        os << "balance: " << account.balance;
        return os;
    }
};

class BankAccount2
{
    int balance{0};
    std::vector<std::shared_ptr<Memento>> changes;
    int current;

public:
    BankAccount2(int balance): balance(balance)
    {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current = 0;
    }

    std::shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const std::shared_ptr<Memento>& m)
    {
        if (m)
        {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    std::shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    std::shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount2& account)
    {
        os << "balance: " << account.balance;
        return os;
    }

};

int main()
{
    BankAccount2 ba{100};
    ba.deposit(50);
    ba.deposit(25);
    std::cout << ba << std::endl;

    ba.undo();

    std::cout << "Undo 1: " << ba << std::endl;
    ba.undo();
    std::cout << "Undo 2: " << ba << std::endl;
    ba.redo();
    std::cout << "Redo 1: " << ba << std::endl;
    
    return 0;
}