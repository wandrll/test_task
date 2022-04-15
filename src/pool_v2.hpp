//
// Created by wandrl on 4/15/22.
//

#ifndef ISP_POOL_V2_H
#define ISP_POOL_V2_H

#include <vector>
#include <iostream>
#include <cstdio>
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
        ControlBlock();

        ControlBlock (const ControlBlock& other) = delete;
        ControlBlock& operator= (const ControlBlock& other) = delete;
        ControlBlock (ControlBlock&& other) = delete;
        ControlBlock& operator= (ControlBlock&& other) = delete;


        void Merge (ControlBlock* first, ControlBlock* second);

        double Measure () const {
          return static_cast<double>(total_amount_of_water_) / static_cast<double>(count_of_pools_);
        }

        void Add (unsigned long long water) {
            total_amount_of_water_ += water;
        }

        int PoolsCount () {
            return count_of_pools_;
        }


        void DecreaseReferenceCount () {
            reference_count_--;
            if (reference_count_ == 0){
                delete this;
            }
        }


        ControlBlock* parent_;
        int count_of_pools_;
        unsigned long long total_amount_of_water_;
        unsigned long long reference_count_;
        std::vector<Pool*> pools_;



    };


    void FindCorrectControlBlock() const;


    mutable ControlBlock* control_; //

};

#endif //ISP_POOL_V2_H
