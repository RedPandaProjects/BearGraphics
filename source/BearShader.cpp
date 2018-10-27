#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
#define CREATE_SHADER_CLASS(name) \
BearGraphics::BearShader##name##CompilerRef::BearShader##name##CompilerRef()\
{\
}\
\
BearGraphics::BearShader##name##CompilerRef::~BearShader##name##CompilerRef()\
{\
	clear();\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::compileText(const bchar * text, BearCore::BearString & out_error)\
{\
	clear();\
	if (!RHIFactoty)return false;\
	if (!m_data.get()->shader_compiler)\
	{\
		clear();\
		return false;\
	}\
	return m_data.get()->shader_compiler->compileFromText(text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::compileFromFile(const bchar * file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearFileStream stream;\
	if (!stream.open(file))\
		return false;\
	BearCore::BearString text;\
	stream.toString(text, coding);\
	return compileText(*text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::compileFromInput(BearCore::BearInputStream & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearString text;\
	stream.toString(text, coding);\
	return compileText(*text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::compileFromBuffer(BearCore::BearBufferedReader & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearString text;\
	stream.toString(text, coding);\
	return compileText(*text,out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::saveToFile(const bchar * file)\
{\
	if (empty())return false;\
	BearCore::BearFileStream stream;\
	if (!stream.open(file,stream.Write))\
		return false;\
	return stream.write(m_data.get()->shader_compiler->getPointerBuffer(), m_data.get()->shader_compiler->getSizeBuffer())== m_data.get()->shader_compiler->getSizeBuffer();\
}\
\
void * BearGraphics::BearShader##name##CompilerRef::begin()\
{\
	if (empty())return 0;\
	return m_data.get()->shader_compiler->getPointerBuffer();\
}\
\
void * BearGraphics::BearShader##name##CompilerRef::end()\
{\
	if (empty())return 0;\
	return  (uint8*) m_data.get()->shader_compiler->getPointerBuffer()+m_data.get()->shader_compiler->getSizeBuffer();\
}\
\
const void * BearGraphics::BearShader##name##CompilerRef::begin() const\
{\
	if (empty())return 0;\
	return m_data.get()->shader_compiler->getPointerBuffer();\
}\
\
const void * BearGraphics::BearShader##name##CompilerRef::end() const\
{\
	if (empty())return 0;\
	return  (uint8*)m_data.get()->shader_compiler->getPointerBuffer() + m_data.get()->shader_compiler->getSizeBuffer();\
}\
\
bsize BearGraphics::BearShader##name##CompilerRef::getSize() const\
{\
	return  m_data.get()->shader_compiler->getSizeBuffer();\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::empty() const\
{\
	return m_data.empty();\
}\
\
void BearGraphics::BearShader##name##CompilerRef::clear()\
{\
	m_data.clear();\
}\
\
void BearGraphics::BearShader##name##CompilerRef::copy(const BearShader##name##CompilerRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::BearShader##name##CompilerRef::swap(BearShader##name##CompilerRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::BearShader##name##CompilerRef::BearShader##name##CompilerRef(const BearShader##name##CompilerRef & right)\
{\
	copy(right);\
	\
}\
\
BearGraphics::BearShader##name##CompilerRef & BearGraphics::BearShader##name##CompilerRef::operator=(const BearShader##name##CompilerRef & right)\
{\
	copy(right);\
	return *this;\
}\
BearGraphics::BearShader##name##CompilerRef::data::data()\
{\
	shader_compiler = RHIFactoty->create##name##ShaderCompiler();\
}\
BearGraphics::BearShader##name##CompilerRef::data::~data()\
{\
	RHIFactoty->destroy##name##ShaderCompiler(shader_compiler);\
}\
BearGraphics::Bear##name##ShaderRef::Bear##name##ShaderRef()\
{\
}\
\
BearGraphics::Bear##name##ShaderRef::~Bear##name##ShaderRef()\
{\
	clear();\
}\
\
bool BearGraphics::Bear##name##ShaderRef::compileText(const bchar * text, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef compiler;\
	if (!compiler.compileText(text, out_error))\
		return false;\
	return loadFromCompiler(compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::compileFromFile(const bchar * file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef compiler;\
	if (!compiler.compileFromFile(file,coding, out_error))\
		return false;\
	return loadFromCompiler(compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::compileFromInput(BearCore::BearInputStream & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef compiler;\
	if (!compiler.compileFromInput(stream, coding, out_error))\
		return false;\
	return loadFromCompiler(compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::compileFromBuffer(BearCore::BearBufferedReader & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef compiler;\
	if (!compiler.compileFromBuffer(stream, coding, out_error))\
		return false;\
	return loadFromCompiler(compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::loadFromFile(const bchar * file)\
{\
	BearCore::BearFileStream stream;\
	if(!stream.open(file))\
	return false;\
	return loadFromInput(stream);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::loadFromCompiler(const BearShader##name##CompilerRef & compiler)\
{\
	BearCore::BearMemoryTranslationStream str((void*)compiler.begin(),(uint8*)compiler.end()-(uint8*)compiler.begin());\
	return loadFromBuffer(str);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::loadFromInput(BearCore::BearInputStream & stream)\
{\
	BearCore::BearMemoryTranslationStream str(stream);\
	return loadFromBuffer(str);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::loadFromBuffer(BearCore::BearBufferedReader & stream)\
{\
	clear();\
	if (!RHIFactoty)return false;\
	m_data.create();\
	m_data.get()->shader = RHIFactoty->create##name##Shader(stream.begin(), (uint8*)stream.end() - (uint8*)stream.begin());\
	if (!m_data.get()->shader)\
	{\
		clear();\
		return false;\
	}\
	return true;\
}\
\
bool BearGraphics::Bear##name##ShaderRef::empty() const\
{\
	return m_data.empty();\
}\
\
void BearGraphics::Bear##name##ShaderRef::clear()\
{\
	m_data.clear();\
}\
\
void BearGraphics::Bear##name##ShaderRef::copy(const Bear##name##ShaderRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::Bear##name##ShaderRef::swap(Bear##name##ShaderRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::Bear##name##ShaderRef::Bear##name##ShaderRef(const Bear##name##ShaderRef & right)\
{\
	copy(right);\
}\
\
BearGraphics::Bear##name##ShaderRef & BearGraphics::Bear##name##ShaderRef::operator=(const Bear##name##ShaderRef & right)\
{\
	copy(right);\
	return*this;\
}\
BearGraphics::Bear##name##ShaderRef::data::data()\
{\
	shader= 0;\
}\
BearGraphics::Bear##name##ShaderRef::data::~data()\
{\
if(shader)\
	RHIFactoty->destroy##name##Shader(shader);\
}


CREATE_SHADER_CLASS(Pixel);
CREATE_SHADER_CLASS(Vertex);