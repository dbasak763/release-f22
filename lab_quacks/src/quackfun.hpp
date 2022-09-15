/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here
    if (s.empty()) {
        return T();
    }
    T popped = s.top();
    s.pop();
    T a = popped + sum(s);
    s.push(popped);
    return a;
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    if (input.empty()) return true;
    std::stack<char> localStack;
    while(!input.empty()) {
        char c = input.front();
        input.pop();
        if (c == '[' || c == ']') localStack.push(c);
    }
    int numLeftSquareBrackets = 0;
    int numRightSquareBrackets = 0;
    //leftsquarebrackets >= rightsquarebrackets throughout the while loop
    //at very end of while loop they must be equal
    while (!localStack.empty()) {
        char c = localStack.top();
        localStack.pop();
        if (c == '[') numLeftSquareBrackets++;
        if (c == ']') numRightSquareBrackets++;
        if (numLeftSquareBrackets < numRightSquareBrackets) return false;
    }
    return (numLeftSquareBrackets == numRightSquareBrackets);
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s, s2;
    queue<T> q2;

    // Your code here
    int window = 1;
    int window_index = 0;
    while (!q.empty()) {
        T front = q.front();
        q2.push(front);
        q.pop();
        window_index++;
        if (window_index == window || q.empty()) {
            bool reverse = 1 - window % 2;
            if (!reverse) {
                while (!q2.empty()) {
                    s.push(q2.front());
                    //std::cout << q2.front() << std::endl;
                    q2.pop();
                }
            } else {
                while (!q2.empty()) {
                    s2.push(q2.front());
                    //std::cout << q2.front() << std::endl;
                    q2.pop();
                }
                while (!s2.empty()) {
                    s.push(s2.top());
                    //std::cout << s2.top() << std::endl;
                    s2.pop();
                }
            }
            window++;
            window_index = 0;
        }
    }
    while(!s.empty()) {
        T popped = s.top();
        s2.push(popped);
        s.pop();
    }
    while(!s2.empty()) {
        T popped = s2.top();
        q.push(popped);
        s2.pop();
    }
}

};