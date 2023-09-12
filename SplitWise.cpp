#include <iostream>
#include <vector>
#include <map>

class User
{
public:
    std::string name;
    double balance;

    User(std::string name_, double balance_)
        : name(name_), balance(balance_) {}
    
};

class Expense
{
public:
    User* paidBy;
    double money;
    std::vector<User*> others;
    bool settled;
    std::string description;

    Expense(User* paidBy_, std::vector<User*> others_, double money_, std::string description_)
        : paidBy(paidBy_), others(others_), money(money_), description(description_), settled(false) {}


    void settle()
    {
        this->settled = true;
    }
};

class Splitwise
{
private:
    inline static Splitwise* instance = nullptr;

    Splitwise() {}

public:
    std::vector<User*> users;
    std::vector<Expense*> expenses;

    void addUser(User* toAdd)
    {
        users.push_back(toAdd);
    }

    void addExpense(Expense* toAdd)
    {
        expenses.push_back(toAdd);
    }

    void displayBalances()
    {
        for (auto user : users)
        {
            std::cout << user->name << ": " << user->balance << std::endl;
        }
    }

    void settleExpense()
    {
        std::map<User*, double> remaining;
        for (auto itr : expenses)
        {
            if (itr->settled)
                continue;
            double individual = itr->money / ((double)1 + itr->others.size());
            remaining[itr->paidBy] += itr->money - individual;
            for (auto A : itr->others)
            {
                remaining[A] -= individual;
            }
            itr->settled = true;
        }
        for (auto A : remaining)
        {
            A.first->balance += A.second;
        }
    }

    static Splitwise* getInstance()
    {
        if (instance)
            return instance;
        return instance = new Splitwise();
    }
};

int main()
{
    Splitwise* sw = Splitwise::getInstance();

    User* user1 = new User("u1", 0.0);
    User* user2 = new User("u2", 0.0);
    User* user3 = new User("u3", 0.0);

    sw->addUser(user1);
    sw->addUser(user2);
    sw->addUser(user3);

    Expense* expense1 = new Expense(user1, {user2, user3}, 100.0, "Dinner");
    Expense* expense2 = new Expense(user2, {user1, user3}, 50.0, "Lunch");

    sw->addExpense(expense1);
    sw->addExpense(expense2);

    sw->settleExpense();
    sw->displayBalances();

    return 0;
}
