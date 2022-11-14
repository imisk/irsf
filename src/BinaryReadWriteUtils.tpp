#include <fstream>
#include "IrsfCommon.h"
namespace irsf {

template <typename T>
void ReadBinary(std::ifstream* stream, T* destination) {
  stream->read(reinterpret_cast<char*>(destination),
               sizeof(decltype(*destination)));

  if (!stream)
    throw IrsfException(IrsfError::CorruptedData);
}

template <typename T>
void WriteBinary(std::fstream& stream, T* source) {
  stream.write(reinterpret_cast<char*>(source),
               static_cast<std::streamsize>(sizeof(decltype(*source))));
}
}  // namespace irsf
