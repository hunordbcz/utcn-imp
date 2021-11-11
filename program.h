// This file is part of the IMP project.

#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>

/**
 * Enumeration of the opcodes supported by the interpreter.
 */
enum class Opcode : uint8_t {
  PUSH_FUNC,
  PUSH_PROTO,
  PUSH_INT,

  PEEK,
  POP,
  CALL,

  EQUALITY,
  ADD,
  SUB,
  RET,
  MUL,
  DIV,
  MOD,

  JUMP_FALSE,
  JUMP,
  STOP
};

/// Helper to print a token kind to a stream.
std::ostream &operator<<(std::ostream &os, Opcode kind);

/**
 * Holds the bytecode for a program.
 */
class Program {
public:

  Program(std::vector<uint8_t> &&code) : code_(std::move(code)) {}

  /// Read a value from a specific location.
  template<typename T>
  T Read(size_t &pc) {
    T t;
    assert(pc + sizeof(T) <= code_.size());
    memcpy(&t, code_.data() + pc, sizeof(T));
    pc += sizeof(T);
    return t;
  }

private:
  std::vector<uint8_t> code_;
};
