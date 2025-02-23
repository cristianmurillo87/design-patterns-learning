/*
 * State Design Pattern
 *
 * The State pattern allows an object to alter its behavior when its internal state changes.
 * The object will appear to change its class.
 * It is useful for implementing state machines.
 * In this example, the phone transitions between different states 
 * (OFF_HOOK, CONNECTING, CONNECTED, ON_HOLD, ON_HOOK)
 * based on triggers 
 * (CALL_DIALED, HUNG_UP, CALL_CONNECTED, PLACED_ON_HOLD, TAKEN_OFF_HOLD, LEFT_MESSAGE, STOP_USING_PHONE).
 */

#include <iostream>
#include <map>
#include <vector> 
#include <memory>

enum class State
{
    OFF_HOOK,
    CONNECTING,
    CONNECTED,
    ON_HOLD,
    ON_HOOK
};

std::ostream& operator<<(std::ostream& os, const State& s)
{
    switch (s)
    {
        case State::OFF_HOOK:
            os << "OFF HOOK";
            break;
        case State::CONNECTING:
            os << "CONNECTING";
            break;
        case State::CONNECTED:
            os << "CONNECTED";
            break;
        case State::ON_HOLD:
            os << "ON HOLD";
            break;
        case State::ON_HOOK:
            os << "ON HOOK";
            break;
    }
    return os;
}

enum class Trigger
{
    CALL_DIALED,
    HUNG_UP,
    CALL_CONNECTED,
    PLACED_ON_HOLD,
    TAKEN_OFF_HOLD,
    LEFT_MESSAGE,
    STOP_USING_PHONE
};

std::ostream& operator<<(std::ostream& os, const Trigger& t)
{
    switch (t)
    {
        case Trigger::CALL_DIALED:
            os << "CALL DIALED";
            break;
        case Trigger::HUNG_UP:
            os << "HUNG UP";
            break;
        case Trigger::CALL_CONNECTED:
            os << "CALL CONNECTED";
            break;
        case Trigger::PLACED_ON_HOLD:
            os << "PLACED ON HOLD";
            break;
        case Trigger::TAKEN_OFF_HOLD:
            os << "TAKEN OFF HOLD";
            break;
        case Trigger::LEFT_MESSAGE:
            os << "LEFT MESSAGE";
            break;
        case Trigger::STOP_USING_PHONE:
            os << "STOP USING PHONE";
            break;
    }
    return os;
}

int main()
{
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;

    rules[State::OFF_HOOK] = {
        {Trigger::CALL_DIALED, State::CONNECTING},
        {Trigger::HUNG_UP, State::ON_HOOK}
    };

    rules[State::CONNECTING] = {
        {Trigger::HUNG_UP, State::OFF_HOOK},
        {Trigger::CALL_CONNECTED, State::CONNECTED}
    };

    rules[State::CONNECTED] = {
        {Trigger::LEFT_MESSAGE, State::OFF_HOOK},
        {Trigger::HUNG_UP, State::ON_HOOK},
        {Trigger::PLACED_ON_HOLD, State::ON_HOLD}
    };

    rules[State::ON_HOLD] = {
        {Trigger::TAKEN_OFF_HOLD, State::CONNECTED},
        {Trigger::HUNG_UP, State::ON_HOOK}
    };

    State currentState{State::OFF_HOOK};
    State exitState{State::ON_HOOK};

    while (true)
    {
        std::cout << "The phone is currently " << currentState << std::endl;
        std::cout << "Select a trigger:" << std::endl;

        int i = 0;
        for (auto item: rules[currentState])
        {
            std::cout << i++ << ". " << item.first << std::endl;
        }

        int input;
        std::cin >> input;

        if (input < 0 || input >= rules[currentState].size())
        {
            std::cout << "Incorrect option. Please try again." << std::endl;
            continue;
        }

        currentState = rules[currentState][input].second;

        if (currentState == exitState)
        {
            break;
        }
    }

    std::cout << "We are done using the phone." << std::endl;
    
    return 0;
}