#include <iostream>
void print() {}
template<typename T, typename... Args>
void print(T&& firstArg, Args&&... rest) {
    std::cout << std::forward<T>(firstArg);
    if(sizeof...(rest) != 0) {
        std::cout << ", ";
    }
    print(std::forward<Args>(rest)...);
}
int main() {
    print(0, "homework", 1, 'a');
    return 0;
}
