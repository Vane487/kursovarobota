//
// Created by Ванесса Гудан on 11.11.2025.
//

#ifndef KURSOVA_IPRINT_H
#define KURSOVA_IPRINT_H

#pragma once
#include <iostream>
#include <string>

class IPrint {
public:
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
    virtual ~IPrint() = default;
};

#endif
