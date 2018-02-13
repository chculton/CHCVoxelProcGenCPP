// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//PolyVox Includes
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"

#include "AVoxelTerrainActor.generated.h"

UCLASS()
class CHCVOXELPROCGENCPP_API AAVoxelTerrainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	//Sets default Actor properaties
	AAVoxelTerrainActor();

	//Called after constructor initialization
	virtual void PostInitializeComponents() override;

	//Terrain Generation Variables
	//Fractal Seed
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) int32 Seed;

	//The number of octaves for noise generator
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) int32 NoiseOctaves;

	//The noise freq
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseFrequency;

	//The scale of the noise
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseScale;

	//The offset of the noise - added to the output of the TerrainFractal
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseOffset;

	//The maximum height of the generated terrain in voxels(Affects where Terrain generation begins)
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float TerrainHeight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TSharedPtr<PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>> VoxelVolume;
};

class VoxelTerrainPager : public PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Pager
{
public:
	// Constructor
	VoxelTerrainPager(uint32 NoiseSeed = 123, uint32 Octaves = 3, float Frequency = 0.01, float Scale = 32, float Offset = 0, float Height = 64);

	// Destructor
	virtual ~VoxelTerrainPager() {};

	// PagedVolume::Pager functions
	virtual void pageIn(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);
	virtual void pageOut(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);

private: //Terrain Generation Variables
	//Fractal Seed
	uint32 Seed = 123;

	//The number of octaves for noise generator
	uint32 NoiseOctaves = 3;

	//The noise freq
	float NoiseFrequency = 0.01;

	//The scale of the noise TerrainFractal is multiplied by NoiseScale
	float NoiseScale = 32;

	//The offset of the noise - added to the output of the TerrainFractal
	float NoiseOffset = 0;

	//The maximum height of the generated terrain in voxels(Affects where Terrain generation begins)
	float TerrainHeight = 64;
};
