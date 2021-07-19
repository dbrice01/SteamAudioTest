// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class STEAMAUDIOTEST_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	void ScaleModeStart();
	void ScaleModeStop();
	void BoomboxModeStart();
	void BoomboxModeStop();
	void XAxisStart();
	void XAxisStop();
	void YAxisStart();
	void YAxisStop();
	void ZAxisStart();
	void ZAxisStop();

	UPROPERTY(EditAnywhere);
	TSoftObjectPtr<AActor> Chamber;

	UPROPERTY(EditAnywhere);
	TSoftObjectPtr<AActor> Boombox;



private:
	FVector MovementDirection;

	UPROPERTY(EditAnywhere);
	float MovementSpeed = 600.0f;

	UPROPERTY(EditAnywhere);
	float ScaleSpeed= 0.03f;

	UPROPERTY(EditAnywhere);
	float BoomboxSpeed = 10.0f;

	UPROPERTY(EditAnywhere);
	float Pitch = 0.0f;

	UPROPERTY(EditAnywhere);
	float Yaw = 0.0f;
	

	bool isScaleMode = false;
	bool isBoomboxMode = false;
	bool isXAxis = false;
	bool isYAxis = false;
	bool isZAxis = false;
};
