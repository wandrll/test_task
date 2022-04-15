//
// Created by wandrl on 4/15/22.
//

#ifndef ISP_POOL_HPP
#define ISP_POOL_HPP


#include <vector>
#include <list>
//Main idea:
//There are pools and control blocks.
//Control block handle all operations for group of pools
//Asymptotic:
//Add water - O(1)
//Measure - O(1)
//Connect - O(min {cnt1, cnt2}), where cnt1(2) - number of pools connected with current pool

const int resize_factor = 10;

class Pool {
public:

    explicit Pool (unsigned long long init_amount_of_water = 0);

    Pool (const Pool& other) = delete;
    Pool& operator= (const Pool& other) = delete;
    Pool (Pool&& other) = default;
    Pool& operator= (Pool&& other) = default;


    [[nodiscard]] double Measure () const;

    void Connect (Pool& pool);

    void Add (unsigned long long water);

    ~Pool ();

private:


    class ControlBlock {
    public:
        ControlBlock (unsigned long long init_amount, Pool* pool);

        ControlBlock (const ControlBlock& other) = delete;
        ControlBlock& operator= (const ControlBlock& other) = delete;
        ControlBlock (ControlBlock&& other) = delete;
        ControlBlock& operator= (ControlBlock&& other) = delete;


        void Merge (ControlBlock* other);

        double Measure () const {
            return static_cast<double>(total_amount_of_water_) / static_cast<double>(count_of_pools_);
        }

        void Add (unsigned long long water) {
            total_amount_of_water_ += water;
        }

        int PoolsCount () {
            return count_of_pools_;
        }


        void DecreasePoolsCount () {
            count_of_pools_--;
        }

    private:
        int count_of_pools_;
        unsigned long long total_amount_of_water_;
        std::vector<Pool*> pools_;
    };

    ControlBlock* control_; //

};


#endif //ISP_POOL_HPP
