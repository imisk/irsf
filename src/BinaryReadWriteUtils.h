#ifndef BINARYREADWRITEUTILS_H
#define BINARYREADWRITEUTILS_H

#include <fstream>
#include <iostream>

namespace irsf {

template <typename T>
void ReadBinary(std::ifstream& stream, T* destination);

void ReadBinaryCharArray(std::ifstream* fstream,
                         char* destination,
                         size_t charCount);

template <typename T>
void WriteBinary(std::fstream& stream, T* source);

void WriteBinaryCharArray(std::fstream& stream,
                          const char* source,
                          size_t charCount);

struct fstream_raii_write {
  fstream_raii_write(std::string Path);
  ~fstream_raii_write() noexcept;

  std::fstream* get();

 private:
  std::unique_ptr<std::fstream> s;
};

struct fstream_raii_read {
  fstream_raii_read(std::string Path);
  ~fstream_raii_read() noexcept;

  std::ifstream* get();

 private:
  std::unique_ptr<std::ifstream> s;
};

}  // namespace irsf
#include "BinaryReadWriteUtils.tpp"

#endif  // BINARYREADWRITEUTILS_H
