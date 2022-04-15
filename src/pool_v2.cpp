//
// Created by wandrl on 4/15/22.
//

#include "pool_v2.hpp"

#include <iostream>

Pool::Pool (unsigned long long init_amount_of_water) :
        control_(new ControlBlock(init_amount_of_water, this)) {}

double Pool::Measure () const {
    FindCorrectControlBlock();
    return control_->Measure();
}

void Pool::Connect (Pool& pool) {
    if (this == &pool) {
        return;
    }

    pool.FindCorrectControlBlock();
    FindCorrectControlBlock();

    if (control_ == pool.control_){
        return;
    }
    ControlBlock* new_control = new ControlBlock;

    new_control->Merge(control_, pool.control_);
}

void Pool::Add (unsigned long long water) {
    FindCorrectControlBlock();
    control_->Add(water);
}




void Pool::FindCorrectControlBlock() const{
    while (control_->parent_ != nullptr){
        auto next = control_->parent_;
        control_->DecreaseReferenceCount();
        control_ = next;
    }

}











Pool::~Pool () {
    FindCorrectControlBlock();
    control_->DecreaseReferenceCount();
}


Pool::ControlBlock::ControlBlock (unsigned long long init_amount, Pool* pool) :
        count_of_pools_(1),
        total_amount_of_water_(init_amount),
        pools_(1, pool),
        reference_count_(1),
        parent_(nullptr){}

Pool::ControlBlock::ControlBlock() :
        count_of_pools_(0),
        total_amount_of_water_(0),
        reference_count_(0),
        parent_(nullptr){}

void Pool::ControlBlock::Merge (ControlBlock* left, ControlBlock* right) {

    total_amount_of_water_ = left->total_amount_of_water_ + right->total_amount_of_water_;
    count_of_pools_ = left->count_of_pools_ + right->count_of_pools_;
    reference_count_ = left->reference_count_ + right->reference_count_;


    right->parent_ = this;
    left->parent_ = this;

}


