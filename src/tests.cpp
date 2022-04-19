//
// Created by wandrl on 4/14/22.
//

#include "pool.hpp"

#include <iostream>
#include <gtest/gtest.h>
#include <ctime>

int main () {

    srand(time(NULL));

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


TEST(Pool, constructor_and_measure) {
    Pool pool(10);

    ASSERT_EQ(pool.Measure(), 10);

}

TEST(Pool, connect) {
    Pool pool1(10);
    Pool pool2(20);

    pool1.Connect(pool2);

    ASSERT_EQ(pool1.Measure(), pool2.Measure());
    ASSERT_EQ(pool1.Measure(), 15);
}


TEST(Pool, connect_from_example) {
    Pool A(10);
    Pool B(20);
    Pool C(50);

    A.Connect(B);

    ASSERT_EQ(A.Measure(), 15);
    ASSERT_EQ(B.Measure(), 15);

    A.Add(10);

    ASSERT_EQ(A.Measure(), 20);
    ASSERT_EQ(B.Measure(), 20);

    B.Connect(C);

    ASSERT_EQ(A.Measure(), 30);
    ASSERT_EQ(B.Measure(), 30);
    ASSERT_EQ(C.Measure(), 30);


}


TEST(Pool, stress_connect) {
    Pool pools[10000];
    int total = 0;

    for (int i = 0; i < 10000; i++) {
        int added = std::rand() % 1000;
        pools[i].Add(added);
        total += added;
    }

    double per_pool = total / 10000.;

    for (int i = 0; i < 10000; i++) {
        pools[i].Connect(pools[(i + 1) % 10000]);
    }


    for (int i = 0; i < 10000; i++) {
        ASSERT_EQ(pools[i].Measure(), per_pool);
    }




//    for (int )



}