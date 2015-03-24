/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef X64ASM_ENV_BITS_H
#define X64ASM_ENV_BITS_H

#include <iostream>
#include <utility>

namespace x64asm {

/** An environment register bit. */
class EnvBits : private std::pair<size_t, size_t> {
public:
  /** Returns this bit's upper register index. */
  constexpr size_t index() {
    return this->first;
  }
  /** Returns the number of bits this register bit spans. */
  constexpr size_t width() {
    return this->second;
  }

  /** Comparison */
  constexpr bool operator==(const EnvBits& rhs) {
    return this->first == rhs.first && this->second == rhs.second;
  }
  /** Comparison */
  constexpr bool operator!=(const EnvBits& rhs) {
    return !(*this == rhs);
  }
  /** Comparison */
  constexpr bool operator<(const EnvBits& rhs) {
    return (this->first < rhs.first) ? true :
           (this->first == rhs.first)  ? false :
           this->second < rhs.second;
  }

  /** STL-compliant hash */
  constexpr size_t hash() {
    return this->first ^ this->second;
  }
  /** STL-compliant swap */
  void swap (EnvBits& rhs) {
    std::pair<size_t, size_t>::swap(rhs);
  }

protected:
  /** Direct access to this constructor is disallowed. */
  constexpr EnvBits(size_t i, size_t w) : std::pair<size_t, size_t>(i, w) {}
};

/** An EFLAGS register bit. */
class Eflags : public EnvBits {
  // Needs access to constructor.
  friend class Constants;

public:
  /** Read from an istream using text. */
  std::istream& read_text(std::istream& is);
  /** Write to an ostream using text. */
  std::ostream& write_text(std::ostream& os) const;

private:
  /** Direct access to this constructor is disallowed. */
  constexpr Eflags(size_t i, size_t w) : EnvBits(i, w) {}
};

/** An FPU control register bit. */
class FpuControl : public EnvBits {
  // Needs access to constructor.
  friend class Constants;

public:
  /** Read from an istream using text. */
  std::istream& read_text(std::istream& is);
  /** Write to an ostream using text. */
  std::ostream& write_text(std::ostream& os) const;

private:
  /** Direct access to this constructor is disallowed. */
  constexpr FpuControl(size_t i, size_t w) : EnvBits(i, w) {}
};

/** An FPU status register bit. */
class FpuStatus : public EnvBits {
  // Needs access to constructor.
  friend class Constants;

public:
  /** Read from an istream using text. */
  std::istream& read_text(std::istream& is);
  /** Write to an ostream using text. */
  std::ostream& write_text(std::ostream& os) const;

private:
  /** Direct access to this constructor is disallowed. */
  constexpr FpuStatus(size_t i, size_t w) : EnvBits(i, w) {}
};

/** An FPU tag register. */
class FpuTag : public EnvBits {
  // Needs access to constructor.
  friend class Constants;

public:
  /** Read from an istream using text. */
  std::istream& read_text(std::istream& is);
  /** Write to an ostream using text. */
  std::ostream& write_text(std::ostream& os) const;

private:
  /** Direct access to this constructor is disallowed. */
  constexpr FpuTag(size_t i, size_t w) : EnvBits(i, w) {}
};

/** An MXCSR register bit. */
class Mxcsr : public EnvBits {
  // Needs access to constructor.
  friend class Constants;

public:
  /** Read from an istream using text. */
  std::istream& read_text(std::istream& is);
  /** Write to an ostream using text. */
  std::ostream& write_text(std::ostream& os) const;

private:
  /** Direct access to this constructor is disallowed. */
  constexpr Mxcsr(size_t i, size_t w) : EnvBits(i, w) {}
};

} // namespace std

namespace std {

/** STL hash specialization. */
template <>
struct hash<x64asm::EnvBits> {
  size_t operator()(const x64asm::EnvBits& e) const {
    return e.hash();
  }
};

/** STL swap specialization */
inline void swap(x64asm::EnvBits& e1, x64asm::EnvBits& e2) {
  e1.swap(e2);
}

/** iostream overload */
inline istream& operator>>(istream& is, x64asm::Eflags& e) {
  return e.read_text(is);
}
/** iostream overload */
inline ostream& operator<<(ostream& os, const x64asm::Eflags& e) {
  return e.write_text(os);
}

/** iostream overload */
inline istream& operator>>(istream& is, x64asm::FpuControl& f) {
  return f.read_text(is);
}
/** iostream overload */
inline ostream& operator<<(ostream& os, const x64asm::FpuControl& f) {
  return f.write_text(os);
}

/** iostream overload */
inline istream& operator>>(istream& is, x64asm::FpuStatus& s) {
  return s.read_text(is);
}
/** iostream overload */
inline ostream& operator<<(ostream& os, const x64asm::FpuStatus& s) {
  return s.write_text(os);
}

/** iostream overload */
inline istream& operator>>(istream& is, x64asm::FpuTag& t) {
  return t.read_text(is);
}
/** iostream overload */
inline ostream& operator<<(ostream& os, const x64asm::FpuTag& t) {
  return t.write_text(os);
}

/** iostream overload */
inline istream& operator>>(istream& is, x64asm::Mxcsr& m) {
  return m.read_text(is);
}
/** iostream overload */
inline ostream& operator<<(ostream& os, const x64asm::Mxcsr& m) {
  return m.write_text(os);
}

} // namespace std

#endif

