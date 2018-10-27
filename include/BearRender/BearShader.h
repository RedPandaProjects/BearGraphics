#pragma once 


namespace BearGraphics
{
#define CREATE_SHADER_CLASS(name) \
	class BEARGRAPHICS_API BearShader##name##CompilerRef\
	{\
	public:\
	friend class Bear##name##ShaderRef;\
		BearShader##name##CompilerRef();\
		~BearShader##name##CompilerRef();\
		\
		bool compileText(const bchar*text, BearCore::BearString&out_error);\
		bool compileFromFile(const bchar*file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool compileFromInput(BearCore::BearInputStream&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool compileFromBuffer(BearCore::BearBufferedReader&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		\
		bool saveToFile(const bchar*file);\
		\
		void*begin();\
		void*end();\
		const void*begin()const;\
		const void*end()const;\
		bsize getSize()const;\
		\
		bool empty()const;\
		\
		void clear();\
		\
		void copy(const BearShader##name##CompilerRef&right);\
		void swap(BearShader##name##CompilerRef&right);\
		BearShader##name##CompilerRef(const BearShader##name##CompilerRef&right);\
		BearShader##name##CompilerRef&operator=(const BearShader##name##CompilerRef&right);\
		\
	private:\
		struct data\
		{\
			data();\
			~data();\
			BearRHI::BearRHI##name##ShaderCompiler*shader_compiler;\
		};\
		BearCore::BearMemoryMultiRef<data> m_data;\
	};\
	\
	class BEARGRAPHICS_API Bear##name##ShaderRef\
	{\
	public:\
	friend class BearRenderInterface;\
		Bear##name##ShaderRef();\
		~Bear##name##ShaderRef();\
		\
		bool compileText(const bchar*text, BearCore::BearString&out_error);\
		bool compileFromFile(const bchar*file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool compileFromInput(BearCore::BearInputStream&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool compileFromBuffer(BearCore::BearBufferedReader&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool loadFromFile(const bchar*file);\
		bool loadFromCompiler(const BearShader##name##CompilerRef&compiler);\
		bool loadFromInput(BearCore::BearInputStream&stream);\
		bool loadFromBuffer(BearCore::BearBufferedReader&stream);\
		bool empty()const;\
		\
		void clear();\
		\
		void copy(const Bear##name##ShaderRef&right);\
		void swap(Bear##name##ShaderRef&right);\
		Bear##name##ShaderRef(const Bear##name##ShaderRef&right);\
		Bear##name##ShaderRef&operator=(const Bear##name##ShaderRef&right);\
	private:\
		struct data\
		{\
			data();\
			~data();\
			BearRHI::BearRHI##name##Shader*shader;\
		};\
		BearCore::BearMemoryMultiRef<data> m_data;\
	};
	CREATE_SHADER_CLASS(Vertex)
	CREATE_SHADER_CLASS(Pixel)
#undef CREATE_SHADER_CLASS
}