//
// Created by wandrl on 4/15/22.
//

#include "pool.hpp"
#include <iostream>

Pool::Pool (unsigned long long init_amount_of_water) :
        control_(new ControlBlock(init_amount_of_water, this)) {}

double Pool::Measure () const {
    return control_->Measure();
}

void Pool::Connect (Pool& pool) {
    if (this == &pool) {
        return;
    }

    if (control_->PoolsCount() > pool.control_->PoolsCount()) {
        control_->Merge(pool.control_);
    } else {
        pool.control_->Merge(control_);
    }
}

void Pool::Add (unsigned long long water) {
    control_->Add(water);
}


Pool::~Pool () {
    control_->DecreasePoolsCount();

    if (control_->PoolsCount() == 0) { //similar idea with std::shared_ptr.
        delete control_;              // Control block will be deleted only if all his pools are deleted
    }

}


Pool::ControlBlock::ControlBlock (unsigned long long init_amount, Pool* pool) :
        count_of_pools_(1),
        total_amount_of_water_(init_amount),
        pools_(1, pool) {}

void Pool::ControlBlock::Merge (ControlBlock* other) {
    if (this == other) {
        return;
    }

    total_amount_of_water_ += other->total_amount_of_water_;
    count_of_pools_ += other->count_of_pools_;

    auto count = other->count_of_pools_;

    for (int i = 0; i < count; i++) {
        pools_.push_back(other->pools_[i]);
        pools_.back()->control_ = this;
    }

    delete other;
}


