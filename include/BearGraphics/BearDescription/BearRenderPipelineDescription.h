#pragma once 
namespace BearGraphics
{

	struct BearInputLayoutElement
	{
		BearInputLayoutElement(const char*Name, BearVertexFormat Type, bsize Offset, bool IsInstance = false) :Name(Name), Type(Type), Offset(Offset), IsInstance(IsInstance), SemanticIndex(0) {}
		BearInputLayoutElement() :Type(VF_NONE), Offset(0), IsInstance(0), SemanticIndex(0) {}
		BearVertexFormat Type;
		BearCore::BearStringConteniarAnsi Name;
		bsize Offset;
		bsize SemanticIndex;
		bool IsInstance;
		inline bool operator ==(const BearInputLayoutElement&Right)const
		{
			return	Type == Right.Type&&
				Offset == Right.Offset&&
				SemanticIndex == Right.SemanticIndex&&
				IsInstance == Right.IsInstance&&
				Name == Right.Name;

		}
		inline bool operator <(const BearInputLayoutElement&Right)const
		{
			if (Type == Right.Type)
			{
				if (Offset == Right.Offset)
				{
					if (SemanticIndex == Right.SemanticIndex)
					{
						if (IsInstance == Right.IsInstance)
						{
							return Name < Right.Name;
						}
						else
						{
							return IsInstance < Right.IsInstance;
						}
					}
					else
					{
						return SemanticIndex < Right.SemanticIndex;
					}
				}
				else
				{
					return Offset < Right.Offset;
				}
			}
			else
			{
				return Type < Right.Type;
			}

		}
	};
	class BEARGRAPHICS_API BearRenderPipelineDescription
	{
	public:
		BearRenderPipelineDescription();
		BearRenderPipelineDescription(const BearRenderPipelineDescription&Right);
		BearRenderPipelineDescription(BearRenderPipelineDescription&&Right);
		inline ~BearRenderPipelineDescription() {}
		

		bool operator<(const BearRenderPipelineDescription&Right) const;
		bool operator ==(const BearRenderPipelineDescription&Right)const;
		void Copy(const BearRenderPipelineDescription&Right);
		void Swap(BearRenderPipelineDescription&Right);
		inline BearRenderPipelineDescription&operator=(const BearRenderPipelineDescription&Right) {			Copy(Right); return*this;		}
		inline BearRenderPipelineDescription&operator=(BearRenderPipelineDescription&&Right) { Swap(Right); return*this; }
		struct
		{
			BearInputLayoutElement Elements[16];

		} InputLayout;

		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Pixel;
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Vertex;
		}Shaders;
	
		struct
		{
			BearRenderTargetFormat Formats[8];
			
		} RenderTargets;

		void ResetCheakSum();
	private:
		uint32 m_CRC32;
		
	};
}
