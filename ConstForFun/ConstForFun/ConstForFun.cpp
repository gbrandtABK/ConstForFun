#include <iostream>
#include "Foo.h"

using std::cout;
using std::endl;

void CastToConst(const int& constInt);
void ConstFoo(const Foo& foo);

int main()
{
    // Constant variables are variables that cannot be changed.
    // Constant variables are used mostly to prevent yourself or more importantly, other programers from changing the value of something accidently.

    // A good use case for a constant variable is to declare a variable such as pi.

    // A lot of math is dependent on pi. A lot of bad things could happen if you accidently changed the value of pi.

    // A common naming convension for const varables is all upper case and snake case i.e. NAME_OF_CONST_VARIABLE.

    // There are a few other ways to get this same behavior. Before we talk about those, its good to understand that there are phases of building a program.
    // There are three phases we care about for the purposes of this repo.
    
    // 1. Pre-compile
    // 2. Compile
    // 3. Runtime
    // In that order.
    
    // Compile time is when the compiler analyzes the code you wrote and converts it into machine code.
    // During compile time, the compiler might be smart enough to figure out what your doing and 
    // make changes to it to accomplish the same thing but more effiecently. 

    // During pre-compile the compiler does when analyzing code is look at pre-processor directives.
    // Pre-proccessor directives are the snipets of code that start with # such as, #include, #pragma once, #define and so on.
    // One way to define a variable is
    #define MACRO_PI 3.14
    // Variables defined this way are known as macros.

    cout << "#define MACRO_PI 3.14" << endl;
    cout << MACRO_PI << endl << endl;

    // When the compiler comes accross #define MACRO_PI 3.14, its going to essentially replace all instances of MACRO_PI with 3.14 as if it were hardcoded.
    // Another way to think about it is, pre-processor directives rewrite you code before it is compiled.
    // This saves performance at runtime.
    // However, macros can be redefined so there not actually constant.

    // Legal
    #define MACRO_PI 5
    cout << "#define MACRO_PI 5" << endl;
    cout << MACRO_PI << endl << endl;

    // A more modern way declaring constant variables use to use constexpr.
    // It works the same was as #define except code rewriting happens at compile time instead of pre-compile with the same benfits and some additional ones.
    // constexpr variables can be typed.
    constexpr float CONSTEXPR_PI = 3.1415f;
    
    cout << "constexpr float CONSTEXPR_PI = 3.1415f;" << endl;
    cout << CONSTEXPR_PI << endl << endl;

    // Illegal
    // CONSTEXPR_PI = 5;

    // There are times when you want the saftey that comes with constexpr but don't know what the value is going to be at compile time.
    // Enter keyword const.

    // Let's pretend this int was determined at runtime. Let's say a user entered this number.
    int runtimeVar = 1;

    // Legal
    const int CONST_INT = runtimeVar;

    // Illegal
    // constexpr int CONSTEXPR_INT = runtimeVar;

    // And if you thought pointers couldn't get any more confusing...
    // Enter constant pointers and pointers to constant variables and constant pointers pointing to constant variables

    // pointer to a constant int
    // Ussually const is a modifying keyword to effect that data type
    // but remember pointers have types and the syntax us (type)*
    // and so (const int)* 
    const int* ptrToConstInt = &CONST_INT;

    // Illegal because this would change the value of a constant int
    //*intPtr = 2;

    // legal because the pointer itself is not constant.
    ptrToConstInt = new int(2);

    // Still Illegl
    //*intPtr = 2;

    // Legal but still causes a memory
    //intPtr = new int(3);

    delete ptrToConstInt;

    int* const CONST_PTR_TO_NON_CONST_INT = new int(3);
     
    // Illegal because you can't change what a constant pointer is pointing to.
    //constPtrToNonConstInt = new int(4);

    // Still ilegal for same reason.
    // constPtrToNonConstInt = &runtimeVar;

    // Legal because your not changing the address the pointer points to, rather you are chaning the value of what it points to.
    *CONST_PTR_TO_NON_CONST_INT = 4;

    delete CONST_PTR_TO_NON_CONST_INT;

    // Ilegal so this pointer is unsuable now.
    //CONST_PTR_TO_NON_CONST_INT = nullptr;

    const int* const CONST_PTR_TO_CONST_INT = new int(5);

    // Everythings illegal.
    // CONST_PTR_TO_CONST_INT = 6;
    // CONST_PTR_TO_CONST_INT = new int(6);
    // CONST_PTR_TO_CONST_INT = &CONST_INT;

    delete CONST_PTR_TO_CONST_INT;

    // Ilegal so this pointer is unsuable now.
    // CONST_PTR_TO_CONST_INT = nullptr;

    // Another use of const is to ensure that a variable passed to a function is unchanged.
    // When a function parameter is marked const, you can pass a non const variable and it will be cast to const and will be temporarily unchangable.
    // This is useful for when you want the perfomance boost of passing by reference with the safety of passing by value.

    CastToConst(runtimeVar);
    runtimeVar = 8;

    cout << "RuntimeVar after CastToConst function is " << runtimeVar << endl << endl;

    // See Foo.h
    Foo foo;
    ConstFoo(foo);
}

void CastToConst(const int& constInt)
{
    cout << "CastToConst function, constInt is " << constInt << endl;

    // Ilegal
    //constInt = 6;
}

void ConstFoo(const Foo& foo)
{
    cout << "Foo's member int is before ConstFunction is " << foo.member_int << endl;

    // Illegal because NonConstFunction is not marked const and could potentially change the internal state of a const Foo
    //foo.NonConstFunction();

    // Legal because it is marked const and therefor cannot change the internal state.
    cout << "Result of Foo's ConstFunction is member_int * 2 => " << foo.ConstFunction() << endl;
    cout << "Foo's member int after ConstFunction is " << foo.member_int << endl << endl;
}