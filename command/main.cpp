/*
 * Command Design Pattern
 *
 * The Command pattern encapsulates a request as an object, 
 * thereby allowing for parameterization of clients with queues, requests, and operations.
 * It also provides support for undoable operations.
 * In this example, the BankAccountCommand class encapsulates operations on a BankAccount,
 * allowing for the execution and undoing of deposits and withdrawals.
 */

#include <iostream>
#include <vector>

struct BankAccount
{
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount)
    {
        balance += amount;
        std::cout << "deposited " << amount << ", balance now " << balance << std::endl;
    }

    bool withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "withdrew " << amount << ", balance now " << balance << std::endl;
            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const BankAccount &account)
    {
        os << "balance: " << account.balance;
        return os;
    }
};

struct Command
{
    bool succeeded;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand: Command
{
    enum Action {deposit, withdraw} action;

    BankAccountCommand(BankAccount &account, Action action, int amount)
        : account(account), action(action), amount(amount) {
            succeeded = false;
        }

    void call() override
    {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            succeeded = true;
            break;
        case withdraw:
            succeeded = account.withdraw(amount);
            break;
        }
    }

    void undo() override
    {
        if(!succeeded) return;

        switch(action)
        {
            case deposit:
                account.withdraw(amount);
                break;
            case withdraw:
                account.deposit(amount);
                break;
        }
    }

private:
    BankAccount &account;
    int amount;
};

struct CompositeBankAccountCommand: std::vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const std::initializer_list<value_type> &items)
        : std::vector<BankAccountCommand>(items) {}

    void call() override
    {
        for(auto& cmd: *this)
            cmd.call();
    }

    void undo() override
    {
        for(auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

struct DependentCompositeCommand: CompositeBankAccountCommand
{
    DependentCompositeCommand(const std::initializer_list<value_type> &items)
        : CompositeBankAccountCommand(items) {}

    void call() override
    {
        bool ok = true;
        for(auto& cmd: *this)
        {
            if(ok)
            {
                cmd.call();
                ok = cmd.succeeded;
            }
            else
            {
                cmd.succeeded = false;
            }
        }
    }
};

struct MoneyTransferCommand: DependentCompositeCommand
{
    MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount)
        : DependentCompositeCommand({
            BankAccountCommand{from, BankAccountCommand::withdraw, amount},
            BankAccountCommand{to, BankAccountCommand::deposit, amount}
        }) {}
};


int main()
{
    /*BankAccount ba;
    std::vector<BankAccountCommand> commands{
        BankAccountCommand{ba, BankAccountCommand::deposit, 100}, 
        BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
    };

    for(auto& command: commands)
        command.call();

    for (auto it = commands.rbegin(); it != commands.rend(); ++it)
        it->undo();*/

    BankAccount from, to;
    from.deposit(100);

    MoneyTransferCommand cmd{from, to, 5000};
    cmd.call();

    std::cout << from << std::endl << to << std::endl;
    cmd.undo();
    std::cout << from << std::endl << to << std::endl;

    return 0;
}