#include "System/ParuRailAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "Character/ParuRailPawnData.h"
#include "ParuRailGameplayTags.h"

UParuRailAssetManager& UParuRailAssetManager::Get()
{
	check(GEngine)
	UParuRailAssetManager* AuraAssetManager = Cast<UParuRailAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

const UParuRailPawnData* UParuRailAssetManager::GetDefaultPawnData() const
{
	return GetAsset(DefaultPawnData);
}

void UParuRailAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}

UObject* UParuRailAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		if (ShouldLogAssetLoads())
		{
			TUniquePtr<FScopeLogTime> LogTimePtr = MakeUnique<FScopeLogTime>(
				*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr,
				FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// Use LoadObject if asset manager isn't ready yet.
		return AssetPath.TryLoad();
	}

	return nullptr;
}

bool UParuRailAssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

void UParuRailAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FParuRailGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
