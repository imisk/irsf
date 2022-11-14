#include "BinaryReadWriteUtils.h"

class IrsfException;

namespace irsf {

void ReadBinaryCharArray(std::ifstream* fstream,
                         char* destination,
                         size_t charCount) {
  fstream->read(reinterpret_cast<char*>(destination),
                static_cast<std::streamsize>(charCount));
  if (!fstream)
    throw IrsfException(IrsfError::CorruptedData);
}

void WriteBinaryCharArray(std::fstream& stream,
                          const char* source,
                          size_t charCount) {
  stream.write(const_cast<const char*>(source),
               static_cast<std::streamsize>(charCount));
}

fstream_raii_write::fstream_raii_write(std::string Path) {
  s = std::make_unique<std::fstream>(
      Path.c_str(), std::ios::out | std::ios::binary | std::ios::ate);
}

fstream_raii_write::~fstream_raii_write() noexcept {
  try  // warning: close is not noexcept!?? so lets just add a try/catch lol
  {
    std::cout << "fstream_ raii close \n";
    s->close();
  } catch (...) {
  }
}

std::fstream* fstream_raii_write::get() {
  return s.get();
}

fstream_raii_read::fstream_raii_read(std::string Path) {
  s = std::make_unique<std::ifstream>(Path, std::ios::binary);
}

fstream_raii_read::~fstream_raii_read() noexcept {
  try  // warning: close is noexcept(false)!?? so lets just add a try/catch :)
  {
    s->close();
  } catch (...) {
  }
}

std::ifstream* fstream_raii_read::get() {
  return s.get();
}

}  // namespace irsf
