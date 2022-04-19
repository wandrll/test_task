//
// Created by wandrl on 4/19/22.
//

#include "pool_v3.hpp"

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
    if (std::min(control_->count_of_pools_, pool.control_->count_of_pools_) < critical_count){
        if (control_->PoolsCount() > pool.control_->PoolsCount()) {
            control_->Merge(pool.control_);
        } else {
            pool.control_->Merge(control_);
        }
    }else{
        ControlBlock* new_control = new ControlBlock;

        new_control->CreateParent(control_, pool.control_);

    }
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


void Pool::ControlBlock::Merge (ControlBlock* other) {
    if (this == other) {
        return;
    }

    auto prev_cnt = count_of_pools_;


    total_amount_of_water_ += other->total_amount_of_water_;
    count_of_pools_ += other->count_of_pools_;
    reference_count_ += other->reference_count_;

    auto count = other->count_of_pools_;


    if(count_of_pools_ > pools_.capacity()) {
        pools_.resize(count_of_pools_ * resize_factor);
    }

    for (int i = prev_cnt; i < count_of_pools_; i++){
        pools_[i] = other->pools_[i - prev_cnt];
        pools_[i]->control_ = this;
    }

//
//    for (auto elem: other->pools_) {
//        pools_.push_back(elem);
//        pools_.back()->control_ = this;
//    }

    delete other;
}








Pool::~Pool () {
    FindCorrectControlBlock();
    control_->DecreaseReferenceCount();
}


Pool::ControlBlock::ControlBlock (unsigned long long init_amount, Pool* pool) :
        count_of_pools_(1),
        total_amount_of_water_(init_amount),
        reference_count_(1),
        parent_(nullptr),
        pools_(1, pool) {}

Pool::ControlBlock::ControlBlock() :
        count_of_pools_(0),
        total_amount_of_water_(0),
        reference_count_(0),
        parent_(nullptr){}

void Pool::ControlBlock::CreateParent (ControlBlock* left, ControlBlock* right) {

    total_amount_of_water_ = left->total_amount_of_water_ + right->total_amount_of_water_;
    count_of_pools_ = left->count_of_pools_ + right->count_of_pools_;
    reference_count_ = left->reference_count_ + right->reference_count_;


    right->parent_ = this;
    left->parent_ = this;

}