#pragma once
class BEARGRAPHICS_API BearTopLevelDescription
{
public:
	BearTopLevelDescription() {}
	inline ~BearTopLevelDescription() {}
	BearTopLevelDescription(const BearTopLevelDescription& Right) { Copy(Right); }
	BearTopLevelDescription(BearTopLevelDescription&& Right) { Swap(Right); }
	inline void Copy(const BearTopLevelDescription& Right)
	{
		InstanceDescriptions.copy(Right.InstanceDescriptions);
		BuildFlags.copy(Right.BuildFlags);
	}
	inline void Swap(BearTopLevelDescription& Right)
	{
		InstanceDescriptions.swap(Right.InstanceDescriptions);
		BuildFlags.swap(Right.BuildFlags);
	}
	inline BearTopLevelDescription& operator=(const BearTopLevelDescription& Right) { Copy(Right); return*this; }
	inline BearTopLevelDescription& operator=(BearTopLevelDescription&& Right) { Swap(Right); return*this; }
	struct InstanceDescription
	{
		InstanceDescription()
		{
			Transform3x4.BuildIdentity();
			InstanceMask = 1;
			InstanceID = 0;
			InstanceContributionToHitGroupIndex = 0;
			Flags = 0;
		}
		BearMatrix			Transform3x4;
		uint32				InstanceID : 24;
		uint8				InstanceMask;
		uint32				InstanceContributionToHitGroupIndex : 24;
		BearFlags<uint8>	Flags;
		BearFactoryPointer<BearRHI::BearRHIBottomLevel> BottomLevel;
	};
	BearVector<InstanceDescription> InstanceDescriptions;
	BearFlags<uint32>  BuildFlags;

};