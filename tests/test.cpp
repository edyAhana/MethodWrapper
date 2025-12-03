#include "gtest/gtest.h"
#include "Engine.h"
#include "Wrapper.h"
#include <string>

class SubjectEx {
public:
    int mul3(int a, int b, int c) {
        return a * b * c;
    }

    void concatTo(std::string s) {
        buffer += s;
    }

    double mix(int a, double b, std::string c) {
        return a + b + c.size(); 
    }

    std::string buffer;
};

TEST(WrapperTestExtended, MethodWithThreeArguments) {
    SubjectEx subj;

    Wrapper wrapper(subj, &SubjectEx::mul3, { {0, 0}, {1, 0}, {2, 0} } );
    Engine engine;
    engine.register_command(&wrapper, "mul3");

    Holder result = engine.execute("mul3", {
        {0, 2},
        {1, 3},
        {2, 4}
    });

    ASSERT_EQ(holder_cast<int>(result), 24);  
}

TEST(WrapperTestExtended, VoidMethodModifiesObject) {
    SubjectEx subj;

    Wrapper wrapper(
        subj,
        &SubjectEx::concatTo,
        { {0, std::string("")} }
    );

    Engine engine;
    engine.register_command(&wrapper, "concat");

    engine.execute("concat", {
        {0, std::string("Hello")} 
    });

    engine.execute("concat", {
        {0, std::string(" World")} 
    });

    ASSERT_EQ(subj.buffer, "Hello World");
}

TEST(WrapperTestExtended, MethodWithDifferentTypes) {
    SubjectEx subj;

    Wrapper wrapper(subj, &SubjectEx::mix, { {0, 0}, {1, 0.0}, {2, std::string("")} });

    Engine engine;
    engine.register_command(&wrapper, "mix");

    Holder result = engine.execute("mix", {
        {0, 5},                          
        {1, 2.5},                        
        {2, std::string("abc")}          
    });

    ASSERT_DOUBLE_EQ(holder_cast<double>(result), 10.5);
}

