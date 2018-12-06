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
		bool CompileText(const bchar*text, BearCore::BearString&out_error);\
		bool CompileFromFile(const bchar*file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool CompileFromStream(BearCore::BearInputStream&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool CompileFromBuffer(BearCore::BearBufferedReader&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		\
		bool SaveToFile(const bchar*file);\
		\
		void*Begin();\
		void*End();\
		const void*Begin()const;\
		const void*End()const;\
		bsize GetSize()const;\
		\
		inline bool Empty()const { return m_data.empty(); }\
	   inline bool IsOne()const { return m_data.is_one(); }\
		\
		void Clear();\
		\
		void Copy(const BearShader##name##CompilerRef&right);\
		void Swap(BearShader##name##CompilerRef&right);\
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
		bool CompileText(const bchar*text, BearCore::BearString&out_error);\
		bool CompileFromFile(const bchar*file, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool CompileFromStream(BearCore::BearInputStream&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool CompileFromBuffer(BearCore::BearBufferedReader&stream, BearCore:: BearEncoding::Encoding  coding, BearCore::BearString&out_error);\
		bool LoadFromFile(const bchar*file);\
		bool LoadFromCompiler(const BearShader##name##CompilerRef&compiler);\
		bool LoadFromStream(BearCore::BearInputStream&stream);\
		bool LoadFromBuffer(BearCore::BearBufferedReader&stream);\
		inline bool Empty()const { return m_data.empty(); }\
	   inline bool IsOne()const { return m_data.is_one(); }\
		\
		void Clear();\
		\
		void Copy(const Bear##name##ShaderRef&right);\
		void Swap(Bear##name##ShaderRef&right);\
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