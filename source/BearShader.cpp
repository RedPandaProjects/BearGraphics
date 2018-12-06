#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
#define CREATE_SHADER_CLASS(name) \
BearGraphics::BearShader##name##CompilerRef::BearShader##name##CompilerRef()\
{\
}\
\
BearGraphics::BearShader##name##CompilerRef::~BearShader##name##CompilerRef()\
{\
	Clear();\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::CompileText(const bchar * text, BearCore::BearString & out_error)\
{\
	Clear();\
	if (!RHIFactoty)return false;\
	if (!m_data.get()->shader_compiler)\
	{\
		Clear();\
		return false;\
	}\
	return m_data.get()->shader_compiler->CompileFromText(text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::CompileFromFile(const bchar * file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearFileStream stream;\
	if (!stream.Open(file))\
		return false;\
	BearCore::BearString text;\
	stream.ToString(text, coding);\
	return CompileText(*text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::CompileFromStream(BearCore::BearInputStream & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearString text;\
	stream.ToString(text, coding);\
	return CompileText(*text, out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::CompileFromBuffer(BearCore::BearBufferedReader & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearCore::BearString text;\
	stream.ToString(text, coding);\
	return CompileText(*text,out_error);\
}\
\
bool BearGraphics::BearShader##name##CompilerRef::SaveToFile(const bchar * file)\
{\
	if (Empty())return false;\
	BearCore::BearFileStream stream;\
	if (!stream.Open(file,stream.M_Write))\
		return false;\
	return stream.Write(m_data.get()->shader_compiler->GetPointerBuffer(), m_data.get()->shader_compiler->GetSizeBuffer())== m_data.get()->shader_compiler->GetSizeBuffer();\
}\
\
void * BearGraphics::BearShader##name##CompilerRef::Begin()\
{\
	if (Empty())return 0;\
	return m_data.get()->shader_compiler->GetPointerBuffer();\
}\
\
void * BearGraphics::BearShader##name##CompilerRef::End()\
{\
	if (Empty())return 0;\
	return  (uint8*) m_data.get()->shader_compiler->GetPointerBuffer()+m_data.get()->shader_compiler->GetSizeBuffer();\
}\
\
const void * BearGraphics::BearShader##name##CompilerRef::Begin() const\
{\
	if (Empty())return 0;\
	return m_data.get()->shader_compiler->GetPointerBuffer();\
}\
\
const void * BearGraphics::BearShader##name##CompilerRef::End() const\
{\
	if (Empty())return 0;\
	return  (uint8*)m_data.get()->shader_compiler->GetPointerBuffer() + m_data.get()->shader_compiler->GetSizeBuffer();\
}\
\
bsize BearGraphics::BearShader##name##CompilerRef::GetSize() const\
{\
	return  m_data.get()->shader_compiler->GetSizeBuffer();\
}\
\
void BearGraphics::BearShader##name##CompilerRef::Clear()\
{\
	m_data.clear();\
}\
\
void BearGraphics::BearShader##name##CompilerRef::Copy(const BearShader##name##CompilerRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::BearShader##name##CompilerRef::Swap(BearShader##name##CompilerRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::BearShader##name##CompilerRef::BearShader##name##CompilerRef(const BearShader##name##CompilerRef & right)\
{\
	Copy(right);\
	\
}\
\
BearGraphics::BearShader##name##CompilerRef & BearGraphics::BearShader##name##CompilerRef::operator=(const BearShader##name##CompilerRef & right)\
{\
	Copy(right);\
	return *this;\
}\
BearGraphics::BearShader##name##CompilerRef::data::data()\
{\
	shader_compiler = RHIFactoty->Create##name##ShaderCompiler();\
}\
BearGraphics::BearShader##name##CompilerRef::data::~data()\
{\
	RHIFactoty->Destroy##name##ShaderCompiler(shader_compiler);\
}\
BearGraphics::Bear##name##ShaderRef::Bear##name##ShaderRef()\
{\
}\
\
BearGraphics::Bear##name##ShaderRef::~Bear##name##ShaderRef()\
{\
	Clear();\
}\
\
bool BearGraphics::Bear##name##ShaderRef::CompileText(const bchar * text, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef Compiler;\
	if (!Compiler.CompileText(text, out_error))\
		return false;\
	return LoadFromCompiler(Compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::CompileFromFile(const bchar * file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef Compiler;\
	if (!Compiler.CompileFromFile(file,coding, out_error))\
		return false;\
	return LoadFromCompiler(Compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::CompileFromStream(BearCore::BearInputStream & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef Compiler;\
	if (!Compiler.CompileFromStream(stream, coding, out_error))\
		return false;\
	return LoadFromCompiler(Compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::CompileFromBuffer(BearCore::BearBufferedReader & stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString & out_error)\
{\
	BearShader##name##CompilerRef Compiler;\
	if (!Compiler.CompileFromBuffer(stream, coding, out_error))\
		return false;\
	return LoadFromCompiler(Compiler);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::LoadFromFile(const bchar * file)\
{\
	BearCore::BearFileStream stream;\
	if(!stream.Open(file))\
	return false;\
	return LoadFromStream(stream);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::LoadFromCompiler(const BearShader##name##CompilerRef & Compiler)\
{\
	BearCore::BearMemoryTranslationStream str((void*)Compiler.Begin(),(uint8*)Compiler.End()-(uint8*)Compiler.Begin());\
	return LoadFromBuffer(str);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::LoadFromStream(BearCore::BearInputStream & stream)\
{\
	BearCore::BearMemoryTranslationStream str(stream);\
	return LoadFromBuffer(str);\
}\
\
bool BearGraphics::Bear##name##ShaderRef::LoadFromBuffer(BearCore::BearBufferedReader & stream)\
{\
	Clear();\
	if (!RHIFactoty)return false;\
	m_data.create();\
	m_data.get()->shader = RHIFactoty->Create##name##Shader(stream.Begin(), (uint8*)stream.End() - (uint8*)stream.Begin());\
	if (!m_data.get()->shader)\
	{\
		Clear();\
		return false;\
	}\
	return true;\
}\
\
void BearGraphics::Bear##name##ShaderRef::Clear()\
{\
	m_data.clear();\
}\
\
void BearGraphics::Bear##name##ShaderRef::Copy(const Bear##name##ShaderRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::Bear##name##ShaderRef::Swap(Bear##name##ShaderRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::Bear##name##ShaderRef::Bear##name##ShaderRef(const Bear##name##ShaderRef & right)\
{\
	Copy(right);\
}\
\
BearGraphics::Bear##name##ShaderRef & BearGraphics::Bear##name##ShaderRef::operator=(const Bear##name##ShaderRef & right)\
{\
	Copy(right);\
	return*this;\
}\
BearGraphics::Bear##name##ShaderRef::data::data()\
{\
	shader= 0;\
}\
BearGraphics::Bear##name##ShaderRef::data::~data()\
{\
if(shader)\
	RHIFactoty->Destroy##name##Shader(shader);\
}


CREATE_SHADER_CLASS(Pixel);
CREATE_SHADER_CLASS(Vertex);

